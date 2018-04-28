#ifndef STATEMENT_CREATOR_HPP
#define STATEMENT_CREATOR_HPP
#include <string>
#include <map>
/*string may_exp = deleteAllBlanks(maybe_exp);
istringstream in_exp{ may_exp };
while (!in_exp.eof())
{

char switch_val = in_exp.peek();
if (isdigit(switch_val))
{

}
}*/
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
