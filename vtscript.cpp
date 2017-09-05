#include <iostream>
#include <fstream>
#include <sstream>

#include "interpreter.hpp"
#include "expression.hpp"

void repl();
void inputFile(char* argv[]);
void immediateScipt(char* argv[]);


int main(int argc, char * argv[])
{
	if (argc == 1){
		repl();
	}
	else if (argc == 2 && argv[2] != "-e"){
		inputFile(argv);
	}
	else{
		immediateScipt(argv);
	}
	std::exit(EXIT_SUCCESS);
	return 0;
}

void repl()
{
	std::string program;

	Interpreter repl;

	std::cout << "vtscript> ";
	getline(std::cin, program);
	while (!std::cin.eof())
	{
		std::istringstream iss(program);
		if (!repl.parse(iss))
			std::cerr << "Error: parse error" << std::endl;
		else
		{
			Expression result;
			try {
				result = repl.eval();
			}
			catch (const InterpreterSemanticError ex)
			{
				std::cerr << ex.what();
			}
			std::string outStr = repl.outputExp(result);
			std::cout << outStr;
		}
		std::cout << "\nvtscript> ";
		getline(std::cin, program);
	}
}

void inputFile(char* argv[])
{
	std::string fileName;
	fileName = argv[1];
	std::ifstream ifs(fileName);
	Interpreter interp;
	if (!interp.parse(ifs))
	{
		std::cerr << "Error: parse error" << std::endl;
		std::exit(EXIT_FAILURE);
	}
	Expression exp;
	try {
		exp = interp.eval();
	}
	catch (const InterpreterSemanticError ex)
	{
		std::cerr << ex.what();
		std::exit(EXIT_FAILURE);
	}
	std::string outStr = interp.outputExp(exp);
	std::cout << outStr;
}

void immediateScipt(char* argv[])
{
	std::string arg2(argv[1]);
	if (arg2 == "-e")
	{
		std::string program = argv[2];
		std::istringstream iss(program);
		Interpreter interp;
		if (!interp.parse(iss))
		{
			std::cerr << "Error: parse error" << std::endl;
			std::exit(EXIT_FAILURE);
		}
		Expression exp;
		try {
			exp = interp.eval();
		}
		catch (const InterpreterSemanticError ex)
		{
			std::cerr << ex.what();
			std::exit(EXIT_FAILURE);
		}
		std::string outStr = interp.outputExp(exp);
		std::cout << outStr;
	}
}