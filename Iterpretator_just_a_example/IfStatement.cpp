#include "IfStatement.hpp"

void IfStatement::invoke(string& line, istream& main_ifstream)
{
	string expression = findExspressionInScope(line);
	expression = deleteAllBlanks(expression);
	string line_tmp;
	if (calculateExpression(expression)) 
	{
		string linesInStatements = createStringBeforeScope(main_ifstream);
		istringstream statement_stream{ linesInStatements };
		while (!statement_stream.eof()) 
		{
			
			getline(statement_stream, line_tmp);
			execute(line_tmp,statement_stream);
		}
	}
	else {
		while (!main_ifstream.eof())
		{
			getline(main_ifstream, line);
			if (isEndScope(line))
				return;
		}
		throw string{ "No end of if" };
	}
	throw string{ "Is statement erroe" };

}

bool IfStatement::isEndScope(const string & line)
{
	int index = 0;
	while (index < line.length() && isblank(line[index]))++index;
	if (line[index] != '}')
		return false;
	++index;
	while (index < line.length())
	{
		if (!isblank(line[index])) return false;
		++index;
	}
	return true;
}

string IfStatement::createStringBeforeScope(istream & main_ifstream)
{
	string linesBeforeScope;
	do {
		string line;
		getline(main_ifstream, line);
		if (isEndScope(line)) return linesBeforeScope;
		line += '\n';
		linesBeforeScope += line;
	} while (!main_ifstream.eof());
	throw string("If has not end");
}






string IfStatement::findExspressionInScope(const string & line)
{
	int index = 0;
	for (; index < line.length() && line[index] != '(';++index);
	++index;
	string result;
	while (line[index] != ')')
	{
		result += line[index];
	}
	return result;
}

Statement* IfStatement::create(Field* parent) const
{
	return new IfStatement{ parent };
}
