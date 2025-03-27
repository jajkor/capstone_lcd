#!/usr/bin/python
# -*- coding: UTF-8 -*-
#import chardet
import os
import sys 
import time
import logging
import socket
import spidev as SPI
sys.path.append("..")
from lib import LCD_1inch69
from PIL import Image, ImageDraw, ImageFont

# Raspberry Pi pin configuration:
RST = 27
DC = 25
BL = 18
bus = 0 
device = 0 
logging.basicConfig(level = logging.DEBUG)

def get_network_info():
    try:
        ssid = os.popen("iwgetid -r").read()

        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.connect(("8.8.8.8", 80))
        ip_address = s.getsockname()[0]
        s.close()
        return ssid, ip_address
    except Exception:
        return "None", "None"

try:
    # display with hardware SPI:
    ''' Warning!!!Don't  creation of multiple displayer objects!!! '''
    #disp = LCD_1inch69.LCD_1inch69(spi=SPI.SpiDev(bus, device),spi_freq=10000000,rst=RST,dc=DC,bl=BL)
    disp = LCD_1inch69.LCD_1inch69()
    # Initialize library.
    disp.Init()
    # Clear display.
    disp.clear()
    #Set the backlight to 100
    disp.bl_DutyCycle(50)

    Font3 = ImageFont.truetype("../Font/Font02.ttf", 32)


    while True:
        # Create blank image for drawing.
        image2 = Image.new("RGB", (disp.height,disp.width ), "BLACK")
        draw = ImageDraw.Draw(image2)

        host_name, ip_address = get_network_info()

        draw.text((22, 22), "HOST: " + host_name, fill = "WHITE", font=Font3)
        draw.text((22, 62), "IP: " + ip_address, fill = "WHITE", font=Font3)
        image2=image2.rotate(0)
        disp.ShowImage(image2)

    disp.module_exit()
    logging.info("quit:")
    
except IOError as e:
    logging.info(e)    
    
except KeyboardInterrupt:
    disp.module_exit()
    logging.info("quit:")
    exit()
