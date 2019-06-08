
/**
        linked_list.h

        Build custom linked list, push new element, clear and print items

        @author Arvid Umrao <akumrao@yahoo.com> <arvind.umrao@harman.com>
        @version 0.1
 */
#ifndef LLIST
#define LLIST

#ifdef __ANDROID__
#include "SDL.h"
#else
#include "SDL2/SDL.h"
#endif

//--------------CAPTION STRUCT --------------
typedef struct Caption_item Caption_item;

struct Caption_item {
    const char * caption_txt;
    int caption_id;
    int caption_color;
    struct Caption_item *nxt;
};

typedef Caption_item* captionlist;
//----------------------------------------

struct Pair {
    float x;
    float y;

    Pair() : x(0), y(0) {
    }

    Pair(int ix, int iy) : x(ix), y(iy) {
    }
};

//-------------COORDINATE STRUCT ------------
typedef struct Coordinate_item Coordinate_item;

struct Coordinate_item {
    float x;
    float y;
    int caption_id;
    struct Coordinate_item *nxt;

    Coordinate_item() : nxt(0) {
    }

    int count() {
        int nc = 0;
        ++nc;
        Coordinate_item* temp = nxt;
        while (temp != NULL) {
            ++nc;
            temp = temp->nxt;
        }

        return nc;
    }

    Pair min() {
        Pair nc(x, y);
        Coordinate_item* temp = nxt;
        while (temp != NULL) {

            if (nc.x > temp->x) {
                nc.x = temp->x;
            }
            if (nc.y > temp->y) {
                nc.y = temp->y;
            }

            temp = temp->nxt;
        }


        return nc;

    }

    Pair max() {
        Pair nc(x, y);
        Coordinate_item* temp = nxt;
        while (temp != NULL) {

            if (nc.x < temp->x) {
                nc.x = temp->x;
            }
            if (nc.y < temp->y) {
                nc.y = temp->y;
            }

            // ++ nc;
            temp = temp->nxt;
        }

        return nc;
    }


};

typedef Coordinate_item* coordlist;
//----------------------------------------



//-------------Plot parameter structure  ------------

typedef struct Plot_params_struct {
    int screen_width;
    int screen_heigth;
    //const char  *      plot_title ;
    //char *      font_text_path    ;
    //int         font_text_size    ;
    const char * caption_text_x;
    const char * caption_text_y;
    captionlist caption_list;
    coordlist coordinate_list;
    SDL_Texture *texTarget;
    Pair scale;
    Pair max;
    Pair min;
    bool dot;
    bool grid;
    bool update;
    Plot_params_struct(const char * caption_x, const char * caption_y, captionlist caption_lst, coordlist coordinate_lst) : update(true),texTarget(NULL) {
        screen_width = 400;
        screen_heigth = 400;
        dot = true;
        grid= true;
        scale.x = 1;
        scale.y = 1;
        caption_text_x = caption_x;
        caption_text_y = caption_y;
        caption_list = caption_lst;
        coordinate_list = coordinate_lst;
        max = coordinate_lst->max();
        min = coordinate_lst->min();
    }
} plot_params;



typedef struct Plot_Window_params Plot_Window_params;

struct Plot_Window_params {
    plot_params * plotparm;
    Plot_Window_params *nxt;

    int count() {
        int nc = 0;

        if (plotparm)
            ++nc;
        Plot_Window_params* temp = nxt;
        while (temp != NULL) {
            ++nc;
            temp = temp->nxt;
        }

        return nc;
    }
};

typedef Plot_Window_params* plotwinlist;




//----------------------------------------

/**
 * @brief push_back_coord
 *      push a new item to the end of coordinate table
 * @param list
 *      list of coordinate items
 * @param x
 *      x coordinate
 * @param y
 *      y coordinate
 */
coordlist push_back_coord(coordlist list, int caption_id, float x, float y);

/**
 * @brief print_list_coord
 *      print coordinate table
 * @param list
 *      list of coordinate items
 */
void print_list_coord(coordlist list);

/**
 * @brief clear_coord
 *      clear coordinate table
 * @param list
 *      list of coordinate items
 */
coordlist clear_coord(coordlist list);

/**
 * @brief push_back_caption
 *      push a new item to the end of caption table
 * @param list std::vector< SDL_Point > points;
 *      list of caption items
 * @param caption_txt
 *      caption text
 * @param caption_id
 *      caption id
 * @param color
 *      caption color
 */
captionlist push_back_caption(captionlist list, const char * caption_txt, int caption_id, int color);

/**
 * @brief print_list_caption
 *      print caption table
 * @param list
 *      list of caption items
 */
void print_list_caption(captionlist list);

/**
 * @brief clear_caption
 *      clear caption table
 * @param list
 *      list of caption items
 */
captionlist clear_caption(captionlist list);

/**
 * @brief push_back_surface
 *      push a new item to the end of surface table
 * @param list
 *      list of surface items
 * @param surface
 *      SDL surface ptr
 */


/**
 * @brief clear_surface
 *      clear surface table
 * @param list
 *      list of surface items
 */



plotwinlist push_back_plot_win(plotwinlist list, plot_params* plotparm);

plotwinlist clear_plot_win(plotwinlist list);

#endif