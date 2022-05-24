const unsigned int TRIG_PIN=3;
const unsigned int ECHO_PIN=2;
const unsigned int BAUD_RATE=9600;


void setup()
{
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(BAUD_RATE);
}


void loop()
{
  long duration, distance;


  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // convert the time into a distance
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = duration / 29.1 / 2;
 
  if (duration==0)
  {
    Serial.println("Warning: no pulse from sensor");
  } 
  else
  {
    Serial.print("Distance:  ");
    Serial.print(distance);
    Serial.println(" cm");
  }

  delay(500);
}
