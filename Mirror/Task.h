#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <memory>
#include <string>



bool Compare_filles(const std::string pathchecker, const std::string pathresult)
{
    bool res = 1;
    std::ifstream Checker(pathchecker);
	if (!Checker.is_open())
	{
		std::cerr << "Result file name does not exist!\n";
		return;
	}
    std::ifstream Result(pathresult);
	if (!Result.is_open())
	{
		std::cerr << "Result file name does not exist!\n";
		return;
	}

    // основной цикл сравнивания файлов

}


int main(int argc, char** argv) // 7 аргумента: 
                                // 1) название программы; 2) адрес результата (проверяемого файла);
                                // 3) адрес Чекера -v; 4) адрес Чекера -g; 
                                // 5) адрес Чекера -r; 6) адрес Чекера -c; 7) адрес Чекера -h 
{
    char flag;
    std::cin >> flag;

    switch (flag)
    {
    case 'v':
        
        std::system("./ Mirror -v");
        // сравниваем эталон с полуенным результатом
        if (Compare_filles(argv[2], argv[1]) == 0)
        {
            std::cout << "success" << std::endl;
        }
        else 
        {
            std::cout << "unsuccess" << std::endl;
        }
        break;

    case 'g':
        
        std::system("./ Mirror -g");
        if (Compare_filles(argv[3], argv[1]) == 0)
        {
            std::cout << "success" << std::endl;
        }
        else 
        {
            std::cout << "unsuccess" << std::endl;
        }
        break;

    case 'r':
        
        std::system("./ Mirror -r");
        if (Compare_filles(argv[4], argv[1]) == 0)
        {
            std::cout << "success" << std::endl;
        }
        else 
        {
            std::cout << "unsuccess" << std::endl;
        }
        break;

    case 'c':
        
        std::system("./ Mirror -c");
        if (Compare_filles(argv[5], argv[1]) == 0)
        {
            std::cout << "success" << std::endl;
        }
        else 
        {
            std::cout << "unsuccess" << std::endl;
        }
        break;

    case 'h':
        
        std::system("./ Mirror -h");
        if (Compare_filles(argv[6], argv[1]) == 0)
        {
            std::cout << "success" << std::endl;
        }
        else 
        {
            std::cout << "unsuccess" << std::endl;
        }
        break;

    default:
        
        std::system("./ Mirror");
        if (Compare_filles(argv[5], argv[1]) == 0)
        {
            std::cout << "success" << std::endl;
        }
        else 
        {
            std::cout << "unsuccess" << std::endl;
        }
        break;
    } 
}
