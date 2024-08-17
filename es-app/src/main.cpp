//EmulationStation, a graphical front-end for ROM browsing. Created by Alec "Aloshi" Lofquist.
//http://www.aloshi.com

#include "guis/GuiDetectDevice.h"
#include "guis/GuiMsgBox.h"
#include "utils/FileSystemUtil.h"
#include "utils/ProfilingUtil.h"
#include "views/ViewController.h"
#include "CollectionSystemManager.h"
#include "EmulationStation.h"
#include "InputManager.h"
#include "Log.h"
#include "MameNames.h"
#include "platform.h"
#include "PowerSaver.h"
#include "ScraperCmdLine.h"
#include "Settings.h"
#include "SystemData.h"
#include "SystemScreenSaver.h"
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

	return 0;
}
