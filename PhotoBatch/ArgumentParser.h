//#ifndef ARGUMENTPARSER_H_
//define ARGUMENTPARSER_H_
#pragma once

#include <string>
#include <map>

using namespace std;

//clasee usada para ler os argumentos da linha de comando
class ArgumentParser
{
public:
	//registra uma flag usada durante o parse
	void RegisterFlag(
		const string& flag
	);

	//obtem uma flag usada durante o parse
	bool GetFlag(
		const string& flag
	) const;

	//faz o parse da lisata de argumentos em argv
	void Parse(
		int argc,
		char* argv[]
	);

	//registra uma opção usada durante o parse
	void RegisterOption(
		const string& option
	);

	void SetHelpMessage(
		const string& message
	);

	const string& GetHelpMessage();

	template<typename T>
	T GetOptionAs(
		const string& option
	) const;
	template<>
	float GetOptionAs(const string& option) const { return GetOptionAsFloat(option); }

	template<>
	int GetOptionAs(const string& option) const { return GetOptionAsInt(option); }

	template<>
	const string& GetOptionAs(const string& option) const { return GetOption(option); }

private:
	//oter o valor de uma opção lida durante o parse
	const string& GetOption(
		const string& option
	) const;

	//obtem o valor de uma opção convertida para float
	float GetOptionAsFloat(
		const string& option
	) const;

	//obtem o valor de uma opção convertida para int
	int GetOptionAsInt(
		const string& option
	) const;

	map<string, bool> m_Flags;
	map<string, string> m_Options;
	string m_HelpMessage;
};


//#endif