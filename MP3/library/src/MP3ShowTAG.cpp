#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>

// namespace MP3
namespace MP3
{
void MP3Check( const std::ifstream& source_file ); //todo name

void ShowTAG( std::ifstream& source_file)
{
    MP3Check(source_file);
    static constexpr const int tag_amount = 3;
    char tag[tag_amount+1] = {'\0'};
    static constexpr const char * correct_tag = "ID3";
    
        read(source_file, bite) //todo

    if (!(std::string(tag) == std::string(correct_tag)))
    {
        throw "wrong format\n"; //todo
    }

}

void MP3Check( const std::ifstream& source_file )
{
	if (!source_file.is_open())
	{
		throw std::invalid_argument("Incorrect source file name!"); 
    }
}
}
