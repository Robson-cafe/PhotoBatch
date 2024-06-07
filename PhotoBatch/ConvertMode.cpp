#include "ConvertMode.h"

#include <iostream> 

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <stb_image_write.h>

//----------------------------------------------------------------------------------------------

using namespace std;

string ToString(
	ConvertMode::Format format
)
{
	switch (format) {
	case ConvertMode::Format::JPG:
		return "jpg";
	case ConvertMode::Format::PNG:
		return "png";
	}

	return "";
}

ostream& operator<< (ostream& out, ConvertMode::Format format) {
	
	return out << ToString(format);
}

//----------------------------------------------------------------------------------------------

ConvertMode::ConvertMode(
	const string& filter,
	const string& folder,
	Format from,
	Format to
)
	:
	Mode(filter, folder),
	m_From(from),
	m_To(to)
{
}

//----------------------------------------------------------------------------------------------

const string& ConvertMode::GetModeNome() const
{
	static const string convertModeName = "[Converter]: ";
	return convertModeName;
}

//----------------------------------------------------------------------------------------------

void ConvertMode::RunImp()
{
	cout << GetModeNome() << "Modo     : Converter" << endl;
	cout << GetModeNome() << "Pasta    : " << GetFolder() << endl;
	cout << GetModeNome() << "Filtro   : " << GetFilter() << endl;
	cout << GetModeNome() << "Origem   : " << m_From << endl;
	cout << GetModeNome() << "Destino  : " << m_To << endl;

	const filesystem::path fromExtension = "." + ToString(m_From);

	for (const filesystem::path& filePath : GetFiles()) {
		cout << GetModeNome() << "Convertendo " << filePath << endl;

		int width = 0;
		int height = 0;
		int numCom = 0;
		const int numReqCom = 3;

		if (unsigned char* data = stbi_load(filePath.string().c_str(), &width, &height, &numCom, numReqCom)) {

			filesystem::path destFilePath = filePath;
			destFilePath.replace_extension(ToString(m_To));

			int writeResult = 0;
			switch (m_To)
			{
				case ConvertMode::Format::JPG:
					writeResult = stbi_write_jpg(destFilePath.string().c_str(), width, height, numCom, data, 50);
					break;
				case ConvertMode::Format::PNG:
					writeResult = stbi_write_png(destFilePath.string().c_str(), width, height, numCom, data, 0);
					break;
				default:
					break;
			}

			if (writeResult == 0) {
				cout << GetModeNome() << "Erro o converter " << filePath << endl;
			}

			stbi_image_free(data);
		}
		else {
			cout << GetModeNome() << "Erro ao carregar " << filePath << endl;
		}
	}
}

//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------

