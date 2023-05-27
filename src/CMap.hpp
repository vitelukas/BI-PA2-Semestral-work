#include <string>
#pragma once

class CMap {
	public:
		CMap();

		bool load ( const std::string & filename );

	private:
		size_t m_Height;
		size_t m_Width;
};