#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>

using namespace std;

//int main()
//{
//	setlocale(LC_ALL, "pt_BR");
//
//	std::cout << "Hello World!!!" << std::endl;
//	std::cout << "Olá Mundo!!!" << std::endl;
//
//	return 0;
//}

string ToLower(
	string str
) 
{
	/*for (char& c : str) {
		c = tolower(c);
	}*/

	transform(begin(str), end(str), begin(str), [](unsigned char c) {return tolower(c); });
	return str;
}

class ArgumentParser
{
	public:
		void RegisterFlag(
			const string& flag
		)
		{
			if (!flag.empty()) {
				m_Flags[flag] = false;
			}
		}

		bool GetFlag(
			const string& flag
		) const
		{
			if (!flag.empty()) {
				auto flagIt = m_Flags.find(flag);

				if (flagIt != end(m_Flags)) {
					return flagIt->second;
				}
			}

			return false;
		}

		void Parse(
			int argc,
			char* argv[]
		)
		{
			if (argc > 1) {
				for (int i = 1; i < argc; ++i) {
					//string arg = argv[i];
					string arg = ToLower(argv[i]);

					if (arg.length() >= 3) {
						//argumentos tem que ter pelo menos 3 caracteres
						// os "--" iniciais e pelo menos um terceiro caracter
						if (arg[0] == '-' && arg[1] == '-') {
							//--rename
							//primeiro remover os "--" iniciais
							arg = arg.substr(2);

							//depois do arg.substr: "rename"
							if (arg.find_first_of('=') != string::npos) {
								//é uma opção
							}
							else {
								// é uma flag
								auto flagIt = m_Flags.find(arg);

								if (flagIt != end(m_Flags)) {
									// encontrou a flag
									flagIt->second = true;
								}
							}
						}
					}
				}
			}
		}

	private:
		map<string, bool> m_Flags;
};
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

	argParser.Parse(argc, argv);

	cout << "Rename : " << boolalpha << argParser.GetFlag("rename") << endl;
	cout << "Convert : " << boolalpha << argParser.GetFlag("convert") << endl;
	cout << "Resize : " << boolalpha << argParser.GetFlag("resize") << endl;
	cout << "Scale : " << boolalpha << argParser.GetFlag("scale") << endl;


	return 0;
}