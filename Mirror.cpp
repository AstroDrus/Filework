#include <fstream>
#include <iostream>
#include <string>

void Help(const char* programName);
bool CheckFormat(char* SourceFile);
std::string FlipLine(const std::string& line);


int main(int argc, char** argv)
{
    const int minProgrammArgsCount = 3;
    if (argc != minProgrammArgsCount)
    {
        std::cerr << "Incorrect using!\n";
        Help(argv[0]);
        return 1;
    }

    if (!CheckFormat(argv[1])) 
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
    int num = 0;
    // перенос данных и отзеркаливание   
    for (std::string line; std::getline(input, line); )
    {
        if (num <= 2) 
        {
            ++num;
            output << line << std::endl;
            continue;
        }
        output << FlipLine(line) << std::endl;
    }
}

void Help(const char* programName)
{
    std::cout << "Usage: " << programName << " <SOURCE_FILENAME.bmp> <DESTINATION_FILENAME.bmp> \n"
        "<SOURCE_FILENAME.bmp> - the path to the file to copy data their \n"
        "<DESTINATION_FILENAME.bmp> - the path to the file to put data from the SOURCE_FILENAME.bmp" << std::endl;
}

bool CheckFormat(char* SourceFile) 
{
    // here must be realization
        
}



std::string FlipLine(const std::string& line)
{
    std::string buffer;  
    for (int i = 0; i < line.size(); ++i)
    {
        buffer += line[line.size() - i];
    }
    return buffer;
}
