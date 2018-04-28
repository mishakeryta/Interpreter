#ifndef STATEMENT_CREATOR_HPP
#define STATEMENT_CREATOR_HPP
#include <string>
#include <map>

class Statement;
class Field;
using namespace std;
class StatementCreator
{
public:
	static bool isStatementWith(const string& key);
	static Statement*  create(const string& key, Field* perent);
private:
	static map<string, Statement*> statements;
	static  void initStatements();
};


#endif
