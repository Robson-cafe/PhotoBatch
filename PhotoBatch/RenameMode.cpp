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

	//renomeando
	int currentNumber = m_StartNumber;
	for (const filesystem::path& filePath : GetFiles()) {
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
