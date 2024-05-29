#pragma once

#include <string>

using namespace std;

class Mode
{
	public:
		Mode(
			string& filter,
			string& folder
		);

		const string& GetFilter();
		const string& GetFolder();

		virtual const string& GetModeNome() const = 0;

		void Run();

	protected:
		virtual void RunImp() = 0;

		string m_Filter;
		string m_Folder;
};