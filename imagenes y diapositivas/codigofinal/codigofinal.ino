#include <Wire.h>     // libreria para bus I2C
#include <Adafruit_GFX.h>   // libreria para pantallas graficas
#include <Adafruit_SSD1306.h>

#define Sx   A0
#define ANCHO 128     // reemplaza ocurrencia de ANCHO por 128
#define ALTO 64       // reemplaza ocurrencia de ALTO por 64

#define OLED_RESET 4      // necesario por la libreria pero no usado
Adafruit_SSD1306 oled(ANCHO, ALTO, &Wire, OLED_RESET);  // crea objeto

const int LENGTH=ANCHO;
const int HEIGHT=ALTO;
 
int i;

const int analogInPin = A0;
int analogInValue = 0;
 
int x;
int y[LENGTH];


void setup()
{
  Serial.begin(9600);
  oled.begin(SSD1306_SWITCHCAPVCC, 0X3C);
  oled.clearDisplay();
  pinMode(Sx, INPUT);
  }
void loop ()
{
  for (i = 0; i <= LENGTH; i++)
  {
   analogInValue = analogRead(analogInPin);
    y[i] = map(analogInValue, 0, 1023, HEIGHT-1, 0);
    
  }
  oled.clearDisplay();
  for(i = 0;i <= LENGTH; i++)
  {
    oled.drawLine(i-1, y[i-1], i, y[i], WHITE);  
  }
    oled.drawFastHLine(1, 63, 127, WHITE);
    oled.drawFastVLine(1, 1, 63, WHITE);
    oled.display();
    delay(1000);
    }