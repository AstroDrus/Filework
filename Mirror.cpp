#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Task
{
public:
    virtual ~Task() = default;
    virtual void Exec() = 0;
};

class Copy : public Task
{
public:
    Copy(const char* path2source, const char* path2dest);

public:
    void Exec() override;

private:
    const char* path2source_;
    const char* path2dest_;
};

class VerticalMirror : public Task
{
public:
    VerticalMirror(const char* path2source, const char* path2dest);

public:
    void Exec() override;

private:
    const char* path2source_;
    const char* path2dest_;
};

class HorizontalMirror : public Task
{
public:
    HorizontalMirror(const char* path2source, const char* path2dest);

public:
    void Exec() override;

private:
    const char* path2source_;
    const char* path2dest_;
};

class Rotate : public Task
{
public:
    Rotate(const char* path2source, const char* path2dest);

public:
    void Exec() override;

private:
    const char* path2source_;
    const char* path2dest_;
};

class ErrorUsage : public Task
{
public:
    ErrorUsage(const char* programname);

public:
    void Exec() override;

private:
    const char* programname_;
};

class Help : public Task
{
public:
    void Exec() override;
};


std::unique_ptr<Task> MakeTask(int argc, char** argv);
bool CheckFormat(char* SourceFile);
bool CheckExpansion(const char* SourceFile);

int main(int argc, char** argv)
{
    if (argc < 2 || argc > 4)
    {
        std::cerr << "Incorrect using!\n";
        std::make_unique<ErrorUsage>(argv[0]);
        return 1;
    }

    std::unique_ptr<Task> task = MakeTask(argc, argv);
    task->Exec();

}

bool CheckFormat(char* SourceFile)
{
    const unsigned BMPmaxsize = 65535;
    std::ifstream input(SourceFile);
    if (!input.is_open())
    {
        std::cerr << "Incorrect source file name!\n";
        return false;
    }

    std::string firstnum;
    std::string secondnum;
    bool flag = 0;
    
    int checkparametrs = 0;
    int checkhelper = 0;

    for (std::string line; std::getline(input, line); ++checkhelper)
    {

        if (checkhelper == 1 &&flag == 0)
        {
            for (int i = 0; i < line.size(); ++i)
            {
                if (line[i] == ' ')
                {
                    flag = true;
                }
                else if (flag == 0)
                {
                    firstnum += line[i];
                }
                else if (flag == 1)
                {
                    secondnum += line[i];
                }
                else 
                {
                    return false;
                }
            }
        }
       
        if (line[0] == '#')
        {
            --checkhelper;
        }
        else if (checkhelper == 0 && line == "P1")
        {
            ++checkparametrs;
        }
        else if (checkhelper == 1 && stoi(firstnum) <= BMPmaxsize && stoi(secondnum) <= BMPmaxsize)
        {           
            ++checkparametrs;
            break;
        }
        else
        {
            return false;
        }
    }

    if (checkparametrs == 2) 
    {
        return true;
    }
    else 
    {
        return false;
    }
    
}

bool CheckExpansion(const char* SourceFile)
{
    const std::string expectedExtension = ".bmp";
    auto idxLastExtOccur = std::string(SourceFile).rfind(expectedExtension);
    if (idxLastExtOccur == std::string::npos)
    {
        return false;
    }
    return (std::string(SourceFile).size() - idxLastExtOccur) == expectedExtension.size();
}

std::unique_ptr<Task> MakeTask(int argc, char** argv)
{
    // Проверить, что вообще есть что-то, кроме имени программы
    if (argc <= 2 || argc > 4)
    {
        return std::make_unique<ErrorUsage>(argv[0]);
    }

    std::string firstOpt = argv[1];
    if (firstOpt[0] == '-')
    {
        if (!CheckExpansion(argv[2]) || !CheckFormat(argv[2]))
        {
            std::cerr << "Incorrect using!\n";
            return std::make_unique<ErrorUsage>(argv[0]);
        }

        if (firstOpt[1] == 'h')
        {
            return std::make_unique<Help>();
        }
        else
        {
            switch (firstOpt[1])
            {
            case 'v':
                return std::make_unique<VerticalMirror>(argv[2], argv[3]);
                break;

            case 'g':
                return std::make_unique<HorizontalMirror>(argv[2], argv[3]);
                break;

            case 'r':
                return std::make_unique<Rotate>(argv[2], argv[3]);
                break;

            case 'c':
                return std::make_unique<Copy>(argv[2], argv[3]);
                break;

            default:
                return std::make_unique<ErrorUsage>(argv[0]);
                break;
            }
        }
    }
    else
    {
        if (argc == 3)
        {
            return std::make_unique<Copy>(argv[1], argv[2]);
        }
        else
        {
            return std::make_unique<ErrorUsage>(argv[0]);
        }
    }

}

Copy::Copy(const char* path2source, const char* path2dest) :
    path2source_(path2source),
    path2dest_(path2dest)
{}

VerticalMirror::VerticalMirror(const char* path2source, const char* path2dest) :
    path2source_(path2source),
    path2dest_(path2dest)
{}

HorizontalMirror::HorizontalMirror(const char* path2source, const char* path2dest) :
    path2source_(path2source),
    path2dest_(path2dest)
{}

Rotate::Rotate(const char* path2source, const char* path2dest) :
    path2source_(path2source),
    path2dest_(path2dest)
{}

ErrorUsage::ErrorUsage(const char* programname) :
    programname_(programname)
{}

