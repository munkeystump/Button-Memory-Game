#include <Key.h>
#include <Keypad.h>
#define  numLeds 12


const byte numRows= 4; //number of rows on the keypad
const byte numCols= 5; //number of columns on the keypad

//keymap defines the key pressed according to the row and columns just as appears on the keypad
char keymap[numRows][numCols]=
{
{'A', 'B', '*', 'C','*'},
{'D', '*', 'E', '*','F'},
{'*', 'G', 'H', '*','I'},
{'J', '*', '*', 'K','L'}
};

//Code that shows the the keypad connections to the arduino terminals
byte rowPins[numRows] = {11,10,9,8}; //Rows 0 to 3
byte colPins[numCols]= {6,5,4,3,2}; //Columns 0 to 3

//initializes an instance of the Keypad class
Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

//initialise led pins
byte ledPins[] = {30,31,32,33,34,35,36,37,38,39,40,41};

//pin for maglock
int lock = 12;
//int solved = 0;
char solvedMap[numLeds];

void setup()
{
Serial.begin(9600);
  for (int i = 0 ; i < numLeds ; i++){
    pinMode(ledPins[i],OUTPUT);
  }
  pinMode(lock,OUTPUT);
  rset();
  Serial.println(":: Painting the Roses Red Puzzle Initialised ::");
}


void loop()
{

char key = myKeypad.getKey();
if(key)  // Check for a valid key.
  {
    Serial.print(key);    
    switch (key)
    {
      case '*':
        rset();
        break;
      case 'A':
        digitalWrite(ledPins[0], LOW);
        solvedMap[0]=key;
        break;
      case 'B':
        digitalWrite(ledPins[1], HIGH);
        solvedMap[1]=key;
        break;
      case 'C':
        digitalWrite(ledPins[2], HIGH);
        solvedMap[2]=key;
        break;
      case 'D':
        digitalWrite(ledPins[3], HIGH);
        solvedMap[3]=key;
        break;
      case 'E':
        digitalWrite(ledPins[4], HIGH);
        solvedMap[4]=key;
        break;
      case 'F':
        digitalWrite(ledPins[5], HIGH);
        solvedMap[5]=key;
        break;
      case 'G':
        digitalWrite(ledPins[6], HIGH);
        solvedMap[6]=key;
        break;
      case 'H':
        digitalWrite(ledPins[7], HIGH);
        solvedMap[7]=key;
        break;
      case 'I':
        digitalWrite(ledPins[8], HIGH);
        solvedMap[8]=key;
        break;
      case 'J':
        digitalWrite(ledPins[9], HIGH);
        solvedMap[9]=key;
        break;
      case 'K':
        digitalWrite(ledPins[10], HIGH);
        solvedMap[10]=key;
        break;
      case 'L':
        digitalWrite(ledPins[11], HIGH);
        solvedMap[11]=key;
        break;
      default:
        Serial.println(key);
    }
    Serial.print(" - Key pressed :: Current Solved Status - ");
    prsMap();
    if (solved()){
      unlock();
    }
  }
}

boolean solved(){
  for (int x = 0 ; x < numLeds ; x ++){
    if (solvedMap[x]=='X'){
      return false;
    }
  }
  return true;
}

void rset(){
  for (int x = 0 ; x < numLeds ; x ++){
    solvedMap[x]='X';
    digitalWrite(ledPins[x], HIGH);
  }
}

void prsMap(){
  for (int x = 0 ; x < numLeds ; x ++){
    Serial.print(solvedMap[x]);
  }
  Serial.println();
}

void unlock(){
  Serial.println("Lock Open");
  digitalWrite(lock,HIGH);
  delay(10000);
  digitalWrite(lock,LOW);
  Serial.println("Lock Closed");
  rset();
}
