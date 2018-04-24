#ifndef IF_STATEMENT_HPP
#define IF_STATEMENT_HPP
#include "Field.hpp"
#include "Statement.hpp"
class IfStatement:Field,Statement
{
	Statement* create(Field* perent = nullptr) const  override;
	void invoke(string& line, ifstream& ifstream) const override;

};

#endif
