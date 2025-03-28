#!/bin/bash

sudo systemctl stop bluetooth

sudo systemctl disable bluetooth
sudo systemctl disable gdm

sudo systemctl disable gnome-remote-desktop
sudo systemctl stop gnome-remote-desktop

sudo systemctl disable cups
sudo systemctl stop cups

sudo systemctl disable cups-browsed
sudo systemctl stop cups-browsed

sudo systemctl disable switcheroo-control
sudo systemctl stop switcheroo-control

sudo systemctl disable ModemManager
sudo systemctl stop ModemManager

sudo systemctl disable docker
sudo systemctl stop docker

sudo systemctl disable snapd
sudo systemctl stop snapd
