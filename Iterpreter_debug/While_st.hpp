#ifndef WHILE_ST_HPP
#define WHILE_ST_HPP
#include "IfStatement.hpp"
class While_st :public IfStatement
{
public:
	While_st(Field* parent);
	Statement * create(Field* parent = nullptr) const  override;
	void invoke(string& line, istream& ifstream)  override;
	
};
#endif
