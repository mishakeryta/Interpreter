#include "Print_st.hpp"

Statement* Print_st::create(Field* parent) const
{
	return new Print_st{ parent };
}

void Print_st::invoke(string& line, ifstream& ifstream) const
{
	int index = 0;
	while(isblank(line.at(index)))
	{
		++index;
	}
	for (int i = 0; i < 6; ++i, ++index);
	string argument;
	while(index < line.length() && isblank(line[index]))
	{
		++index;
	}
	if (line[index] == ')') cout << "\n";
	if(line[index] == '\"')
	{
		while (index < line.length() && line[index] != ' \"')
		{
			argument+= line[index];
			++index;
		}
		if(index == line.length() - 1)
		{
			throw string("Inappropriate format!!!");
		}
		else
		{
			if(line[index] == '\"')
			{
				while(index < line.length())
				{
					if(!isblank(line[index]))
					{
						if(line[index] == ')')
						{
							cout << argument;
							return;
						}
						else
						{
							throw string{ "Error with print arguments" };
						}
					}
				}
			}
		}
	}
	else
	{}
}

