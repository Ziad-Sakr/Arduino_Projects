// Getting Code From RemoteXY Website And Edited By @Ziad-Sakr

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
const int analogInPin = A0;
int sensorValue = 0;  
// Global Pin Nmubers Variables for Motors and leds
int M1_1     = 4;
int M1_2     = 5;
int M2_1     = 6;
int M2_2     = 7;
int Front_Led =8;
int Back_Led =9;

#define REMOTEXY_MODE__SOFTSERIAL
#include <SoftwareSerial.h>

#include <RemoteXY.h>

// RemoteXY connection settings
#define REMOTEXY_SERIAL_RX 2
#define REMOTEXY_SERIAL_TX 3
#define REMOTEXY_SERIAL_SPEED 9600


// RemoteXY configurate
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 108 bytes
{ 255, 3, 0, 2, 0, 101, 0, 16, 173, 2, 5, 21, 42, 25, 34, 34, 24, 42, 35, 35,
  2, 26, 31, 1, 8, 3, 33, 19, 19, 1, 51, 19, 19, 31, 24, 66, 117, 109, 112, 32,
  66, 117, 116, 116, 116, 111, 110, 0, 70, 32, 77, 13, 13, 13, 37, 23, 15, 15, 26, 135,
  36, 32, 70, 32, 6, 16, 11, 11, 3, 24, 15, 15, 26, 135, 0, 2, 129, 0, 12, 3,
  75, 8, 4, 3, 56, 6, 31, 70, 105, 114, 101, 32, 116, 114, 117, 99, 107, 32, 67, 111,
  110, 116, 114, 111, 108, 101, 114, 0
};

// this structure defines all the variables and events of your control interface
struct {

  // input variables
  int8_t joystick_1_x; // from -100 to 100
  int8_t joystick_1_y; // from -100 to 100
  uint8_t button_1; // =1 if button pressed, else =0

  // output variables
  uint8_t led_1; // led state 0 .. 2
  uint8_t led_2; // led state 0 .. 2

  // other variable
  uint8_t connect_flag;  // =1 if wire connected, else =0

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////



void setup()
{
  RemoteXY_Init ();
  myservo.attach(8, 1000, 2500); // (pin, min, max)
  pinMode(M1_1   , OUTPUT); // First Motor  Pin 1
  pinMode(M1_2   , OUTPUT); // First Motor  Pin 2
  pinMode(M2_1   , OUTPUT); // Second Motor Pin 1
  pinMode(M2_2   , OUTPUT); // Second Motor Pin 2
  pinMode(Front_Led, OUTPUT); // white Front Led pin
  pinMode(Back_Led,OUTPUT);   // Red Back led pin
}

void loop()
{
  RemoteXY_Handler ();
  if (RemoteXY.connect_flag == 1) // To check The bluetooth Connections
  {
    digitalWrite(LED_BUILTIN, HIGH);
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);
  }
   
  if (RemoteXY.joystick_1_y > 0 && RemoteXY.joystick_1_x > 0) // For Moving Forward + Right
  {
    digitalWrite(M1_1, LOW);
    digitalWrite(M1_2, LOW);
    digitalWrite(M2_1, HIGH);
    digitalWrite(M2_2, LOW);
    RemoteXY.led_1 = 1;
    digitalWrite(Back_Led,LOW);
  }
  else if (RemoteXY.joystick_1_y > 0 && RemoteXY.joystick_1_x < 0)// For Moving Forward + Left
  {
    digitalWrite(M1_1, HIGH);
    digitalWrite(M1_2, LOW);
    digitalWrite(M2_1, LOW);
    digitalWrite(M2_2, LOW);
    RemoteXY.led_1 = 1;
    digitalWrite(Back_Led,LOW);
  }
  else if (RemoteXY.joystick_1_y > 0)// For Moving just Forward
  {
    digitalWrite(M1_1, HIGH);
    digitalWrite(M1_2, LOW);
    digitalWrite(M2_1, HIGH);
    digitalWrite(M2_2, LOW);
    RemoteXY.led_1 = 1;
    digitalWrite(Back_Led,LOW);
  }
  else if (RemoteXY.joystick_1_y < 0 && RemoteXY.joystick_1_x < 0) // For Moving Backward + Right
  {
    digitalWrite(M1_1,  LOW);
    digitalWrite(M1_2,  LOW);
    digitalWrite(M2_1,  LOW);
    digitalWrite(M2_2, HIGH);
    RemoteXY.led_1 = 2;
    digitalWrite(Back_Led,HIGH); // To Turn The Back red led ON
  }
  else if (RemoteXY.joystick_1_y < 0 && RemoteXY.joystick_1_x < 0) // For Moving Backward + Left
  {
    digitalWrite(M1_1,  LOW);
    digitalWrite(M1_2, HIGH);
    digitalWrite(M2_1,  LOW);
    digitalWrite(M2_2,  LOW);
    RemoteXY.led_1 = 2;
    digitalWrite(Back_Led,HIGH);// To Turn The Back red led ON
  }
  else if (RemoteXY.joystick_1_y < 0) // For Moving Just Backward
  {
    digitalWrite(M1_1,  LOW);
    digitalWrite(M1_2, HIGH);
    digitalWrite(M2_1,  LOW);
    digitalWrite(M2_2, HIGH);
    RemoteXY.led_1 = 2;
    digitalWrite(Back_Led,HIGH);// To Turn The Back red led ON
  }
  else // To Stop The Car if we don't Do anything
  {
    digitalWrite(M1_1,  LOW);
    digitalWrite(M1_2,  LOW);
    digitalWrite(M2_1,  LOW);
    digitalWrite(M2_2,  LOW);
    RemoteXY.led_1 = 0;

  }
  if(RemoteXY.button_1) // For Turn ON The White Forward Led
  {
    digitalWrite(Front_Led,HIGH);
  }
  if(RemoteXY.button_1)
  {
    digitalWrite(Front_Led,LOW);
  }
}
