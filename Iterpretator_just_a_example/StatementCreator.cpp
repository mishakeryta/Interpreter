#include "StatementCreator.hpp"
#include "Statement.hpp"
#include "Print_st.hpp"

map<string,Statement*> StatementCreator::statements;

bool StatementCreator::isStatementWith(const string& key)
{
	initStatements();
	return statements.find(key) != statements.end();
}

Statement* StatementCreator::create(const string& key,Field* parent)
{
	initStatements();

	if (isStatementWith(key))
	{
		return statements["print"]->create(parent);
	}
	return nullptr;
}

void StatementCreator::initStatements()
{
	if (statements.empty())
	{
		statements["print"] = new Print_st{ nullptr };
	}
}
