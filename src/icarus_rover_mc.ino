//Basic Definitions
#define TRUE 1
#define FALSE 0

//Pin Definitions
#define A_LED_PIN 27
#define B_LED_PIN 26
#define C_LED_PIN 25

//Timing Stuff Definitions
#define FAST_LOOP 1 //1000 Hz
#define MEDIUM_LOOP 20 //50 Hz
#define SLOW_LOOP 1000 //1 Hz

#define PRIORITY_HIGH 0
#define PRIORITY_MEDIUM 1
#define PRIORITY_SLOW 2

//Timing Stuff declarations
int ontime = 0;
int fast_loop_count = 0;
int medium_loop_count = 0;
int slow_loop_count = 0;
int priority_level = -1;

void setup()
{
  Serial.begin(115200);
  pinMode(A_LED_PIN,OUTPUT);
  pinMode(B_LED_PIN,OUTPUT);
  pinMode(C_LED_PIN,OUTPUT);
  digitalWrite(A_LED_PIN, FALSE);
  digitalWrite(B_LED_PIN, FALSE);
  digitalWrite(C_LED_PIN, FALSE);
}
void loop()
{
  
  delay(1);
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
      digitalWrite(A_LED_PIN, !digitalRead(A_LED_PIN));
      break;
    case PRIORITY_MEDIUM:
      digitalWrite(B_LED_PIN, !digitalRead(B_LED_PIN));
      break;
    case PRIORITY_SLOW:
      digitalWrite(C_LED_PIN, !digitalRead(C_LED_PIN));
      break;
    default:
      break;
  }
  
}
