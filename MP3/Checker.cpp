#include <fstream>

bool Check( std::ifstream source_file )
{
	if (!source_file.is_open())
	{
		throw "Incorrect source file name!"; 
    }
    return true;
}