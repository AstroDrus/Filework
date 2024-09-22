#include <fstream>
#include <iostream>
#include <string>

void Help(const char* programName);

int main(int argc, char** argv)
{
    const int minProgrammArgsCount = 3;
    if (argc != minProgrammArgsCount)
    {
        std::cerr << "Incorrect using!\n";
        Help(argv[0]);
        return 1;
    }

    // Получить имя файла из аргументов
    const std::string source_file_name(argv[1]);

    // Открыть файл для чтения - ifstream 
    std::ifstream input;
    input.open(source_file_name);
    if (!input.is_open())
    {
        std::cerr << "Incorrect source file name!\n";
        return 1;
    }

    // Открыть файл для записи - ofstream 
    std::ofstream output(argv[2], std::ios_base::app); // open
    if (!output.is_open())
    {
        std::cerr << "Failed to open destination file " << argv[2] << std::endl;
        return 1;
    }

    // перенос данных    
    for (std::string line; std::getline(input, line); )
    {      
        output << line << std::endl;   
    }
}

void Help(const char* programName)
{
    std::cout << "Usage: " << programName << " <SOURCE_FILENAME> <DESTINATION_FILENAME> \n"
        "<SOURCE_FILENAME> - the path to the file to copy data their \n"
        "<DESTINATION_FILENAME> - the path to the file to put data from the SOURCE FILENAME" << std::endl;
}
