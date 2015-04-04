/*
 *  PuyoPuyo
 *
 *
 *  Created by mike on 6/30/12.
 *  Copyright 2013 MiGuEl Inc. All rights reserved.
 *
 */

#ifdef __cplusplus
    #include <cstdlib>
#else
    #include <stdlib.h>
#endif

#include "PuyoPuyo.h"

PuyoPuyo* PuyoPuyoApp = new PuyoPuyo();

int main ( int argc, char** argv )
{
    PuyoPuyoApp->CreateWindow(480, 480, 16,SDL_SWSURFACE|SDL_DOUBLEBUF);/*Create The window: 480 Width, 480 Height*/
    PuyoPuyoApp->Text->LoadFont("Gfx/arial.ttf", 18, 255, 255, 255);/* Load Font*/
    while (PuyoPuyoApp->IsRuning)/*Game Loop*/
    {
        PuyoPuyoApp->GameLogic();/* Run the Game Logic*/
    }
    delete PuyoPuyoApp; /*Free All used memory*/
    return 0; /*Exit Success*/
}
