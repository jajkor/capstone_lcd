#include "DEV_Config.h"
#include "LCD_1in5.h"
#include "GUI_Paint.h"
#include "GUI_BMP.h"
#include "test.h"
#include <stdio.h>		//printf()
#include <stdlib.h>		//exit()
#include <signal.h>     //signal()

void LCD_1IN5_test(void)
{
    // Exception handling:ctrl + c
    signal(SIGINT, Handler_1IN5_LCD);
    
    /* Module Init */
	if(DEV_ModuleInit() != 0){
        DEV_ModuleExit();
        exit(0);
    }
	
    /* LCD Init */
	printf("1.5inch LCD demo...\r\n");
	LCD_1IN5_Init(VERTICAL);
	LCD_1IN5_Clear(WHITE);
    //LCD_SetBacklight(1023);
	
    UWORD *BlackImage;
    UDOUBLE Imagesize = LCD_1IN5_HEIGHT*LCD_1IN5_WIDTH*2;
    printf("Imagesize = %d\r\n", Imagesize);
    if((BlackImage = (UWORD *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        exit(0);
    }
    // /*1.Create a new image cache named IMAGE_RGB and fill it with white*/
    Paint_NewImage(BlackImage, LCD_1IN5_WIDTH, LCD_1IN5_HEIGHT, 0, WHITE, 16);
    Paint_Clear(WHITE);
	Paint_SetRotate(0);
    // /* GUI */
    printf("drawing...\r\n");
    Paint_DrawString_EN(7, 20, "12345678",        &Font24,  YELLOW, RED);  
	Paint_DrawString_EN(7, 44, "ABCDEFGH",        &Font24,  BLUE,   CYAN);
    Paint_DrawFloatNum (7, 68 ,987.654321,4, &Font24,  WHITE,  BLACK);
	Paint_DrawString_CN(7,92, "Î¢Ñ©µç×Ó",   &Font24CN,WHITE,  RED);

    Paint_DrawCircle(188, 40, 25, GREEN, DOT_PIXEL_1X1, DRAW_FILL_EMPTY);
    Paint_DrawCircle(188, 100, 25, GREEN, DOT_PIXEL_1X1, DRAW_FILL_FULL);
	Paint_DrawLine( 163,  40, 213, 40, RED , DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
	Paint_DrawLine( 188,  15, 188, 65, RED , DOT_PIXEL_1X1, LINE_STYLE_DOTTED);
    
	Paint_DrawCircle(65,180,  40,        BLUE    ,DOT_PIXEL_3X3,DRAW_FILL_EMPTY);
	Paint_DrawCircle(115,180,  40,        BLACK   ,DOT_PIXEL_3X3,DRAW_FILL_EMPTY);
	Paint_DrawCircle(165,180,  40,        RED     ,DOT_PIXEL_3X3,DRAW_FILL_EMPTY);
	Paint_DrawCircle(100,235,  40,        YELLOW  ,DOT_PIXEL_3X3,DRAW_FILL_EMPTY);
	Paint_DrawCircle(140,235,  40,        GREEN   ,DOT_PIXEL_3X3,DRAW_FILL_EMPTY);
    LCD_1IN5_Display(BlackImage);
    DEV_Delay_ms(3000);
    Paint_Clear(BLACK);
	  
    /* show bmp */
	printf("show bmp\r\n");
	GUI_ReadBmp("./pic/LCD_1inch5.bmp");
    
    LCD_1IN5_Display(BlackImage);
    DEV_Delay_ms(2000);
    
    /* Module Exit */
    free(BlackImage);
    BlackImage = NULL;
	DEV_ModuleExit();
}

