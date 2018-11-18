#include <OneWire.h>
#include <GxEPD.h>
#include <GxGDEW0154Z04/GxGDEW0154Z04.h>
#include <Fonts/FreeMonoBold24pt7b.h>
#include <GxIO/GxIO_SPI/GxIO_SPI.h>
#include <GxIO/GxIO.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS D4

float tempC = 0;

OneWire  oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
GxIO_Class io(SPI, 15, 4, 5);
GxEPD_Class display(io,  5,  16);

void setup() {
  Serial.begin(9600);
  Serial.println();
  display.init();
  sensors.begin(); 
}

void loop() {
  sensors.requestTemperatures();
  tempC = sensors.getTempCByIndex(0);
  show(tempC);
  display.update();
  delay(5000);
}

void show(float temperature)
{
  String temperatureString = String(temperature,1);
  const char* name = "FreeMonoBold24pt7b";
  const GFXfont* f = &FreeMonoBold24pt7b;
  uint16_t box_x = 0;
  uint16_t box_y = 0;
  uint16_t box_w = 200;
  uint16_t box_h = 200;
  uint16_t cursor_y = box_y + 16;
  display.setRotation(2);
  display.setFont(f);
  display.setTextColor(GxEPD_WHITE);
  display.fillRect(box_x, box_y, box_w, box_h, GxEPD_BLACK);
  display.setCursor(box_x+15, cursor_y+88);
  display.print(temperature, 1);
  display.print(" ");
  display.fillCircle(144, 82, 5, GxEPD_WHITE);  //Xpos,Ypos,r,Farbe
  display.fillCircle(144, 82, 2, GxEPD_BLACK);  //Xpos,Ypos,r,Farbe
  display.print("C");
  display.updateWindow(box_x, box_y, box_w, box_h, true);
}
