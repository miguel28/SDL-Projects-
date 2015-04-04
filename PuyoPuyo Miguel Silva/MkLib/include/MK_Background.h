#ifndef MK_BACKGROUND_H
#define MK_BACKGROUND_H

#ifdef BUILD_DLL
    #define DLL_EXPORT __declspec(dllexport)
#else
    #define DLL_EXPORT __declspec(dllimport)
#endif

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <iostream>
#include "MK_Graphics.h"

using namespace std;


#ifdef __cplusplus
extern "C"
{
#endif



class DLL_EXPORT MK_Background{
public:
	Uint16 SizeX,SizeY;
	Sint16 x,y;
	Uint8 ScrollTimeX,ScrollTimeY;
	Uint16 Time;
	Sint16 Counter;
	Sint8 Factor;
	Uint8 Aumenta;
	Uint8 Alpha,tAlpha;
	Uint8 GfxCreated;

	SDL_Surface *Graphic;
	SDL_Surface *GfxEffect;

	MK_Background(string Filename,Uint32 KeyColor, int FSizeX, int FSizeY);
	MK_Background(string Filename, int FSizeX, int FSizeY);

	void DrawBackground(SDL_Surface *Screen);
	void DrawBackgroundInt(SDL_Surface *gfx,SDL_Surface *Screen);
	void DrawBackgroundParallax(SDL_Surface *Screen, Sint16 ParallaxX,Sint16 ParallaxY, Uint16 timex, Uint16 timey);
	void SineEffect(SDL_Surface *Screen,Uint8 Longitude,double Interval,Uint8 time);
	void ExpoEffect(SDL_Surface *Screen,Uint8 Longitude, Sint8 Low, Sint8 High, Uint8 Interval1, Uint8 Interval2);
	void MoveLine(SDL_Surface *Screen,int Magnitude, int yy);
	void CreateGfxEffect(Uint32 width, Uint32 height);
	void DeleteGfxEffect();

	~MK_Background();
private:


};


#ifdef __cplusplus
}
#endif

#endif // MK_BACKGROUND_H
