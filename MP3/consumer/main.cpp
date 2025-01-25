#include <iostream>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include "libMP3.h"

class MP3_Header
{
public:  
    // massiv for the result of this func (C-style -> std::string)
    std::string tag_;  
};


int main(int argc, char ** argv )
{
    if (argc != 2)
    {
        std::cerr << "wrong count of files!\n";
        return 1;
    }
    // MP3_file for the result after using MP3::GetHeading
    std::ofstream Head_file("Head_file.txt", std::ios_base::app);
    // source MP3_file for the MP3::GetHeading
    std::ifstream source_file(argv[2], std::ios::binary);

    try 
    {
        MP3_Header MP3_h;
        MP3_h.tag_ = MP3::GetHeading(source_file);
        std::cout << MP3_h.tag_ << std::endl;
        //give to the main.cpp the head of the MP3_file
        //Head_file << MP3_h.tag_;    
    }
    catch( const std::exception& exeption )
    {
        std::cout << exeption.what() << std::endl;
    }

    return 0;
}
