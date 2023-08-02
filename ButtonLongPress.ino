
//BUTTON PROCESSING
const byte buttonPin = A0;
long holdingTime;
long previousHoldingTime;
unsigned long firstButtonPressTime;
byte buttonState;
byte previousButtonState = HIGH;

void setup() 
{
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  Serial.println ("Hello World.  In setup");
}


void buttonCheck()
{
  buttonState = digitalRead(buttonPin);

  if (buttonState == LOW && previousButtonState == HIGH && (millis() - firstButtonPressTime) > 200) 
  {
    firstButtonPressTime = millis();
  }
  holdingTime = (millis() - firstButtonPressTime);

  if (holdingTime > 50) 
  {
    if (buttonState == LOW && holdingTime > previousHoldingTime) 
    {
      //Serial.println("button is pressed");
    }
    if (buttonState == HIGH && previousButtonState == LOW) 
    {
      if (holdingTime <= 400)
      {
        Serial.println("short button press");       
      }
      if (holdingTime > 5000) 
      {
        Serial.println("long button press. restarting in 3 seconds");
        delay(3000);
        ESP.restart();
      }
    }
  }
   previousButtonState = buttonState;
   previousHoldingTime = holdingTime;

}

void loop() 
{

    
    buttonCheck();
}