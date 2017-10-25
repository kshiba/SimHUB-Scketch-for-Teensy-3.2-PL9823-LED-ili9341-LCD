# DisplayClientV2 for Teensy 3.2 ,PL9823 LED & ILI9341 LCD
Sample VIDEO : https://youtu.be/aUkEF8cC8qU

# Hardware
- Teensy 3.2 
- 2.2" ILI9340 LCD MODULE(e.g. http://www.aitendo.com/product/11963)
- PL9823( can also be used WS2812B module)

# Library
 - Optimized ILI9341 TFT Library for Teensy 3.x (https://github.com/PaulStoffregen/ILI9341_t3)
 - SimHub 5.4.7 (http://www.racedepartment.com/downloads/simhub-diy-sim-racing-dash.10252/)
 - Other library is included  SimHub's _Addon Folder

# Pin assignment
|TEENSY 3.2|ILI9340 LCD|PL9823|
|---|---|---|
|3.3V|VCC|VDD|
|GND|GND|GND|
|10|CS|-|
|14|REST|-|
|15|DC|-|
|12|MISO|-|
|11|MOSI|-|
|13|SCK|-|
|16|-|DIN|

