#include "environment.hpp"
#include <cmath>

Environment::Environment()
{
	procedureMap.insert(std::pair<std::string, functPtr>("not", logicNot));
	procedureMap.insert(std::pair<std::string, functPtr>("and", logicAnd));
	procedureMap.insert(std::pair<std::string, functPtr>("or", logicOr));
	procedureMap.insert(std::pair<std::string, functPtr>("<", lessThan));
	procedureMap.insert(std::pair<std::string, functPtr>("<=", lessThanEq));
	procedureMap.insert(std::pair<std::string, functPtr>(">", greatThan));
	procedureMap.insert(std::pair<std::string, functPtr>(">=", greatThanEq));
	procedureMap.insert(std::pair<std::string, functPtr>("=", eq));
	procedureMap.insert(std::pair<std::string, functPtr>("+", plus));
	procedureMap.insert(std::pair<std::string, functPtr>("-", minus));
	procedureMap.insert(std::pair<std::string, functPtr>("*", times));
	procedureMap.insert(std::pair<std::string, functPtr>("/", divide));
	procedureMap.insert(std::pair<std::string, functPtr>("sin", sinPt));
	procedureMap.insert(std::pair<std::string, functPtr>("cos", cosPt));
	procedureMap.insert(std::pair<std::string, functPtr>("arctan", arctanPt));
	procedureMap.insert(std::pair<std::string, functPtr>("point", pointPt));
	procedureMap.insert(std::pair<std::string, functPtr>("line", linePt));
	procedureMap.insert(std::pair<std::string, functPtr>("arc", arcPt));

	symbolMap.insert(std::pair<std::string, Expression>("pi", Expression(atan2(0, -1))));

}

Expression notFunct(Expression exp)
{
	if (exp.children.size() != 1)
		throw InterpreterSemanticError("\nError: not only takes 1 argument");
	bool b;
	Expression temp = exp.children[0];
	b = !(temp.getBoolValue());
	return Expression(b);
}

Expression andFunct(Expression exp)
{
	if (exp.children.empty())
		throw InterpreterSemanticError("\nError: procedure does not take 0 arguments");
	bool b;
	for (unsigned int i = 0; i < exp.children.size(); ++i)
	{
		if (!exp.children[i].getBoolValue())
		{
			b = false;
			return Expression(b);
		}
	}
	b = true;
	return Expression(b);
}

Expression orFunct(Expression exp)
{
	if (exp.children.empty())
		throw InterpreterSemanticError("\nError: procedure does not take 0 arguments");
	bool b;
	for (unsigned int i = 0; i < exp.children.size(); ++i)
	{
		if (exp.children[i].getBoolValue())
		{
			b = true;
			return Expression(b);
		}
	}
	b = false;
	return Expression(b);
}

Expression lessThanFunct(Expression exp)
{
	if (exp.children.size() != 2)
		throw InterpreterSemanticError("\nError: < only takes 2 arguments");
	bool b;
	b = (exp.children[0].getDoubleValue() < exp.children[1].getDoubleValue());
	return Expression(b);
}

Expression lessThanEqFunct(Expression exp)
{
	if (exp.children.size() != 2)
		throw InterpreterSemanticError("\nError: <= only takes 2 arguments");
	bool b;
	b = (exp.children[0].getDoubleValue() <= exp.children[1].getDoubleValue());
	return Expression(b);
}

Expression greatThanFunct(Expression exp)
{
	if (exp.children.size() != 2)
		throw InterpreterSemanticError("\nError: > only takes 2 arguments");
	bool b;
	b = (exp.children[0].getDoubleValue() > exp.children[1].getDoubleValue());
	return Expression(b);
}

Expression greatThanEqFunct(Expression exp)
{
	if (exp.children.size() != 2)
		throw InterpreterSemanticError("\nError: >= only takes 2 arguments");
	bool b;
	b = (exp.children[0].getDoubleValue() >= exp.children[1].getDoubleValue());
	return Expression(b);
}

