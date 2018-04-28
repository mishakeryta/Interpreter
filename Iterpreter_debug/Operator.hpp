#ifndef OPERATORS_HPP
#define OPERATORS_HPP

class Operator
{
public:
	
	Operator(char ch,unsigned int numOfOpenScope);
	bool operator <(const Operator& oper)const;
private:
	char oper;
	unsigned int priority;
	
};
#endif

