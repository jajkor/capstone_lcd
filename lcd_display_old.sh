#!/bin/bash
LCD_VERSION="1.699"

# Get hostname and IP
HOSTNAME=$(hostname)
IP=$(hostname -I | awk '{print $1}')

# Check if wlan0 exists
if [ -e /sys/class/net/wlan0 ]; then
  # Check if it's a wireless connection
  if [ -d "/sys/class/net/wlan0/wireless" ] || [ -L "/sys/class/net/wlan0/phy80211" ]; then
    # It's a wireless connection
    NETWORK=$(iwgetid -r 2>/dev/null)
  else
    # It's a wired connection over wlan0 interface
    if command -v nmcli &>/dev/null; then
      # Try to get connection name from NetworkManager
      NETWORK=$(nmcli -t -f NAME,DEVICE connection show --active | grep ":wlan0$" | cut -d: -f1)
      if [ -z "$NETWORK" ]; then
        NETWORK="Ethernet"
      fi
    else
      # Fallback if nmcli is not available
      NETWORK="Ethernet"
    fi
  fi
else
  NETWORK="None"
fi

# If NETWORK is still empty, set it to None
if [ -z "$NETWORK" ]; then
  NETWORK="None"
fi

# Pass to C program
#/opt/LCD/RaspberryPi/c/main $LCD_VERSION $HOSTNAME $NETWORK $IP
echo $LCD_VERSION $HOSTNAME $NETWORK $IP
