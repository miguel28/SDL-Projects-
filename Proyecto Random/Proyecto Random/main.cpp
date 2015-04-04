#include "MikeLibrary.h"

#define WIDTH 640
#define HEIGHT 480
#define BPP 4
#define DEPTH 32

PadType Pad;
MouseType Mouse;

int main(int argc, char* argv[])
{
    SDL_Surface *screen;

    if (SDL_Init(SDL_INIT_VIDEO) < 0 ) return 1;
	
	MK_Background MoonLight((char*)"MoonLight.png",NULL,0,640, 480);
	
    if (!(screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_HWSURFACE|SDL_DOUBLEBUF)))
    {
        SDL_Quit();
        return 1;
    }

    while(1) 
    {
		
		MoonLight.DrawBackground(screen);
		
		CheckKeyboardMouse();
		
		MoonLight.y+=(Pad.Held.Down-Pad.Held.Up);
		MoonLight.x+=(Pad.Held.Right-Pad.Held.Left);
		
		SDL_Flip(screen); 
		
    }
	
    SDL_Quit();
	
    return 0;
}




