#include <Servo.h>
Servo portal;
#include <SoftwareSerial.h>
SoftwareSerial s(10,11);
const int buzz = 4;
const int LED_y = 8;
const int LED_r = 6;
const int servo = 2;

int pos = 0;//

void setup()
{
  pinMode(buzz, OUTPUT);
  pinMode(LED_y, OUTPUT);
  pinMode(LED_r, OUTPUT);
  pinMode(servo, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  portal.attach(2);
  portal.write(0);
  delay(3000);
  
  s.begin(115200);
  while (!Serial) {
  ; // wait for serial port to connect. Needed for native USB port only
  }
}

void loop()
{
  if (s.available()>0) 
  {
    //String reply = s.readStringUntil('.');
    char reply = s.read();
    //reply = ok;
    //Serial.print(reply);
    switch(reply)
    {
      case 'a': buzzer_ok(); break;
      case 'b': buzzer_hot(); break;
      case 'c': buzzer_vhot(); break;
    }
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW); 
    s.read(); 
    s.println(reply);
  }
}

void buzzer_ok()
{
  for (pos = 0; pos <= 90; pos += 1) 
  { 
    portal.write(pos);              
    delay(15);                       
  }
  delay(1000);
  for (pos = 90; pos >= 0; pos -= 1) 
  { 
    portal.write(pos);              
    delay(15);                       
  }
}
void buzzer_hot()
{
  digitalWrite(LED_y, HIGH);
  digitalWrite(buzz, HIGH);
  delay(200);     
  digitalWrite(buzz, LOW);
  digitalWrite(LED_y, LOW);
}
void buzzer_vhot()
{
  digitalWrite(LED_r, HIGH);
  digitalWrite(buzz, HIGH);
  delay(100);     
  digitalWrite(buzz, LOW);
  delay(100);   
  digitalWrite(buzz, HIGH);
  delay(100);     
  digitalWrite(buzz, LOW);
  delay(100); 
  digitalWrite(buzz, HIGH);
  delay(100);     
  digitalWrite(buzz, LOW);
  digitalWrite(LED_r, LOW);
}
