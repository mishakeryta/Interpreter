#include "StatementCreator.hpp"
#include "Print_st.hpp"
#include "IfStatement.hpp"
#include "While_st.hpp"
#include "StatementCreator.hpp"
map<string, Statement*> StatementCreator::statements;

bool StatementCreator::isStatementWith(const string& key)
{
	initStatements();
	return statements.find(key) != statements.end();
}

Statement* StatementCreator::create(const string& key, Field* parent)
{
	initStatements();

	if (isStatementWith(key))
	{
		return statements[key]->create(parent);
	}
	return nullptr;
}

void StatementCreator::initStatements()
{
	if (statements.empty())
	{
		statements["print"] = new Print_st{ nullptr };
		statements["if"] = new IfStatement{ nullptr };
		statements["while"] = new While_st{ nullptr };
	}
}
