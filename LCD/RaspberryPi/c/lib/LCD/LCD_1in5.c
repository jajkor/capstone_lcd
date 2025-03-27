/*****************************************************************************
* | File      	:   LCD_1IN5_1in3.c
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
#include "LCD_1in5.h"
#include "DEV_Config.h"

#include <stdlib.h>		//itoa()
#include <stdio.h>

//LCD_1IN5_ATTRIBUTES LCD;


/******************************************************************************
function :	Hardware reset
parameter:
******************************************************************************/
static void LCD_1IN5_Reset(void)
{
    LCD_1IN5_RST_1;
    DEV_Delay_ms(100);
    LCD_1IN5_RST_0;
    DEV_Delay_ms(100);
    LCD_1IN5_RST_1;
    DEV_Delay_ms(100);
}

/******************************************************************************
function :	send command
parameter:
     Reg : Command register
******************************************************************************/
static void LCD_1IN5_SendCommand(UBYTE Reg)
{
    LCD_1IN5_DC_0;
    // LCD_1IN5_CS_0;
    DEV_SPI_WriteByte(Reg);
    // LCD_1IN5_CS_1;
}

/******************************************************************************
function :	send data
parameter:
    Data : Write data
******************************************************************************/
static void LCD_1IN5_SendData_8Bit(UBYTE Data)
{
    LCD_1IN5_DC_1;
    // LCD_1IN5_CS_0;
    DEV_SPI_WriteByte(Data);
    // LCD_1IN5_CS_1;
}

/******************************************************************************
function :	send data
parameter:
    Data : Write data
******************************************************************************/
static void LCD_1IN5_SendData_16Bit(UWORD Data)
{
    LCD_1IN5_DC_1;
    // LCD_1IN5_CS_0;
    DEV_SPI_WriteByte((Data >> 8) & 0xFF);
    DEV_SPI_WriteByte(Data & 0xFF);
    // LCD_1IN5_CS_1;
}

