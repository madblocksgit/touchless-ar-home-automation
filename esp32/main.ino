/**********************************************************************
 PROJECT NAME             :   Touchless Home Automation using Augmented Reality
 Input                    :   madBlocks DB
 Output                   :   Relay
*********************************************************************/

#include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "Madhu P";
const char* password = "madhu2022";

//Your Domain name with URL path or IP address with path
String serverName = "http://madblocks.tech/projects/divija-ar/device_pull.php?device_id=";

int d1Flag=-1;
int d2Flag=-1;
int d3Flag=-1;
int d4Flag=-1;
int d5Flag=-1;
int d6Flag=-1;

int statusLED=2;

#define LED_ON 1
#define LED_OFF 0

#define relay_on 0
#define relay_off 1

int relay1=19;
int relay2=18;
int relay3=5;
int relay4=17;
int relay5=16;
int relay6=4;

void setup() { 
  Serial.begin(9600);
  pinMode(statusLED,OUTPUT);
  pinMode(relay1,OUTPUT);
  pinMode(relay2,OUTPUT);
  pinMode(relay3,OUTPUT);
  pinMode(relay4,OUTPUT);
  pinMode(relay5,OUTPUT);
  pinMode(relay6,OUTPUT);
  digitalWrite(relay1,relay_off);
  digitalWrite(relay2,relay_off);
  digitalWrite(relay3,relay_off);
  digitalWrite(relay4,relay_off);
  digitalWrite(relay5,relay_off);
  digitalWrite(relay6,relay_off);
  digitalWrite(statusLED,LED_OFF);
  delay(2000);
  Serial.println("Welcome");
  bsp_init();
  digitalWrite(statusLED,LED_ON);
}

void loop() {
  digitalWrite(statusLED,LED_ON);
  delay(1000);
  while(d1Flag==-1) {
        d1Flag=device_read_from_madblocksdb(1);  
  }
  while(d2Flag==-1) {
        d2Flag=device_read_from_madblocksdb(2);  
  }
  while(d3Flag==-1) {
        d3Flag=device_read_from_madblocksdb(3);  
  }
  while(d4Flag==-1) {
        d4Flag=device_read_from_madblocksdb(4);  
  }
  while(d5Flag==-1) {
        d5Flag=device_read_from_madblocksdb(5);  
  }
  while(d6Flag==-1) {
        d6Flag=device_read_from_madblocksdb(6);  
  }
  
  Serial.print("Device1 Status: ");
  Serial.println(d1Flag);
  Serial.print("Device2 Status: ");
  Serial.println(d2Flag);
  Serial.print("Device3 Status: ");
  Serial.println(d3Flag);
  Serial.print("Device4 Status: ");
  Serial.println(d4Flag);
  Serial.print("Device5 Status: ");
  Serial.println(d5Flag);
  Serial.print("Device6 Status: ");
  Serial.println(d6Flag);

  if(d1Flag==0) {
    digitalWrite(relay1,relay_off);
  } else if(d1Flag==1) {
    digitalWrite(relay1,relay_on);
  }
  if(d2Flag==0) {
    digitalWrite(relay2,relay_off);
  } else if(d2Flag==1) {
    digitalWrite(relay2,relay_on);
  }
  if(d3Flag==0) {
    digitalWrite(relay3,relay_off);
  } else if(d3Flag==1) {
    digitalWrite(relay3,relay_on);
  }
  if(d4Flag==0) {
    digitalWrite(relay4,relay_off);
  } else if(d4Flag==1) {
    digitalWrite(relay4,relay_on);
  }
  if(d5Flag==0) {
    digitalWrite(relay5,relay_off);
  } else if(d5Flag==1) {
    digitalWrite(relay5,relay_on);
  }
  if(d6Flag==0) {
    digitalWrite(relay6,relay_off);
  } else if(d6Flag==1) {
    digitalWrite(relay6,relay_on);
  }
  
  d1Flag=-1;
  d2Flag=-1;
  d3Flag=-1;
  d4Flag=-1;
  d5Flag=-1;
  d6Flag=-1;
}

void bsp_init(void) {
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

int device_read_from_madblocksdb(int deviceID) {
  
  if(WiFi.status()== WL_CONNECTED){
      HTTPClient http;

      String serverPath = serverName + String(deviceID);
            
      http.begin(serverPath.c_str());
       
      int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        //Serial.print("HTTP Response code: ");
        //Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
        return(payload.toInt());
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
        return(0);
        
      }
      http.end();
    }
    else {
      Serial.println("WiFi Disconnected");
    }
}

