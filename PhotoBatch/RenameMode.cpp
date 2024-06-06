#include"RenameMode.h"

#include <iostream>
#include <filesystem>

using namespace std;

RenameMode::RenameMode(
	const string& filter,
	const string& folder,
	const string& prefix,
	int startNumber
) :
	Mode(filter, folder),
	m_Prefix(prefix),
	m_StartNumber(startNumber)
{
}

//----------------------------------------------------------------------------------------------

const string& RenameMode::GetModeNome() const
{
	static const string renameModeName = "[Renomear]";
	return renameModeName;
}

//----------------------------------------------------------------------------------------------

void RenameMode::RunImp()
{
	cout << GetModeNome() << "Modo           : Renomear" << endl;
	cout << GetModeNome() << "Pasta          : " << GetFolder() << endl;
	cout << GetModeNome() << "Filtro         : " << GetFilter() << endl;
	cout << GetModeNome() << "Prefixo        : " << m_Prefix << endl;
	cout << GetModeNome() << "Número inicial : " << m_StartNumber << endl;

	vector<filesystem::path> filesToRaname;
	int numSkippeFiles = 0;

	for (const filesystem::directory_entry& entry : filesystem::directory_iterator(GetFolder())) {
		//verifica se é arquivo válido ou pasta
		const bool bIsFile = filesystem::is_regular_file(entry.path());
		const bool bMatchFilter = GetFilter().empty() || (entry.path().string().find(GetFilter()) != string::npos);

		if (bIsFile && bMatchFilter) {
			filesToRaname.push_back(entry.path());
		}
		else {
			numSkippeFiles++;
		}	
	}

	cout << GetModeNome() << "Numero de arquivos encontrados: " << filesToRaname.size() << endl;
	cout << GetModeNome() << "Numero de arquivos ignorados  : " << numSkippeFiles << endl;

	//renomeando
	int currentNumber = m_StartNumber;
	for (const filesystem::path& filePath : filesToRaname) {
		filesystem::path extension = filePath.extension();
		string newFileName = m_Prefix + to_string(currentNumber) + extension.string();

		filesystem::path newFilePath = filePath;
		newFilePath.replace_filename(newFileName);

		try {
			filesystem::rename(filePath, newFilePath);
			cout << GetModeNome() << filePath << "->" << newFilePath << endl;
		}
		catch (exception& exception) {
			cout << GetModeNome() << "Erro ao renomear \"" << filePath << "\":" << exception.what() << endl;
		}

		currentNumber++;
	}
}
