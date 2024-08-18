//EmulationStation, a graphical front-end for ROM browsing. Created by Alec "Aloshi" Lofquist.
//http://www.aloshi.com

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_events.h>
#include <SDL_main.h>
#include <SDL_timer.h>
#include <iostream>
#include <time.h>
#include <Windows.h>
#include <stdlib.h>

#include "renderers/Renderer.h"

using namespace std;

SDL_Window* sdlWindow = nullptr;
SDL_GLContext sdlContext = nullptr;
int windowWidth = 0;
int windowHeight = 0;
int screenWidth = 0;
int screenHeight = 0;
int screenOffsetX = 0;
int screenOffsetY = 0;
int screenRotate = 0;
bool initialCursorState = 1;
GLuint whiteTexture = 0;

inline SDL_Window* getSDLWindow()
{
	return sdlWindow;
}

float rn()
{
	return ((rand() / 32767.0) - 0.5) / 10.0;
}

void swapBuffers()
{
	cout << "Renderer::swapBuffers() start" << endl;

	SDL_GL_SwapWindow(getSDLWindow());
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	cout << "Renderer::swapBuffers() end" << endl;
}

int main(int argc, char* argv[])
{
	std::locale::global(std::locale("C"));

	cout << "main() start" << endl;

	cout << "Renderer::init() start" << endl;

	cout << "Renderer::createWindow() start" << endl;

	if(SDL_Init(SDL_INIT_VIDEO) != 0){
		cout << "Error initializing SDL!\n	" << SDL_GetError() << endl;
		return 1;
	}

	initialCursorState = (SDL_ShowCursor(0) != 0);

	int displays = SDL_GetNumVideoDisplays();
	for(int i = 0; i < displays; ++i){
		SDL_Rect rc;
		SDL_GetDisplayBounds(i, &rc);
		cout << "Monitor #" << i << " x:" << rc.x << " y:" << rc.y << " w:" << rc.w << " h:" << rc.h << endl;
	}

	int displayIndex = 0;

	if(argc >= 1){
		displayIndex = atoi(argv[1]);
	}

	if(displayIndex < 0 || displayIndex >= SDL_GetNumVideoDisplays()){
		displayIndex = 0;
	}

	cout << "displayIndex:" << displayIndex << endl;

	SDL_DisplayMode dispMode;
	SDL_GetDesktopDisplayMode(displayIndex, &dispMode);
	windowWidth   = dispMode.w;
	windowHeight  = dispMode.h;
	screenWidth   = windowWidth;
	screenHeight  = windowHeight;
	screenOffsetX = 0;
	screenOffsetY = 0;
	screenRotate  = 0;

	cout << "Renderer::setupWindow() start" << endl;
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,  SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE,           8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,         8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,          8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,        24);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,       1);
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	cout << "Renderer::setupWindow() end" << endl;

	const unsigned int windowFlags = SDL_WINDOW_FULLSCREEN | SDL_WINDOW_OPENGL;

	if((sdlWindow = SDL_CreateWindow("EmulationStation", SDL_WINDOWPOS_UNDEFINED_DISPLAY(displayIndex), SDL_WINDOWPOS_UNDEFINED_DISPLAY(displayIndex), windowWidth, windowHeight, windowFlags)) == nullptr)
	{
		cout << "Error creating SDL window!\n\t" << SDL_GetError() << endl;
		return false;
	}

	cout << "Created window successfully." << endl;

	cout << "Renderer::createContext() start" << endl;
	sdlContext = SDL_GL_CreateContext(sdlWindow);
	SDL_GL_MakeCurrent(sdlWindow, sdlContext);

	const std::string vendor     = glGetString(GL_VENDOR)     ? (const char*)glGetString(GL_VENDOR)     : "";
	const std::string renderer   = glGetString(GL_RENDERER)   ? (const char*)glGetString(GL_RENDERER)   : "";
	const std::string version    = glGetString(GL_VERSION)    ? (const char*)glGetString(GL_VERSION)    : "";
	const std::string extensions = glGetString(GL_EXTENSIONS) ? (const char*)glGetString(GL_EXTENSIONS) : "";

	cout << "GL vendor:   " << vendor << endl;
	cout << "GL renderer: " << renderer << endl;
	cout << "GL version:  " << version << endl;
	cout << "Checking available OpenGL extensions..." << endl;
	cout << " ARB_texture_non_power_of_two: " << (extensions.find("ARB_texture_non_power_of_two") != std::string::npos ? "ok" : "MISSING") << endl;

	const uint8_t data[4] = {255, 255, 255, 255};
	// whiteTexture = createTexture(Texture::RGBA, false, true, 1, 1, data);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	cout << "Renderer::createContext() end" << endl;
	// setIcon();
	cout << "Renderer::setSwapInterval() start" << endl;
	if(SDL_GL_SetSwapInterval(1) != 0)
		cout << "Tried to enable vsync, but failed! (" << SDL_GetError() << ")" << endl;
	cout << "Renderer::setSwapInterval() end" << endl;

	cout << "Renderer::createWindow() end" << endl;

	cout << "Renderer::setViewport() start" << endl;
	//setViewport(viewport);
	cout << "Renderer::setViewport() end" << endl;

	cout << "Renderer::setProjection() start" << endl;
	//setProjection(projection);
	cout << "Renderer::setProjection() end" << endl;

	swapBuffers();

	cout << "Renderer::init() end" << endl;

	////////

	SDL_Event
		event;
	int
		frame = 0;
	bool
		quit = false;

	while(!quit){
		while(SDL_PollEvent(&event)){
			if(event.type == SDL_KEYDOWN){
				switch(event.key.keysym.sym){
				case SDLK_ESCAPE:
					quit = true;
					break;
				}
			}else if(event.type == SDL_QUIT){
				quit = true;
			}
		}

		switch(frame++){
		case 0:
			glBegin(GL_QUADS);
			glVertex2f(-0.5f + rn(), -0.5f + rn());
			glVertex2f(0.5f + rn(), -0.5f + rn());
			glVertex2f(0.5f + rn(), 0.5f + rn());
			glVertex2f(-0.5f + rn(), 0.5f + rn());
			glEnd();
			break;
		case 1:
			// NOP
			break;
		default:
			frame = 0;
		}

		swapBuffers();
	}

	////////

	cout << "Renderer::destroyWindow() start" << endl;

	cout << "Renderer::destroyContext() start" << endl;
	SDL_GL_DeleteContext(sdlContext);
	cout << "Renderer::destroyContext() end" << endl;

	SDL_DestroyWindow(sdlWindow);
	SDL_ShowCursor(initialCursorState);
	SDL_Quit();
	cout << "Renderer::destroyWindow() end" << endl;

	cout << "main() end" << endl;

	return 0;
}
