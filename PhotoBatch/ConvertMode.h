#pragma once

#include "Mode.h"

#include <iostream> 

using namespace std;

//----------------------------------------------------------------------------------------------

class ConvertMode final : public Mode
{
	public:
		enum class Format
		{
			JPG,
			PNG
		};

		ConvertMode(
			const string& filter,
			const string& folder,
			Format from,
			Format to
		);

		const string& GetModeNome() const override;

	protected:
		void RunImp() override;

	private:
		Format m_To;
		Format m_From;
};

//----------------------------------------------------------------------------------------------
