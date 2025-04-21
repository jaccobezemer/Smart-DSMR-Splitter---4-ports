## Flash

I've made this github repository long time after I created this splitter.
I used PlatformIO and a microUPDI to build and flash.

+ [microUPDI](https://github.com/MCUdude/microUPDI)

I'm not sure how the commandline would be to flash the firmware. I think it would be something like:

`avrdude -C avrdude.conf -v -p atmega4809 -c xplainedmini_updi`

