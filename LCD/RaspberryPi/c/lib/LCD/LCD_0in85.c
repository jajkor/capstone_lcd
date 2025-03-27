/*****************************************************************************
* | File      	:   LCD_0IN85_0IN85.c
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
#include "LCD_0in85.h"
#include "DEV_Config.h"

#include <stdlib.h>		//itoa()
#include <stdio.h>

//LCD_0IN85_ATTRIBUTES LCD;


/******************************************************************************
function :	Hardware reset
parameter:
******************************************************************************/
static void LCD_0IN85_Reset(void)
{
    LCD_0IN85_RST_1;
    DEV_Delay_ms(100);
    LCD_0IN85_RST_0;
    DEV_Delay_ms(100);
    LCD_0IN85_RST_1;
    DEV_Delay_ms(100);
}

/******************************************************************************
function :	send command
parameter:
     Reg : Command register
******************************************************************************/
static void LCD_0IN85_SendCommand(UBYTE Reg)
{
    LCD_0IN85_DC_0;
    // LCD_0IN85_CS_0;
    DEV_SPI_WriteByte(Reg);
    // LCD_0IN85_CS_1;
}

/******************************************************************************
function :	send data
parameter:
    Data : Write data
******************************************************************************/
static void LCD_0IN85_SendData_8Bit(UBYTE Data)
{
    LCD_0IN85_DC_1;
    // LCD_0IN85_CS_0;
    DEV_SPI_WriteByte(Data);
    // LCD_0IN85_CS_1;
}

/******************************************************************************
function :	send data
parameter:
    Data : Write data
******************************************************************************/
static void LCD_0IN85_SendData_16Bit(UWORD Data)
{
    LCD_0IN85_DC_1;
    // LCD_0IN85_CS_0;
    DEV_SPI_WriteByte((Data >> 8) & 0xFF);
    DEV_SPI_WriteByte(Data & 0xFF);
    // LCD_0IN85_CS_1;
}

/******************************************************************************
function :	Initialize the lcd register
parameter:
******************************************************************************/
static void LCD_0IN85_InitReg(void)
{
	LCD_0IN85_SendCommand(0xB0);		
	LCD_0IN85_SendData_8Bit(0xC0); 
	LCD_0IN85_SendCommand(0xB2);			
	LCD_0IN85_SendData_8Bit(0x2F); 
	LCD_0IN85_SendCommand(0xB3);		
	LCD_0IN85_SendData_8Bit(0x03);
	LCD_0IN85_SendCommand(0xB6);		
	LCD_0IN85_SendData_8Bit(0x19); 
	LCD_0IN85_SendCommand(0xB7);		
	LCD_0IN85_SendData_8Bit(0x01);  
	
	LCD_0IN85_SendCommand(0xAC);
	LCD_0IN85_SendData_8Bit(0xCB);
	LCD_0IN85_SendCommand(0xAB); 
	LCD_0IN85_SendData_8Bit(0x0e);
		
	LCD_0IN85_SendCommand(0xB4);	
	LCD_0IN85_SendData_8Bit(0x04);
	
	LCD_0IN85_SendCommand(0xA8);
	LCD_0IN85_SendData_8Bit(0x19);

	LCD_0IN85_SendCommand(0x3A);		
	LCD_0IN85_SendData_8Bit(0x05); 

	LCD_0IN85_SendCommand(0xb8);
	LCD_0IN85_SendData_8Bit(0x08);
 
	LCD_0IN85_SendCommand(0xE8);
	LCD_0IN85_SendData_8Bit(0x24);

	LCD_0IN85_SendCommand(0xE9);
	LCD_0IN85_SendData_8Bit(0x48);

	LCD_0IN85_SendCommand(0xea);	
	LCD_0IN85_SendData_8Bit(0x22);

 			
	LCD_0IN85_SendCommand(0xC6);
	LCD_0IN85_SendData_8Bit(0x30);
	LCD_0IN85_SendCommand(0xC7);
	LCD_0IN85_SendData_8Bit(0x18);

	LCD_0IN85_SendCommand(0xF0);
	LCD_0IN85_SendData_8Bit(0x1F);
	LCD_0IN85_SendData_8Bit(0x28);
	LCD_0IN85_SendData_8Bit(0x04);
	LCD_0IN85_SendData_8Bit(0x3E);
	LCD_0IN85_SendData_8Bit(0x2A);
	LCD_0IN85_SendData_8Bit(0x2E);
	LCD_0IN85_SendData_8Bit(0x20);
	LCD_0IN85_SendData_8Bit(0x00);
	LCD_0IN85_SendData_8Bit(0x0C);
	LCD_0IN85_SendData_8Bit(0x06);
	LCD_0IN85_SendData_8Bit(0x00);
	LCD_0IN85_SendData_8Bit(0x1C);
	LCD_0IN85_SendData_8Bit(0x1F);
	LCD_0IN85_SendData_8Bit(0x0f);

	LCD_0IN85_SendCommand(0xF1); 
	LCD_0IN85_SendData_8Bit(0X00);
	LCD_0IN85_SendData_8Bit(0X2D);
	LCD_0IN85_SendData_8Bit(0X2F);
	LCD_0IN85_SendData_8Bit(0X3C);
	LCD_0IN85_SendData_8Bit(0X6F);
	LCD_0IN85_SendData_8Bit(0X1C);
	LCD_0IN85_SendData_8Bit(0X0B);
	LCD_0IN85_SendData_8Bit(0X00);
	LCD_0IN85_SendData_8Bit(0X00);
	LCD_0IN85_SendData_8Bit(0X00);
	LCD_0IN85_SendData_8Bit(0X07);
	LCD_0IN85_SendData_8Bit(0X0D);
	LCD_0IN85_SendData_8Bit(0X11);
	LCD_0IN85_SendData_8Bit(0X0f);

    LCD_0IN85_SendCommand(0x21);  //Display Inversion On

    LCD_0IN85_SendCommand(0x11);  //Sleep Out

    LCD_0IN85_SendCommand(0x29);  //Display On
}

