// Painting the roses red puzzle

int button[] = {2,3,4,5,6}; //pins for buttons whiuch turn on lights
int lights[] = {7,8,9,10,11}; // pins for light to turn on
int rset = 13;
int lock = 12; // pin controlling relay for 12V maglock
int inputs = 5; // number of buttons/led combinations
int complete = 0;


void setup() {
  Serial.begin(9600);
  for (int i = 0; i < inputs; i++){
    pinMode(button[i], INPUT); // for all buttons which turns lights on set as input
    pinMode(lights[i], OUTPUT); // for all leds set output
  }
  pinMode(lock, OUTPUT); // set lock pin as output
  pinMode(rset, INPUT); // set all other buttons to reset the puzzle (lights all off)
}

void loop() {
  for (int i = 0; i < inputs; i++){       // scan each button which turns leds on to see if it has been pressed
    if (digitalRead(button[i])== HIGH){
      digitalWrite(lights[i], HIGH);
      complete++;
    }
  }
  if (digitalRead(rset) == HIGH){         // if any other button is pressed turn off all leds
    for (int j = 0; j < inputs; j++){
      digitalWrite(lights[j], LOW);
      complete = 0;
    }
  }
  if (complete == inputs){
    unlock();
  }
}

void unlock(){
  digitalWrite(lock, HIGH);
  for (int j = 0; j < inputs; j++){
    digitalWrite(lights[j], LOW);
    delay(50);
  }
  for (int j = 0; j < inputs; j++){
    digitalWrite(lights[j], HIGH);
    delay(50);
  }
  delay(100);
  digitalWrite(lock, LOW);
}
