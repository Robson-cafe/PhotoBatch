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
	setlocale(LC_NUMERIC, "en_US");

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
	cout << "Folder : " << argParser.GetOptionAs<const string&>("folder") << endl;
	cout << "Amount (float): " << argParser.GetOptionAs<float>("amount") << endl;
	cout << "Amount (int): " << argParser.GetOptionAs<int>("amount") << endl;

	return 0;
}