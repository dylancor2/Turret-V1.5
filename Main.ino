#include <Keypad.h>
#include <LiquidCrystal.h>

#define VERT_PIN 27
#define HORZ_PIN 28
int x = 7;
int y = 8;

int pwX = 0;
int pwY = 0;

int rel = 9;

int slid = 26;

int led = 10;

LiquidCrystal lcd(0, 1, 2, 3, 4, 5);

const uint8_t ROWS = 4;
const uint8_t COLS = 4;
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

uint8_t rowPins[ROWS] = { 15, 22, 21, 20 }; // Pins connected to R1, R2, R3, R4
uint8_t colPins[COLS] = { 19, 18, 17, 16}; // Pins connected to C1, C2, C3, C4

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);
bool passSet = false;
int passPos = 0;
char password[10];

bool locked = true;
int guessPos = 0;
char guess[10] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};

void setup() {
  lcd.begin(16, 2);
  start();
  pinMode(x, OUTPUT);
  pinMode(y, OUTPUT);
  moveServoY(0);
  moveServoX(0);
  pinMode(rel, OUTPUT);
  digitalWrite(rel, LOW);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
  char key = keypad.getKey();

  if (key != NO_KEY) {
    if(!passSet){
      pass(key);
    }
    else{
      if(locked){
        guesst(key);
      }
      else{
        if(key == '#'){
          lock();
        }
      }
    }
  }
  if(!locked){
    moveServoY(map(analogRead(VERT_PIN), 0, 1023, 0, 180));
    moveServoX(map(analogRead(HORZ_PIN), 0, 1023, 180, 0));
    if(analogRead(slid) == 1023){
      digitalWrite(rel, HIGH);
    }
    else{
      digitalWrite(rel, LOW);
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
  if (passPos == 9){
    passSet = true;
    delay(500);
    lcd.clear();
    slowprint("  Password Set  ");
    lcd.setCursor(0, 1);
    slowprint(password);
    slowprint("     ~");
    delay(500);
    for(int i = 0; i < 5; i++){
      lcd.setCursor(14, 1);
      lcd.print(5-i);
      delay(1000);
      lcd.setCursor(14, 1);
      lcd.print(" ");
      delay(200);
    }
    lcd.clear();
    lock();
  }
  else{
    passPos++;
    for(int i = 0; i < passPos; i++){
      lcd.print(password[i]);
    }
    for(int i = 0; i < 10-passPos; i++){
      lcd.print(" ");
    }
    lcd.print(")  ");
  }
}

void lock(){
  reset();
  locked = true;
  lcd.clear();
  slowprint("Turrt is Locked");
  delay(3000);
  for(int i = 0; i < 10; i++){
        guess[i] = ' ';
      }
  guessPos = 0;
  enterPass();
}

void enterPass(){
  lcd.clear();
  slowprint(" Enter Password ");
  lcd.setCursor(0, 1);
  delay(100);
  lcd.print("  (          )  ");
}

void guesst(char next){
  lcd.setCursor(3, 1);
  guess[guessPos] = next;
  if (guessPos == 9){
    bool temp = true;
    for(int i = 0; i < 10; i++){
      if(password[i] != guess[i]){
        temp = false;
      }
    }
    if (temp){
      unlocked();
    }
    else{
      delay(250);
      lcd.clear();
      slowprint(" Incorrect Pass ");
      lcd.setCursor(0, 1);
      slowprint("~~~~~~~~~~~~~~~~");
      for(int i = 0; i < 10; i++){
        guess[i] = ' ';
      }
      guessPos = 0;
      enterPass();
    }
  }
  else{
    guessPos++;
    for(int i = 0; i < guessPos; i++){
      lcd.print(guess[i]);
    }
    for(int i = 0; i < 10-guessPos; i++){
      lcd.print(" ");
    }
    lcd.print(")  ");
  }
}

void unlocked(){
  locked = false;
  delay(250);
  lcd.clear();
  slowprint("  Correct Pass  ");
  lcd.setCursor(0, 1);
  slowprint("~~~~~~~~~~~~~~~~");
  lcd.clear();
  digitalWrite(led, HIGH);
  slowprint(" Turrt Enabled ");
  lcd.setCursor(0, 1);
  slowprint("Press # To Lock");
}

void moveServoX(int pre){
  int pulseWidth = map(pre, 0, 180, 1000, 2000);
  digitalWrite(x, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(x, LOW);
  delay(20 - pulseWidth / 1000);
}

void moveServoY(int pre){
  int pulseWidth = map(pre, 0, 180, 1000, 2000);
  digitalWrite(y, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(y, LOW);
  delay(20 - pulseWidth / 1000);
}

void reset(){
  digitalWrite(led, LOW);
  digitalWrite(rel, LOW);
  moveServoX(0);
  moveServoY(0);
}