Expression eqFunct(Expression exp)
{
	if (exp.children.size() != 2)
		throw InterpreterSemanticError("\nError: = only takes 2 arguments");
	bool b;
	double diff = exp.children[0].getDoubleValue() - exp.children[1].getDoubleValue();
	b = (fabs(diff) < 0.000001);
	return Expression(b);
}

Expression plusFunct(Expression exp)
{
	if (exp.children.empty())
		throw InterpreterSemanticError("\nError: procedure does not take 0 arguments");
	double sum = 0;
	for (unsigned int i = 0; i < exp.children.size(); ++i)
		sum = sum + exp.children[i].getDoubleValue();
	return Expression(sum);
}

Expression minusFunct(Expression exp)
{
	if (exp.children.size() != 1 && exp.children.size() != 2)
		throw InterpreterSemanticError("\nError: - only takes 1 or 2 arguments");
	double result;
	if (exp.children.size() == 1)
		result = -(exp.children[0].getDoubleValue());
	else
		result = (exp.children[0].getDoubleValue() - exp.children[1].getDoubleValue());
	return Expression(result);
}

Expression timesFunct(Expression exp)
{
	if (exp.children.empty())
		throw InterpreterSemanticError("\nError: procedure does not take 0 arguments");
	double product = 1;
	for (unsigned int i = 0; i < exp.children.size(); ++i)
		product = product * exp.children[i].getDoubleValue();
	return Expression(product);
}

Expression divideFunct(Expression exp)
{
	if (exp.children.size() != 2)
		throw InterpreterSemanticError("\nError: / only takes 2 arguments");
	double result, lchild, rchild;
	lchild = exp.children[0].getDoubleValue();
	rchild = exp.children[1].getDoubleValue();
	result = lchild / rchild;
	return Expression(result);
}

Expression sinFunct(Expression exp)
{
	if (exp.getNumArgs() != 1)
		throw InterpreterSemanticError("Error: only 1 arg. allowed");
	if (exp.children.front().getType() != "Number")
		throw InterpreterSemanticError("Error: Not a number");
	double arg = exp.children[0].getDoubleValue();
	double result = sin(arg);
	return Expression(result);
}

Expression cosFunct(Expression exp)
{
	if (exp.getNumArgs() != 1)
		throw InterpreterSemanticError("Error: only 1 arg. allowed");
	if (exp.children.front().getType() != "Number")
		throw InterpreterSemanticError("Error: Not a number");
	double arg = exp.children[0].getDoubleValue();
	double result = cos(arg);
	return Expression(result);
}

Expression arctanFunct(Expression exp)
{
	if (exp.getNumArgs() != 2)
		throw InterpreterSemanticError("Error: only 2 arg. allowed");
	if (exp.children[0].getType() != "Number")
		throw InterpreterSemanticError("Error: Not a number");
	if (exp.children[1].getType() != "Number")
		throw InterpreterSemanticError("Error: Not a number");
	double argy = exp.children[0].getDoubleValue();
	double argx = exp.children[1].getDoubleValue();
	double result = atan2(argy, argx);
	return Expression(result);

}

Expression pointFunct(Expression exp)
{
	double x, y;
	x = exp.children[0].getDoubleValue();
	y = exp.children[1].getDoubleValue();
	std::tuple<double, double> pt(x, y);
	return Expression(pt);
}

Expression lineFunct(Expression exp)
{
	std::tuple<double, double> start = exp.children[0].getPtVal();
	std::tuple<double, double> end = exp.children[1].getPtVal();

	return Expression(start, end);
}

Expression arcFunct(Expression exp)
{
	std::tuple<double, double> center = exp.children[0].getPtVal();
	std::tuple<double, double> start = exp.children[1].getPtVal();
	
	double angle = exp.children[2].getDoubleValue();

	return Expression(center, start, angle);
}