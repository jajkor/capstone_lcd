#!/bin/bash

LCD_VERSION="1.699"

# Get hostname, NETWORK, and IP
HOSTNAME=$(hostname)

# Get NETWORK with fallback
NETWORK="SSID: $(nmcli connection show --active | grep wifi | awk '{print $1}')"
if [ -z "$NETWORK" ]; then
  NETWORK="WIRED: " + $(nmcli connection show --active | grep ethernet | awk '{print $1}')
fi

if [ -z "$NETWORK" ]; then
  NETWORK="None"
fi

IP=$(hostname -I | awk '{print $1}')
if [ -z "$IP" ]; then
  IP="None"
fi

# Pass to C program
/opt/LCD/RaspberryPi/c/main $LCD_VERSION $HOSTNAME $NETWORK $IP
#echo $LCD_VERSION $HOSTNAME $NETWORK $IP
