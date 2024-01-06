// 4x7segment clock code :)

#include <Wire.h>
#include <I2C_RTC.h>

static DS1307 RTC;

// D1, D2, D3, D4
const int digitPins[] = {7, 8, 13, 12};
// A, B, C, D, E, F, G, DP
const int segmentPins[] = {9, 11, 5, 3, 2, 10, 6, 4};

const int numeral[]= {
  B11111100, //0
  B01100000, //1
  B11011010, //2
  B11110010, //3
  B01100110, //4
  B10110110, //5
  B10111110, //6
  B11100000, //7
  B11111110, //8
  B11100110, //9
};

void setup() {
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(9600);

    Serial.begin(9600);
  while (!Serial); // wait for serial port to connect. Needed for native USB
    
    RTC.begin();

    Serial.print("Is Clock Running: ");
    if (RTC.isRunning()) {
        Serial.println("Yes");
    }       
    else
    {
        Serial.println("No");
        Serial.println("Setting Time");
        // RTC.setHourMode(CLOCK_H12); // Comment if RTC PCF8563.
        RTC.setHourMode(CLOCK_H24);  
        RTC.setDateTime(__DATE__, __TIME__);
        RTC.updateWeek();           // Update Weekdaybased on new date.    
        Serial.println("New Time Set");
        Serial.print(__DATE__);
        Serial.print(" ");
        Serial.println(__TIME__);
        RTC.startClock(); // Start the clock.
    }
 }
 
void loop() {
  int  h1, h2, m1, m2;
  int hours = RTC.getHours();
  h1 = hours / 10;
  h2 = hours % 10;

  int minutes = RTC.getMinutes();
  m1 = minutes / 10;
  m2 = minutes % 10;

  showDigit(0, h1);
  showDigit(1, h2);
  showDigit(2, m1);
  showDigit(3, m2);
}

void showDigit(int digit, int value) {
  digitalWrite(digitPins[digit], LOW);
  for(int segment = 1; segment < 8; segment++) {
      bool bit = bitRead(numeral[value], segment);
      digitalWrite(segmentPins[7 - segment], bit);
  }
  if(digit == 1) {
    digitalWrite(segmentPins[7], HIGH);
  } else {
    digitalWrite(segmentPins[7], LOW);
  }
  delay(5);
  digitalWrite(digitPins[digit], HIGH);
}