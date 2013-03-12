/*
 * =====================================================================================
 *
 *       Filename:  effect.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  2013年03月11日 20时31分41秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  陆唯一 (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "game.h"
#include "common.h"
#include "string.h"
#include "adt/linklist.h"
#include "device/video.h"
#include "x86/x86.h"

#define move_by_key(key,direction,distance) \
    if (query_key((key) - 'a')){ \
        release_key((key) - 'a'); \
        mycar-> direction += (distance); \
        return true; \
    }

bool 
update_keypress(void){
    struct car* mycar = get_car();
    disable_interrupt();
    move_by_key('a',y,-8);
    move_by_key('d',y,8);
    move_by_key('w',x,-8);
    move_by_key('s',x,8);
    enable_interrupt();
    return false;
}
