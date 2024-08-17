//EmulationStation, a graphical front-end for ROM browsing. Created by Alec "Aloshi" Lofquist.
//http://www.aloshi.com

#include <SDL_events.h>
#include <SDL_main.h>
#include <SDL_timer.h>
#include <iostream>
#include <time.h>
#ifdef WIN32
#include <Windows.h>
#endif

int main(int argc, char* argv[])
{
	std::locale::global(std::locale("C"));

	cout << "main() start" << endl;


	cout << "main() end" << endl;

	return 0;
}
