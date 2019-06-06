

#ifndef SDL_font_h_
#define SDL_font_h_

//#include "begin_code.h"
/* Set up for C function definitions, even when using C++ */
#ifdef __cplusplus
extern "C" {
#endif

/* Function prototypes */

#define FONT_CHARACTER_SIZE  8

/**
 *  \brief Draw a string in the currently set font.
 *
 *  \param renderer The renderer to draw on.
 *  \param x The X coordinate of the upper left corner of the character.
 *  \param y The Y coordinate of the upper left corner of the character.
 *  \param c The character to draw.
 *
 *  \returns Returns 0 on success, -1 on failure.
 */
int SDL_DrawCharacter(SDL_Renderer *renderer, int x, int y, char c, int size, bool flip, SDL_Color * col) ;

/**
 *  \brief Draw a string in the currently set font.
 *
 *  \param renderer The renderer to draw on.
 *  \param x The X coordinate of the upper left corner of the string.
 *  \param y The Y coordinate of the upper left corner of the string.
 *  \param s The string to draw.
 *
 *  \returns Returns 0 on success, -1 on failure.
 */
int SDL_DrawString(SDL_Renderer * renderer, int x, int y, const char *s, int size, SDL_Color * col);

int SDL_DrawString_Flip(SDL_Renderer * renderer, int x, int y, const char *s, int size, SDL_Color * col);
/**
 *  \brief Cleanup textures used by font drawing functions.
 */
void SDL_CleanupTextDrawing(void);

/* Ends C function definitions when using C++ */
#ifdef __cplusplus
}
#endif
//#include "close_code.h"

#endif /* SDL_font_h_ */

/* vi: set ts=4 sw=4 expandtab: */
