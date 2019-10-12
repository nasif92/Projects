#define C 261
#define D 294
#define E 330
#define F 349
int buzzer = 8;
int button1 = 12;
int button2 = 11;
int buttonState1 = 0;
int buttonState2 = 0;
int notes[] = {C, D, E, F};
//              C    D    E    F
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  pinMode(buzzer, OUTPUT);
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  buttonState1 = digitalRead(button1);
  buttonState2 = digitalRead(button2); 
  // button 1
  if (buttonState1 == HIGH){
      digitalWrite(13, HIGH);
      tone(buzzer, C);
      delay(500);
      tone(buzzer, F);
   
  }
  else if (buttonState1 == LOW){
    digitalWrite(13,LOW);
    noTone(buzzer);
  }
  // button 2
  if (buttonState2 == HIGH){
      digitalWrite(13, HIGH);
      tone(buzzer, notes[1]);
   
  }
  else if (buttonState2 == LOW){
    digitalWrite(13,LOW);
    noTone(buzzer);
  }
  
 
}
