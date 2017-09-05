#include "expression.hpp"
#include <tuple>
#include <limits>
#include <cmath>

Expression::Expression()
{
	type = None;
	
}

Expression::Expression(bool value) 
{
	type = Boolean;
	s.bVal = value;

}

Expression::Expression(double value) 
{
	type = Number;
	s.dVal = value;
}

Expression::Expression(const std::string value)
{
	type = Symbol;
	s.sVal = value;
}

//point
Expression::Expression(std::tuple<double, double> value)
{
	type = Point;
	s.ptVal = value;
	
}

//line
Expression::Expression(std::tuple<double, double> start, std::tuple<double, double> end)
{
	type = Line;
	s.linStrtVal = start;
	s.linEndVal = end;
}

//arc
Expression::Expression(std::tuple<double, double> center, std::tuple<double, double> start, double angle)
{
	type = Arc;
	
	s.arcCntrVal = center;
	s.arcStrtVal = start;
	s.arcAnglVal = angle;

}

bool Expression::operator==(const Expression & exp) const noexcept
{
	if (type != exp.type) {
		return false;
	}

	if (this->getNumArgs() != exp.getNumArgs()) {
		return false;
	}

	if (type == Boolean){
		return(s.bVal == exp.s.bVal);
	}
	if (type == Number){
		return std::abs(s.dVal - exp.s.dVal) < std::numeric_limits<double>::epsilon();
	}
	if (type == Symbol){
		return(s.sVal == exp.s.sVal);
	}
	return true;
}


std::string Expression::getType() const
{
	switch (type)
	{
	case Boolean:
		return "Boolean";
		break;
	case Number:
		return "Number";
		break;
	case Symbol:
		return "Symbol";
		break;
	case Point:
		return "Point";
		break;
	case Line:
		return "Line";
		break;
	case Arc:
		return "Arc";
		break;
	}
	return "None";
}

bool Expression::getBoolValue() const
{
	return s.bVal;
}

double Expression::getDoubleValue() const
{
	return s.dVal;
}

std::string Expression::getSymbolValue() const
{
	return s.sVal;
}

std::tuple<double, double> Expression::getPtVal() const
{
	return s.ptVal;
}

std::tuple<double, double> Expression::getLinStrtVal() const
{
	return s.linStrtVal;
}

std::tuple<double, double> Expression::getLinEndVal() const
{
	return s.linEndVal;
}

std::tuple<double, double> Expression::getArcCntrVal() const
{
	return s.arcCntrVal;
}

std::tuple<double, double> Expression::getArcStrtVal() const
{
	return s.arcStrtVal;
}

double Expression::getArcAnglVal() const
{
	return s.arcAnglVal;
}

int Expression::getNumArgs() const
{
	return children.size();
}