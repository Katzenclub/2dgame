#pragma once
#include <iostream>

namespace geometry
{
	class MeineKlasse
	{
	public:
		MeineKlasse();
		~MeineKlasse();

		void update();
		void handle();

	private:

		int calcAnything();

		int m_member;
		int m_value;

	};


}