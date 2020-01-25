#include <Adafruit_GFX.h>  
#include <Adafruit_ST7735.h> 
#define TFT_CS     D3
#define TFT_RST    D4  
#define TFT_DC     D2
// The rest of the pins are pre-selected as the default hardware SPI for Arduino Uno (SCK = 13 and SDA = 11)
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);
#include <Fonts/FreeSerif18pt7b.h>  // Add a custom font
int Variable1;  // Create a variable to have something dynamic to show on the display
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
// Set these to run example.
#define FIREBASE_HOST "atr-sc.firebaseio.com"
#define FIREBASE_AUTH "o4m7OdSmIZ5G8PMZb5v2QAJOUnDowPru4Ez4gr0Z"
#define WIFI_SSID "dell"
#define WIFI_PASSWORD "ipadpro2327"
String chipId = "storage";
void setup() {
   tft.initR(INITR_BLACKTAB);  // Initialize a ST7735S chip, black tab

  tft.fillScreen(ST7735_BLACK);  // Fill screen with black

  //tft.setRotation(0);  // Set orientation of the display. Values are from 0 to 3. If not declared, orientation would be 0,
                         // which is portrait mode.

  tft.setTextWrap(false);  // By default, long lines of text are set to automatically “wrap” back to the leftmost column.
                           
Serial.begin(9600);
pinMode(D1, OUTPUT);
// connect to wifi.
WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
Serial.print("connecting");
while (WiFi.status() != WL_CONNECTED) {
Serial.print(".");
delay(500);
}
Serial.println();

Serial.print("connected: ");
Serial.println(WiFi.localIP());
Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
Firebase.set("storage", "true");
}
//0 = off
//1 = on

String n = "true";
void loop() {

  ESP.wdtDisable();

// get value

n = Firebase.getString("storage");
// handle error
if (n =="true" ) {

  tft.setCursor(0, 0);  // Set position (x,y)
  tft.setTextColor(ST7735_WHITE);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(3);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println("lock"); 
  Serial.println("Lock");
}
else {

  tft.setCursor(0, 0);  // Set position (x,y)
  tft.setTextColor(ST7735_WHITE);  // Set color of text. First is the color of text and after is color of background
  tft.setTextSize(3);  // Set text size. Goes from 0 (the smallest) to 20 (very big)
  tft.println("unlock"); 
  Serial.println("unlock");
  

}
}
