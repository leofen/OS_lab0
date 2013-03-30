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
#define SECOND_TO_NEXT_LEVEL 15
#define SECOND_BE_INVINCIBLE 3
#define UPDATE_PER_SECOND 100

/* 飞机的属性，设为全局变量方便调用 */
struct airplane myairplane = { 180.0 , 160.0 , 3 , true};

volatile int tick = 0;

/* 时钟中断相应函数 */
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

static int score;
int
get_score(void){
    return score;
}

/* 
 * 游戏主循环，不会跳出该函数
 */
void
main_loop(){
    int now = 0 , target;
    int num_draw = 0;
    int now_fps;
    int aerolite_per_second = 5;//每秒掉落的陨石数
    bool redraw;

    while(TRUE){
        /* 若飞机还有生命，游戏继续 */
        if (myairplane.life > 0){
            wait_for_interrupt();
            disable_interrupt();
            if (now == tick){
                enable_interrupt();
                continue;
            }
            assert(now < tick);
            target = tick;
            score = tick/100;//分数和坚持时间挂钩
            enable_interrupt();

            redraw = false;
            while(update_keypress())
                ;

            while(now < target){

                if (now % (HZ / FPS) == 0){
                    redraw = true;
                }

                /* 增加每秒出现的陨石数 */
                if (now % (SECOND_TO_NEXT_LEVEL * HZ) == 0){
                    aerolite_per_second += 5;
                }

                /* 失去无敌效果 */
                if (now % (SECOND_BE_INVINCIBLE * HZ) == 0){
                    myairplane.invincible = false;
                }

                /* 增加陨石 */
                if (now % (HZ / aerolite_per_second) == 0){
                    create_new_aerolite();
                }

                /* 更新陨石位置 */
                if (now % (HZ / UPDATE_PER_SECOND) == 0){
                    update_aerolite_pos();
                }

                /* 统计FPS */
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
        /* 游戏结束 */
        else{
            redraw_screen();
            while(wait_restart()){
                /* 重生时一切初始化 */
                myairplane.x = 180.0; myairplane.y = 160.0; myairplane.life = 3; myairplane.invincible = true;
                tick = 0;
                now = 0;
                aerolite_per_second = 5;
                score = 0;
                clear_screen();
            }
        }
    }
}
