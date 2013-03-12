/*
 * =====================================================================================
 *
 *       Filename:  game.c
 *
 *    Description: 
 *
 *        Version:  1.0
 *        Created:  2013年03月10日 14时25分26秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  陆唯一 (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include "x86/x86.h"
#include "game.h"
#include "string.h"
#include "device/timer.h"

#define FPS 30
#define SECOND_TO_NEXT_LEVEL 10
#define UPDATE_PER_SECOND 100

struct airplane myairplane = { 100 , 160 };

volatile int tick = 0;

void 
timer_event(void){
    tick ++;
}

static int real_fps;
void set_fps(int value){
    real_fps = value;
}
int
get_fps(void){
    return real_fps;
}

void
main_loop(){
    int now = 0 , target;
    int num_draw = 0;
    int now_fps;
    int aerolite_per_second = 5;
    bool redraw;

    while(TRUE){
        wait_for_interrupt();
        disable_interrupt();
        if (now == tick){
            enable_interrupt();
            continue;
        }
        assert(now < tick);
        target = tick;
        enable_interrupt();

        redraw = false;
        while(update_keypress())
            ;

        while(now < target){
            
            if (now % (HZ / FPS) == 0){
                redraw = true;
            }

            if (now % (SECOND_TO_NEXT_LEVEL * HZ) == 0){
                aerolite_per_second += 5;
            }

            if (now % (HZ / aerolite_per_second) == 0){
                create_new_aerolite();
            }

            if (now % (HZ / UPDATE_PER_SECOND) == 0){
                update_aerolite_pos();
            }

            if (now % (HZ / 2) == 0){
                now_fps = num_draw * 2 + 1;
                if (now_fps > FPS) now_fps = FPS;
                set_fps(now_fps);
                num_draw = 0;
            }
            now++;

        }

        if (redraw){
            num_draw++;
            redraw_screen();
        }
    }
}
