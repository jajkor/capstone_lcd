/*****************************************************************************
* | File      	:   LCD_1IN5_APP.c
* | Author      :   Waveshare team
* | Function    :   Hardware underlying interface
* | Info        :
*                Used to shield the underlying layers of each master 
*                and enhance portability
*----------------
* |	This version:   V1.0
* | Date        :   2018-01-11
* | Info        :   Basic version
*
******************************************************************************/
#ifndef __LCD_1IN5_H
#define __LCD_1IN5_H	
	
#include "DEV_Config.h"
#include <stdint.h>

#include <stdlib.h>		//itoa()
#include <stdio.h>


#define LCD_1IN5_HEIGHT 280
#define LCD_1IN5_WIDTH 240


#define HORIZONTAL 0
#define VERTICAL   1

#define LCD_1IN5_SetBacklight(Value) DEV_SetBacklight(Value) 

#define LCD_1IN5_CS_0	LCD_CS_0	 
#define LCD_1IN5_CS_1	LCD_CS_1	
	                 
#define LCD_1IN5_RST_0	LCD_RST_0	
#define LCD_1IN5_RST_1	LCD_RST_1	
	                  
#define LCD_1IN5_DC_0	LCD_DC_0	
#define LCD_1IN5_DC_1	LCD_DC_1	
	                  
#define LCD_1IN5_BL_0	LCD_BL_0	
#define LCD_1IN5_BL_1	LCD_BL_1	

typedef struct{
	UWORD WIDTH;
	UWORD HEIGHT;
	UBYTE SCAN_DIR;
}LCD_1IN5_ATTRIBUTES;
extern LCD_1IN5_ATTRIBUTES LCD;

/********************************************************************************
function:	
			Macro definition variable name
********************************************************************************/
void LCD_1IN5_Init(UBYTE Scan_dir);
void LCD_1IN5_Clear(UWORD Color);
void LCD_1IN5_Display(UWORD *Image);
void LCD_1IN5_DisplayWindows(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD *Image);
void LCD_1IN5_DisplayPoint(UWORD X, UWORD Y, UWORD Color);
void Handler_1IN5_LCD(int signo);
#endif
