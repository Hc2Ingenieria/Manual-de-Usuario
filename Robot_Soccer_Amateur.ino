#include "BluetoothSerial.h"
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
char estado ;
int vel=255;
const int frecuencia = 5000;
const int resolucion = 8;
const int ch1=0;
const int ch2=1;
const int mia=26;
const int mir=27;
const int mda=13;
const int mdr=12;

void setup() {
  Serial.begin(115200);
  SerialBT.begin("Puerto"); //Bluetooth device name
  Serial.println("The device started, now you can pair it with bluetooth!");
  ledcSetup(ch1,frecuencia,resolucion);
  ledcSetup(ch2,frecuencia,resolucion);
  pinMode(mia,OUTPUT);
  pinMode(mir,OUTPUT);
  pinMode(mda,OUTPUT);
  pinMode(mdr,OUTPUT);

  ledcAttachPin(14,ch1);
  ledcAttachPin(25,ch2);
}

void loop() {
  if(SerialBT.available()){
  estado=SerialBT.read();
  }
  Serial.println(estado);
  //frente
  if(estado == 'A')
  {
    digitalWrite(mia,HIGH);
    digitalWrite(mir,LOW);
    digitalWrite(mda,HIGH);
    digitalWrite(mdr,LOW);
    ledcWrite(ch1,vel);
    ledcWrite(ch2,vel);
  }
  //atras
  if(estado == 'D')
  {
    digitalWrite(mia,LOW);
    digitalWrite(mir,HIGH);
    digitalWrite(mda,LOW);
    digitalWrite(mdr,HIGH);
    ledcWrite(ch1,vel);
    ledcWrite(ch2,vel);
  }
  //izquierda
  if(estado == 'B')
  {
    digitalWrite(mia,LOW);
    digitalWrite(mir,HIGH);
    digitalWrite(mda,HIGH);
    digitalWrite(mdr,LOW);
    ledcWrite(ch1,vel);
    ledcWrite(ch2,vel);
  }
  //derecha
  if(estado == 'C')
  {
    digitalWrite(mia,HIGH);
    digitalWrite(mir,LOW);
    digitalWrite(mda,LOW);
    digitalWrite(mdr,HIGH);
    ledcWrite(ch1,vel);
    ledcWrite(ch2,vel);
  }
  //parada
  if(estado == 'E')
  {
    digitalWrite(mia,LOW);
    digitalWrite(mir,LOW);
    digitalWrite(mda,LOW);
    digitalWrite(mdr,LOW);
    ledcWrite(ch1,0);
    ledcWrite(ch2,0);
  }
   if(estado == 'F')
  {
    vel=150;
  }
     if(estado == 'G')
  {
    vel=200;
  }
     if(estado == 'H')
  {
    vel=255;
  }
}
