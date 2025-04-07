#!/bin/bash

LCD_VERSION="1.699"

HOSTNAME=$(hostname)

NETWORK=$(nmcli connection show --active | grep ethernet | awk '{ print $1 }')
if [[ $NETWORK != "" ]]; then
  NETWORK="WIRED: $NETWORK"
else
  NETWORK=$(nmcli connection show --active | grep wifi | awk '{ print $1 }')
  if [[ $NETWORK != "" ]]; then
    NETWORK="WIFI: $NETWORK"
  else
    NETWORK="NET: N/A"
  fi
fi

IP=$(hostname -I | awk '{ print $1 }')
if [[ "$IP" != "" ]]; then
  IP="IP: $IP"
else
  IP="IP: N/A"
fi

# Pass to C program
/opt/LCD/RaspberryPi/c/main "$LCD_VERSION" "$HOSTNAME" "$NETWORK" "$IP"
