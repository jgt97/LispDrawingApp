#ifndef INTERPRETER_HPP_
#define INTERPRETER_HPP_

#include "environment.hpp"
#include "tokenize.hpp"
#include "expression.hpp"

class Interpreter
{
private:
	Tokenize tokenizer;
	Environment defaultEnviron;
	Expression evaluate(const Expression& tree);
	std::vector<Expression> graphicContainer;

public:
	//Default construct an Interpreter with the default environment and empty AST
	Interpreter();
	
	//Given a vtscript program as a std::istream, attempt to parse into an internal AST
	//return true on success, false on failure
	bool parse(std::istream & expression ) noexcept;
	
	//Evaluate the current AST and return the resulting Expression
	//throws InterpreterSemanticError if a semantic error is encountered
	//the exception message string should document the nature of the semantic error
	Expression eval();
		
	std::string outputExp(const Expression& expres);

	bool hasDraw();

	std::vector<Expression> getGraphicContainer();

	Expression evaluateDefine(const Expression& tree);

	Expression evaluateBegin(const Expression& tree);

	Expression evaluateIf(const Expression& tree);


};


#endif