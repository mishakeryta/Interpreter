#ifndef  STATEMENT_HPP
#define STATEMENT_HPP
#include <iostream>
#include <fstream>
#include <map>

class Field;
using namespace std;
class  Statement
{
public:
	virtual Statement* create(Field* perent = nullptr) const = 0;
	virtual void invoke(string& line,istream& ifstream) = 0;
	virtual ~Statement() = default;
};
#endif
