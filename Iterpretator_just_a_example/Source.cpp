#include  "MainProgram.hpp"
inline void EndOfProgram();
int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		EndOfProgram();
		return 0;
	}
	MainField main_field;
	main_field.run(argv[1]);
	EndOfProgram();
	return 0;
}

void EndOfProgram()
{
	getchar(); getchar();
}
