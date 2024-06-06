#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>
#include <string>

#include "ArgumentParser.h"
#include "Mode.h"

using namespace std;

//-------------------------------------------------------------------------

//int main()
//{
//	setlocale(LC_ALL, "pt_BR");
//
//	std::cout << "Hello World!!!" << std::endl;
//	std::cout << "Ol� Mundo!!!" << std::endl;
//
//	return 0;
//}


int main(int argc, const char* argv[])
{
	setlocale(LC_ALL, "pt_BR");
	setlocale(LC_NUMERIC, "en_US");

	/*for (int i = 0; i < argc; ++i) {
		std::cout << argv[i] << std::endl;
	}*/

	//getchar();

	//teste
	/*auto mode = new RenameMode("Filtro", "Pasta", "Prefixo", 1);

	if (mode != nullptr) {
		cout << mode->GetModeNome() << endl;
		mode->Run();
	}
	return 0;*/
	ArgumentParser argParser;
	//registra flags
	argParser.RegisterFlag(Args::Flags::Rename);
	argParser.RegisterFlag(Args::Flags::Convert);
	argParser.RegisterFlag(Args::Flags::Resize);
	argParser.RegisterFlag(Args::Flags::Scale);
	argParser.RegisterFlag(Args::Flags::Help);

	//registra op��es
	argParser.RegisterOption(Args::Opts::Folder);
	argParser.RegisterOption(Args::Opts::Filter);
	argParser.RegisterOption(Args::Opts::Width);
	argParser.RegisterOption(Args::Opts::Heigth);
	argParser.RegisterOption(Args::Opts::Amount);
	argParser.RegisterOption(Args::Opts::Prefix);
	argParser.RegisterOption(Args::Opts::StartNumber);
	argParser.RegisterOption(Args::Opts::From);
	argParser.RegisterOption(Args::Opts::To);

	argParser.SetHelpMessage(R"([USO]: Photobatch --[Rename|Convert|Resize|Scale] [Op��es]
    O Photobatch possui 4 opera��es. Somente um modo pode estar ativo.
    Para ativar um modulo escolha uma das flags:

    --Rename  : Ativa o modulo para renomear arquivos
    --Convert : Ativa o modulo para converter arquivos
    --Resize  : Ativa o modulo para redimensionar arquivos
    --Scale   : Ativa o modulo para escalar arquivos

    As seguintes op��es s�o comuns a todos os modos:
    --Folder  : Especifica a pasta onde o PhotoBatch ir� atuar
    --Filter  : Especifica o filtro usado para selecionar arquivos

Op��es do modo Rename:

    No modo Rename, cada arquivo selecionado ser� renomeado para o formato
    <Prefix>_<N>.<ext>, onde <Prefix> e <N> s�o especificados atrav�s de op��es.
    <ext> � a extens�o do arquivo que permanece inalterada.

    --Prefix=<Prefix> : Prefixo usado ao renomear os arquivos
    --StartNumber=<N> : N�mero inicial a ser adicionado em cada arquivo que for renomeado

Op��es do modo Convert:

    No modo Convert, cada arquivo selecionado ser� convertido do formato <from> para
    o formato <to>. <from> e <to> n�o podem ser iguais. O nome do arquivo permanece
    inalterado.

    --From=<jpg|png> : Extens�o de origem para convers�o
    --To=<jpg|png>   : Extens�o de destino para convers�o

Op��es do modo Resize:

    No modo Resize, cada arquivo selecionado ser� redimensionado para as dimens�es
    especificadas nas seguintes op��es. Note que N >= 1.

    --Width=<N>  : Novo comprimento da imagem
    --Height=<N> : Nova altura da imagem

Op��es do modo Scale:

    No modo Scale, cada arquivo selecionado ser� escalado uniformemente pelo
    fator especificado pelas seguintes op��es. Note que N > 0 e ser� interpretado
    como um n�mero em ponto flutuante.

    --Amount=<N> : Fator de escala a ser aplicado em cada imagem selecionada.

Exemplos de uso:

    Renomear todos os arquivos da pasta "C:\Viagem" com a extens�o ".png" para Viagem_N.png, onde N come�a do 0

	    PhotoBatch --Rename --Folder="C:\Viagem" --Filter=".png" --StartNumber=0

    Redimensionar todos os arquivos na pasta "C:\Viagem" com a extens�o ".jpg" para o tamanho 500x500

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
			if (unique_ptr<Mode> photoBach = CreateMode(argParser)) {
				photoBach->Run();
			}
		} 
		catch (const std::exception& exception) {
			cerr << "Erro:" << exception.what() << endl;
			cerr << "Para maiores informa��es rode o Photobach com a flag --help" << endl;
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