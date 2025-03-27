/*****************************************************************************
* | File      	:   LCD_0IN85_APP.c
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
#ifndef __LCD_0IN85_H
#define __LCD_0IN85_H	
	
#include "DEV_Config.h"
#include <stdint.h>

#include <stdlib.h>		//itoa()
#include <stdio.h>


#define LCD_0IN85_HEIGHT 128
#define LCD_0IN85_WIDTH 128


#define HORIZONTAL 0
#define VERTICAL   1

#define LCD_0IN85_SetBacklight(Value) DEV_SetBacklight(Value) 

#define LCD_0IN85_CS_0	LCD_CS_0	 
#define LCD_0IN85_CS_1	LCD_CS_1	
	                 
#define LCD_0IN85_RST_0	LCD_RST_0	
#define LCD_0IN85_RST_1	LCD_RST_1	
	                  
#define LCD_0IN85_DC_0	LCD_DC_0	
#define LCD_0IN85_DC_1	LCD_DC_1	
	                  
#define LCD_0IN85_BL_0	LCD_BL_0	
#define LCD_0IN85_BL_1	LCD_BL_1	

typedef struct{
	UWORD WIDTH;
	UWORD HEIGHT;
	UBYTE SCAN_DIR;
}LCD_0IN85_ATTRIBUTES;
extern LCD_0IN85_ATTRIBUTES LCD;

/********************************************************************************
function:	
			Macro definition variable name
********************************************************************************/
void LCD_0IN85_Init(UBYTE Scan_dir);
void LCD_0IN85_Clear(UWORD Color);
void LCD_0IN85_Display(UWORD *Image);
void LCD_0IN85_DisplayWindows(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD *Image);
void LCD_0IN85_DisplayPoint(UWORD X, UWORD Y, UWORD Color);
void Handler_0IN85_LCD(int signo);
#endif
