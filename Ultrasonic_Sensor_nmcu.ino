#include "PubSubClient.h"
#include <ESP8266WiFi.h> 
#include <WiFiClient.h>  
#include <ThingSpeak.h> 

const char* ssid ="NithinEiswar";
const char* password ="NittNit123";


unsigned long myChannelNumber =  796231; //Your Channel Number (Without Brackets)
 
const char * myWriteAPIKey = "LCF6N37V2Q87OMA1"; //Your Write API Key



WiFiClient client;
 

// defines pins numbers
const int trigPin = 2;  
const int echoPin = 0;  

// defines variables
long duration=0;
float Distance=0;

void setup() {
Serial.begin(115200);  
 
  delay(10);  
  // Connect to WiFi network  
  Serial.println();  
  Serial.println();  
  Serial.print("Connecting to ");  
  Serial.println(ssid);  
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)  
  {  
   delay(500);  
   Serial.print(".");  
  }  
  Serial.println("");  
  Serial.println("WiFi connected");  
  // Print the IP address  
  Serial.println(WiFi.localIP());  
//  ThingSpeak.begin(client);  
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  


}

void loop() {
 
static int counter = 0;
Serial.println("hi");
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration = pulseIn(echoPin, HIGH);

// Calculating the distance
Distance= duration*0.034/2;
// Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(Distance);


/*  
  if( 1 )  
  {  
   ThingSpeak.writeField(myChannelNumber, 1,Distance , myWriteAPIKey);  
     
  }  
*/
  delay(30000); // ThingSpeak will only accept updates every 15 seconds.  
}
