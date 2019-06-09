
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

#include "dump.h"

#include<map>
#include<vector>

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
    SDL_Rect plot_caption_position;
    SDL_Rect plot_position;
    std::map< int, std::vector< SDL_Point > > points;
    
    float scale_x_num ;
    float scale_y_num ;
    
    int colPos;
    int rowPos;
    
     void clean()
    {
        
         for(auto& kv : points)
         {
             
            kv.second.clear();
          
         }
    }
    
     
    void pop( int id)
    {
       if (!points[id].empty())
        points[id].erase(points[id].begin());
     }
         
    void push_back( int id, int x, int y)
    {
       
        if(!scale_x_num)
        scale_x_num = plot_position.w / ((max.x - min.x) / scale.x);
        if(!scale_y_num)
        scale_y_num = plot_position.h / ((max.y - min.y) / scale.y);
        
        int _x1 = colPos +plot_position.x + ((x - min.x) / scale.x) * scale_x_num;
        int _y1 = rowPos +plot_position.y + plot_position.h - ((y - min.y) / scale.y) * scale_y_num;

       // myPrintf("(%d , %d)", _x1 , _y1 );
        
        points[id].push_back( { _x1 , _y1 } );
    }

    Plot_params_struct(const char * caption_x, const char * caption_y, captionlist caption_lst, coordlist coordinate_lst) : update(true),texTarget(NULL),scale_x_num(0), scale_y_num(0), colPos(0),rowPos(0) {
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
       
        float plot_width = screen_width * 0.8;
        float plot_heigth = screen_heigth * 0.8;
        float plot_caption_heigth = screen_heigth * 0.05;
 
   
        plot_position.x = (screen_width / 2)-(plot_width * 0.47);
        plot_position.y = (screen_heigth * 0.50)-(plot_heigth / 2);
        plot_position.w = plot_width;
        plot_position.h = plot_heigth;
       
        plot_caption_position.x = plot_position.x;
        plot_caption_position.y = plot_position.y - 20 - plot_caption_heigth;
        plot_caption_position.w = plot_width;
        plot_caption_position.h = plot_caption_heigth;
      

    }
    Plot_params_struct(const char * caption_x, const char * caption_y, int w, int h, captionlist caption_lst, coordlist coordinate_lst) : update(true),texTarget(NULL),scale_x_num(0), scale_y_num(0), colPos(0),rowPos(0) {
        screen_width = w;
        screen_heigth = h;
        dot = false;
        grid= true;
        scale.x = 1;
        scale.y = 1;
        caption_text_x = caption_x;
        caption_text_y = caption_y;
        caption_list = caption_lst;
        coordinate_list = coordinate_lst;
        if(coordinate_lst)
        {
        max = coordinate_lst->max();
        min = coordinate_lst->min();
        }
       
        float plot_width = screen_width * 0.8;
        float plot_heigth = screen_heigth * 0.8;
        float plot_caption_heigth = screen_heigth * 0.05;
 
   
        plot_position.x = (screen_width / 2)-(plot_width * 0.47);
        plot_position.y = (screen_heigth * 0.50)-(plot_heigth / 2);
        plot_position.w = plot_width;
        plot_position.h = plot_heigth;
       
        plot_caption_position.x = plot_position.x;
        plot_caption_position.y = plot_position.y - 20 - plot_caption_heigth;
        plot_caption_position.w = plot_width;
        plot_caption_position.h = plot_caption_heigth;
      

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