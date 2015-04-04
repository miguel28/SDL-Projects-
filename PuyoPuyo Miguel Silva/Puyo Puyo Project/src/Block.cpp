/*
 *  PuyoPuyo
 *
 *
 *  Created by mike on 6/30/12.
 *  Copyright 2013 MiGuEl Inc. All rights reserved.
 *
 */
#include "Block.h"

Block::Block() : MK_Sprite("Gfx/blocks.png")
{
    Type = 0;
    PosX = PosY = 0;
    CreateGfxEffect(64,64);
    ExtraEffect = SDL_CreateRGBSurface(SDL_HWSURFACE, 64, 64, Graphic->format->BitsPerPixel, Graphic->format->Rmask, Graphic->format->Gmask, Graphic->format->Bmask, Graphic->format->Amask);
}

Block::Block(SDL_Surface* FromImageGFX) : MK_Sprite(FromImageGFX)
{
    Type = 0;
    PosX = PosY = 0;
    CreateGfxEffect(64,64);
    ExtraEffect = SDL_CreateRGBSurface(SDL_HWSURFACE, 32, 32, Graphic->format->BitsPerPixel, Graphic->format->Rmask, Graphic->format->Gmask, Graphic->format->Bmask, Graphic->format->Amask);
}

Block::~Block()
{

}

void Block::Render(SDL_Surface* Screen)
{
    if(Type>0)
    {
        x=(PosX*32)+64-((int)(AnimStarted)*1);
        y=(PosY*32)+64-((int)(AnimStarted)*1);
        if(AnimStarted)
        {
            Prerender(Type-1);
            ExtraEffect = Effects->MK_SurfaceZoom(ExtraEffect, Zoom, Zoom);
            GfxEffect = Effects->MK_SurfaceRot(ExtraEffect, tAngle, 22, 22, 1, 0x00FF00FF);
            DrawEffect(Screen);
            SDL_FreeSurface(ExtraEffect);
        }
        else DrawSprite(Screen,Type-1);
    }

}

void Block::SetAnimation(Uint16 Angle, float z)
{
    Zoom = z;
    AnimStarted=true;
    tAngle=(double)Angle;
}

void Block::StopAnimation()
{
    AnimStarted=false;
}

void Block::Prerender(int frame)
{
    ExtraEffect = SDL_CreateRGBSurface(SDL_SWSURFACE, 32, 32, Graphic->format->BitsPerPixel, Graphic->format->Rmask, Graphic->format->Gmask, Graphic->format->Bmask, Graphic->format->Amask);

    int framey = frame/SheetSizeX;
	int framex = frame-(SheetSizeX*framey);
	SDL_Rect Sframe={(Sint16)(framex*FrameSizeX),(Sint16)(framey*FrameSizeY),(Uint16)FrameSizeX,(Uint16)FrameSizeY};
	//SDL_Rect dest={x,y,FrameSizeX,FrameSizeY};
	if(tAlpha!=Alpha)
	{
		SDL_SetAlpha(Graphic, SDL_SRCALPHA, Alpha);
		tAlpha=Alpha;
	}
	SDL_BlitSurface(Graphic,&Sframe,ExtraEffect,NULL);
}
