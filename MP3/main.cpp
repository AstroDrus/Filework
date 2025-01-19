#include <iostream>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "libMP3"

int main(int argc, char ** argv )
{
    if (argc != 2)
    {
        std::cerr << "wrong count of files!\n";
        return 1;
    }
    std::ifstream source_file(argv[2], binary);
    try 
    {
        MP3::ShowTAG(source_file); //todo no void return full Zagalovoc
    }
    catch( const std::exception& exeption )
    {
        std::cout << exeption << std::endl;
    }    


    return 0;
}
