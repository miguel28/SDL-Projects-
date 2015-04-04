#include "MikeLibrary.h"

#define WIDTH 854
#define HEIGHT 480
#define BPP 4
#define DEPTH 32

PadType Pad;
MouseType Mouse;

int main(int argc, char* argv[])
{
    SDL_Surface *screen;

    if (SDL_Init(SDL_INIT_VIDEO) < 0 ) return 1;
	TTF_Init();
	TTF_Font *font;
	
	MK_FPSInit();
	
	font = TTF_OpenFont("arial.ttf",20);
	if(font==NULL)exit(1);
	
	
	SDL_Color color={255,255,255};
	SDL_Surface *fontsurf = TTF_RenderText_Solid(font,"Hola \n jeje",color);
	
	MK_Sprite Sprite((char*)"Fighter.bmp",TRANSPARENT,1,48,48,3,5);
	MK_Background Background((char*)"bosque.mpf",NULL,0,854, 480);
	MK_Background Niebla((char*)"Niebla.bmp",NULL,0,854, 480);
	Niebla.Alpha=128;
	Background.CreateGfxEffect(Background.Graphic->w, Background.Graphic->h);
	
	
	SDL_Surface *NewSurface2 = IMG_Load("Gradient.png");
	
	
    if (!(screen = SDL_SetVideoMode(WIDTH, HEIGHT, DEPTH, SDL_DOUBLEBUF)))
    {
        SDL_Quit();
        return 1;
    }

	
	char temp[100];
    while(1) 
    {
		
		sprintf(temp, "Prueba de Libreria de Graficos 2D %d %d",Background.x,Background.y);
		fontsurf = TTF_RenderText_Solid(font,temp,color);

		SDL_Surface *NewSurface = MK_SurfaceRot(NewSurface2,Background.y,32,32,1,0xFFFF00FF);
		//SDL_Surface *NewSurface = MK_SurfaceRot(NewSurface2,Background.y,Sprite.x,Sprite.y);
		//Background.DrawBackground(screen);
		//Background.DrawBackgroundParallax(screen, 0, -1, 1, 1);
		//Niebla.SineEffect(screen,100,2,1);
		if(Pad.Held.A) Background.SineEffect(screen,10,2,1);
		else if(Pad.Held.S) Background.ExpoEffect(screen,30,-20,0,2,1);
		else Background.DrawBackground(screen);


		Sprite.DrawSpriteAnim(screen, 0, 2, 5);
		//Sprite.DrawSprite(screen,0);
		//Niebla.DrawBackgroundParallax(screen, 0, 1, 1, 1);
		
		if(Pad.Held.Q)Niebla.DrawBackground(screen);
		
		SDL_BlitSurface(NewSurface,NULL,screen,NULL);	
		SDL_BlitSurface(fontsurf,NULL,screen,NULL);

		CheckKeyboardMouse();
		if(Mouse.Held.LClick)
		{
			Sprite.x=Mouse.x;
			Sprite.y=Mouse.y;
		}
		Background.y+=(Pad.Held.Down-Pad.Held.Up);
		Background.x+=(Pad.Held.Right-Pad.Held.Left);
		
		SDL_FreeSurface(NewSurface);
		SDL_FreeSurface(fontsurf);
		MK_ShowFPSInWindow();
		SDL_Flip(screen); 
		
    }
	
    SDL_Quit();
	
    return 0;
}




