
#include "Satement.hpp"
#include "Field.hpp"
#include "StatementCreator.hpp"



Field::Field(Field* parent)
{
	this->parent = parent;
}

void Field::execute(string& line, istream& ifstream_main)
{
	if (isEmptyOrWithAllBlanks(line)) return;
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
			int_variables[name_of_variable] = calculateExpression(findExpressionInAssigment(line));
		}
		else
		{
			throw string{ "Error:two variables with the same name!!!" };
		}

	}
	else if (isAssigmentFormat(line))
	{
		istringstream inLine{ line };
		string name_of_variable;
		getline(inLine, name_of_variable, '=');
		name_of_variable = deleteAllBlanks(name_of_variable);
		setVariableInt(name_of_variable, calculateExpression(findExpressionInAssigment(line)));
	}
	else
	{
		throw string{ "Error: inappropeiate format of the row" };
	}
}

int Field::countNumberOfParents() const
{
	int num = 0;
	const Field* parentCrawler = this;
	while (parentCrawler->parent)
	{
		parentCrawler = parentCrawler->parent;
		++num;
	}
	return num;
}
void Field::setVariableInt(const string& name, int val)
{
	if (int_variables.find(name) != int_variables.end())
	{
		int_variables[name] = val;
		return;
	}
	if (parent) {
		parent->setVariableInt(name, val);
	}
	else
	{
		throw string{ "Error : no  such variable" };
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

int Field::convertStrToInt(const string& maybeVariableOrVal)
{
	string maybe = deleteAllBlanks(maybeVariableOrVal);
	try {
		if (!isdigit(maybe[0])) throw invalid_argument{ "" };
		int val = std::atoi(maybe.c_str());
		return val;
	}
	catch (invalid_argument exo) {
		return find_int_variable(maybe);
	}
	catch (...)
	{
		throw;
	}
}

int Field::calculateExpression(const string& maybe_exp)
{
	string may_exp = deleteAllBlanks(maybe_exp);
	istringstream in_exp{ may_exp };
	bool wasVarBefore = false;
	bool wasOperatorBefore = false;
	int  numberOfOpenScope = 0;
	stack<int> variableStack;
	stack<Operator> operatorStack;

	while (!in_exp.eof())
	{
		Operator curOperator;
		char switch_val = in_exp.peek();
		if (switch_val == '+' || switch_val == '-')
		{
			in_exp.get();
			if (!wasVarBefore)
			{
				variableStack.push(0);
			}
			curOperator = Operator(switch_val, numberOfOpenScope);
		}
		else if (switch_val == '*' || switch_val == '/' || switch_val == '>' || switch_val == '<')
		{
			in_exp.get();
			if (!wasVarBefore)
			{
				throw string{ "Error: bad expression format" };
			}
			curOperator = Operator(switch_val, numberOfOpenScope);
		}
		else if (isalnum(switch_val))
		{
			string  varOrNum;
			char tmp;
			while (!isExpressionSymbol(tmp = in_exp.peek()))
			{
				in_exp.get();
				if (in_exp.eof()) break;
				varOrNum += tmp;
			}
			variableStack.push(convertStrToInt(varOrNum));
			wasVarBefore = true;
		}
		else if (switch_val == ')')
		{
			--numberOfOpenScope;
			in_exp.get();
		}
		else if (switch_val == '(')
		{
			++numberOfOpenScope;
			in_exp.get();
		}
		else if (switch_val == -1)
		{
			break;
		}
		else
		{
			throw string{ "Error: unknown symbol in expression" };
		}
		if (!curOperator.isEmpty())
		{
			while (!operatorStack.empty() && curOperator <= operatorStack.top())
			{
				calculateOne(operatorStack, variableStack);
			}
			operatorStack.push(curOperator);
			wasVarBefore = false;
		}
	}
	if (numberOfOpenScope) throw string("Error: to many scopes");
	while (!operatorStack.empty())
	{
		calculateOne(operatorStack, variableStack);
	}
	return variableStack.top();
}

bool Field::isExpressionSymbol(char symbol)
{
	return symbol == ')' || symbol == '(' || symbol == '+' || symbol == '-' ||
		symbol == '/' || symbol == '*' || symbol == '>' || symbol == '<';
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
	unsigned int numOfBrackets = 1;
	for (; i < formatLine.size(); ++i)
	{
		switch (formatLine[i])
		{
		case('('): {
			++numOfBrackets; break;
		}
		case(')'): {
			--numOfBrackets; break;
		}
		}
	}
	if (numOfBrackets) return false;
	return true;
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

bool Field::isAssigmentFormat(const string & line) const
{
	istringstream inLine{ line };
	string variable;
	getline(inLine, variable, '=');
	return variable.length() != line.length();
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
	getline(input, buff, '=');
	return  deleteAllBlanks(buff);

}

string Field::findExpressionInAssigment(const string& line) {
	int index = 0;
	while (index < line.length()) {
		if (line[index] == '=') {
			++index;
			string result;
			while (index < line.length())
			{
				result += line[index];
				++index;
			}
			return result;
		}
		++index;
	}
	throw string("Not assigment");
}

bool Field::isEmptyOrWithAllBlanks(const string& line) const
{
	if (line.empty()) return true;
	for (unsigned int index = 0; index < line.length(); ++index)
	{
		if (!isblank(line[index])) return false;
	}
	return true;


}

void Field::calculateOne(stack<Operator>& operators, stack<int>& variables)
{
	int val2 = variables.top();
	variables.pop();
	int val1 = variables.top();
	variables.pop();
	variables.push(operators.top().calculate(val1, val2));
	operators.pop();
}
