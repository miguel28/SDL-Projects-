#ifndef MK_GRAPHICS_H
#define MK_GRAPHICS_H

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

#define TRANSPARENT	0xFF00FF
#define PI 3.14159265

#ifdef __cplusplus
extern "C"
{
#endif

class DLL_EXPORT MK_Graphics
{
    public:
        MK_Graphics();
        Uint32 MK_getpixel(SDL_Surface *surface, int x, int y);
        void MK_putpixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
        Uint32 *MK_PixelsArray(SDL_Surface *surface);
        SDL_Surface *MK_ArrayToSurface(Uint32 *array, int w, int h);
        void MK_SetGrayScaleColor(SDL_Surface *src,Uint32 Key, Uint8 Type);
        Uint32 MK_GreyPixel(Uint32 pix);
        Uint32 MK_BlackPixel(Uint32 pix);
        void MK_HFlipSurface(SDL_Surface *surface);
        void MK_VFlipSurface(SDL_Surface *surface);

        SDL_Surface *MK_SurfaceZoom(SDL_Surface *source, float zoomx, float zoomy);
        SDL_Surface *MK_SurfaceRot(SDL_Surface *source, double Angle, int cx, int cy, Uint8 Resize, Uint32 Key);

        Uint32 MK_GetSizeRotedGfx(Uint32 w, Uint32 h);
        virtual ~MK_Graphics();
    protected:
    private:
};

#ifdef __cplusplus
}
#endif

#endif // MK_GRAPHICS_H
