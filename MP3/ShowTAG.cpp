#include <fstream>
#include <iostream>
#include <string>

void ShowTAG( std::ifstream source_file)
{
    const int tag_amount = 3;
    char * tag[tag_amount+1] {'\0'};
    char ** correct_tag = 'TAG\0';
    char bite;
    
    for ( int i = 0; i <= tag_amount; ++i  )
    {
        std::getline(source_file, bite)
        tag[i] = bite;
    }

    if (tag == correct_tag)
    {
        std::cout << "correct format - " << tag << std::endl;
    }
    else
    {
        throw "wrong format\n";
    }
}
