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

#define square(n) (n)*(n)

#define move_by_key(key,direction,distance,limit) \
    if (query_key((key) - 'a')){ \
        release_key((key) - 'a'); \
        myairplane. direction = (float) (((limit) + (int)myairplane. direction + (distance))%(limit)) ; \
        return true; \
    }

LINKLIST_IMPL(aerolite,10000)

static aerolite_t aerolite_head = NULL;

aerolite_t
get_aerolite_head(void){
    return aerolite_head;
}

void
create_new_aerolite(void){
    if (aerolite_head == NULL){
        aerolite_head = aerolite_new();
    } else {
        aerolite_t aerolite_now = aerolite_new();
        aerolite_insert(NULL,aerolite_head,aerolite_now);
        aerolite_head = aerolite_now;
    }
    aerolite_head->x = 0;
    aerolite_head->y = rand() % (SCR_WIDTH / 8 - 2) * 8 + 8;
    aerolite_head->v_x = (rand() % 1000 / 1000.0 + 1) / 2.0;
    aerolite_head->v_y = (rand() % 1000 / 1000.0 - 0.5) / 2.0;
}

void
update_aerolite_pos(void){
    aerolite_t it;
    for ( it = aerolite_head ; it != NULL ; ){
        aerolite_t next = it->_next;
        it->x += it->v_x;
        it->y += it->v_y;
        if ( it->x + 8.0 > SCR_HEIGHT || it->y < 0 || it->y + 8 > SCR_WIDTH ){
            aerolite_remove(it);
            aerolite_free(it);
            if(it == aerolite_head)
                aerolite_head = next;
        }
        else{
            if ( (square(it->x - myairplane.x) + square(it->y - myairplane.y) < 64))//bomb!!
                myairplane.life--;
        }
        it = next;
    }
}

bool 
update_keypress(void){
    disable_interrupt();
    move_by_key('a',y,-8,SCR_WIDTH);
    move_by_key('d',y,8,SCR_WIDTH);
    move_by_key('w',x,-8,SCR_HEIGHT - 8);
    move_by_key('s',x,8,SCR_HEIGHT - 8);
    enable_interrupt();
    return false;
}
