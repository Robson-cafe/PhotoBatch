#include "ScaleMode.h"

#include <stb_image.h>

#include <iostream> 

//----------------------------------------------------------------------------------------------

ScaleMode::ScaleMode(
	const string& filter,
	const string& folder,
	float scaleFactor
)
	:
	ResizeMode(filter, folder),
	m_ScaleFactor(scaleFactor)
{
}

//----------------------------------------------------------------------------------------------

const string& ScaleMode::GetModeNome() const
{
	static const string scaleModeName = "[Escalar]:";
	return scaleModeName;
}

//----------------------------------------------------------------------------------------------

void ScaleMode::RunImp()
{
	cout << GetModeNome() << "Modo           : Escalar" << endl;
	cout << GetModeNome() << "Pasta          : " << GetFolder() << endl;
	cout << GetModeNome() << "Filtro         : "	 << GetFilter() << endl;
	cout << GetModeNome() << "Fator          : " << m_ScaleFactor << endl;

	for (const filesystem::path& filePath : GetFiles()) {
		cout << GetModeNome() << "Escalando o " << filePath << endl;

		int imputWidth = 0;
		int imputWHeight = 0;
		int imputNumComp = 0;
		
		stbi_info(filePath.string().c_str(), &imputWidth, &imputWHeight, &imputNumComp);
		const int newWidth = static_cast<int>(imputWidth * m_ScaleFactor);
		const int newHeight = static_cast<int>(imputWHeight * m_ScaleFactor);

		ResizeImage(filePath, newWidth, newHeight);
	}
}

//----------------------------------------------------------------------------------------------
