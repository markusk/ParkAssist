const unsigned int TRIG_PIN = 3;
const unsigned int ECHO_PIN = 2;
//const unsigned int BAUD_RATE = 9600;

// for measuring the distance
long duration = 0;
long distance = 0;

// defining the delay factor between each LED blink
const int blinkFactor = 10;
// at this distance (or lower) the LED stays on - to stop the car
const int parkHereDistance = 50;




void setup()
{
  // The ultrasonic sensor SRF 05
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  //Serial.begin(BAUD_RATE);
}


void loop()
{
  // trigger ultrasonic sensor now
  measure();
 
  if (duration == 0)
  {
    //Serial.println("Warning: no pulse from sensor");
    // set for blinking
    distance = 1;
  } 
  else
  {
    distance = duration / 29.1 / 2;
    //Serial.print("Distance:  ");
    //Serial.print(distance);
    //Serial.println(" cm");
  }


  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);
  // wait depending on the measured distance
  delay(distance * blinkFactor);

  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);
  // wait depending on the measured distance
  delay(distance * blinkFactor);
}


void measure(void)
{
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);
  
  // convert the time into a distance
  duration = pulseIn(ECHO_PIN, HIGH);
}
