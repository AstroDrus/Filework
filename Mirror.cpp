#include <fstream>
#include <iostream>
#include <string>

class Task
{
    public:
    virtual void Exec(int argc, char** argv) = 0;
};

class Copy : public Task
{
    public:
    void Exec(int argc, char** argv) override;
};

class VerticalMirror : public Task
{
    public:
    void Exec(int argc, char** argv) override;
};

class HorizontalMirror : public Task
{
    public:
    void Exec(int argc, char** argv) override;
};

class Rotate : public Task
{
    public:
    void Exec(int argc, char** argv) override;
};

class ErrorUsage : public Task
{
    public:
    void Exec(int argc, char** argv) override;
};

class Help : public Task
{
    public:
    void Exec(int argc, char** argv) override;
};


Task* MakeTask( int argc, char** argv);
bool CheckFormat(char* SourceFile);
std::string FlipLine(const std::string& line);


int main(int argc, char** argv)
{
    const int minProgrammArgsCount = 3;
    if (argc != minProgrammArgsCount)
    {
        std::cerr << "Incorrect using!\n";
        ErrorUsage Error;
        Error.Exec(argc, argv);
        return 1;
    }

    if (!CheckFormat(argv[1])) 
    {
        std::cerr << "Incorrect using!\n";
        ErrorUsage Error;
        Error.Exec(argc, argv);
        return 1;
    }
    
    Task* task = MakeTask( argc, argv );
    task->Exec(argc, argv);
    delete task;

}

bool CheckFormat(char* SourceFile) 
{
    // here must be realization
    return 1;
        
}

Task* MakeTask( int argc, char** argv ) // return Task from new
{
    // Проверить, что вообще есть что-то, кроме имени программы
    if (argc < 2 || argc > 4)
    {
        return new ErrorUsage;
    }
    
    std::string firstOpt = argv[1];
    if (firstOpt[0] == '-')
    {
        switch (firstOpt[1])
        {
            case 'h':
                return new Help;
                break;
                
            case 'v':
                return ( 4 == argc ) ? new VerticalMirror : new ErrorUsage;
                break;
                
            case 'g':
                return ( 4 == argc ) ? new HorizontalMirror : new ErrorUsage;
                break;
                
            case 'r':
                return ( 4 == argc ) ? new Rotate : new ErrorUsage;
                break;
                
            default:
                return new ErrorUsage;
                break;
        }
        
    }
    else
    {
        if (argc == 3)
        {
            return new Copy;
        }
    }
    
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

std::ifstream OpenSourceFile(int argc,char** argv)
{
// Получить имя файла из аргументов
    const std::string source_file_name(argv[1]);

    // Открыть файл для чтения - ifstream
    std::ifstream input;
    input.open(source_file_name);
    if (!input.is_open())
    {
        std::cerr << "Incorrect source file name!\n";
        ErrorUsage Error;
        Error.Exec(argc, argv);
        return; // todo
    }
    return input;
}

std::ofstream OpenDestFile(int argc,char** argv)
{    // Открыть файл для записи - ofstream 
    std::ofstream output(argv[2], std::ios_base::app); // open
    if (!output.is_open())
    {
        std::cerr << "Failed to open destination file " << argv[2] << std::endl;
        ErrorUsage Error;
        Error.Exec(argc, argv);
    }
    return output;
}



void Copy::Exec(int argc, char** argv)
{
    std::ifstream input = OpenSourceFile(argc, argv);
    std::ofstream output = OpenDestFile(argc, argv);
    
    // Открыть файл для записи - ofstream
    std::ofstream output(argv[2], std::ios_base::app); // open
    if (!output.is_open())
    {
        std::cerr << "Failed to open destination file " << argv[2] << std::endl;
        ErrorUsage Error;
        Error.Exec(argc, argv);
    }

    // перенос данных
    for (std::string line; std::getline(input, line); )
    {
        output << line << std::endl;
    }
}
    

    
void VerticalMirror::Exec(int argc, char** argv)
{
    std::ifstream input = OpenSourceFile(argc, argv);
    std::ofstream output = OpenDestFile(argc, argv);

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



void HorizontalMirror::Exec(int argc, char** argv)
{
    std::ifstream input = OpenSourceFile(argc, argv);
    std::ofstream output = OpenDestFile(argc, argv);
}



void Rotate::Exec(int argc, char** argv)
{
    std::ifstream input = OpenSourceFile(argc, argv);
    std::ofstream output = OpenDestFile(argc, argv);
}



void ErrorUsage::Exec(int argc, char** argv)
{
    std::cout << "Usage: " << argv[0] << " <SOURCE_FILENAME.bmp> <DESTINATION_FILENAME.bmp> \n"
    "<SOURCE_FILENAME.bmp> - the path to the file to copy data their \n"
    "<DESTINATION_FILENAME.bmp> - the path to the file to put data from the SOURCE_FILENAME.bmp" << std::endl;

}

void Help::Exec(int argc, char** argv)
{
    std::cout <<  "1) Просто скопировать           - ./bmp_worker src.bmp dst.bmp" << std::endl;
    std::cout <<  "2) Посмотреть справку           - ./bmp_worker -h" << std::endl;
    std::cout <<  "3) Отобразить по вертикали      - ./bmp_worker -v src.bmp dst.bmp" << std::endl;
    std::cout <<  "4) Отобразить по горизонтали    - ./bmp_worker -g src.bmp dst.bmp" << std::endl;
    std::cout <<  "5) Повернуть на 90 град         - ./bmp_worker -r src.bmp dst.bmp" << std::endl;
    std::cout <<   "./program [option] [src file] [dst file]" << std::endl;
}
