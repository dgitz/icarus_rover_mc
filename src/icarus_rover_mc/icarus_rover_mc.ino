#include <Servo.h> 
//Basic Definitions
#define TRUE 1
#define FALSE 0

#define LED_ON 0
#define LED_OFF 1

//Pin Definitions
#define A_LED_PIN 27
#define B_LED_PIN 26
#define C_LED_PIN 25

#define STEER_SERVO 12
#define DRIVE_MOTOR 11


//Timing Stuff Definitions
#define FAST_LOOP 1 //1000 Hz
#define MEDIUM_LOOP 50 //50 Hz
#define SLOW_LOOP 1000 //1 Hz

#define PRIORITY_HIGH 0
#define PRIORITY_MEDIUM 1
#define PRIORITY_SLOW 2

//Communications Definitions
#define BAUD_RATE 115200

//Timing Stuff declarations
int ontime = 0;
int fast_loop_count = 0;
int medium_loop_count = 0;
int slow_loop_count = 0;
int priority_level = -1;

//Communication declarations
String in_message;
int in_message_completed = 0;
int in_message_started = 0;
int temp = 0;
int value1 = 0;
int value2 = 0;
Servo SteerServo;
Servo DriveMotor;
float pos_x = 12.345678f;
float pos_y = 87.654321f;
float heading = 189.370245f;
void setup()
{
  Serial.begin(BAUD_RATE);
  Serial2.begin(BAUD_RATE);
  pinMode(A_LED_PIN,OUTPUT);
  pinMode(B_LED_PIN,OUTPUT);
  pinMode(C_LED_PIN,OUTPUT);
  digitalWrite(A_LED_PIN, LED_OFF);
  digitalWrite(B_LED_PIN, LED_OFF);
  digitalWrite(C_LED_PIN, LED_OFF);
  in_message.reserve(200);
  SteerServo.attach(STEER_SERVO);
  DriveMotor.attach(DRIVE_MOTOR);
  
}
void loop()
{
  
  delay(1);
  //digitalWrite(C_LED_PIN, !digitalRead(C_LED_PIN));
  
  
  //digitalWrite(A_LED_PIN, !digitalRead(A_LED_PIN));
  //digitalWrite(B_LED_PIN, !digitalRead(B_LED_PIN));
  //digitalWrite(C_LED_PIN, !digitalRead(C_LED_PIN));
  ontime++;
  if (ontime > 100000)
  {
     ontime = 1;
     fast_loop_count = medium_loop_count = slow_loop_count = 0;
  }
  if ((ontime - fast_loop_count) > FAST_LOOP)
  {
    fast_loop_count = ontime;
    priority_level = PRIORITY_HIGH;
  }
  else if ((ontime - medium_loop_count) > MEDIUM_LOOP)
  {
    medium_loop_count = ontime;
    priority_level = PRIORITY_MEDIUM;
  }
  else if ((ontime - slow_loop_count) > SLOW_LOOP)
  {
    slow_loop_count = ontime;
    priority_level = PRIORITY_SLOW;
  }
  else
  { 
    priority_level = -1;
  }
  switch (priority_level)
  {
    case PRIORITY_HIGH:
      //digitalWrite(A_LED_PIN, !digitalRead(A_LED_PIN));
      break;
    case PRIORITY_MEDIUM:
      if (in_message_completed == 1)
      {
          if (in_message.substring(0,4) == "$NAV")
          {
            Serial.print("Got NAV Message: ");
            value1 = getValue(in_message,',',1).toInt();
            value2 = getValue(in_message,',',2).toInt();
            SteerServo.write(value1);
            DriveMotor.write(value2);
            Serial.print(value1);
            Serial.print(" ");
            Serial.println(value2);
          }
          else if(in_message.substring(0,4) == "$SEN")
          {
            Serial.println("Got SEN Message.");
          }
          Serial.println(in_message);
          Serial2.println(in_message);
          in_message = "";
          in_message_completed = 0;
          in_message_started = 0;
      }
      heading = heading+1.01f;
      pos_x = pos_x + 1.01;
      pos_y = pos_y + 1.01;
      Serial2.print("$POS,");
      Serial2.print(pos_x,2);
      Serial2.print(",");
      Serial2.print(pos_y,2);
      Serial2.print(",");
      Serial2.print(heading,2);
      Serial2.println("*");
            
      
      
      
      break;
    case PRIORITY_SLOW:
      digitalWrite(C_LED_PIN, !digitalRead(C_LED_PIN));
      break;
    default:
      break;
  }
  
}
void serialEvent2() {
  while ((Serial2.available()>0) && (in_message_completed == 0)) {
      char inChar = (char)Serial2.read(); 
      if (inChar == '$')
      {
         in_message_started = 1;
      }
      if (in_message_started == 1)
      {
        in_message += inChar;
      }
      if (inChar == '*') {
        in_message_completed = 1;
        in_message_started = 0;
      }
  }
}

String getValue(String data, char separator, int index)
{
 int found = 0;
  int strIndex[] = {
0, -1  };
  int maxIndex = data.length()-1;
  for(int i=0; i<=maxIndex && found<=index; i++){
  if(data.charAt(i)==separator || i==maxIndex){
  found++;
  strIndex[0] = strIndex[1]+1;
  strIndex[1] = (i == maxIndex) ? i+1 : i;
  }
 }
  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
