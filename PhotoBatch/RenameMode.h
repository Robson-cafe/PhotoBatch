#pragma once

#include "Mode.h"

//----------------------------------------------------------------------------------------------

class RenameMode : public Mode
{
	public:
		RenameMode(
			const string& filter,
			const string& folder,
			const string& prefix,
			int startNumber
		);

		const string& GetModeNome() const override;

	protected:
		void RunImp() override;

	private:
		string m_Prefix;
		int m_StartNumber;
};
