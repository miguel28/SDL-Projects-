#ifndef MK_APPLICATION_H
#define MK_APPLICATION_H

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
#include <iostream>
#include "MK_Background.h"
#include "MK_Sprite.h"
#include "MK_Text.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct{
	Uint8 A,Z,X,S,Q,W,E,D,C,Shift,Enter,Up,Down,Left,Right,Space;
}KeysType;

typedef struct{
	KeysType Newpress,Held;
}PadType;

typedef struct{
	Uint8 RClick, LClick;
}ClickType;

typedef struct{
	Uint16 x,y;
	ClickType Newpress,Held;
}MouseType;




class DLL_EXPORT MK_Application
{
    public:
        PadType Pad;
        MouseType Mouse;
        SDL_Surface* Screen;
        bool IsRuning;

        MK_Application();
        bool CreateWindow(int width, int height, int bpp, Uint32 flags);

        void Update();
        void Quit();
        virtual ~MK_Application();

    protected:
    private:
        SDL_Event _event;

        void ClearKeyboard();
        void CheckKeyboardMouse();
};

#ifdef __cplusplus
}
#endif


#endif // MK_APPLICATION_H
