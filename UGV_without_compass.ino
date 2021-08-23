#include <Wire.h>
#include <TinyGPS.h>
#include <SoftwareSerial.h>
TinyGPS gps; 
float lat1;
float lng1;
float lat2;
float lng2;
float LAT;
float LNG;
float Earth_Radius;
void setup()
{
  pinMode(10,OUTPUT); //left side motor
  pinMode(11,OUTPUT); //left side motor
  pinMode(12,OUTPUT); //right side motor
  pinMode(13,OUTPUT); //right side motor
}

void loop()
{
    for(int i=1;i<4;i++)
  {
  float heading=getheading();
  float bearing=Bearing();
  float tta=bearing-heading;
  float a; //the time dc motor must move in order to turn the ugv 1 degree
  float dt;
  if (tta>=0)
  {
    dt=tta*a;
    left();
    delay(dt);
    brake();
    delay(100);
  }
  else
  {
    dt=-tta*a;
    right();
    delay(dt);
    brake();
    delay(100);
  }
  float b; //the time dc motor must move in order to move the ugv 1 meter forward
  float dist=Distance();
  float dd=dist*b;
  forward();
  delay(dd/4);
  brake();
  delay(100);
  }
}
float Distance()
{
  //The haversine formula is used to calculate the distance between drop location and target location
  float dLat = radians(LAT - lat2);
  float dLon = radians(LNG - lng2);
  float a = sin(dLat/2.0f)*sin(dLat / 2.0f) + cos(radians(lat2)) * cos(radians(LAT)) *
    sin(dLon/2.0f)*sin(dLon/2.0f);

  float d = 2.0f * atan2(sqrt(a), sqrt(1.0f - a));
  return d * Earth_Radius;
} 
float getheading() 
{
  gpsvalue(lat1,lng1);
  forward();
  delay(1000);
  brake;
  delay(100);
  gpsvalue(lat2,lng2);
  float X=cos(lat1)*sin(lng2-lng1);
  float Y=cos(lat1)*sin(lat2)-sin(lat1)*cos(lat2)*cos(lng2-lng1);
  float heading=atan2(X,Y);
  return heading;
}
float gpsvalue(float a,float b)
{
   while(Serial.available()){ 
    if(gps.encode(Serial.read()))
    { 
    gps.f_get_position(&a,&b);
    Serial.print("Position: ");
    }}
  return 0;
}
float Bearing()
{
  float X=cos(lat2)*sin(LNG-lng2);
  float Y=cos(lat2)*sin(LAT)-sin(lat2)*cos(LAT)*cos(LNG-lng2);
  float bearing=atan2(X,Y);

  return bearing;
}
void forward()
{
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  digitalWrite(12,HIGH);
  digitalWrite(13,LOW);
}

void left()
{
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
  digitalWrite(12,HIGH);
  digitalWrite(13,LOW);
}
void right()
{
  digitalWrite(10,HIGH);
  digitalWrite(11,LOW);
  digitalWrite(12,LOW);
  digitalWrite(13,HIGH);
}
void brake()
{
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(12,HIGH);
  digitalWrite(13,HIGH);
}

  
