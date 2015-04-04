/*
 *  MK_Sprites.h
 *  SDLExample
 *
 *  Created by mike on 4/5/12.
 *  Copyright 2012 MiGuEl Inc. All rights reserved.
 *
 */

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_TTF.h>

#include "MK_Graphics.h"

class MK_Sprite{
public:
	Uint8 FrameSizeX,FrameSizeY;
	Uint8 SheetSizeX,SheetSizeY;	
	Uint8 FrameAnim;
	Uint8 FrameTime;
	Uint8 Alpha,tAlpha;
	SDL_Surface *Graphic,*GfxEffect;
	int x,y;
	void DrawSprite(SDL_Surface *Screen, int frame);
	MK_Sprite(char *Filename,Uint32 KeyColor, Uint8 Key ,Uint8 FSizeX,Uint8 FSizeY,Uint8 SizeX,Uint8 Sizey);
	void DrawSpriteAnim(SDL_Surface *Screen, Uint8 framestart, Uint8 framefinish, Uint8 Speed);
	void HFlip();
	void VFlip();
	void CreateGfxEffect(Uint32 width, Uint32 height);
	void DeleteGfxEffect();
};