#ifndef PRINT_ST_HPP
#define PRINT_ST_HPP



#include "Field.hpp"
#include "Statement.hpp"

class Print_st: public Field,public Statement
{
public:
	Print_st(Field* parent):Field{parent}{};
	Statement* create(Field* parent = nullptr) const override;
	void invoke(string& line, istream& ifstream) override;
private:
};
#endif
