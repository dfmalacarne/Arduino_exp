//References:
//Light sensor: Arduino Uno project 4
//Servo: Arduino Uno project 5
//Push button: https://www.arduino.cc/en/tutorial/pushbutton


//Import lybraries
#include <Servo.h>
Servo myServo;

//Variable declaration
const int LightSensorPin= A0;
int exp_time = 0;
int LightSensorValue = 0;
int angle1 = 0;
int angle2 = 120;  // --NEED CALIBRATION--
int inPin = 7;   // choose the input pin (for a pushbutton)
int val = 0;     // variable for reading the pin status


void setup() {
  myServo.attach(9);
  Serial.begin(9600);
  pinMode(inPin, INPUT);    // declare pushbutton as input
  myServo.write(angle1);
}

void loop() {
  //myServo.write(angle1);
  val = digitalRead(inPin);  // read pushbutton input value
  if (val == HIGH) {         // check if the input is HIGH (button released)

      LightSensorValue = analogRead(LightSensorPin);
      delay(5);
    
      //map the sensor reading to set the exposure time. --NEED CALIBRATION--
      exp_time = map(LightSensorValue,0,1023,10000,15); 
      //with the minimum light detected set the exp_time to 10s, this is the value which need to be calibrated, 
      //with the max light detected set just 15 millisec so the servo has the time to move
      
      //show values on the screen, refresh rate 1s
      Serial.print("Light Sensor Value: ");
      Serial.print(LightSensorValue);
      Serial.print("; Exposure Time: ");
      Serial.println(exp_time);
      delay(1000);
    
  } else {
      LightSensorValue = analogRead(LightSensorPin);
      delay(5);
    
      //map the sensor reading to set the exposure time. --NEED CALIBRATION--
      exp_time = map(LightSensorValue,0,1023,10000,15); 
      //with the minimum light detected set the exp_time to 10s, this is the value which need to be calibrated, 
      //with the max light detected set just 15 millisec so the servo has the time to move
      
      //show values on the screen
      Serial.println("-------------------- CAMERA SHOOT --------------------");
      Serial.print("Light Sensor Value: ");
      Serial.print(LightSensorValue);
      Serial.print("; Exposure Time: ");
      Serial.println(exp_time);
      
      //Move the servo to trigger the camera shutter
      myServo.write(angle2);
      delay(exp_time);
      myServo.write(angle1); 

      Serial.println("------------------------------------------------------");

      delay(5000); //5s delay to avoid multiple camera shoot while the button is pressed
  }
}
