#include "DEV_Config.h"
#include "LCD_0in85.h"
#include "GUI_Paint.h"
#include "GUI_BMP.h"
#include "test.h"
#include <stdio.h>		//printf()
#include <stdlib.h>		//exit()
#include <signal.h>     //signal()

void LCD_0IN85_test(void)
{
    // Exception handling:ctrl + c
    signal(SIGINT, Handler_0IN85_LCD);
    
    /* Module Init */
	if(DEV_ModuleInit() != 0){
        DEV_ModuleExit();
        exit(0);
    }
	
    /* LCD Init */
	printf("1.3inch LCD demo...\r\n");
	LCD_0IN85_Init(VERTICAL);
	LCD_0IN85_Clear(WHITE);
    //LCD_SetBacklight(1023);
	
    UWORD *BlackImage;
    UDOUBLE Imagesize = LCD_0IN85_HEIGHT*LCD_0IN85_WIDTH*2;
    printf("Imagesize = %d\r\n", Imagesize);
    if((BlackImage = (UWORD *)malloc(Imagesize)) == NULL) {
        printf("Failed to apply for black memory...\r\n");
        exit(0);
    }
    // /*1.Create a new image cache named IMAGE_RGB and fill it with white*/
    Paint_NewImage(BlackImage, LCD_0IN85_WIDTH, LCD_0IN85_HEIGHT, 0, WHITE, 16);
    Paint_Clear(WHITE);
	Paint_SetRotate(0);
    // /* GUI */
    printf("drawing...\r\n");
    // /*2.Drawing on the image*/
    Paint_DrawString_EN(5, 10, "123",        &Font24,  YELLOW, RED);  
	Paint_DrawString_EN(5, 34, "ABC",        &Font24,  BLUE,   CYAN);
    Paint_DrawFloatNum (5, 58 ,987.654321,3, &Font12,  WHITE,  BLACK);
	Paint_DrawString_CN(0,80, "Î¢Ñ©µç×Ó",   &Font24CN,WHITE,  RED);
    LCD_0IN85_Display(BlackImage);
 	DEV_Delay_ms(3000);
	Paint_Clear(WHITE);
	
	Paint_DrawCircle(35,50,  25,        BLUE    ,DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
	Paint_DrawCircle(65,50,  25,        BLACK   ,DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
	Paint_DrawCircle(95,50,  25,        RED     ,DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
	Paint_DrawCircle(50,75,  25,        YELLOW  ,DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
	Paint_DrawCircle(80,75,  25,        GREEN   ,DOT_PIXEL_2X2,DRAW_FILL_EMPTY);
    LCD_0IN85_Display(BlackImage);
    DEV_Delay_ms(3000);
    Paint_Clear(BLACK);
    /* show bmp */
	printf("show bmp\r\n");
	GUI_ReadBmp("./pic/LCD_0inch85.bmp");
    
    LCD_0IN85_Display(BlackImage);
    DEV_Delay_ms(2000);
    
    /* Module Exit */
    free(BlackImage);
    BlackImage = NULL;
	DEV_ModuleExit();
}

