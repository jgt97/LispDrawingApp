#ifndef EXPRESSION_HPP_
#define EXPRESSION_HPP_

#include <string>
#include <vector>
#include <tuple>


class Expression
{
public:
	enum lispType { None, Boolean, Number, Symbol, Point, Line, Arc };
	std::string originalToken;
	std::vector<Expression> children;
	inline void insert(Expression x)
	{
		children.push_back(x);
	}

	//Default construction of an Expression of type None
	Expression();

	//Construct an Expression with a single Boolean atom with value
	Expression(bool value);

	//Construct an Expression with a single Number atom with value
	Expression(double value);

	//Construct an Expression with a single Symbol atom with value
	Expression(const std::string value);

	//point
	Expression(std::tuple<double, double> value);

	//line
	Expression(std::tuple<double, double> start, std::tuple<double, double> end);

	//arc
	Expression(std::tuple<double, double> center, std::tuple<double, double> start, double angle);

	//Equality operator for two Expressions, two expressions are equal if they have the same
	//type, atom value, and number of arguments
	bool operator==(const Expression  & exp) const noexcept;

	std::string getType() const;

	bool getBoolValue() const;

	double getDoubleValue() const;

	std::string getSymbolValue() const;

	std::tuple<double, double> getPtVal() const;

	std::tuple<double, double> getLinStrtVal() const;
	std::tuple<double, double> getLinEndVal() const;

	std::tuple<double, double> getArcCntrVal() const;
	std::tuple<double, double> getArcStrtVal() const;
	double getArcAnglVal() const;


	int getNumArgs() const;

private:
	
	lispType type;

	
	struct S
	{
		bool bVal;
		double dVal;
		std::string sVal;
		std::tuple<double, double> ptVal;
		std::tuple<double, double> linStrtVal, linEndVal;
		std::tuple<double, double> arcCntrVal, arcStrtVal;
		double arcAnglVal;
	} s;
	

};	



#endif