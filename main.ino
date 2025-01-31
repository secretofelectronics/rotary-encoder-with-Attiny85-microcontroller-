#include <TinyWireM.h>
#include <Tiny4kOLED.h>

#define CLK  4  // Rotary Encoder CLK (PB4)
#define DT   3  // Rotary Encoder DT (PB3)
#define SW   1  // Rotary Encoder Button (PB1) - Optional

volatile int encoderValue = 0;
int lastStateCLK;

void setup() {
    pinMode(CLK, INPUT);
    pinMode(DT, INPUT);
    pinMode(SW, INPUT_PULLUP); // Optional button

    lastStateCLK = digitalRead(CLK);

    // Initialize OLED
    oled.begin();
    oled.clear();
    oled.on();
    oled.setFont(FONT8X16);
    displayValue(encoderValue);
}

void loop() {
    int currentStateCLK = digitalRead(CLK);
    
    // Detect rotation only on falling edge of CLK
    if (currentStateCLK != lastStateCLK && currentStateCLK == LOW) {
        if (digitalRead(DT) == HIGH) {
            encoderValue++;  // Clockwise
        } else {
            encoderValue--;  // Counter-clockwise
        }
        
        displayValue(encoderValue);
    }

    lastStateCLK = currentStateCLK;  // Update last state

    // Check button press (optional reset)
    if (digitalRead(SW) == LOW) {
        encoderValue = 0; // Reset value when button is pressed
        displayValue(encoderValue);
        delay(300);  // Debounce delay
    }
}

// Function to display value on OLED
void displayValue(int value) {
    oled.clear();
    oled.setCursor(0, 2);
    oled.print("Value: ");
    oled.print(value);
}
