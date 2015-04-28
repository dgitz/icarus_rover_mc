//Basic Definitions
#define TRUE 1
#define FALSE 0

#define LED_ON 0
#define LED_OFF 1

//Pin Definitions
#define A_LED_PIN 27
#define B_LED_PIN 26
#define C_LED_PIN 25

//Timing Stuff Definitions
#define FAST_LOOP 1 //1000 Hz
#define MEDIUM_LOOP 20 //50 Hz
#define SLOW_LOOP 100 //1 Hz

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
}
void loop()
{
  
  delay(1);
  digitalWrite(C_LED_PIN, !digitalRead(C_LED_PIN));
  if (in_message_completed == 1)
  {
        Serial.println(in_message);
        Serial2.println(in_message);
        in_message = "";
        in_message_completed = 0;
        in_message_started = 0;
   }
  /*
  //digitalWrite(A_LED_PIN, !digitalRead(A_LED_PIN));
  //digitalWrite(B_LED_PIN, !digitalRead(B_LED_PIN));
  //digitalWrite(C_LED_PIN, !digitalRead(C_LED_PIN));
  dontime++;
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
  (if (Serial.available() > 0)
      {
        //Serial.flush();
        //digitalWrite(B_LED_PIN, !digitalRead(B_LED_PIN));
        //in_char = Serial.read();
        //Serial.println(in_char);
      }
  
  switch (priority_level)
  {
    case PRIORITY_HIGH:
      //digitalWrite(A_LED_PIN, !digitalRead(A_LED_PIN));
      break;
    case PRIORITY_MEDIUM:
      if (in_message_complete == 1)
      {
        digitalWrite(A_LED_PIN, !digitalRead(A_LED_PIN));
        Serial2.println(in_message);
        in_message = "";
        in_message_complete = 0;
      }
      //digitalWrite(B_LED_PIN, !digitalRead(B_LED_PIN));
       
        memset(response,'\0',sizeof response);
        digitalWrite(B_LED_PIN,FALSE);
        do
        {
          digitalWrite(B_LED_PIN,TRUE);
          in_byte = Serial.read();
          //Serial.print(in_byte);
          sprintf(&response[spot],"%c",in_byte);
          spot += 1; 
        }while((Serial.available() > 0) && (in_byte != '\0') && (in_byte != '*'));
        digitalWrite(B_LED_PIN, FALSE);
        //Serial.println(response);
        if (in_char == '$')
        {
          digitalWrite(A_LED_PIN, !digitalRead(A_LED_PIN));
          message_started = 1;
          message_completed = 0;
          in_message = (String)'$';
        }
        else if (in_char == '*')
        {
          digitalWrite(B_LED_PIN, !digitalRead(B_LED_PIN));
          message_started = 0;
          message_completed = 1;
          in_message += '*';
          in_message += '\0';
        }
        else
        {
          in_message += (String)'x';
        }
        
      
      
      
      break;
    case PRIORITY_SLOW:
      digitalWrite(C_LED_PIN, !digitalRead(C_LED_PIN));
      //Serial2.print("$NAV,123,");
      //Serial2.print(temp++);
      //Serial2.println("*");
      if ( temp > 256) { temp = 0;}
      break;
    default:
      break;
  }
  */
}
void serialEvent2() {
  //digitalWrite(A_LED_PIN, LED_OFF);
  
  while ((Serial2.available()>0) && (in_message_completed == 0)) {
    digitalWrite(B_LED_PIN, LED_ON);
      // get the new byte:
      char inChar = (char)Serial2.read(); 
      //Serial.print(inChar);
      // add it to the inputString:
      if (inChar == '$')
      {
         in_message_started = 1;
      }
      if (in_message_started == 1)
      {
        in_message += inChar;
      }
      // if the incoming character is a newline, set a flag
      // so the main loop can do something about it:
      if (inChar == '*') {
        in_message_completed = 1;
        in_message_started = 0;
      }
  }
}
