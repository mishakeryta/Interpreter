
#include "Statement.hpp"
#include "Field.hpp"
#include "StatementCreator.hpp"



Field::Field(Field* parent)
{
	this->parent = parent;
}

void Field::execute(string& line, istream& ifstream_main)
{
	if (isStatementFormat(line))
	{
		string key = getStatementKey(line);
		if (StatementCreator::isStatementWith(key))
		{
			Statement* state = StatementCreator::create(key, this);
			state->invoke(line, ifstream_main);
			delete state;
			return;
		}
		throw string{ "Error:No such statement" };
	}
	else if (isNewVarFormat(line))
	{
		string name_of_variable = getNameOfNewVar(line);
		if (int_variables.find(name_of_variable) == int_variables.end())
		{
			int_variables[name_of_variable] = calculateExpression(findExpresionInAssigment(line));
		}
		else
		{
			throw string{ "Error:two variables with the same name!!!" };
		}

	}
}


int Field::find_int_variable(const string& name)
{
	if (int_variables.find(name) != int_variables.end())
	{
		return int_variables[name];
	}
	if (parent)
	{
		return  parent->find_int_variable(name);
	}
	throw string("Error: no shuch variable in the program");	
}

void Field::setVariableInt(const string & name)
{
	//TO DO
}

int Field::calculateExpression(const string& maybe_exp)  
{
	string may_exp  = deleteAllBlanks(maybe_exp);
	try {
		if (!isdigit(may_exp[0])) throw invalid_argument{ "" };
		int val = std::atoi(may_exp.c_str());
		return val;
	}
	catch(invalid_argument exo){
		return find_int_variable(may_exp);
	}
	catch(...)
	{
		throw;
	}
}

bool Field::isStatementFormat(const string& line) const
{
	string formatLine = deleteAllBlanks(line);
	if (formatLine.empty()) return false;
	if (!isalpha(formatLine[0])) return false;
	int i = 0;
	for (i = 1; i < formatLine.size(); ++i)
	{
		if (formatLine[i] == '(') break;
		if (!isalpha(formatLine[i]) && !isdigit(formatLine[i])) return false;
	}
	if (i == formatLine.size() - 1) return false;
	++i;
	for (; i < formatLine.size(); ++i)
	{
		if (formatLine[i] == ')') return true;
	}
	return false;
}

bool Field::isNewVarFormat(const string& line) const
{
	istringstream input{ line };
	string type;
	input >> type;
	if (type != "int")
	{
		return false;
	}
	while (!input.eof() && isblank(input.peek())) input.get();
	if (input.eof() || !isalpha(input.peek())) return false;
	while (true)
	{
		if (input.eof()) return false;
		char ch = input.get();
		if (isblank(ch)) break;
		if (ch == '=') return true;
		if (!isalpha(ch) && !isdigit(ch)) return false;
	}
	while (!input.eof() && isblank(input.peek())) input.get();
	if (input.eof() || input.get() != '=') return false;
	return true;
}


string Field::deleteAllBlanks(const string& line) const
{
	string result;
	for (int i = 0; i < line.length(); ++i)
	{
		if (!isblank(line[i]))
		{
			result += line[i];
		}
	}
	return result;
}

string Field::getStatementKey(const string& line) const
{
	string key;
	int index = 0;

	while (index < line.length())
	{
		if (line[index] == '(') break;
		if (isalpha(line[index]) || isdigit(line[index]))
		{
			key += line[index];
		}
		++index;
	}
	return key;
}

string Field::getNameOfNewVar(const string& line) const
{
	istringstream input{ line };
	string buff;
	input >> buff;
	buff = "";
	getline(input, buff,'=');
	return  deleteAllBlanks(buff);

}

string Field::findExpresionInAssigment(const string& line) {
	int index = 0;
	while (index < line.length()) {
		if (line[index] == '=') {
			++index;
			string result;
			while (index < line.length())
			{
				result+= line[index];
				++index;
			}
			return result;
		}
		++index;
	}
	throw string("Not assigment");
}