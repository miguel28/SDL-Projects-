#ifndef MK_SPRITE_H
#define MK_SPRITE_H

/*
 *  MK_Sprites.h
 *  SDLExample
 *
 *  Created by mike on 4/5/12.
 *  Copyright 2012 MiGuEl Inc. All rights reserved.
 *
 */

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
#include <cmath>
#include <iostream>
#include "MK_Graphics.h"
using namespace std;

#define TRANSPARENT	0xFF00FF
#define PI 3.14159265

#ifdef __cplusplus
extern "C"
{
#endif



class DLL_EXPORT MK_Sprite{
public:
    MK_Graphics* Effects;
	Uint16 FrameSizeX,FrameSizeY;
	Uint16 SheetSizeX,SheetSizeY;
	Uint8 FrameAnim;
	Uint8 FrameTime;
	Uint8 Alpha,tAlpha;
	SDL_Surface *Graphic,*GfxEffect;
	Sint16 x,y;
	MK_Sprite(string Filename);
	MK_Sprite(string Filename,Uint32 KeyColor);
	MK_Sprite(SDL_Surface* FromGraphic);
	void Load(string Filename);
	void Load(string Filename,Uint32 KeyColor);
	void SetLayout(Uint16 FSizeX,Uint16 FSizeY,Uint16 SizeX,Uint16 SizeY);
	void DrawSprite(SDL_Surface *Screen, int frame);
	void DrawSpriteAnim(SDL_Surface *Screen, Uint8 framestart, Uint8 framefinish, Uint8 Speed);
	void HFlip();
	void VFlip();
	void CreateGfxEffect(Uint32 width, Uint32 height);
	void DeleteGfxEffect();
	void Rot(double Angle, int cx, int cy, Uint8 Resize, Uint32 Key);
	void DrawEffect(SDL_Surface *Screen);
	~MK_Sprite();
private:

};




#ifdef __cplusplus
}
#endif

#endif // MK_SPRITE_H
