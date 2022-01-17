#include <iostream>
#include "MyClass.h"

int main()
{
	// Snakecase -> Hallo Welt -> hallo_welt
	// Camelcase -> Hallo Welt -> halloWelt
	//				Hallo Welt -> HALLOWELT

	geometry::MeineKlasse *l_meine_klasse = new geometry::MeineKlasse();
	
	while (true)
	{
		l_meine_klasse->update();
		l_meine_klasse->handle();
	}

	delete l_meine_klasse;

	std::cout << "Hallowelt" << std::endl;
}