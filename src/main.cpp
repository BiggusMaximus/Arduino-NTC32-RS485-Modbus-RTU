#include <Arduino.h>
#include <SoftwareSerial.h>
#include <ModbusMaster.h>
#define DE 3
#define RE 2

ModbusMaster node;

void preTransmission()
{
  digitalWrite(RE, 1);
  digitalWrite(DE, 1);
}

void postTransmission()
{
  digitalWrite(RE, 0);
  digitalWrite(DE, 0);
}

void setup()
{

  pinMode(DE, OUTPUT); // initiate both as output
  pinMode(RE, OUTPUT);
  digitalWrite(RE, 0); // both start at no signal for receive mode
  digitalWrite(DE, 0);

  Serial.begin(9600);

  node.begin(1, Serial);
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);

  Serial.print("Testing");
  delay(500);
}

void loop()
{
  uint8_t result;
  result = node.readHoldingRegisters(1, 1);
  if (result == node.ku8MBSuccess)
  {

    Serial.println(result);
    Serial.println("berhasil");
    Serial.println(node.getResponseBuffer(0));
  }
  else
  {
    Serial.println("gagal");
  }
  delay(500);
}