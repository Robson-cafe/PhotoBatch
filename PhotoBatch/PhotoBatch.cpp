#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>
#include <array>
#include <filesystem>
#include <string>

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
		static constexpr const char* Width = "width";
		static constexpr const char* Heigth = "heigth";
		static constexpr const char* Amount = "amount";
		static constexpr const char* Prefix = "prefix";
		static constexpr const char* StartNumber = "startnumber";
		static constexpr const char* From = "from";
		static constexpr const char* To = "to";
	}
}

const std::string& GetInvalidChars()
{
	static const std::basic_string invalidCharacters = "\\/*?\"<>|:";
	return invalidCharacters;
}

bool HasInvalidChars(
	const std::string& str
)
{
	return str.find_first_of(GetInvalidChars()) != std::string::npos;
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
	if (!filter.empty() && HasInvalidChars(filter)) {
		throw std::invalid_argument("O filtro não pode conter os caracteres:" + GetInvalidChars());
	}

	//validar o modo resize
	if (bResizeMode) {
		int width = 0;
		int height = 0;

		try {
			width = argParser.GetOptionAs<int>(Args::Opts::Width);
			height = argParser.GetOptionAs<int>(Args::Opts::Heigth);
		}
		catch (const std::invalid_argument&){
			throw std::invalid_argument("O valor informado para Width ou height não são números válidos");
		}

		if (width <= 0 || height <= 0) {
			throw std::invalid_argument("Width e Height devem ser maiores que zero");
		}

		if (filter.empty()) {
			throw std::invalid_argument("Filtro não pode estar em branco no modo Resize");
		}
	}

	//validar modo scale
	if (bScaleMode) {
		float amount = 0.0;
		try {
			amount = argParser.GetOptionAs<float>(Args::Opts::Amount);
		}
		catch (const std::invalid_argument&) {
			throw std::invalid_argument("O valor informado para Amount não são números válidos");
		}

		// no modo scala o amount deve ser maior que zero
		if (amount <= 0.0) {
			throw std::invalid_argument("Amount devem ser maior que zero");
		}

		if (filter.empty()) {
			throw std::invalid_argument("Filtro não pode estar em branco no modo Scale");
		}
	}

	//validar rename
	if (bRenameMode) {

		int startNumber = -1;

		try {
			startNumber = argParser.GetOptionAs<int>(Args::Opts::StartNumber);
		}
		catch (const std::invalid_argument&) {
			throw std::invalid_argument("O valor informado para StartNumber não é um número válido");
		}

		const std::string prefix = argParser.GetOptionAs<const std::string&>(Args::Opts::Prefix);

		if (startNumber < 0) {
			throw std::invalid_argument("StartNumber deve ser maior que zero");
		}

		if (prefix.empty() || HasInvalidChars(prefix)) {
			throw std::invalid_argument("O Prefixo não pode estar em branco e não pode conter os caractres " + GetInvalidChars());
		}

		
		
	}

	//validar convert
	if (bConvertMode) {
		const std::string from = argParser.GetOptionAs<const std::string&>(Args::Opts::From);
		const std::string to = argParser.GetOptionAs<const std::string&>(Args::Opts::To);
		const std::array<std::string, 2> optionsConvert = { "jpg", "png" };

		bool fromIsValid = std::find(std::begin(optionsConvert), std::end(optionsConvert), from) != std::end(optionsConvert);
		bool toIsValid = std::find(std::begin(optionsConvert), std::end(optionsConvert), to) != std::end(optionsConvert);

		if (!fromIsValid || !toIsValid) {
			throw std::invalid_argument("Extensão válida apenas em jpg e png");
		}

		if (from == to) {
			throw std::invalid_argument("Extensão para conversão são iguais");
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
	//registra flags
	argParser.RegisterFlag(Args::Flags::Rename);
	argParser.RegisterFlag(Args::Flags::Convert);
	argParser.RegisterFlag(Args::Flags::Resize);
	argParser.RegisterFlag(Args::Flags::Scale);

	//registra opções
	argParser.RegisterOption(Args::Opts::Folder);
	argParser.RegisterOption(Args::Opts::Filter);
	argParser.RegisterOption(Args::Opts::Width);
	argParser.RegisterOption(Args::Opts::Heigth);
	argParser.RegisterOption(Args::Opts::Amount);
	argParser.RegisterOption(Args::Opts::Prefix);
	argParser.RegisterOption(Args::Opts::StartNumber);
	argParser.RegisterOption(Args::Opts::From);
	argParser.RegisterOption(Args::Opts::To);

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