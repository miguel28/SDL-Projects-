/*
 *  PuyoPuyo
 *
 *
 *  Created by mike on 6/30/12.
 *  Copyright 2013 MiGuEl Inc. All rights reserved.
 *
 */

#ifndef BLOCK_H
#define BLOCK_H
#include <MK_Application.h>


class Block : public MK_Sprite
{
    public:
        Block();
        Block(SDL_Surface* FromImageGFX);
        Uint8 Type;
        Uint8 PosX,PosY;
        bool AnimStarted;
        double tAngle;
        float Zoom;
        void SetAnimation(Uint16 Angle, float z);
        void StopAnimation();
        void Render(SDL_Surface* Screen);
        virtual ~Block();
    protected:
    private:
        SDL_Surface* ExtraEffect;
        void Prerender(int frame);

};

#endif // BLOCK_H
