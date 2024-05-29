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
		static constexpr const char* Help = "help";
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

const string& GetInvalidChars()
{
	static const std::basic_string invalidCharacters = "\\/*?\"<>|:";
	return invalidCharacters;
}

bool HasInvalidChars(
	const string& str
)
{
	return str.find_first_of(GetInvalidChars()) != string::npos;
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
  const string folder = argParser.GetOptionAs<const string&>(Args::Opts::Folder);
	if (folder.empty()) {
		throw invalid_argument("A pasta não pode estar em branco!");
	}

	if (!std::filesystem::exists(folder)) {
		throw invalid_argument("A pasta não existe!");
	}

	//validar se o filtro é uma string valida
	const string filter = argParser.GetOptionAs<const string&>(Args::Opts::Filter);
	if (!filter.empty() && HasInvalidChars(filter)) {
		throw invalid_argument("O filtro não pode conter os caracteres:" + GetInvalidChars());
	}

	//validar o modo resize
	if (bResizeMode) {
		int width = 0;
		int height = 0;

		try {
			width = argParser.GetOptionAs<int>(Args::Opts::Width);
			height = argParser.GetOptionAs<int>(Args::Opts::Heigth);
		}
		catch (const invalid_argument&){
			throw invalid_argument("O valor informado para Width ou height não são números válidos");
		}

		if (width <= 0 || height <= 0) {
			throw invalid_argument("Width e Height devem ser maiores que zero");
		}

		if (filter.empty()) {
			throw invalid_argument("Filtro não pode estar em branco no modo Resize");
		}
	}

	//validar modo scale
	if (bScaleMode) {
		float amount = 0.0;
		try {
			amount = argParser.GetOptionAs<float>(Args::Opts::Amount);
		}
		catch (const invalid_argument&) {
			throw invalid_argument("O valor informado para Amount não são números válidos");
		}

		// no modo scala o amount deve ser maior que zero
		if (amount <= 0.0) {
			throw invalid_argument("Amount devem ser maior que zero");
		}

		if (filter.empty()) {
			throw invalid_argument("Filtro não pode estar em branco no modo Scale");
		}
	}

	//validar rename
	if (bRenameMode) {

		int startNumber = -1;

		try {
			startNumber = argParser.GetOptionAs<int>(Args::Opts::StartNumber);
		}
		catch (const invalid_argument&) {
			throw invalid_argument("O valor informado para StartNumber não é um número válido");
		}

		const string prefix = argParser.GetOptionAs<const string&>(Args::Opts::Prefix);

		if (startNumber < 0) {
			throw invalid_argument("StartNumber deve ser maior que zero");
		}

		if (prefix.empty() || HasInvalidChars(prefix)) {
			throw invalid_argument("O Prefixo não pode estar em branco e não pode conter os caractres " + GetInvalidChars());
		}
	}

	//validar convert
	if (bConvertMode) {
		const string from = argParser.GetOptionAs<const string&>(Args::Opts::From);
		const string to = argParser.GetOptionAs<const string&>(Args::Opts::To);
		const array<string, 2> optionsConvert = { "jpg", "png" };

		bool fromIsValid = find(begin(optionsConvert), end(optionsConvert), from) != end(optionsConvert);
		bool toIsValid = find(begin(optionsConvert), end(optionsConvert), to) != end(optionsConvert);

		if (!fromIsValid || !toIsValid) {
			throw invalid_argument("Extensão válida apenas em jpg e png");
		}

		if (from == to) {
			throw invalid_argument("Extensão para conversão são iguais");
		}
	}
}

int main(int argc, const char* argv[])
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
	argParser.RegisterFlag(Args::Flags::Help);

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

	argParser.SetHelpMessage(R"([USO]: Photobatch --[Rename|Convert|Resize|Scale] [Opções]
    O Photobatch possui 4 operações. Somente um modo pode estar ativo.
    Para ativar um modulo escolha uma das flags:

    --Rename  : Ativa o modulo para renomear arquivos
    --Convert : Ativa o modulo para converter arquivos
    --Resize  : Ativa o modulo para redimensionar arquivos
    --Scale   : Ativa o modulo para escalar arquivos

    As seguintes opções são comuns a todos os modos:
    --Folder  : Especifica a pasta onde o PhotoBatch irá atuar
    --Filter  : Especifica o filtro usado para selecionar arquivos

Opções do modo Rename:

    No modo Rename, cada arquivo selecionado será renomeado para o formato
    <Prefix>_<N>.<ext>, onde <Prefix> e <N> são especificados através de opções.
    <ext> é a extensão do arquivo que permanece inalterada.

    --Prefix=<Prefix> : Prefixo usado ao renomear os arquivos
    --StartNumber=<N> : Número inicial a ser adicionado em cada arquivo que for renomeado

Opções do modo Convert:

    No modo Convert, cada arquivo selecionado será convertido do formato <from> para
    o formato <to>. <from> e <to> não podem ser iguais. O nome do arquivo permanece
    inalterado.

    --From=<jpg|png> : Extensão de origem para conversão
    --To=<jpg|png>   : Extensão de destino para conversão

Opções do modo Resize:

    No modo Resize, cada arquivo selecionado será redimensionado para as dimensões
    especificadas nas seguintes opções. Note que N >= 1.

    --Width=<N>  : Novo comprimento da imagem
    --Height=<N> : Nova altura da imagem

Opções do modo Scale:

    No modo Scale, cada arquivo selecionado será escalado uniformemente pelo
    fator especificado pelas seguintes opções. Note que N > 0 e será interpretado
    como um número em ponto flutuante.

    --Amount=<N> : Fator de escala a ser aplicado em cada imagem selecionada.

Exemplos de uso:

    Renomear todos os arquivos da pasta "C:\Viagem" com a extensão ".png" para Viagem_N.png, onde N começa do 0

	    PhotoBatch --Rename --Folder="C:\Viagem" --Filter=".png" --StartNumber=0

    Redimensionar todos os arquivos na pasta "C:\Viagem" com a extensão ".jpg" para o tamanho 500x500

        PhotoBatch --Resize --Folder="C:\Viagem" --Filter=".jpg" --Width=500 --Height=500

    Converter todos os arquivos da pasta "C:\Viagem" de "png" para "jpg"

        PhotoBatch --Convert --Folder="C:\Viagem" --From=png --To=jpg

    Reduzir o pela metade o tamanho de todos os arquivos "png" da pasta "C:\Viagem"

        PhotoBatch --Scale --Folder="C:\Viagem" --Filter=".png" --Amount=0.5)");

	argParser.Parse(argc, argv);

	if (argParser.GetFlag(Args::Flags::Help)) {
		cout << argParser.GetHelpMessage() << endl;
	}
	else {
		try {
			ValidateArguments(argParser);
		} 
		catch (const std::exception& exception) {
			cerr << "Erro:" << exception.what() << endl;
			cerr << "Para maiores informações rode o Photobach com a flag --help" << endl;
		}
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