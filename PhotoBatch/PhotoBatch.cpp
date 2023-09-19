#include <iostream>

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

	for (int i = 0; i < argc; ++i) {
		std::cout << argv[i] << std::endl;
	}

	//getchar();
	return 0;
}