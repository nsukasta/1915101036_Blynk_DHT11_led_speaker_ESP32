// copy paste from your Info page Firmware confign. following 2 lines


#define BLYNK_TEMPLATE_ID "TMPLGNIEs-fK"
#define BLYNK_DEVICE_NAME "TemperatureHumudity"

#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define LED_TOO_COLD 21
#define LED_PERFECT 19
#define LED_TOO_HOT 22


#include "BlynkEdgent.h"
#include <DHT.h>

#define APP_DEBUG

int speakerPin = 18;
int length = 1;

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_WROVER_BOARD

#define DHTPIN 2      // What digital pin we're connected to
#define DHTTYPE DHT11     // DHT 11


DHT dht(DHTPIN, DHTTYPE);
//BlynkTimer timer;


void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); 

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  Blynk.virtualWrite(V1, t);
  Blynk.virtualWrite(V2, h);
}



void setup()
{
  
  Serial.begin(115200);
  Serial.println("DHT11 test!");
  
 
// delay(100);
   
//  

  Serial.begin(115200);
  dht.begin();
  timer.setInterval(1000L, sendSensor);

   // Setup a function to be called every second
  timer.setInterval(2000L, sendSensor);
  BlynkEdgent.begin();
  
}

void loop() {
  pinMode (speakerPin, OUTPUT);
  pinMode (21 , OUTPUT);
  pinMode (19 , OUTPUT);
  pinMode (22 , OUTPUT);
  
  delay(2000);

  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);


  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");

  
  if (t <= 20) {
    Serial.println("Suhu terlalu dingin");
    digitalWrite(21, HIGH);
    digitalWrite(speakerPin, HIGH);
    delay (1000);
    digitalWrite(speakerPin, LOW);
    digitalWrite(21, LOW);
  }
  if (20 < t < 27) {
    Serial.println("Suhu normal!");
    digitalWrite(19, HIGH);
    delay (2000);
    digitalWrite(19, LOW);
  }
  if (t >= 35) {
    Serial.println("Suhu terlalu panas!");
    digitalWrite(22, HIGH);
    digitalWrite(speakerPin, HIGH);
    delay (1000);
    digitalWrite(speakerPin, LOW);
    digitalWrite(22, LOW);
  }

  
  BlynkEdgent.run();
  timer.run();
}
