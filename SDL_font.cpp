
/**
        linked_list.c

        Build custom linked list, push new element, clear and print items

        @author Arvid Umrao <akumrao@yahoo.com> <arvind.umrao@harman.com>
        @version 0.1
 */

#include <SDL2/SDL.h>
#include "SDL_font.h"
#include "font_basic.h"
/* ---- 8x8 font definition ---- */

/* Originally part of SDL2_gfx */

/* ZLIB (c) A. Schiffler 2012 */

//#define SDL_TESTFONTDATAMAX (8*256)

/*


void usage(char *exec) {
    printf("Usage: %s <char_code>\n", exec);
    printf("       <char_code> Decimal character code between 0 and 127\n");
}

void render(char *bitmap) {
    int x,y;
    int set;
    int mask;
    for (x=0; x < 8; x++) {
          for (y=7; y >= 0; --y) {
            set = bitmap[x] & 1 << y;
            printf("%c", set ? 'X' : ' ');
        }
        printf("\n");
    }
}

void render16(char *bitmap) {
    int x,y;
    int set;
    int mask;
    for (x=0; x < 32; x = x+2) {
        for (y=7; y >= 0; --y) {
            set = bitmap[x] & 1 << y;
            printf("%c", set ? 'X' : ' ');
        }
        
        for (y=7; y >= 0; --y) {
            set = bitmap[x+1] & 1 << y;
            printf("%c", set ? 'X' : ' ');
        }
        
    
            printf("\n");
    }
}

int main(int argc, char **argv) {
    int ord;
    if (argc != 2) {
        usage(argv[0]);
        return 1;
    }
    ord = atoi(argv[1]);
    if (ord > 127 || ord < 0) {
        usage(argv[0]);
        return 2;
    }
    char *bitmap16 = font16x16_basic[ord];
    
    render16(bitmap16);
    
    char *bitmap = font8x8_basic[ord];
    
    render(bitmap);
   
    return 0;
}; 
 */
int render(Uint32 ci, int charWidth, SDL_Surface *character) {

    Uint32 ix, iy;
    const unsigned char *charpos;
    Uint8 *curpos;
    Uint8 patt, mask;
    Uint8 *linepos;
    Uint32 pitch;

    if (charWidth == 8)
        charpos = font8x8_basic[ci];
    else
        charpos = font16x16_basic[ci];


    linepos = (Uint8 *) character->pixels;
    pitch = character->pitch;

    /*
     * Drawing loop
     */
    patt = 0;
    for (iy = 0; iy < charWidth; ++iy) {
        mask = 0x00;
        curpos = linepos;
        for (ix = 0; ix < charWidth; ix++) {
            if (!(mask >>= 1)) {
                patt = *charpos++;
                mask = 0x80;
            }
            if (patt & mask) {
                *(Uint32 *) curpos = 0xffffffff;
            } else {
                *(Uint32 *) curpos = 0;
            }
            curpos += 4;
        }
        linepos += pitch;
    }

    /* Convert temp surface into texture */

    return 0;
}


int renderFlip(Uint32 ci, int charWidth, SDL_Surface *character) {

    Uint32 ix, iy;
    const unsigned char *charpos;
    Uint8 *curpos;
    Uint8 patt, mask;
    Uint8 *linepos;
    Uint32 pitch;

    if (charWidth == 8)
        charpos = font8x8_basic[ci];
    else
        charpos = font16x16_basic[ci];


    linepos = (Uint8 *) character->pixels;
    pitch = character->pitch;

    /*
     * Drawing loop
     */
    patt = 0;
    for (iy = 0; iy < charWidth; ++iy) {
        mask = 0x00;
        
        for (ix = 0; ix < charWidth; ix++) {
            curpos = &linepos[iy*4 + (charWidth -1 -ix)*pitch];
            if (!(mask >>= 1)) {
                patt = *charpos++;
                mask = 0x80;
            }
            if (patt & mask) {
                *(Uint32 *) curpos = 0xffffffff;
            } else {
                *(Uint32 *) curpos = 0;
            }
           // curpos += 4;
        }
        //linepos += pitch;
    }

    /* Convert temp surface into texture */

    return 0;
}

/* ---- Character */

/*!
\brief Global cache for 8x8 pixel font textures created at runtime.
 */
static SDL_Texture *SDL_CharTextureCache[4][256];

