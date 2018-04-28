#include "While_st.hpp"

void While_st::invoke(string& line, istream& main_ifstream)
{
	string expression = findExspressionInScope(line);
	expression = deleteAllBlanks(expression);
	string line_tmp;
	string linesInStatements = createStringInScope(main_ifstream);
	while (calculateExpression(expression))
	{
		istringstream statement_stream{ linesInStatements };
		while (!statement_stream.eof())
		{
			getline(statement_stream, line_tmp);
			execute(line_tmp, statement_stream);
		}
	}
}

While_st::While_st(Field * parent):IfStatement(parent) {}

Statement* While_st::create(Field *parent) const
{
	return new While_st(parent);
}

