#include <iostream>
#include <iostream>
#include <fstream>
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
        Check(source_file);
        ShowTAG(source_file);
    }
    catch( ... )
    {
        std::cout << error_message << std::endl;
    }

    return 0;
}