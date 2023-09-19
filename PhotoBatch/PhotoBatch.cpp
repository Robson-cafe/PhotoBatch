#include <iostream>
#include <iomanip>
#include <map>

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