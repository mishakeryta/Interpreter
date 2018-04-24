#ifndef FIELD_HPP
#define FIELD_HPP
#include <map>
#include <stdexcept>
#include <memory>
#include <regex>
#include <sstream>
#include <cctype>


using namespace std;
class Field
{
public:
	
	Field(Field* parent = nullptr);
	void execute(string& line,ifstream&  ifstream_main);
	int find_int_variable(const string& name);
	int calcuateExpression(const string& maybe_exp);
private:
	map<string, int> int_variables;
	Field* parent;
	bool isStatementFormat(const string& line) const;
	bool isNewVarFormat(const string& line) const;
	string deleteAllBlanks(const string& line) const;
	string getStatementKey(const string& line) const;
	string getNameOfNewVar(const string& line) const;
	
};


#endif
