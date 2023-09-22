#include "ArgumentParser.h"

#include <iomanip>

#include "Utils.h"

//-------------------------------------------------------------------------

void ArgumentParser::RegisterFlag(
	const string& flag
)
{
	if (!flag.empty()) {
		m_Flags[flag] = false;
	}
}

//-------------------------------------------------------------------------

bool ArgumentParser::GetFlag(
	const string& flag
) const
{
	if (!flag.empty()) {
		auto flagIt = m_Flags.find(flag);

		if (flagIt != end(m_Flags)) {
			return flagIt->second;
		}
	}

	return false;
}

//-------------------------------------------------------------------------

void ArgumentParser::Parse(
	int argc,
	char* argv[]
)
{
	if (argc > 1) {
		for (int i = 1; i < argc; ++i) {
			//string arg = argv[i];
			string arg = Utils::ToLower(argv[i]);

			if (arg.length() >= 3) {
				//argumentos tem que ter pelo menos 3 caracteres
				// os "--" iniciais e pelo menos um terceiro caracter
				if (arg[0] == '-' && arg[1] == '-') {
					//--rename
					//primeiro remover os "--" iniciais
					arg = arg.substr(2);

					//depois do arg.substr: "rename"
					if (arg.find_first_of('=') != string::npos) {
						//é uma opção
					}
					else {
						// é uma flag
						auto flagIt = m_Flags.find(arg);

						if (flagIt != end(m_Flags)) {
							// encontrou a flag
							flagIt->second = true;
						}
					}
				}
			}
		}
	}
}

//-------------------------------------------------------------------------

void ArgumentParser::RegisterOption(
	const string& option
)
{
	if (!option.empty()) {
		m_Options[option] = "";
	}
}

//-------------------------------------------------------------------------

const string& ArgumentParser::GetOption(
	const string& option
) const
{
	if (!option.empty()) {
		auto optionIt = m_Options.find(option);

		if (optionIt != end(m_Options)) {
			return optionIt->second;
		}
	}

	static string emptyOption = "";

	return emptyOption;
}

//-------------------------------------------------------------------------
