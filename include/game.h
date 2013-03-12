#ifndef __GAME_H__
#define __GAME_H__

#include "common.h"
#include "adt/linklist.h"

/* 中断时调用的函数 */
void timer_event(void);
void keyboard_event(int scan_code);

/* 按键相关 */
void press_key(int scan_code);
void release_key(int ch);
bool query_key(int ch);
int last_key_code(void);

/* 定义aerolite_t链表 */
LINKLIST_DEF(aerolite)
	float x, y;
	float v_x,v_y;
LINKLIST_DEF_FI(aerolite)

/* 主循环 */
void main_loop(void);

/* 游戏逻辑相关 */
void create_new_aerolite(void);
void update_aerolite_pos(void);
bool update_keypress(void);

int get_fps(void);
void set_fps(int fps);
aerolite_t get_aerolite_head(void);

void redraw_screen(void);

/* 随机数 */
int rand(void);
void srand(int seed);

/* airplane */
struct airplane{
    int x,y;
};

extern struct airplane myairplane;

#endif
