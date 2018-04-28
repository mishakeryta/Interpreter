#ifndef IF_STATEMENT_HPP
#define IF_STATEMENT_HPP

#include "Satement.hpp"
#include "Field.hpp"

class IfStatement :public Field, public Statement
{
public:
	string findExspressionInScope(const string& line);
	IfStatement(Field* parent) :Field{ parent } { };
	Statement* create(Field* parent = nullptr) const  override;
	void invoke(string& line, istream& ifstream)  override;
	bool isEndScope(const string& line);
	string createStringBeforeScope(istream& main_ifstream);
private:
	string arguments;
};
#endif
