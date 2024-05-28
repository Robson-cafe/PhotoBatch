#include "ArgumentParser.h"

#include <iomanip>

#include "Utils.h"

//-------------------------------------------------------------------------

void ArgumentParser::RegisterFlag(
	const string& flag
)
{
	if (!flag.empty() && !Utils::HasWhiteSpace(flag)) {
		m_Flags[flag] = false;
	}
}

//-------------------------------------------------------------------------

bool ArgumentParser::IsFlagRegistered(
	const std::string& flag
)
{
	if (!flag.empty()) {
		return m_Flags.count(flag) == 1;
	}

	return false;
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
	const char* argv[]
)
{
	if (argc > 1 && argv != nullptr) {
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
						const size_t equalSignPos = arg.find('=');

						if (equalSignPos != string::npos) {
							//divide opção em chave valor
							string optionName = arg.substr(0, equalSignPos);
							string optionValue = arg.substr(equalSignPos + 1);

							auto optionIt = m_Options.find(optionName);

							if (optionIt != end(m_Options)) {
								//achou uma opção registrada
								optionIt->second = optionValue;
							}

						}
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
	if (!option.empty() && !Utils::HasWhiteSpace(option)) {
		m_Options[option] = "";
	}
}

//-------------------------------------------------------------------------

bool ArgumentParser::IsOptionRegistered(
	const string& option
)
{
	if (!option.empty()) {
		return m_Options.count(option) == 1;
	}

	return false;
}

//-------------------------------------------------------------------------

void ArgumentParser::SetHelpMessage(const string& message)
{
	m_HelpMessage = message;
}

//-------------------------------------------------------------------------

const string& ArgumentParser::GetHelpMessage()
{
	return m_HelpMessage;
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

float ArgumentParser::GetOptionAsFloat(
	const string& option
) const
{
	const string& optionValue = GetOption(option);

	if (!optionValue.empty()) {
		return stof(optionValue);
	}
	return -1;
}

//-------------------------------------------------------------------------

int ArgumentParser::GetOptionAsInt(const string& option) const
{
	const string& optionValue = GetOption(option);

	if (!optionValue.empty()) {
		return stoi(optionValue);
	}
	return -1;
}

//-------------------------------------------------------------------------
