#pragma once

#include "Mode.h"

class ResizeMode : public Mode
{
	public:
		ResizeMode(
			const string& filter,
			const string& folder,
			int width = -1,
			int heigth = -1
		);

		const string& GetModeNome() const override;

		protected:
			void RunImp() override;

			void ResizeImage(
				const filesystem::path& filepath,
				int newWidth,
				int newHeigth
			) const;

			int m_Width;
			int m_Heigth;
};