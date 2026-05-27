#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "DHT.h"


#define DHTPIN 8       // Pin connected to the DHT sensor
#define DHTTYPE DHT11  // Define your sensor type

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// Set OLED_RESET to -1 if your display doesn't have a physical reset pin
#define OLED_RESET     -1 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Initialize the display. 
  // Change 0x3C to 0x3D if your specific screen requires it.
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    for(;;); // Don't proceed, loop forever if initialization fails
  }
  pinMode(11,OUTPUT);
  dht.begin();

  // Clear the buffer (Adafruit displays show a splash screen by default)
  //display.clearDisplay();

  // Set text size (1 is small, 2 is medium, 3 is large)
  display.setTextSize(1);      
  
  // Set text color (always WHITE for monochrome OLEDs)
  display.setTextColor(SSD1306_WHITE); 
  
  // Set the cursor position (X, Y) coordinates
  //display.setCursor(0, 1);     
  
  // Print the message to the internal buffer
  //display.println("Albert");
  
  //display.setCursor(0, 10);
  //display.println(F("World!"));

  // Push the buffer contents to the actual physical screen
  display.display();
  digitalWrite(11,HIGH);

}

void loop() {
  delay(2000);  

  display.clearDisplay();

  // Nothing needed in the loop for a static message!
  float f = dht.readTemperature(true);

  if(isnan(f)){
    display.setCursor(0, 0);
    display.println("NO TEMPERATURE");  
  }else{
    display.setCursor(0, 0);
    display.println(f);
    display.setCursor(0, 12);
    display.println("DEGREES FARENHEIGHT");
  }

  display.display();
}