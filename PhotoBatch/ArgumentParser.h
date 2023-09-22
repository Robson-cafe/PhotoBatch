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
	void RegisterFlag(
		const string& flag
	);

	bool GetFlag(
		const string& flag
	) const;

	void Parse(
		int argc,
		char* argv[]
	);

private:
	map<string, bool> m_Flags;
};


//#endif