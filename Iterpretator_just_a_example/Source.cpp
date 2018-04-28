#include  "MainProgram.hpp"
#include <iostream>
inline void EndOfProgram();
int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		EndOfProgram();
		return 0;
	}
	MainField main_field;
	try
	{
		main_field.run(argv[1]);
	}
	catch (string message)
	{
		std::cout << message;
	}
	EndOfProgram();
	return 0;
}

void EndOfProgram()
{
	getchar(); getchar();
}
