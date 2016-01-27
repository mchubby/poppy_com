#!/bin/sh

ln -s $PWD /usr/local/share/arduino/libraries/poppy_com
arduino --verify --board arduino:avr:uno extras/template/template.ino
