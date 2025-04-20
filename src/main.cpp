#include <Arduino.h>
#include <dsmr.h>

//#define USE_MONITOR                 // uncomment this if you want to use one of the UARTs to monitor during development

#define P1_DR   10 //36  // P1 Data request  
#define P1_LED  16 //20  // Led indicating a received telegram
#define P2_DR   11 // P2 Data request
#define P2_LED  17 //21  // P2 Data request led
#define P3_DR   22 //17  // P3 Data request
#define P3_LED  19 //39  // P3 Data request led
#define P4_DR   23 //18  // P4 Data request
#define P4_LED  18 //38  // P4 Data request led

#define GREEN_BRIGHTNESS  16
#define BLUE_BRIGHTNESS   64

P1Reader reader(&Serial,P1_DR);

const int blinkTime = 100;            // must be less than telegram interval!
unsigned long time_now = 0;

void setup() {
#ifdef USE_MONITOR
  Serial2.begin(115200,SERIAL_8N1);              //  UART2, now used for monitoring
  Serial2.println("Smart Splitter for DSMR P1, Copyright 2022-2024, Jacco Bezemer");
#endif
  pinMode(P1_LED,OUTPUT);
  pinMode(P2_DR,INPUT);
  pinMode(P2_LED,OUTPUT);  
  pinMode(P3_DR,INPUT);
  pinMode(P3_LED,OUTPUT);  
  pinMode(P4_DR,INPUT);
  pinMode(P4_LED,OUTPUT);

  //digitalWrite(P1_LED,HIGH);
  analogWrite(P1_LED,GREEN_BRIGHTNESS);
  //digitalWrite(P2_LED,HIGH);
  analogWrite(P2_LED,BLUE_BRIGHTNESS);
  //digitalWrite(P3_LED,HIGH);
  analogWrite(P3_LED,BLUE_BRIGHTNESS);
  //digitalWrite(P4_LED,HIGH);
  analogWrite(P4_LED,BLUE_BRIGHTNESS);
  delay(2000);
  digitalWrite(P1_LED,LOW);
  //digitalWrite(P2_LED,LOW);
  //digitalWrite(P3_LED,LOW);
  //digitalWrite(P4_LED,LOW);

  Serial.begin (115200,SERIAL_8N1);  //  UART0: Rx = pin 1,  Telgram receive port, attached to DSMR P1 port receiving telegrams at maximum interval, no send pin nessesary
  PORTA_PIN1CTRL |= PORT_INVEN_bm;   //  invert input
  Serial1.begin(115200,SERIAL_8N1);  //  UART1: Tx = pin 14
  PORTC_PIN0CTRL |= PORT_INVEN_bm;   //  invert output
#ifndef USE_MONITOR  
  Serial2.begin(115200,SERIAL_8N1);  //  UART2: Tx = pin 34
  PORTF_PIN0CTRL |= PORT_INVEN_bm;   // invert output
#endif  
  Serial3.begin(115200,SERIAL_8N1);  //  UART3: Tx = pin 8
  PORTB_PIN0CTRL |= PORT_INVEN_bm;   //  invert output

  reader.enable(false);              //  Reads the telegram send by the P1 meter

}

void loop() {
  time_now = millis();
  //digitalWrite(P2_LED, digitalRead(P2_DR));
  //digitalWrite(P3_LED, digitalRead(P3_DR));
  //digitalWrite(P4_LED, digitalRead(P4_DR));    
  if (digitalRead(P2_DR) == HIGH) analogWrite(P2_LED,BLUE_BRIGHTNESS);
  else digitalWrite(P2_LED, LOW);
  if (digitalRead(P3_DR) == HIGH) analogWrite(P3_LED,BLUE_BRIGHTNESS);
  else digitalWrite(P3_LED, LOW);
  if (digitalRead(P4_DR) == HIGH) analogWrite(P4_LED,BLUE_BRIGHTNESS);
  else digitalWrite(P4_LED, LOW);
  reader.loop();                          // Allow the reader to check the serial buffer regularly
  if (reader.available()) {               // A complete and correct telegram has been received
    //digitalWrite(P1_LED, HIGH);
    analogWrite(P1_LED,GREEN_BRIGHTNESS);
    if (digitalRead(P2_DR) == HIGH) {
      Serial1.print("/");                 // this whas stripped from the stored telegram so it has to be send ahead
      Serial1.print(reader.raw());        // sends the telegram that whas stored by the reader
      Serial1.print(reader.rawCRC());     // this whas stripped from the stored telegram so it has to be sent afterwards
    }
    if (digitalRead(P3_DR) == HIGH) {
      Serial2.print("/");                 // this whas stripped from the stored telegram so it has to be send ahead
      Serial2.print(reader.raw());        // sends the telegram that whas stored by the reader
      Serial2.print(reader.rawCRC());     // this whas stripped from the stored telegram so it has to be sent afterwards
    }
    if (digitalRead(P4_DR) == HIGH) {
      Serial3.print("/");                 // this whas stripped from the stored telegram so it has to be send ahead
      Serial3.print(reader.raw());        // sends the telegram that whas stored by the reader
      Serial3.print(reader.rawCRC());     // this whas stripped from the stored telegram so it has to be sent afterwards
    }
    reader.clear();                       // clears the stored telegram if we don't parse
    if (millis() < (time_now + blinkTime)) { 
      while(millis() < time_now + blinkTime){
          //wait approx. [period] ms
      }
    }
    digitalWrite(P1_LED, LOW);   // turn off the telegram stored led so we get notified of a new telegram
  }
}
