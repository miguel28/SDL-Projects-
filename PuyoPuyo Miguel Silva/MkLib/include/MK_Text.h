#ifndef MK_TEXT_H
#define MK_TEXT_H

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
#include <SDL/SDL_ttf.h>
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

#ifdef __cplusplus
extern "C"
{
#endif



class DLL_EXPORT MK_Text
{
    public:
    Uint32 x,y;
    Uint8 Alpha,tAlpha;
    SDL_Surface *Graphic;
    TTF_Font *Font;
    SDL_Color Color;
    bool Created;

    MK_Text();
    void LoadFont(string Filename, Uint8 SizeFont, Uint8 R, Uint8 G, Uint8 B);
    void SetText(string Text);
    void SetColor(Uint8 R, Uint8 G, Uint8 B);
    void DrawText(SDL_Surface *Screen);
    void FreeGraphic();
};




#ifdef __cplusplus
}
#endif

#endif // MK_TEXT_H
