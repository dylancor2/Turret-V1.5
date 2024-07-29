#include <Keypad.h>

const uint8_t ROWS = 4;
const uint8_t COLS = 4;
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

uint8_t colPins[COLS] = { 20, 19, 18, 17}; // Pins connected to C1, C2, C3, C4
uint8_t rowPins[ROWS] = { 27, 26, 22, 21 }; // Pins connected to R1, R2, R3, R4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  pinMode(15, OUTPUT);
  Serial.begin(115200);
  digitalWrite(15, LOW);
}

void loop() {
  char key = keypad.getKey();

  if (key != NO_KEY) {
    digitalWrite(15, LOW);
    delay(1000);
    digitalWrite(15, HIGH);
    delay(1000);
    Serial.println(key);
  }
}
