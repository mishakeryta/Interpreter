#include "IfStatement.hpp"
void IfStatement::invoke(string& line, istream& main_ifstream)
{
	string expression = findExspressionInScope(line);
	expression = deleteAllBlanks(expression);
	string line_tmp;
	string linesInStatements = createStringInScope(main_ifstream);
	if (calculateExpression(expression))
	{
		istringstream statement_stream{ linesInStatements };
		while (!statement_stream.eof())
		{
			getline(statement_stream, line_tmp);
			execute(line_tmp, statement_stream);
		}
		return;
	}

}
bool IfStatement::isInScope(const string & line,int countOfParents)
{
	for (int i = 0; i < line.length() && i < (countOfParents*3); ++i)
	{
		if (line[i] != ' ') return false;
	}
	return true;
}
string IfStatement::createStringInScope(istream & main_ifstream)
{
	string linesInScope;
	int countOfParents = countNumberOfParents();
	do {
		string line;
		streampos now = main_ifstream.tellg();
		getline(main_ifstream, line);
		if (!isInScope(line, countOfParents))
		{
			main_ifstream.seekg(now);
			return linesInScope;
		}
		line += "\n";
		linesInScope += line;
	} while (!main_ifstream.eof());
	return linesInScope;
}

string IfStatement::findExspressionInScope(const string & line)
{
	int index = 0;
	for (; index < line.length() && line[index] != '('; ++index);
	++index;
	string result;
	while (line[index] != ')')
	{
		result += line[index];
		++index;
	}
	return result;
}

Statement* IfStatement::create(Field* parent) const
{
	return new IfStatement{ parent };
}
