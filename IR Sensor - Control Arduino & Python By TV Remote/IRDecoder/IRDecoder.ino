/*

Author : @Ziad-Sakr
Des    : Arduino Code To Get The Values form TV Remote and print it to Serial Monitor.

*/
#include <IRremote.h>

int IRPIN = 2;
int output = 8;
bool bol=0;
void setup()

{

  Serial.begin(9600);
  pinMode(output, OUTPUT);

  Serial.println("Enabling IRin");

  IrReceiver.begin(IRPIN, ENABLE_LED_FEEDBACK);

  Serial.println("Enabled IRin");

}

void loop()
{
  if (IrReceiver.decode())
  {
    unsigned long dataa = IrReceiver.decodedIRData.decodedRawData ;
    Serial.println(dataa);
    IrReceiver.resume();
  }

  delay(500);

}
