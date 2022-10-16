#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>

#define LED_PIN    6
#define LED_COUNT 180

int addr = 7;
int val = 1; 

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);

  val=EEPROM.read(addr);
  Serial.print("1 wartosc val: ");
  Serial.println(val);

  if ((val<3)and(val>0)){
    val+=1;
  }
  else{
    val=1;
  }
  
EEPROM.write(addr, val);
Serial.print("2 wartosc val: ");
Serial.println(val);

  strip.begin();           
  strip.show();
  strip.setBrightness(100);    
}

void loop() {
  switch(val){
    case 1: 
      rainbow(10);
      break ;
    case 2:
      whiteFull();
      break ;
    case 3:
      whiteHalf();
      break ;  
  }
}

void rainbow(int wait) {
  strip.clear();
  strip.setBrightness(60);
  for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) {
    for(int i=0; i<strip.numPixels(); i++) {
      int pixelHue = firstPixelHue + (i * 65536L / strip.numPixels());
      strip.setPixelColor(i, strip.gamma32(strip.ColorHSV(pixelHue)));
    }
    strip.show();
    delay(wait);
  }
}

void whiteFull(){
  strip.clear();
  strip.setBrightness(255);
  for(int i=0; i<LED_COUNT; i++) {
    strip.setPixelColor(i, strip.Color(255, 255, 255));
  }
  strip.show();
  delay(43200000);
}

void whiteHalf(){
  strip.clear();
  strip.setBrightness(70);
  for(int i=0; i<LED_COUNT; i++) {
    strip.setPixelColor(i, strip.Color(255, 140, 45)); //RGB
  }
  strip.show();
  delay(43200000);
}
