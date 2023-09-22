#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>

#include "ArgumentParser.h"

using namespace std;

//-------------------------------------------------------------------------

//int main()
//{
//	setlocale(LC_ALL, "pt_BR");
//
//	std::cout << "Hello World!!!" << std::endl;
//	std::cout << "Olá Mundo!!!" << std::endl;
//
//	return 0;
//}


int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "pt_BR");

	/*for (int i = 0; i < argc; ++i) {
		std::cout << argv[i] << std::endl;
	}*/

	//getchar();

	ArgumentParser argParser;
	argParser.RegisterFlag("rename");
	argParser.RegisterFlag("convert");
	argParser.RegisterFlag("resize");
	argParser.RegisterFlag("scale");
	argParser.RegisterOption("folder");
	argParser.RegisterOption("amount");

	argParser.Parse(argc, argv);

	cout << boolalpha << "Rename : " << argParser.GetFlag("rename") << endl;
	cout << boolalpha << "Convert : " << argParser.GetFlag("convert") << endl;
	cout << boolalpha << "Resize : " << argParser.GetFlag("resize") << endl;
	cout << boolalpha << "Scale : " << argParser.GetFlag("scale") << endl;
	cout << "Folder : " << argParser.GetOption("folder") << endl;
	cout << "Amount : " << argParser.GetOption("amount") << endl;


	return 0;
}