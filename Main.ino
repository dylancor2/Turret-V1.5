#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(0, 1, 2, 3, 4, 5);

const uint8_t ROWS = 4;
const uint8_t COLS = 4;
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

uint8_t rowPins[ROWS] = { 26, 22, 21, 20 }; // Pins connected to R1, R2, R3, R4
uint8_t colPins[COLS] = { 19, 18, 17, 16}; // Pins connected to C1, C2, C3, C4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
bool passSet = false;
int passPos = 0;
String password[10];


void setup() {
  lcd.begin(16, 2);
  start();

}

void loop() {
  char key = keypad.getKey();

  if (key != NO_KEY) {
    if(passSet == false){
      pass(key);
    }
  }
  delay(10);
}

void start(){
  lcd.setCursor(0, 0);
  slowprint("Welcome to Turrt");
  lcd.setCursor(0, 1);
  slowprint("~~~~~~~~~~~~~~~~");
  lcd.clear();
  slowprint(" Enter New Pass ");
  lcd.setCursor(0, 1);
  delay(100);
  lcd.print("  (          )  ");
}

void slowprint(String mes) {
  for(int i = 0;i < mes.length();i++){
    lcd.print(mes[i]);
    delay(100);
  }
}

void pass(char next){
  lcd.setCursor(3, 1);
  password[passPos] = next;
  passPos++;
  for(int i = 0; i < passPos; i++){
    lcd.print(password[i]);
  }
  for(int i = 0; i < 10-passPos; i++){
    lcd.print(" ");
  }
  lcd.print(")  ");
}
