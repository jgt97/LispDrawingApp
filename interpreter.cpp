#include <sstream>
#include <tuple>

#include <iostream>

#include "interpreter.hpp"

Interpreter::Interpreter()
{
	
}

bool Interpreter::parse(std::istream & expression) noexcept
{
	if (!expression.good()) {
		return false;
	}
	
	if (!tokenizer.parse(expression)) {
		return false;
	}
	return(tokenizer.buildAST());
}


Expression Interpreter::eval()
{
	return evaluate(tokenizer.getSyntaxTree());;
}

Expression Interpreter::evaluateDefine(const Expression& tree)
{
	if (tree.children.size() != 2) {
		throw InterpreterSemanticError("Error: define takes 2 arguments");
	}
	std::string symbol = tree.children.front().getSymbolValue();
	if (symbol == "if" || symbol == "define" || symbol == "begin") {
		throw InterpreterSemanticError("Error: attempted redefinition of special form");
	}
	if (symbol == "pi") {
		throw InterpreterSemanticError("Error: attempted redefinition of pi");
	}
	Expression exp(evaluate(tree.children.back()));
	defaultEnviron.symbolMap.insert(std::pair<std::string, Expression>(symbol, exp));
	return exp;
}

Expression Interpreter::evaluateBegin(const Expression& tree)
{
	Expression ret;
	for (unsigned int i = 0; i < tree.children.size(); ++i) {
		if (i == tree.children.size() - 1) {
			ret = evaluate(tree.children[i]);
		}
		else {
			evaluate(tree.children[i]);
		}
	}
	return ret;
}

Expression Interpreter::evaluateIf(const Expression& tree)
{
	if (tree.children.size() != 3) {
		throw InterpreterSemanticError("Error: if needs 3 arguments");
	}
	bool b;
	Expression exp;
	exp = evaluate(tree.children[0]);
	b = exp.getBoolValue();
	if (b) {
		return evaluate(tree.children[1]);
	}
	else {
		return evaluate(tree.children[2]);
	}
}

Expression Interpreter::evaluate(const Expression& tree)
{
	if (tree.getType() == "Symbol"){
		std::string token = tree.getSymbolValue();
		if (defaultEnviron.symbolMap.find(token) != defaultEnviron.symbolMap.end()) {
			return defaultEnviron.symbolMap.at(token);
		}
		else if (token == "define"){
			return evaluateDefine(tree);
		}
		else if (token == "begin"){
			return evaluateBegin(tree);
		}
		else if (token == "if"){
			return evaluateIf(tree);
		}
		else if (token == "draw"){
			if (tree.children.size() == 0) {
				throw InterpreterSemanticError("Error: draw needs an argument");
			}
			for (unsigned int i = 0; i < tree.children.size(); ++i) {
				Expression item(evaluate(tree.children[i]));
				graphicContainer.push_back(item);
			}
			return Expression();
		}
		else{
			std::vector<Expression> evalArgs;
			for (unsigned int i = 0; i < tree.children.size(); ++i){
				Expression exp = evaluate(tree.children[i]);
				evalArgs.push_back(exp);
			}
			Expression temp(token);
			temp.children = evalArgs;
			if (temp.children.size() == 0) {
				throw InterpreterSemanticError("Error: unknown symbol");
			}
			try { 
				defaultEnviron.procedureMap[token](temp);
			}
			catch (InterpreterSemanticError){
				throw InterpreterSemanticError("Error: evaluation error");
			}
			if (defaultEnviron.procedureMap.find(token) == defaultEnviron.procedureMap.end()) {
				throw InterpreterSemanticError("Error: procedure not found");
			}
			return defaultEnviron.procedureMap[token](temp);
		}
	}
	else {
		return tree;
	}
}

std::string Interpreter::outputExp(const Expression& expres)
{
	std::stringstream result;
	if (expres.getType() == "Boolean")
	{
		if (expres.getBoolValue()) {
			result << "(True)";
		}
		else {
			result << "(False)";
		}
	}
	else if (expres.getType() == "Number") {
		result << '(' << expres.getDoubleValue() << ')';
	}
	else if (expres.getType() == "Symbol") {
		result << '(' << expres.getSymbolValue() << ')';
	}
	else if (expres.getType() == "Point") {
		double x = std::get<0>(expres.getPtVal());
		double y = std::get<1>(expres.getPtVal());
		result << '(' << x << ',' << y << ')';
	}
	else if (expres.getType() == "Line") {
		double x1 = std::get<0>(expres.getLinStrtVal());
		double y1 = std::get<1>(expres.getLinStrtVal());
		double x2 = std::get<0>(expres.getLinEndVal());
		double y2 = std::get<1>(expres.getLinEndVal());
		result << '(' << '(' << x1 << ',' << y1 << ')' << '(' << x2 << ',' << y2 << ')' << ')';
	}
	else if (expres.getType() == "Arc") {
		double x1 = std::get<0>(expres.getArcCntrVal());
		double y1 = std::get<1>(expres.getArcCntrVal());
		double x2 = std::get<0>(expres.getArcStrtVal());
		double y2 = std::get<1>(expres.getArcStrtVal());
		double angle = expres.getArcAnglVal();
		result << '(' << '(' << x1 << ',' << y1 << ')' << '(' << x2 << ',' << y2 << ") " << angle << ')';
	}
	return result.str();
}

bool Interpreter::hasDraw()
{
	return (graphicContainer.size() != 0);
}

std::vector<Expression> Interpreter::getGraphicContainer()
{
	return graphicContainer;
}