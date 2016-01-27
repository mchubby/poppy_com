#!/bin/sh

sudo apt-get install python-software-properties
sudo apt-add-repository -y ppa:libreoffice/libreoffice-4-2
sudo apt-get update
# sudo apt-get install arduino arduino-core
sudo apt-get install doxygen graphviz

wget http://downloads.arduino.cc/arduino-1.6.5-linux64.tar.xz
tar xf arduino-1.6.5-linux64.tar.xz
sudo mv arduino-1.6.5 /usr/local/share/arduino
sudo ln -s /usr/local/share/arduino/arduino /usr/local/bin/arduino
