#ifndef FIELD_HPP
#define FIELD_HPP
#include <map>
#include <stdexcept>
#include <memory>
#include <regex>
#include <iostream>
#include <sstream>
#include <cctype>


using namespace std;
class Field
{
public:
	string deleteAllBlanks(const string& line) const;
	Field(Field* parent = nullptr);
	void execute(string& line,istream&  ifstream_main);
	int find_int_variable(const string& name);
	void setVariableInt(const string& name);
	int calculateExpression(const string& maybe_exp);
	string findExpresionInAssigment(const string& line);
private:
	map<string, int> int_variables;
	Field* parent;
	bool isStatementFormat(const string& line) const;
	bool isNewVarFormat(const string& line) const;
	string getStatementKey(const string& line) const;
	string getNameOfNewVar(const string& line) const;
	
};


#endif
