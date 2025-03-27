#!/bin/bash

LCD_VERSION="1.699"

# Get hostname, SSID, and IP
HOSTNAME=$(hostname)

# Get SSID with fallback
SSID=$(iwgetid -r 2>/dev/null)
IP=$(hostname -I | awk '{print $1}')
if [ -z "$SSID" ]; then
  SSID="None"
  IP="None"
fi

# Pass to C program
./main $LCD_VERSION $HOSTNAME $SSID $IP
