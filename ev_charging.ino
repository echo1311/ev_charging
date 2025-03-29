#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define TRIG_PIN 6  // Ultrasonic sensor trigger pin
#define ECHO_PIN 7  // Ultrasonic sensor echo pin
#define RELAY_PIN 5 // Relay control pin
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(RELAY_PIN, OUTPUT);
    Serial.begin(9600);

    // Initialize OLED display
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
        Serial.println("OLED init failed!");
        for (;;);
    }
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);
}

void loop() {
    long duration;
    float distance;

    // Send ultrasonic pulse
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Measure the echo pulse duration
    duration = pulseIn(ECHO_PIN, HIGH);
    distance = (duration * 0.0343) / 2; // Convert to cm

    // Display on OLED
    display.clearDisplay();
    display.setCursor(0, 10);
    display.print("Slot 1: ");

    // If EV is detected, turn ON charging
    if (distance < 20) { // Adjust threshold if needed
        digitalWrite(RELAY_PIN, HIGH);
        display.print("CHARGING");
    } else {
        digitalWrite(RELAY_PIN, LOW);
        display.print("FREE");
    }

    display.display();
    delay(500);
}
