#include "ResizeMode.h"

#include <stb_image.h>
#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include <stb_image_resize2.h>
#include <stb_image_write.h>
#include <iostream> 

//----------------------------------------------------------------------------------------------

ResizeMode::ResizeMode(
	const string& filter,
	const string& folder,
	int width,
	int heigth
) :
	Mode(filter, folder),
	m_Width(width),
  m_Heigth(heigth)
{
}

//----------------------------------------------------------------------------------------------

const string& ResizeMode::GetModeNome() const
{
	static const string resizeModeName = "[Redimensionar]";
	return resizeModeName;
}

//----------------------------------------------------------------------------------------------

void ResizeMode::RunImp()
{
	cout << GetModeNome() << "Modo           : Redimensionar" << endl;
	cout << GetModeNome() << "Pasta          : " << GetFolder() << endl;
	cout << GetModeNome() << "Filtro         : " << GetFilter() << endl;
	cout << GetModeNome() << "Comprimento    : " << m_Width << endl;
	cout << GetModeNome() << "Altura         : " << m_Heigth << endl;

	if (m_Width > 0 || m_Heigth > 0) {
		for (const filesystem::path& filePath : GetFiles()) {
			cout << GetModeNome() << "Redimensionando " << filePath << endl;
			ResizeImage(filePath, m_Width, m_Heigth);
		}
	}
}

//----------------------------------------------------------------------------------------------
#include <vector>
void ResizeMode::ResizeImage(
	const filesystem::path& filepath,
	int newWidth,
	int newHeigth
) const 
{
	int imputWidth = 0;
	int imputWHeight = 0;
	int imputNumComp = 0;
	int imputNumReq = 4;

	if (unsigned char* inputData = stbi_load(filepath.string().c_str(), &imputWidth, &imputWHeight, &imputNumComp, imputNumReq)) {
		const int numOutputPixel = newWidth * newHeigth * imputNumReq;
		vector<uint8_t> outputData(numOutputPixel, 0);

		unsigned char* resizeResult = stbir_resize_uint8_srgb(inputData, imputWidth, imputWHeight, 0,
			outputData.data(), newWidth, newHeigth, 0,
			STBIR_RGBA);

		if (resizeResult != nullptr) {
			const filesystem::path extension = filepath.extension();
			int writeResult = 1;
			if (extension == ".jpg") {
				writeResult = stbi_write_jpg(filepath.string().c_str(), newWidth, newHeigth, imputNumReq, outputData.data(), 50);
			}
			else if (extension == ".png") {
				writeResult = stbi_write_png(filepath.string().c_str(), newWidth, newHeigth, imputNumReq, outputData.data(), 0);
			}
			else {
				cout << GetModeNome() << "Formato não suportado " << filepath << endl;
			}

			if (writeResult == 0) {
				cout << GetModeNome() << "Erro ao escrever " << filepath << endl;
			}
		}
		else {
			cout << GetModeNome() << "Erro ao redimensionar " << filepath << endl;
		}

		stbi_image_free(inputData);
	}
	else {
		cout << GetModeNome() << "Erro ao carregar " << filepath << endl;
	}

}

//----------------------------------------------------------------------------------------------
