#include <SoftwareSerial.h>
SoftwareSerial s(3,1);
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614(0x5A); 

float finaltemp = 0;

const int trigPin = D0;
const int echoPin = D8;
long duration;
int distance;
void setup() 
{
  s.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  if (!mlx.begin()) {
    while (1);
  };
}

void loop() 
{
  ultrasonic();
}

void ultrasonic()
{
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);     
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
  if(distance <= 5 )
  {
    temp();
    s.flush();
  }  
}

void temp()
{
  float finaltemp = mlx.readObjectTempC();

  if(finaltemp > 40)
  {
    s.write('c');
  }
  else if(finaltemp <= 37 && finaltemp >= 33)
  {
    s.write('a');
  }
  else 
  {
    s.write('b');
  }
  s.println(finaltemp);
  delay(5000);
}
