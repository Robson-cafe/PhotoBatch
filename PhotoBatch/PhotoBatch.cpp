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
//	std::cout << "Olá Mundo!!!" << std::endl;
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
			if (unique_ptr<Mode> photoBach = CreateMode(argParser)) {
				photoBach->Run();
			}
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