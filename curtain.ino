#include <Servo.h> 

Servo snurr;  // create servo object to control a servo 

int state=0;  //state of curtain
int prevstate=0;
int dest = 0;
int spd = 100;
int servopin = 13;

int debug=1;
int pos = 90;    // variable to store the servo position 

void setup() 
{ 
  Serial.begin(9600);
  snurr.attach(servopin);  // attaches the servo on pin 9 to the servo object 
} 


void loop() 
{ 
  //Serial.println(pos);
  while(Serial.available() > 0)
  {
    int action = Serial.parseInt();
    Serial.println(action);
    Serial.println(state);
    Serial.println(prevstate);
    //if (Serial.read() == '\n') {
      if(action == 1)
      {
        Serial.println("Stänger medurs");
        dest = 180;
        state = 1;
        action = 12;
        Serial.println("Destination=-1-");
        Serial.println(dest);
      }

      if(action == 2)
      {
        Serial.println("Stänger moturs");
        dest = 0;
        state = 2;
        action = 12;
        Serial.println("Destination=-2-");
        Serial.println(dest);
      }

      if(action == 0)
      {
        Serial.println("Öppnar");
        dest = 90;
        state = 0; 
        action = 12;
        Serial.println("Destination=-3-");
        Serial.println(dest);
      }

      if(state != prevstate)
      {
        twist();
      }
      else
      {
        Serial.println("Curtain is already in correct state");
      }

      prevstate = state;
    }
  //}
}


void twist() {
  snurr.attach(servopin);
  Serial.println("Roterar gardin");
  
  if(pos>dest)
  {
    for(pos; pos>=dest;pos-=1)
    {
      snurr.write(pos);
      delay(spd);
      Serial.println(pos);
    } 
  }
  else
  {
    for(pos; pos < dest; pos += 1)
    {
      snurr.write(pos);
      delay(spd);
      Serial.println(pos);
  }
  }
  snurr.detach();
}

void retract() {
  Serial.println("Drar gardin");
  if(state != 0) //check to see if curtain is in a position when it's possible to move
  {
    Serial.println("Gardin i fel läge, åtgärdar detta");
    dest = 90;
    state = 0;
    twist();
    delay(50000); //wait to make sure curtains are done twisting
  }


}