/******************************************************************************
function :	Initialize the lcd register
parameter:
******************************************************************************/
static void LCD_1IN5_InitReg(void)
{
LCD_1IN5_SendCommand(0xfd);//private_access
	LCD_1IN5_SendData_8Bit(0x06);
	LCD_1IN5_SendData_8Bit(0x08);

	LCD_1IN5_SendCommand(0x61);//add
	LCD_1IN5_SendData_8Bit(0x07);//
	LCD_1IN5_SendData_8Bit(0x04);//

	LCD_1IN5_SendCommand(0x62);//bias setting
	LCD_1IN5_SendData_8Bit(0x00);//00
	LCD_1IN5_SendData_8Bit(0x44);//44
	LCD_1IN5_SendData_8Bit(0x45);//40  47

	LCD_1IN5_SendCommand(0x63);//
	LCD_1IN5_SendData_8Bit(0x41);//
	LCD_1IN5_SendData_8Bit(0x07);//
	LCD_1IN5_SendData_8Bit(0x12);//
	LCD_1IN5_SendData_8Bit(0x12);//

	LCD_1IN5_SendCommand(0x64);//
	LCD_1IN5_SendData_8Bit(0x37);//
	//VSP
	LCD_1IN5_SendCommand(0x65);//Pump1=4.7MHz //PUMP1 VSP
	LCD_1IN5_SendData_8Bit(0x09);//D6-5:pump1_clk[1:0] clamp 28 2b
	LCD_1IN5_SendData_8Bit(0x10);//6.26
	LCD_1IN5_SendData_8Bit(0x21);
	//VSN
	LCD_1IN5_SendCommand(0x66); //pump=2 AVCL
	LCD_1IN5_SendData_8Bit(0x09); //clamp 08 0b 09
	LCD_1IN5_SendData_8Bit(0x10); //10
	LCD_1IN5_SendData_8Bit(0x21);
	//add source_neg_time
	LCD_1IN5_SendCommand(0x67);//pump_sel
	LCD_1IN5_SendData_8Bit(0x21);//21 20
	LCD_1IN5_SendData_8Bit(0x40);

	//gamma vap/van
	LCD_1IN5_SendCommand(0x68);//gamma vap/van
	LCD_1IN5_SendData_8Bit(0x90);//
	LCD_1IN5_SendData_8Bit(0x4c);//
	LCD_1IN5_SendData_8Bit(0x50);//VCOM  
	LCD_1IN5_SendData_8Bit(0x70);//

	LCD_1IN5_SendCommand(0xb1);//frame rate
	LCD_1IN5_SendData_8Bit(0x0F);//0x0f fr_h[5:0] 0F
	LCD_1IN5_SendData_8Bit(0x02);//0x02 fr_v[4:0] 02
	LCD_1IN5_SendData_8Bit(0x01);//0x04 fr_div[2:0] 04

	LCD_1IN5_SendCommand(0xB4);
	LCD_1IN5_SendData_8Bit(0x01); //01:1dot 00:column
	////porch
	LCD_1IN5_SendCommand(0xB5);
	LCD_1IN5_SendData_8Bit(0x02);//0x02 vfp[6:0]
	LCD_1IN5_SendData_8Bit(0x02);//0x02 vbp[6:0]
	LCD_1IN5_SendData_8Bit(0x0a);//0x0A hfp[6:0]
	LCD_1IN5_SendData_8Bit(0x14);//0x14 hbp[6:0]

	LCD_1IN5_SendCommand(0xB6);
	LCD_1IN5_SendData_8Bit(0x04);//
	LCD_1IN5_SendData_8Bit(0x01);//
	LCD_1IN5_SendData_8Bit(0x9f);//
	LCD_1IN5_SendData_8Bit(0x00);//
	LCD_1IN5_SendData_8Bit(0x02);//
	////gamme sel
	LCD_1IN5_SendCommand(0xdf);//
	LCD_1IN5_SendData_8Bit(0x11);//gofc_gamma_en_sel=1
	////gamma_test1 A1#_wangly
	//3030b_gamma_new_
	//GAMMA---------------------------------/////////////

	//GAMMA---------------------------------/////////////
	LCD_1IN5_SendCommand(0xE2);	
	LCD_1IN5_SendData_8Bit(0x03);//vrp0[5:0]	V0 03
	LCD_1IN5_SendData_8Bit(0x00);//vrp1[5:0]	V1 
	LCD_1IN5_SendData_8Bit(0x00);//vrp2[5:0]	V2 
	LCD_1IN5_SendData_8Bit(0x30);//vrp3[5:0]	V61 
	LCD_1IN5_SendData_8Bit(0x33);//vrp4[5:0]	V62 
	LCD_1IN5_SendData_8Bit(0x3f);//vrp5[5:0]	V63

	LCD_1IN5_SendCommand(0xE5);	
	LCD_1IN5_SendData_8Bit(0x3f);//vrn0[5:0]	V63
	LCD_1IN5_SendData_8Bit(0x33);//vrn1[5:0]	V62	
	LCD_1IN5_SendData_8Bit(0x30);//vrn2[5:0]	V61 
	LCD_1IN5_SendData_8Bit(0x00);//vrn3[5:0]	V2 
	LCD_1IN5_SendData_8Bit(0x00);//vrn4[5:0]	V1 
	LCD_1IN5_SendData_8Bit(0x03);//vrn5[5:0]  V0 03

	LCD_1IN5_SendCommand(0xE1);	
	LCD_1IN5_SendData_8Bit(0x05);//prp0[6:0]	V15
	LCD_1IN5_SendData_8Bit(0x67);//prp1[6:0]	V51 

	LCD_1IN5_SendCommand(0xE4);	
	LCD_1IN5_SendData_8Bit(0x67);//prn0[6:0]	V51 
	LCD_1IN5_SendData_8Bit(0x06);//prn1[6:0]  V15

	LCD_1IN5_SendCommand(0xE0);
	LCD_1IN5_SendData_8Bit(0x05);//pkp0[4:0]	V3 
	LCD_1IN5_SendData_8Bit(0x06);//pkp1[4:0]	V7  
	LCD_1IN5_SendData_8Bit(0x0A);//pkp2[4:0]	V21
	LCD_1IN5_SendData_8Bit(0x0C);//pkp3[4:0]	V29 
	LCD_1IN5_SendData_8Bit(0x0B);//pkp4[4:0]	V37 
	LCD_1IN5_SendData_8Bit(0x0B);//pkp5[4:0]	V45 
	LCD_1IN5_SendData_8Bit(0x13);//pkp6[4:0]	V56 
	LCD_1IN5_SendData_8Bit(0x19);//pkp7[4:0]	V60 

	LCD_1IN5_SendCommand(0xE3);	
	LCD_1IN5_SendData_8Bit(0x18);//pkn0[4:0]	V60 
	LCD_1IN5_SendData_8Bit(0x13);//pkn1[4:0]	V56 
	LCD_1IN5_SendData_8Bit(0x0D);//pkn2[4:0]	V45 
	LCD_1IN5_SendData_8Bit(0x09);//pkn3[4:0]	V37 
	LCD_1IN5_SendData_8Bit(0x0B);//pkn4[4:0]	V29 
	LCD_1IN5_SendData_8Bit(0x0B);//pkn5[4:0]	V21 
	LCD_1IN5_SendData_8Bit(0x05);//pkn6[4:0]	V7  
	LCD_1IN5_SendData_8Bit(0x06);//pkn7[4:0]	V3 
	//GAMMA---------------------------------/////////////

	//source
	LCD_1IN5_SendCommand(0xE6);
	LCD_1IN5_SendData_8Bit(0x00);
	LCD_1IN5_SendData_8Bit(0xff);//SC_EN_START[7:0] f0

	LCD_1IN5_SendCommand(0xE7);
	LCD_1IN5_SendData_8Bit(0x01);//CS_START[3:0] 01
	LCD_1IN5_SendData_8Bit(0x04);//scdt_inv_sel cs_vp_en
	LCD_1IN5_SendData_8Bit(0x03);//CS1_WIDTH[7:0] 12
	LCD_1IN5_SendData_8Bit(0x03);//CS2_WIDTH[7:0] 12
	LCD_1IN5_SendData_8Bit(0x00);//PREC_START[7:0] 06
	LCD_1IN5_SendData_8Bit(0x12);//PREC_WIDTH[7:0] 12

	LCD_1IN5_SendCommand(0xE8); //source
	LCD_1IN5_SendData_8Bit(0x00); //VCMP_OUT_EN 81-
	LCD_1IN5_SendData_8Bit(0x70); //chopper_sel[6:4]
	LCD_1IN5_SendData_8Bit(0x00); //gchopper_sel[6:4] 60
	////gate
	LCD_1IN5_SendCommand(0xEc);
	LCD_1IN5_SendData_8Bit(0x52);//52

	LCD_1IN5_SendCommand(0xF1);
	LCD_1IN5_SendData_8Bit(0x01);//te_pol tem_extend 00 01 03
	LCD_1IN5_SendData_8Bit(0x01);
	LCD_1IN5_SendData_8Bit(0x02);


	LCD_1IN5_SendCommand(0xF6);
	LCD_1IN5_SendData_8Bit(0x01);
	LCD_1IN5_SendData_8Bit(0x30);
	LCD_1IN5_SendData_8Bit(0x00);//
	LCD_1IN5_SendData_8Bit(0x00);//40 3Ïß2Í¨µÀ

	LCD_1IN5_SendCommand(0xfd);
	LCD_1IN5_SendData_8Bit(0xfa);
	LCD_1IN5_SendData_8Bit(0xfc);

	LCD_1IN5_SendCommand(0x3a);
	LCD_1IN5_SendData_8Bit(0x55);//

	LCD_1IN5_SendCommand(0x35);
	LCD_1IN5_SendData_8Bit(0x00);

    LCD_1IN5_SendCommand(0x21);  //Display Inversion On

    LCD_1IN5_SendCommand(0x11);  //Sleep Out

    LCD_1IN5_SendCommand(0x29);  //Display On
}

