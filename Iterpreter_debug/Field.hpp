#ifndef FIELD_HPP
#define FIELD_HPP
#include <map>
#include <stdexcept>
#include <memory>
#include <regex>
#include <iostream>
#include <sstream>
#include <cctype>
#include <stack>

#include "Operator.hpp"
using namespace std;
class Field
{
public:
	string deleteAllBlanks(const string& line) const;
	Field(Field* parent = nullptr);
	void execute(string& line, istream&  ifstream_main);
	int find_int_variable(const string& name);
	void setVariableInt(const string& name, int val);
	
	int calculateExpression(const string& maybe_exp);
	string findExpressionInAssigment(const string& line);
	int convertStrToInt(const string& maybeVariableOrVal);
	int countNumberOfParents() const;
private:
	map<string, int> int_variables;
	Field* parent;
	bool isExpressionSymbol(char symbol);
	bool isStatementFormat(const string& line) const;
	bool isNewVarFormat(const string& line) const;
	bool isAssigmentFormat(const string& line) const;
	string getStatementKey(const string& line) const;
	string getNameOfNewVar(const string& line) const;
	bool isEmptyOrWithAllBlanks(const string& line) const;
	void calculateOne(stack<Operator>& operators, stack<int>& variable);
};
#endif