int SDL_DrawCharacter(SDL_Renderer *renderer, int x, int y, char c, int size, bool flip, SDL_Color * col) {
    const Uint32 charWidth = size;
    const Uint32 charHeight = size;
    const Uint32 charSize = size;
    SDL_Rect srect;
    SDL_Rect drect;
    int result;
    Uint32 ci;
    //Uint8 r, g, b, a;

    /*
     * Setup source rectangle
     */
    srect.x = 0;
    srect.y = 0;
    srect.w = charWidth;
    srect.h = charHeight;

    /*
     * Setup destination rectangle
     */
    drect.x = x;
    drect.y = y;
    drect.w = charWidth;
    drect.h = charHeight;

    /* Character index in cache */
    ci = (unsigned char) c;

    /*
     * Create new charWidth x charHeight bitmap surface if not already present.
     */
    if (SDL_CharTextureCache[(size/8) -1 + flip*2][ci] == NULL) {
        /*
         * Redraw character into surface
         */
        SDL_Surface *character = SDL_CreateRGBSurface(SDL_SWSURFACE,
                charWidth, charHeight, 32,
                0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
        if (character == NULL) {
            return (-1);
        }
        if(flip)
        renderFlip(ci, charWidth, character);
        else
        render(ci, charWidth, character);      
        
        SDL_CharTextureCache[(size/8) -1 + flip*2][ci] = SDL_CreateTextureFromSurface(renderer, character);
        SDL_FreeSurface(character);

        /*
         * Check pointer
         */
        if (SDL_CharTextureCache[(size/8) -1 + flip*2][ci] == NULL) {
            return (-1);
        }

    }

    /*
     * Set color
     */
    result = 0;
    ///result |= SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    result |= SDL_SetTextureColorMod(SDL_CharTextureCache[(size/8) -1+ flip*2][ci], col->r, col->g, col->b);
    result |= SDL_SetTextureAlphaMod(SDL_CharTextureCache[(size/8) -1+ flip*2][ci], col->a);

    /*
     * Draw texture onto destination
     */
    result |= SDL_RenderCopy(renderer, SDL_CharTextureCache[(size/8) -1+ flip*2][ci], &srect, &drect);

    return (result);
}
/*
int SDL_DrawString_Flip(SDL_Renderer * renderer, int x, int y, const char *s, SDL_Color * col) {
    const Uint32 charWidth = 8;

    // Uint8 r, g, b, a;

    // SDL_GetRenderDrawColor(renderer, &r, &g, &b, &a);
    SDL_Texture *parentTarget = SDL_GetRenderTarget(renderer);

    int widthText = charWidth * strlen(s);

    int heightText = charWidth + 2;

    SDL_Texture *texTarget = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
            SDL_TEXTUREACCESS_TARGET, widthText, heightText);

    // SDL_SetTextureColorMod(texTarget, r, g, b);
    //SDL_SetTextureAlphaMod(texTarget, 0);
    SDL_SetTextureBlendMode(texTarget, SDL_BLENDMODE_BLEND);

    SDL_Rect srect = {0, 0, widthText, heightText};
    SDL_SetRenderTarget(renderer, texTarget);

    int result = 0;
    //    result = SDL_DrawString(renderer, 0, 0, s, col);

    //Now render the texture target to our screen, but upside down
    SDL_SetRenderTarget(renderer, parentTarget);

    SDL_Rect drect = {x, y, widthText, heightText};
    SDL_RendererFlip flip = SDL_RendererFlip(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
    SDL_RenderCopyEx(renderer, texTarget, &srect, &drect, 90, NULL, flip);

    SDL_DestroyTexture(texTarget);

    return (result);
}*/

int SDL_DrawString(SDL_Renderer * renderer, int x, int y, const char *s, int size, SDL_Color * col) {
    const Uint32 charWidth = size;

    int result = 0;
    int curx = x;
    int cury = y;
    const char *curchar = s;

    while (*curchar && !result) {
        result |= SDL_DrawCharacter(renderer, curx, cury, *curchar, charWidth, false, col);
        curx += charWidth;
        curchar++;
    }
    //SDL_RenderPresent(renderer);
    return (result);
}

int SDL_DrawString_Flip(SDL_Renderer * renderer, int x, int y, const char *s, int size, SDL_Color * col) {
    const Uint32 charWidth = size;

    int widthText = charWidth * strlen(s);
    int result = 0;
    int curx = x;
    int cury = y + widthText/2;
    const char *curchar = s;

   
    
    while (*curchar && !result) {
        result |= SDL_DrawCharacter(renderer, curx, cury, *curchar, charWidth,true, col);
        cury -= charWidth;
        curchar++;
    }
    //SDL_RenderPresent(renderer);
    return (result);
}

void SDL_CleanupTextDrawing(void) {
    unsigned int i, j;

    for (j = 0; j < SDL_arraysize(SDL_CharTextureCache); ++j){


            for (i = 0; i < SDL_arraysize(SDL_CharTextureCache[j]); ++i) {
                if (SDL_CharTextureCache[j][i]) {
                    SDL_DestroyTexture(SDL_CharTextureCache[j][i]);
                            SDL_CharTextureCache[j][i] = NULL;
                }
            }

        }
    }

/* vi: set ts=4 sw=4 expandtab: */
