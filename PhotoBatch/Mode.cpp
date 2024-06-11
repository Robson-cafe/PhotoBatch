#include "Mode.h"

#include <array>
#include <chrono>
#include <filesystem>
#include <iostream>

#include "ArgumentParser.h"
#include "ConvertMode.h"
#include "RenameMode.h"
#include "ResizeMode.h"

using namespace std;

//----------------------------------------------------------------------------------------------

Mode::Mode(
	const string& filter,
	const string& folder
) : 
	m_Filter(filter),
	m_Folder(folder)
{
}

//----------------------------------------------------------------------------------------------

const string& Mode::GetFilter() const
{
	return m_Filter;
}

//----------------------------------------------------------------------------------------------

const string& Mode::GetFolder() const
{
	return m_Folder;
}

//----------------------------------------------------------------------------------------------

void Mode::Run()
{
	using ClockT = chrono::high_resolution_clock;
	ClockT::time_point startTime = ClockT::now();
	
	RunImp();

	ClockT::time_point endTime = ClockT::now();

	ClockT::duration elapsedTime = startTime - endTime;
	chrono::milliseconds elapsedTimeMs = chrono::duration_cast<chrono::milliseconds>(elapsedTime);

	cout << GetModeNome() << "Operação finalizada em " << elapsedTimeMs.count() << " ms" << endl;
}

//----------------------------------------------------------------------------------------------

vector<filesystem::path> Mode::GetFiles(
	const filesystem::path& extension
) const
{
	vector<filesystem::path> files;
	int numSkippeFiles = 0;

	for (const filesystem::directory_entry& entry : filesystem::directory_iterator(GetFolder())) {
		//verifica se é arquivo válido ou pasta
		const bool bIsFile = filesystem::is_regular_file(entry.path());
		const bool bMatchFilter = GetFilter().empty() || (entry.path().string().find(GetFilter()) != string::npos);
		const bool bMatchExtension = extension.empty() || entry.path().extension() == extension;

		if (bIsFile && bMatchFilter && bMatchExtension) {
			files.push_back(entry.path());
		}
		else {
			numSkippeFiles++;
		}
	}

	cout << GetModeNome() << "Numero de arquivos encontrados: " << files.size() << endl;
	cout << GetModeNome() << "Numero de arquivos ignorados  : " << numSkippeFiles << endl;

	return files;
}

//----------------------------------------------------------------------------------------------

const string& GetInvalidChars()
{
	static const std::basic_string invalidCharacters = "\\/*?\"<>|:";
	return invalidCharacters;
}

//----------------------------------------------------------------------------------------------

bool HasInvalidChars(
	const string& str
)
{
	return str.find_first_of(GetInvalidChars()) != string::npos;
}

//----------------------------------------------------------------------------------------------

unique_ptr<Mode> CreateMode(
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
		catch (const invalid_argument&) {
			throw invalid_argument("O valor informado para Width ou height não são números válidos");
		}

		if (width <= 0 || height <= 0) {
			throw invalid_argument("Width e Height devem ser maiores que zero");
		}

		if (filter.empty()) {
			throw invalid_argument("Filtro não pode estar em branco no modo Resize");
		}

		return make_unique<ResizeMode>(filter, folder, width, height);
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

		return make_unique<RenameMode>(filter, folder, prefix, startNumber);
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

		map<string, ConvertMode::Format> convertOptionsMap = {
			{ "jpg", ConvertMode::Format::JPG },
			{ "png", ConvertMode::Format::PNG }
		};

		return make_unique<ConvertMode>(filter, folder, convertOptionsMap.at(from), convertOptionsMap.at(to));
	}

	return nullptr;
}
