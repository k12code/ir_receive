#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRrecv.h>
#include <IRutils.h>

const int irRecvPin = D5;
const int ledPin = D2;

IRrecv irrecv(irRecvPin);
decode_results results;

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);

  irrecv.enableIRIn();  // start the IR receiver
}

void loop() {
  if (irrecv.decode(&results)) {
    if (results.value != 0xFFFFFFFFFFFFFFFF) {  // ignore repeat codes
      serialPrintUint64(results.value, HEX);    // print received code as hex
      Serial.println();
    }

    if (results.value == 0xFFA857) {    // compare received code with a known hex
      Serial.println("PLUS button pressed");
      digitalWrite(ledPin, HIGH);
    }

    if (results.value == 0xFFE01F) {
      Serial.println("MINUS button pressed");
      digitalWrite(ledPin, LOW);
    }

    irrecv.resume();  // receive the next code
  }

  delay(100);
}
