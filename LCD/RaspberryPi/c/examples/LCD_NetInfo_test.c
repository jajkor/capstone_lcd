#include "DEV_Config.h"
#include "LCD_1in69.h"
#include "GUI_Paint.h"
#include "GUI_BMP.h"
#include "test.h"
#include <stdio.h>      //printf()
#include <stdlib.h>     //exit()
#include <signal.h>     //signal()
#include <unistd.h>

void LCD_NetInfo_test(char* host, char* ssid, char* ip)
{
	// Exception handling:ctrl + c
	signal(SIGINT, Handler_1IN69_LCD);

	/* Module Init */
	if(DEV_ModuleInit() != 0){
		DEV_ModuleExit();
		exit(0);
	}

	/* LCD Init */
	printf("1.69inch LCD NetInfo demo...\r\n");
	LCD_1IN69_Init(VERTICAL);
	LCD_1IN69_Clear(WHITE);

	LCD_SetBacklight(1023);

	UWORD *BlackImage;
	UDOUBLE Imagesize = LCD_1IN69_HEIGHT * LCD_1IN69_WIDTH * 2;
	printf("Imagesize = %d\r\n", Imagesize);
	if((BlackImage = (UWORD *)malloc(Imagesize)) == NULL) {
		printf("Failed to apply for black memory...\r\n");
		exit(0);
	}
	char ssidStr[64] = "SSID: ";
	strcat(ssidStr, ssid);

	char ipStr[64] = "IP: ";
	strcat(ipStr, ip);

	Paint_NewImage(BlackImage, LCD_1IN69_WIDTH, LCD_1IN69_HEIGHT, 90, BLACK, 16);
//	while (1) {
		Paint_Clear(BLACK);

		Paint_DrawString_EN(LCD_1IN69_WIDTH / 2, 20, host, &Font24, BLACK, WHITE);
		Paint_DrawString_EN(10, 60, ssidStr, &Font20, BLACK, WHITE);
		Paint_DrawString_EN(10, 90, ipStr, &Font20, BLACK, WHITE);

		LCD_1IN69_DisplayWindows(0, 0, LCD_1IN69_WIDTH, LCD_1IN69_HEIGHT, BlackImage);
//	}

	//  Module Exit 
	free(BlackImage);
	BlackImage = NULL;
	DEV_ModuleExit();
}

