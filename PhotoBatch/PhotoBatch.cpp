#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>
#include <array>
#include <filesystem>

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

namespace Args
{
	namespace Flags 
	{
		static constexpr const char* Rename = "rename";
		static constexpr const char* Convert = "convert";
		static constexpr const char* Resize = "resize";
		static constexpr const char* Scale = "scale";
	}

	namespace Opts
	{
		static constexpr const char* Folder = "folder";
		static constexpr const char* Filter = "filter";
	}
}

void ValidateArguments (
	const ArgumentParser& argParser
)
{
	//ler as flags que o argumentparser verificou
	const bool bRenameMode = argParser.GetFlag(Args::Flags::Rename);
	const bool bConvertMode = argParser.GetFlag(Args::Flags::Convert);
	const bool bResizeMode = argParser.GetFlag(Args::Flags::Resize);
	const bool bScaleMode = argParser.GetFlag(Args::Flags::Scale);
	
	const std::array<bool, 4> modes = { bRenameMode, bConvertMode, bResizeMode, bScaleMode };
	const std::ptrdiff_t numActiveModes = std::count(std::begin(modes), std::end(modes), true);

	//if (!(bRenameMode ^ bConvertMode ^ bResizeMode ^ bScaleMode)) {
	if (numActiveModes != 1) {
		throw std::invalid_argument("Somente um modo pode estar ativo!");
	}

	// validar a pasta passada como a opção folder
  const std::string folder = argParser.GetOptionAs<const std::string&>(Args::Opts::Folder);
	if (folder.empty()) {
		throw std::invalid_argument("A pasta não pode estar em branco!");
	}

	if (!std::filesystem::exists(folder)) {
		throw std::invalid_argument("A pasta não existe!");
	}

	//validar se o filtro é uma string valida
	const std::string filter = argParser.GetOptionAs<const std::string&>(Args::Opts::Filter);
	if (!filter.empty()) {
		const std::string invalidCharacters = "\\/*?\"<>|:";
		if (filter.find_first_of(invalidCharacters) != std::string::npos) {
			throw std::invalid_argument("O filtro não pode conter os caracteres:" + invalidCharacters);
		}
	}
}

int main(int argc, char* argv[])
{
	setlocale(LC_ALL, "pt_BR");
	setlocale(LC_NUMERIC, "en_US");

	/*for (int i = 0; i < argc; ++i) {
		std::cout << argv[i] << std::endl;
	}*/

	//getchar();

	ArgumentParser argParser;
	argParser.RegisterFlag(Args::Flags::Rename);
	argParser.RegisterFlag(Args::Flags::Convert);
	argParser.RegisterFlag(Args::Flags::Resize);
	argParser.RegisterFlag(Args::Flags::Scale);
	argParser.RegisterOption(Args::Opts::Folder);
	argParser.RegisterOption(Args::Opts::Filter);

	argParser.Parse(argc, argv);

	try {
		ValidateArguments(argParser);
	} 
	catch (const std::exception& exception) {
		std::cerr << exception.what() << endl;
	}
	/*cout << boolalpha << "Rename : " << argParser.GetFlag(Args::Flags::Rename) << endl;
	cout << boolalpha << "Convert : " << argParser.GetFlag(Args::Flags::Convert) << endl;
	cout << boolalpha << "Resize : " << argParser.GetFlag(Args::Flags::Resize) << endl;
	cout << boolalpha << "Scale : " << argParser.GetFlag(Args::Flags::Scale) << endl;*/
	//cout << "Folder : " << argParser.GetOptionAs<const string&>("folder") << endl;
	//cout << "Amount (float): " << argParser.GetOptionAs<float>("amount") << endl;
	//cout << "Amount (int): " << argParser.GetOptionAs<int>("amount") << endl;

	return 0;
}