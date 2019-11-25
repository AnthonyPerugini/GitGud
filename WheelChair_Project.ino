//Pins & Constants:
const int analogInPin1 = A0;         // Analog input pin wheel 1 is attached to.
const int analogInPin2 = A1;         // Analog input pin wheel 2 is attached to.
const int analogOutPin1 = 9;         // Analog output pin wheel 1 is attached to.
const int analogOutPin2 = 10;        // Analog output pin wheel 2 is attached to.
const int reversePin1 = 4;           // Digital output pin for wheel 1.  Forward = off, Reverse = on.
const int reversePin2 = 8;           // Digital output pin for wheel 2.  Forward = off, Reverse = on.
const int buzzerPin = 5;             // Neutral Buzzer output pin.
const int neutralLedPin = 6;         // Neutral LED output pin.
const int threshholdValue = 500;     // Threshhold value for time spent in the deadzone before program reverts to neutral mode (in milliseconds).
const int deadZoneMagnitude = 150;   // Magnitude of the deadzone (512 is the center).

//Input & Output Variables:
double sensorValue1 = 512;           // value read from potetiometer 1 (0-1023).
double sensorValue2 = 512;           // value read from potetiometer 2 (0-1023).
double timeStart = 0;                // Start time variable.
double outputValue1 = 0;             // analog output1 for the PWM (0-255).
double outputValue2 = 0;             // analog output2 for the PWM (0-255).
double outputValueScaled1 = 0;       // parabolic power curve output 1 to ASI controller.
double outputValueScaled2 = 0;       // parabolic power curve output 2 to ASI controller.


void setup()
{
  Serial.begin(9600);
  pinMode(reversePin1, INPUT);
  pinMode(reversePin2, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(neutralLedPin, OUTPUT);
}


void loop()
{
  Serial.println("**VoidLoop Entered**");
  
  timeStart = millis();
  
  while (deadZoneCheck() == 1)
  {
    scaleConvertWrite(512, 512);

    if (millis() - timeStart >= threshholdValue)
    {
      Serial.println("millis() - timeStart IS greater than threshholdValue");
      neutralLoop();
    }
    Serial.println("millis() - timeStart IS NOT greater than threshholdValue");
  }
}


void neutralLoop()
{
  Serial.println("**neutralLoop entered**");
  digitalWrite(buzzerPin, HIGH);
  digitalWrite(neutralLedPin, HIGH);
  delay(50);
  digitalWrite(buzzerPin, LOW);
  
  while (true)
  {
    
    if (deadZoneCheck() == 0 && sensorValue1 >= 512  && sensorValue2 >= 512)
    {
      digitalWrite(neutralLedPin, LOW);
      forwardMode();

    } if (deadZoneCheck() == 0 && sensorValue1 <= 512  && sensorValue2 <= 512)
    {
      digitalWrite(neutralLedPin, LOW);
      reverseMode();

    } if (deadZoneCheck() == 0 && sensorValue1 <= 512  && sensorValue2 >= 512)
    {
      digitalWrite(neutralLedPin, LOW);
      rightMode();

    } if (deadZoneCheck() == 0 && sensorValue1 >= 512  && sensorValue2 <= 512)
    {
      digitalWrite(neutralLedPin, LOW);
      leftMode();
    }
  }
}


int deadZoneCheck()
{
  Serial.println("**deadZoneCheck entered**");
  sensorValue1 = analogRead(analogInPin1);
  sensorValue2 = analogRead(analogInPin2);

  Serial.print("sensorValue1 is: ");
  Serial.println(sensorValue1);
  Serial.print("sensorValue2 is: ");
  Serial.println(sensorValue2);
  
  if (sqrt(sq(512 - sensorValue1) + sq(512 - sensorValue2)) < deadZoneMagnitude)
  {
    Serial.println("Joystick is inside the deadzone");
    return 1;
  }
  Serial.println("Joystick is outside the deadzone");
  return 0;
}


void forwardMode()
{
  Serial.println("**forwardMode entered**");
  
  while (true)
  {
    //set reverse pins to forward.
    pinMode(reversePin1, INPUT);
    pinMode(reversePin2, INPUT);

    // read the analog in values from both potentiometers.
    sensorValue1 = analogRead(analogInPin1);
    sensorValue2 = analogRead(analogInPin2);

    //Map left and right sensor values to upper quadrant.
    if (sensorValue1 <= 512)
    {
      sensorValue1 = 512;
    }
    if (sensorValue2 <= 512)
    {
      sensorValue2 = 512;
    }

    scaleConvertWrite(sensorValue1, sensorValue2);
    loop();
  }
}


void reverseMode()
{
  Serial.println("**reverseMode entered**");
  
  while (true)
  {
    //set reverse pins to reverse.
    pinMode(reversePin1, OUTPUT);
    pinMode(reversePin2, OUTPUT);

    // read the analog in values from both potentiometers.
    sensorValue1 = analogRead(analogInPin1);
    sensorValue2 = analogRead(analogInPin2);

    //Map left and right sensor values to lower quadrant.
    if (sensorValue1 >= 512)
    {
      sensorValue1 = 512;
    }
    if (sensorValue2 >= 512)
    {
      sensorValue2 = 512;
    }

    scaleConvertWrite(sensorValue1, sensorValue2);
    loop();
  }
}


void leftMode()
{
  Serial.println("**leftMode entered**");
  
  while (true)
  {
    //set right wheel to forward mode and left wheel to reverse mode.
    pinMode(reversePin1, INPUT);
    pinMode(reversePin2, OUTPUT);

    // read the analog in values from both potentiometers.
    sensorValue1 = analogRead(analogInPin1);
    sensorValue2 = analogRead(analogInPin2);

    //Map left and right sensor values to left quadrant.
    if (sensorValue1 <= 512)
    {
      sensorValue1 = 512;
    }
    if (sensorValue2 >= 512)
    {
      sensorValue2 = 512;
    }

    scaleConvertWrite(sensorValue1, sensorValue2);
    loop();
  }
}


void rightMode()
{
  Serial.println("**rightMode entered**");
  
  while (true)
  {
    //set right wheel to reverse mode and left wheel to forward mode.
    pinMode(reversePin1, OUTPUT);
    pinMode(reversePin2, INPUT);

    // read the analog in values from both potentiometers.
    sensorValue1 = analogRead(analogInPin1);
    sensorValue2 = analogRead(analogInPin2);

    //Map left and right sensor values to right quadrant.
    if (sensorValue1 >= 512)
    {
      sensorValue1 = 512;
    }
    if (sensorValue2 <= 512)
    {
      sensorValue2 = 512;
    }

    scaleConvertWrite(sensorValue1, sensorValue2);
    loop();
  }
}


void scaleConvertWrite(double sensorValue1, double sensorValue2)
{
  Serial.println("**scaleConvertWrite entered**");
  Serial.println(sensorValue1);
  Serial.println(sensorValue2);

  float y = 0.33333333 ;
  float result1 = pow(abs(((32768 * sensorValue1) - 16777216)), y);
  float result2 = pow(abs(((32768 * sensorValue2) - 16777216)), y);

  if (result1 > 255)
  {
    result1 = 255;
  }

  if (result2 > 255)
  {
    result2 = 255;
  }

  Serial.print("result1 is: ");
  Serial.println(result1);
  Serial.print("result2 is: ");
  Serial.println(result2);

  // write the analog out values.
  analogWrite(analogOutPin1, result1);
  analogWrite(analogOutPin2, result2);
}
