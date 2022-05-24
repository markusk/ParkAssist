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

// needed for a better delay
unsigned long previousMillis = 0;
// ledState used to set the LED
int ledState = LOW;





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

  // check time for 'delay'
  unsigned long currentMillis = millis();

  // blink LED depending on the distance
  if (currentMillis - previousMillis >= (distance * blinkFactor))
  {
    // save the last time you blinked the LED
    previousMillis = currentMillis;

    // if the LED is off turn it on and vice-versa:
    if (ledState == LOW)
    {
      ledState = HIGH;
    }
    else
    {
      ledState = LOW;
    }

    // set the LED with the ledState of the variable:
    digitalWrite(LED_BUILTIN, ledState);
  }
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

  // sensor okay?
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
}
