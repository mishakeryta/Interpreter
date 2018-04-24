#ifndef MAIN_PROGRAM_HPP
#define MAIN_PROGRAM_HPP
#include "Field.hpp"

class MainField:private Field
{
public:
	void run(string path);
};
#endif