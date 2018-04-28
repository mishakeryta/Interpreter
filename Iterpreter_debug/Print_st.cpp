#include "Print_st.hpp"

Statement* Print_st::create(Field* parent) const
{
	return new Print_st{ parent };
}

void Print_st::invoke(string& line, istream& ifstream)
{
	int index = 0;
	while (isblank(line.at(index)))
	{
		++index;
	}
	for (int i = 0; i < 6; ++i, ++index);
	string argument;
	while (index < line.length() && isblank(line[index]))
	{
		++index;
	}
	if (line[index] == ')') {
		cout << "\n";
		return;
	}

	if (line[index] == '\"')
	{
		++index;
		while (index < line.length() && line[index] != '\"')
		{
			argument += line[index];
			++index;
		}
		if (line[index] == '\"')
		{
			++index;
			while (index < line.length())
			{
				if (!isblank(line[index]))
				{
					if (line[index] == ')')
					{
						cout << argument;
						return;
					}
					else
					{
						throw string{ "Error: print arguments" };
					}
				}
				++index;
			}
		}
		else
		{
			throw string{ "Error: print arguments" };
		}
	}
	else
	{
		string expression;
		while (index < line.length())
		{
			if (line[index] == ')') break;
			expression += line[index];
			if (!isblank(line[index]) && !isalnum(line[index]) && line[index] != '+' && line[index] != '-')
				throw string{ "Error: print argument" };
			++index;
		}
		std::cout << calculateExpression(expression);
	}
}
