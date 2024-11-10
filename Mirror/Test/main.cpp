
#include <iostream>
#include <string>
#include <fstream>



bool IsSame( const std::string& lhv, const std::string& rhv )
{
    std::ifstream lhvStream (lhv);
    if(!lhvStream.is_open())
    {
        std::cerr << "The result-file of the tested programm dose not exist\n";
		return false;
    }

     std::ifstream rhvStream (lhv);
    if(!rhvStream.is_open())
    {
        std::cerr << "The model-file of the tested programm dose not exist\n";
		return false;
    }

    bool isSame{ true };
    bool isDone{ false };

    while( isSame && !isDone )
    {
        const bool lhvEnded{ lhvStream.eof() };
        const bool rhvEnded{ rhvStream.eof() };
        if( !lhvEnded && !rhvEnded )
        {
            char lhvSym;
            char rhvSym;
            lhvStream >> lhvSym;
            rhvStream >> rhvSym;
            isSame = ( lhvSym == rhvSym );
        }
        else if( lhvEnded != rhvEnded )
        {
            isSame  = false;
        }
        else 
        {
            isDone = true;
        }
    }
    
    return isSame;
}

int main(int argc, char** argv) // 8 arguments
                                // 0) programm name; 1) original programm; 
                                // 2) result of programm; 3) model of -v res;
                                // 4) model of -g res; 5) model of -r res;
                                // 6) model of -c res.
{
    const std::string ProgrammName = "Mirror ";
    std::string Flag;
    std::cin >> Flag;
    Flag += " ";
    const std::string FromFile = argv[1];
    const std::string ToFile = argv[2];
    const std::string TerminalPath = ProgrammName + Flag + FromFile + " " + ToFile;
        switch (Flag[1])
        {
			case 'v':
				std::system(TerminalPath.c_str());
                if ( IsSame(argv[2], argv[3]) )
                {
                    std::cout << "success" << std::endl;
                }
                else
                {
                    std::cout << "unsuccess" << std::endl;
                }
				break;

			case 'g':
				std::system(TerminalPath.c_str());
                if ( IsSame(argv[2], argv[4]) )
                {
                    std::cout << "success" << std::endl;
                }
                else
                {
                    std::cout << "unsuccess" << std::endl;
                }
				break;

			case 'r':
				std::system(TerminalPath.c_str());
                if ( IsSame(argv[2], argv[5]) )
                {
                    std::cout << "success" << std::endl;
                }
                else
                {
                    std::cout << "unsuccess" << std::endl;
                }
				break;

			case 'c':
				std::system(TerminalPath.c_str());
                if ( IsSame(argv[2], argv[6]) )
                {
                    std::cout << "success" << std::endl;
                }
                else
                {
                    std::cout << "unsuccess" << std::endl;
                }
				break;

			default:
				std::system(TerminalPath.c_str());
                if ( IsSame(argv[2], argv[6]) )
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
