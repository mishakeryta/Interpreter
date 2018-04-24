#include <fstream>
#include "MainProgram.hpp"

void MainField::run(string fileName)
{
	ifstream main_ifstream{ fileName,ios::in };
	if(main_ifstream.fail())
	{
		throw string{ "Bad file name" };	
	}
	while(!main_ifstream.eof())
	{
		string line;
		getline(main_ifstream, line);
		execute(line, main_ifstream);
	}
}