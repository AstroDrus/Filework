#include <fstream>
#include <iostream>
#include <string>
#include <stdexcept>


namespace MP3
{
//give to the main.cpp the head of the MP3_file
std::string GetHeading( std::ifstream& source_file)
{  
    // amount of bayts in head of MP3_file
    static constexpr const int size_of_tag = 9;
    // massiv for the result of this func (C-style -> std::string)
    char tag[size_of_tag+1] = {'\0'};  

    //verification if file can be opened  
    if (!source_file.is_open())
	{
		throw std::invalid_argument("Incorrect source file name!"); 
    }

    source_file.read(tag, size_of_tag);
    return tag;

}
}// namespace MP3
