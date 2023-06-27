#include<Keypad.h>
#include<LiquidCrystal.h>
#include<Servo.h>
//#include<String.h>
#define buzzer
    LiquidCrystal lcd(A0,A1,A2,A3,A4,A5); 
    // PINS FOR LCD char
    keys[4][4]={{'1','2','3','A'}, {'4','5','6', 'B'}, {'7','8','9', 'C'}, {'*','0','#', 'D'}};
    byte rowPin[4]={8,7,6,5}; // ROW PINS OF KEYPAD
    byte colPin[4]={4,3,2,1}; // COLUMN PINS OF KEYPAD
    Servo servo_Motor;
    String password = "912"; // SETTING DEFAULT PASSWORD.
    int position = 0; int wrong = 0;
    int redPin = 10; int greenPin = 11;
    // VARIABLE FOR DETERMINING THE POSITION.
    // VARIABLE FOR CALCULATING THE WRONG INPUT.
    // DEFINING PIN FOR RED LED
    // DEFINING PIN FOR GREEN LED
    Keypad keypad=Keypad(makeKeymap(keys),rowPin,colPin,4,4);
    int total = 0; // VARIABLE TO DETERMINE THE NUMBER OF WRONG ATTEMPTS.
    void setup() {
        pinMode(redPin,OUTPUT);
        pinMode(greenPin,OUTPUT); lcd.begin(16,2);
        lcd.print("DOOR LOCK SYSTEM"); lcd.setCursor(0,2);
        delay(1000);
        lcd.clear(); servo_Motor.attach(9); setLocked(true); delay(1000); pinMode(buzzer, OUTPUT); 
    }
    void loop() {
        lcd.clear();
        lcd.print("Enter Password:"); delay(10);
        char pressed=keypad.getKey();
        String key[3];
        if(pressed) { // IF THE KEY IS PRESSED
        lcd.clear();
        // TAKING THE INPUT FROM KEYPAD

        lcd.print("Enter Password:"); lcd.setCursor(position,2); lcd.print(pressed); delay(100);
        if(pressed == '*' || pressed == '#') {
            position = 0; setLocked(true); lcd.clear();
        }
        else if(pressed == password[position]){
            key[position]=pressed; position++;
        }
        else if (pressed != password[position] ){
            wrong++;
            position ++; 
        }
        if(position == 3){ if( wrong >0){
            total++;
            wrong = 0;
            position = 0;
            lcd.clear(); lcd.print("WRONG"); lcd.setCursor(5,2); lcd.print("PASSWORD"); delay(1000); setLocked(true);
        }
        else if(position == 3 && wrong == 0){
            position = 0;
            wrong = 0;
            lcd.clear(); lcd.print("PASSWORD"); lcd.setCursor(6,2); lcd.print("ACCEPTED"); delay(1000);
            lcd.clear(); lcd.print("Door Open"); delay(1000); setLocked(false); 
        }
        if(total ==3){
            total=0;
            buzzer_beep();
            delay(500); 
        }
        } }
    }
    void setLocked(int locked){ // FUNCTION TO CHANGE STATUS OF SERVO MOTOR.
        if (locked) {
            digitalWrite(redPin, HIGH); digitalWrite(greenPin, LOW); delay(1000); servo_Motor.attach(9); servo_Motor.write(10); delay(1000); servo_Motor.detach();
        } else{
            digitalWrite(redPin, LOW);
            digitalWrite(greenPin, HIGH); delay(1000); servo_Motor.attach(9); servo_Motor.write(90); delay(1000); servo_Motor.detach();
        } }
    void buzzer_beep() { // FUNCTION TO BEEP THE BUZZER.
        digitalWrite(buzzer,HIGH); delay(1000); digitalWrite(buzzer,LOW); delay(1000);
        lcd.clear();
    }