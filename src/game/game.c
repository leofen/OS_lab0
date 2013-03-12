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

struct airplane myairplane = { 100.0 , 160.0 };

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
