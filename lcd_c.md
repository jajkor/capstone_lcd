# Due to performance and resource issues we are converting the LCD Network Info script from Python to C 

## Install lgpio

  wget https://github.com/joan2937/lg/archive/master.zip
  unzip master.zip
  cd lg-master
  sudo make install

## Create systemd units 

  sudo systemctl enable lcd_display.service
  sudo systemctl enable lcd_display.path
  sudo systemctl start lcd_display.path