/********************************************************************************
function:	Set the resolution and scanning method of the screen
parameter:
		Scan_dir:   Scan direction
********************************************************************************/
static void LCD_1IN5_SetAttributes(UBYTE Scan_dir)
{
    //Get the screen scan direction
    LCD.SCAN_DIR = Scan_dir;
    UBYTE MemoryAccessReg = 0x00;

    //Get GRAM and LCD width and height
    if(Scan_dir == HORIZONTAL) {
        LCD.HEIGHT	= LCD_1IN5_HEIGHT;
        LCD.WIDTH   = LCD_1IN5_WIDTH;
        MemoryAccessReg = 0X70;
    } else {
        LCD.HEIGHT	= LCD_1IN5_WIDTH;
        LCD.WIDTH   = LCD_1IN5_HEIGHT;
        MemoryAccessReg = 0X00;
    }

    // Set the read / write scan direction of the frame memory
    LCD_1IN5_SendCommand(0x36); //MX, MY, RGB mode
    LCD_1IN5_SendData_8Bit(MemoryAccessReg);	//0x08 set RGB
}

/********************************************************************************
function :	Initialize the lcd
parameter:
********************************************************************************/
void LCD_1IN5_Init(UBYTE Scan_dir)
{
    //Turn on the backlight
    LCD_1IN5_BL_1;

    //Hardware reset
    LCD_1IN5_Reset();

    //Set the resolution and scanning method of the screen
    LCD_1IN5_SetAttributes(Scan_dir);
    
    //Set the initialization register
    LCD_1IN5_InitReg();
}