/********************************************************************************
function:	Set the resolution and scanning method of the screen
parameter:
		Scan_dir:   Scan direction
********************************************************************************/
static void LCD_0IN85_SetAttributes(UBYTE Scan_dir)
{
    //Get the screen scan direction
    LCD.SCAN_DIR = Scan_dir;
    UBYTE MemoryAccessReg = 0x00;

    //Get GRAM and LCD width and height
    if(Scan_dir == HORIZONTAL) {
        LCD.HEIGHT	= LCD_0IN85_HEIGHT;
        LCD.WIDTH   = LCD_0IN85_WIDTH;
        MemoryAccessReg = 0X70;
    } else {
        LCD.HEIGHT	= LCD_0IN85_WIDTH;
        LCD.WIDTH   = LCD_0IN85_HEIGHT;
        MemoryAccessReg = 0XC8;
    }

    // Set the read / write scan direction of the frame memory
    LCD_0IN85_SendCommand(0x36); //MX, MY, RGB mode
    LCD_0IN85_SendData_8Bit(MemoryAccessReg);	//0x08 set RGB
}

/********************************************************************************
function :	Initialize the lcd
parameter:
********************************************************************************/
void LCD_0IN85_Init(UBYTE Scan_dir)
{
    //Turn on the backlight
    LCD_0IN85_BL_1;

    //Hardware reset
    LCD_0IN85_Reset();

    //Set the resolution and scanning method of the screen
    LCD_0IN85_SetAttributes(Scan_dir);
    
    //Set the initialization register
    LCD_0IN85_InitReg();
}

/********************************************************************************
function:	Sets the start position and size of the display area
parameter:
		Xstart 	:   X direction Start coordinates
		Ystart  :   Y direction Start coordinates
		Xend    :   X direction end coordinates
		Yend    :   Y direction end coordinates
********************************************************************************/
void LCD_0IN85_SetWindows(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend)
{
	Xstart = Xstart + 2;
	Xend = Xend +  2;	
    Ystart = Ystart + 1;
    Yend = Yend + 1;

    //set the X coordinates
    LCD_0IN85_SendCommand(0x2A);
    LCD_0IN85_SendData_8Bit((Xstart >> 8) & 0xFF);
    LCD_0IN85_SendData_8Bit(Xstart & 0xFF);
    LCD_0IN85_SendData_8Bit(((Xend  - 1) >> 8) & 0xFF);
    LCD_0IN85_SendData_8Bit((Xend  - 1) & 0xFF);

    //set the Y coordinates
    LCD_0IN85_SendCommand(0x2B);
    LCD_0IN85_SendData_8Bit((Ystart >> 8) & 0xFF);
    LCD_0IN85_SendData_8Bit(Ystart & 0xFF);
    LCD_0IN85_SendData_8Bit(((Yend  - 1) >> 8) & 0xFF);
    LCD_0IN85_SendData_8Bit((Yend  - 1) & 0xFF);

    LCD_0IN85_SendCommand(0X2C);
}

/******************************************************************************
function :	Clear screen
parameter:
******************************************************************************/
void LCD_0IN85_Clear(UWORD Color)
{
    UWORD j;
    UWORD Image[LCD_0IN85_WIDTH*LCD_0IN85_HEIGHT];
    
    Color = ((Color<<8)&0xff00)|(Color>>8);
   
    for (j = 0; j < LCD_0IN85_HEIGHT*LCD_0IN85_WIDTH; j++) {
        Image[j] = Color;
    }
    
    LCD_0IN85_SetWindows(0, 0, LCD_0IN85_WIDTH, LCD_0IN85_HEIGHT);
    LCD_0IN85_DC_1;
    for(j = 0; j < LCD_0IN85_HEIGHT; j++){
        DEV_SPI_Write_nByte((uint8_t *)&Image[j*LCD_0IN85_WIDTH], LCD_0IN85_WIDTH*2);
    }
}

/******************************************************************************
function :	Sends the image buffer in RAM to displays
parameter:
******************************************************************************/
void LCD_0IN85_Display(UWORD *Image)
{
    UWORD j;
    LCD_0IN85_SetWindows(0, 0, LCD_0IN85_WIDTH, LCD_0IN85_HEIGHT);
    LCD_0IN85_DC_1;
    for (j = 0; j < LCD_0IN85_HEIGHT; j++) {
        DEV_SPI_Write_nByte((uint8_t *)&Image[j*LCD_0IN85_WIDTH], LCD_0IN85_WIDTH*2);
    }
}

void LCD_0IN85_DisplayWindows(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD *Image)
{
    // display
    UDOUBLE Addr = 0;

    UWORD j;
    LCD_0IN85_SetWindows(Xstart, Ystart, Xend , Yend);
    LCD_0IN85_DC_1;
    for (j = Ystart; j < Yend - 1; j++) {
        Addr = Xstart + j * LCD_0IN85_WIDTH ;
        DEV_SPI_Write_nByte((uint8_t *)&Image[Addr], (Xend-Xstart)*2);
    }
}

void LCD_0IN85_DisplayPoint(UWORD X, UWORD Y, UWORD Color)
{
    LCD_0IN85_SetWindows(X,Y,X,Y);
    LCD_0IN85_SendData_16Bit(Color);
}

void  Handler_0IN85_LCD(int signo)
{
    //System Exit
    printf("\r\nHandler:Program stop\r\n");     
    DEV_ModuleExit();
	exit(0);
}
