#include <FastLED.h>

// stuff related to FastLED
#define LED_PIN     8
#define NUM_LEDS    19
#define BRIGHTNESS  50
#define LED_TYPE    WS2811
#define COLOR_ORDER RGB

CRGB leds[NUM_LEDS];


char inChar;
String inString = "";            // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete



//********************************FETCH_DATA*********************************//
void serialReadEvent() {

  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inString += inChar;
    if (inChar == ';') {
      stringComplete = true;
    }
  }
}

//****************************FILTER_DATA****************************
void filterData() {

  if (stringComplete) {

    //****************************Varianta 1****************************

    if (inString.substring(0, 1) == "1") {
    
    Serial.print("Varianta 1");
    fill_solid(leds, NUM_LEDS, CRGB(255,0,0));

    }

    //****************************Varianta 2****************************

    else if (inString.substring(0, 1) == "2") {
    
    Serial.print("Varianta 2");
    fill_solid(leds, NUM_LEDS, CRGB(0,255,0));
    }

    inString = "";
    stringComplete = false;
  
  FastLED.show();
  FastLED.delay(1000);
  }
}

//********************************MAIN*********************************//


void setup() {
  delay(3000); // wait a bit
  
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS);
  FastLED.setBrightness(  BRIGHTNESS );

  Serial.begin(9600);

}


void loop() {
  
  filterData();
  
  serialReadEvent();

}