/********************************************************************************
function:	Sets the start position and size of the display area
parameter:
		Xstart 	:   X direction Start coordinates
		Ystart  :   Y direction Start coordinates
		Xend    :   X direction end coordinates
		Yend    :   Y direction end coordinates
********************************************************************************/
void LCD_1IN5_SetWindows(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend)
{
	// Xstart = Xstart + 2;
	// Xend = Xend +  2;	
    Ystart = Ystart + 20;
    Yend = Yend + 20;

    //set the X coordinates
    LCD_1IN5_SendCommand(0x2A);
    LCD_1IN5_SendData_8Bit((Xstart >> 8) & 0xFF);
    LCD_1IN5_SendData_8Bit(Xstart & 0xFF);
    LCD_1IN5_SendData_8Bit(((Xend  - 1) >> 8) & 0xFF);
    LCD_1IN5_SendData_8Bit((Xend  - 1) & 0xFF);

    //set the Y coordinates
    LCD_1IN5_SendCommand(0x2B);
    LCD_1IN5_SendData_8Bit((Ystart >> 8) & 0xFF);
    LCD_1IN5_SendData_8Bit(Ystart & 0xFF);
    LCD_1IN5_SendData_8Bit(((Yend  - 1) >> 8) & 0xFF);
    LCD_1IN5_SendData_8Bit((Yend  - 1) & 0xFF);

    LCD_1IN5_SendCommand(0X2C);
}

/******************************************************************************
function :	Clear screen
parameter:
******************************************************************************/
void LCD_1IN5_Clear(UWORD Color)
{
    UDOUBLE j;
    UWORD Image[LCD_1IN5_WIDTH*LCD_1IN5_HEIGHT];
    
    Color = ((Color<<8)&0xff00)|(Color>>8);
   
    for (j = 0; j < LCD_1IN5_HEIGHT*LCD_1IN5_WIDTH; j++) {
        Image[j] = Color;
    }
    
    LCD_1IN5_SetWindows(0, 0, LCD_1IN5_WIDTH, LCD_1IN5_HEIGHT);
    LCD_1IN5_DC_1;
    for(j = 0; j < LCD_1IN5_HEIGHT; j++){
        DEV_SPI_Write_nByte((uint8_t *)&Image[j*LCD_1IN5_WIDTH], LCD_1IN5_WIDTH*2);
    }
}

/******************************************************************************
function :	Sends the image buffer in RAM to displays
parameter:
******************************************************************************/
void LCD_1IN5_Display(UWORD *Image)
{
    UWORD j;
    LCD_1IN5_SetWindows(0, 0, LCD_1IN5_WIDTH, LCD_1IN5_HEIGHT);
    LCD_1IN5_DC_1;
    for (j = 0; j < LCD_1IN5_HEIGHT; j++) {
        DEV_SPI_Write_nByte((uint8_t *)&Image[j*LCD_1IN5_WIDTH], LCD_1IN5_WIDTH*2);
    }
}

void LCD_1IN5_DisplayWindows(UWORD Xstart, UWORD Ystart, UWORD Xend, UWORD Yend, UWORD *Image)
{
    // display
    UDOUBLE Addr = 0;

    UWORD j;
    LCD_1IN5_SetWindows(Xstart, Ystart, Xend , Yend);
    LCD_1IN5_DC_1;
    for (j = Ystart; j < Yend - 1; j++) {
        Addr = Xstart + j * LCD_1IN5_WIDTH ;
        DEV_SPI_Write_nByte((uint8_t *)&Image[Addr], (Xend-Xstart)*2);
    }
}

void LCD_1IN5_DisplayPoint(UWORD X, UWORD Y, UWORD Color)
{
    LCD_1IN5_SetWindows(X,Y,X,Y);
    LCD_1IN5_SendData_16Bit(Color);
}

void  Handler_1IN5_LCD(int signo)
{
    //System Exit
    printf("\r\nHandler:Program stop\r\n");     
    DEV_ModuleExit();
	exit(0);
}
