# Extended Super Simon
Inspired by [this Hackaday project](https://hackaday.com/2016/12/31/tiny-game-of-simon-on-an-attiny13/)
Parts of that code were adapted to my version (mainly in simon.c)
# Demo
![Photo](https://github.com/roman-oberenkowski/ext-super-simon/blob/439cec614d1024ddc54e4d4cfaf007ceecc2a929/readme_resources/image.jpg)
# Video demo
- Game demo: [Link](https://mega.nz/file/ERETgDTL#8WjVBw2f1JaynFDqS6BCI4y_ScoYtYXVx-7Yk8EPEzM)
- Set text demo: [Link](https://mega.nz/file/AAMgxKTI#T9gVQXDIDjVFTvOzm8CTvg5Iv-4GHJlT4ohppsRxDGg)

# Original game rules 
Press color coded buttons in the same order as you are shown. Every time you do that correctly, the sequence gets longer by one. Even one mistake results in game over.

# Extended part
Every time you input sequence correctly you are shown one more letter of the "secret text".

# How to start
- Boot the console and press RED, GREEN or BLUE button
- If you press YELLOW, than you enter editing mode - you can easily set new "secret text". Don't worry, you cannot read the previously set text in edit mode :)

# Edit mode - controls
- YELLOW changes current letter to next in the alphabet (a->b)
- BLUE changes current letter to previous in the alphabet (b->a)
- All segments lit on the 16-segment display means 'end character'
- RED goes back one position in 'secret text' string
- GREEN goes one position forward (if selected character is 'end character' than it saves choosen text)

# Special modes
Hold specific button and press `RESET` (code checks if any button is pressed at startup)
- `RED` Pressed at startup -> Don't start (go to sleep immediately)
- `YELLOW` Pressed at startup -> Program EEPROM with hardcoded text1  
- `BLUE` Pressed at startup -> Program EEPROM with hardcoded text2

# Schematic
![Schematic](https://github.com/roman-oberenkowski/super-simon/blob/38c23dbe415070697ed50af558a2374dfa718a67/Schematic/SimonSchematic.png)

# Parts
- 16-segment LED display
- Laptop battery casing
- 2x 17650 Li-ion (demounted from the same battery)
- Powerbank circuit (to supply 5V and charge )
- 4 LEDs (4 diffrent colors)
- 6x Button (4 for colors and one for Powerbank circuit, and last for Atmega reset)
- Goldpin for programming port on the back
- (optional) 2x USB connector for charging other devices


