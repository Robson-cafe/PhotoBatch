#pragma once

#include <string>
#include <memory>

using namespace std;

class Mode
{
	public:
		Mode(
			const string& filter,
			const string& folder
		);

		const string& GetFilter() const;
		const string& GetFolder() const;

		virtual const string& GetModeNome() const = 0;

		void Run();

	protected:
		virtual void RunImp() = 0;

	private:
		string m_Filter;
		string m_Folder;
};

//----------------------------------------------------------------------------------------------
class ArgumentParser;
//----------------------------------------------------------------------------------------------

namespace Args
{
	namespace Flags
	{
		static constexpr const char* Rename = "rename";
		static constexpr const char* Convert = "convert";
		static constexpr const char* Resize = "resize";
		static constexpr const char* Scale = "scale";
		static constexpr const char* Help = "help";
	}

	namespace Opts
	{
		static constexpr const char* Folder = "folder";
		static constexpr const char* Filter = "filter";
		static constexpr const char* Width = "width";
		static constexpr const char* Heigth = "heigth";
		static constexpr const char* Amount = "amount";
		static constexpr const char* Prefix = "prefix";
		static constexpr const char* StartNumber = "startnumber";
		static constexpr const char* From = "from";
		static constexpr const char* To = "to";
	}
}

//----------------------------------------------------------------------------------------------

unique_ptr<Mode> CreateMode(
	const ArgumentParser& argParser
);

//----------------------------------------------------------------------------------------------