void Copy::Exec()
{
    std::ifstream input(path2source_);
    if (!input.is_open())
    {
        std::cerr << "Incorrect source file name!\n";
        return;
    }

    std::ofstream output(path2dest_, std::ios_base::app);
    if (!output.is_open())
    {
        std::cerr << "Incorrect dest file name!\n";
        return;
    }

    // перенос данных
    for (std::string line; std::getline(input, line); )
    {
        output << line << std::endl;
    }
}

void VerticalMirror::Exec()
{
    std::ifstream input(path2source_);
    if (!input.is_open())
    {
        std::cerr << "Incorrect source file name!\n";
        return;
    }

    std::ofstream output(path2dest_, std::ios_base::app);
    if (!output.is_open())
    {
        std::cerr << "Incorrect dest file name!\n";
        return;
    }

    int num = 0;
    // перенос данных и отзеркаливание   
    for (std::string line; std::getline(input, line); )
    {
        if (num < 2 || line[0] == '#')
        {
            ++num;
            output << line << std::endl;
        }
        else
        {
            std::string reverseline(line.rbegin(), line.rend());
            output << reverseline << std::endl;
        }
    }
}

void HorizontalMirror::Exec()
{
    std::ifstream input(path2source_);
    if (!input.is_open())
    {
        std::cerr << "Incorrect source file name!\n";
        return;
    }

    std::ofstream output(path2dest_, std::ios_base::app);
    if (!output.is_open())
    {
        std::cerr << "Incorrect dest file name!\n";
        return;
    }

    int cols = 0;

    for (std::string line; std::getline(input, line); )
    {
        if (line[0] == '#' || line == "P1")
        {
            continue;
        }
        else
        {
            cols = int(line[0]);
            break;
        }
    }
    std::vector <std::string> picture;
    int num = 0;
    // добавлем в вектор строки
    for (std::string line; std::getline(input, line); )
    {
        if (num <= 2)
        {
            if (line[0] == '#')
            {
                --num;
                continue;
            }
            else
            {
                ++num;
                output << line << std::endl;
                continue;
            }
        }
        std::string str(line.begin(), line.end());
        // меняем строки местами и вставляем их в вектор
        picture.insert(picture.begin(), str);
    }

    // вектор передаем в файл
    for (int i = 0; i < cols; ++i)
    {
        output << picture[i] << std::endl;
    }
}

void Rotate::Exec() // картинка должна быть квадратной
{
    std::ifstream input(path2source_);
    if (!input.is_open())
    {
        std::cerr << "Incorrect source file name!\n";
        return;
    }

    std::ofstream output(path2dest_, std::ios_base::app);
    if (!output.is_open())
    {
        std::cerr << "Incorrect dest file name!\n";
        return;
    }
    std::vector <std::vector<std::string>> Mtxofpicture;
    int colsize = 0;
    int rowsize = 0;


    for (std::string line; std::getline(input, line); )
    {
        if (line[0] == '#' || line == "P1")
        {
            continue;
        }
        else
        {
            colsize = int(line[0]);
            rowsize = int(line[1]);
            break;
        }
    }

    if (colsize != rowsize)
    {
        std::cerr << "Incorrect picture size!\n";
        return;
    }

    for (int cols = 0; cols < colsize; ++cols)
    {
        for (int rows = 0; rows < rowsize; ++rows)
        {
            for (std::string line; std::getline(input, line); )
            {
                if (line[0] == '#' || line == "P1")
                {
                    continue;
                }
                else
                {
                    for (int i = 0; line[i] != '\n'; ++i)
                    {
                        if (line[i] == '0' || line[i] == '1')
                        {
                            Mtxofpicture[cols][rows] = line[i];
                            break;
                        }
                    }
                }
            }
        }
    }
    // переворачиваем на 90 градусов вправо
    std::vector <std::vector<std::string>> reverseMtxofpicture;

    for (int cols = 0; cols < colsize; ++cols)
    {
        for (int rows = 0; rows < rowsize; ++rows)
        {
            reverseMtxofpicture[rows][cols] = Mtxofpicture[cols][colsize - rows + 1];
        }
    }

    // передаем вектор в файл
    for (int cols = 0; cols < colsize; ++cols)
    {
        for (int rows = 0; rows < rowsize; ++rows)
        {
            output << reverseMtxofpicture[rows][cols];
        }
        output << std::endl;
    }
}

void ErrorUsage::Exec()
{
    std::cout << "Usage: " << programname_ << " <SOURCE_FILENAME.bmp> <DESTINATION_FILENAME.bmp> \n"
        "<SOURCE_FILENAME.bmp> - the path to the file to copy data their \n"
        "<DESTINATION_FILENAME.bmp> - the path to the file to put data from the SOURCE_FILENAME.bmp" << std::endl;

}

void Help::Exec()
{
    std::cout << "1) Просто скопировать           - ./bmp_worker src.bmp dst.bmp" << std::endl;
    std::cout << "2) Посмотреть справку           - ./bmp_worker -h" << std::endl;
    std::cout << "3) Отобразить по вертикали      - ./bmp_worker -v src.bmp dst.bmp" << std::endl;
    std::cout << "4) Отобразить по горизонтали    - ./bmp_worker -g src.bmp dst.bmp" << std::endl;
    std::cout << "5) Повернуть на 90 град         - ./bmp_worker -r src.bmp dst.bmp" << std::endl;
    std::cout << "./program [option] [src file] [dst file]" << std::endl;
}
