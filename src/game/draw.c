/*
 * =====================================================================================
 *
 *       Filename:  draw.c
 *
 *    Description:  :
 *
 *        Version:  1.0
 *        Created:  2013年03月11日 21时31分41秒
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  陆唯一 (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include "game.h"
#include "string.h"
#include "device/video.h"

/* 绘制屏幕上的内容。
 * 注意程序在绘图之前调用了prepare_buffer，结束前调用了display_buffer。
 * prepare_buffer会准备一个空白的绘图缓冲区，display_buffer则会将缓冲区绘制到屏幕上，
 * draw_pixel或draw_string绘制的内容将保存在缓冲区内(暂时不会显示在屏幕上)，调用
 * display_buffer后才会显示。
*/
void
redraw_screen() {
	prepare_buffer(); /* 准备缓冲区 */
    draw_airplane(myairplane.x, myairplane.y, 40);
	display_buffer(); /* 绘制缓冲区 */
}


