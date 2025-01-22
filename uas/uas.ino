// library
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Dunia Pin
const int trigger = 9;
const int echo = 8;
const int buzzer = 4;
const int berem = 2;
const int hejo = 3;

// Variables
long durasi;
int jarak;
LiquidCrystal_I2C lcd(0x27, 20, 4);
Servo myServo;

//Setup I/O
void setup() {
    lcd.init();
    lcd.backlight();
    pinMode(trigger, OUTPUT);
    pinMode(echo, INPUT);
    pinMode(buzzer, OUTPUT);
    pinMode(berem, OUTPUT);
    pinMode(hejo, OUTPUT);
    Serial.begin(9600);
    myServo.attach(5);
}

void loop() {
    // rotasi servo 15 ke 165
    for (int i = 15; i <= 165; i++) {
        myServo.write(i);
        delay(30);
        jarak = hitungJarak(); // panggil fungsi hitung jarak buat tiap sudut
        updateOutputs(jarak);

        Serial.print(i);        // output sudut sekarang ke serial monitor
        Serial.print(",");      // pemisah nilai jarak sama sudut
        Serial.print(jarak);    // output jarak objek ke serial monitor
        Serial.print(".");      // pemisah biar ga pusing baca
    }

    // rotasi servo 165 ke 15
    for (int i = 165; i > 15; i--) {
        myServo.write(i);
        delay(30);
        jarak = hitungJarak();
        updateOutputs(jarak);

        Serial.print(i);
        Serial.print(",");
        Serial.print(jarak);
        Serial.print(".");
    }
}

// fungsi buat deteksi objek
void updateOutputs(int jarak) {
    if (jarak > 0 && jarak <= 40) {
        digitalWrite(buzzer, HIGH);
        digitalWrite(berem, HIGH);
        digitalWrite(hejo, LOW);
        lcd.setCursor(0, 0);
        lcd.print("Musuh         ");
        lcd.setCursor(0, 1);
        lcd.print("Terlihat      ");
    } else {
        digitalWrite(buzzer, LOW);
        digitalWrite(berem, LOW);
        digitalWrite(hejo, HIGH);
        lcd.setCursor(0, 0);
        lcd.print("Musuh         ");
        lcd.setCursor(0, 1);
        lcd.print("Hilang        ");
    }
}

// fungsi hitung jarak
int hitungJarak() {
    digitalWrite(trigger, LOW);
    delayMicroseconds(2);
    digitalWrite(trigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigger, LOW);

    durasi = pulseIn(echo, HIGH);
    int tes = durasi * 0.034 / 2;
    return tes > 0 ? tes : 400; // Antisipasi deteksi objek terlalu jauh/dekat atau gangguan sensor
}
