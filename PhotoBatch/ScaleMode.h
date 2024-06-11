#pragma once

#include "ResizeMode.h"

class ScaleMode final : public ResizeMode
{
	public:
		ScaleMode(
			const string& filter,
			const string& folder,
			float scaleFactor);

		const string& GetModeNome() const override;

	protected:
		void RunImp() override;

	private:
		float m_ScaleFactor;
};
