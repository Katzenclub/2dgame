#include "MyClass.h"

geometry::MeineKlasse::MeineKlasse()
{
	std::cout << "ich wurde erstellt!" << std::endl;
	m_member = 10;
	m_value = 50;
}

geometry::MeineKlasse::~MeineKlasse()
{
	std::cout << "ich wurde geloescht!" << std::endl;
}

void geometry::MeineKlasse::update()
{
	std::cout << "ich werde geupdated" << std::endl;
}

void geometry::MeineKlasse::handle()
{
}

int geometry::MeineKlasse::calcAnything()
{
	return 0;
}
