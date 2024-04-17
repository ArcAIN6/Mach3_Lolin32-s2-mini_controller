#include <esp_now.h>
#include <WiFi.h>
#include "USB.h"
#include "USBHIDKeyboard.h"
USBHIDKeyboard Keyboard;

#define OSX 0
#define Windows 1
#define UBUNTU 2

int platorm = Windows;

int keyState;




#define SIGNAL_TIMEOUT 1000  // This is signal timeout in milli seconds. We will reset the data if no signal

unsigned long lastRecvTime = 0;

struct PacketData
{

  byte switch1Value;
  byte switch2Value;
  byte switch3Value;
  byte switch4Value;  

};
PacketData receiverData;

int   led1 = 2;
int   led2 = 3;
int   led3 = 4;
int   led4 = 5;


//Assign default input received values
void setInputDefaultValues()
{

  receiverData.switch1Value = LOW;
  receiverData.switch2Value = LOW;
  receiverData.switch3Value = LOW;
  receiverData.switch4Value = LOW; 
 
}

void mapAndWriteValues()
{
  
  digitalWrite(led1, receiverData.switch1Value);
  digitalWrite(led2, receiverData.switch2Value);
  digitalWrite(led3, receiverData.switch3Value);
  digitalWrite(led4, receiverData.switch4Value); 
 
}

// callback function that will be executed when data is received
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) 
{
  if (len == 0)
  {
    return;
  }
  memcpy(&receiverData, incomingData, sizeof(receiverData));
  mapAndWriteValues();  
  lastRecvTime = millis(); 
}

void setUpPinModes()
{

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);      
  
  setInputDefaultValues();
  mapAndWriteValues();
}

void setup() 
{
  setUpPinModes();
  WiFi.mode(WIFI_STA);
  delay(1000);
  Serial.begin(115200);
  Serial.println("I'm Alive!");
  
  //Keyboard Startup
  Keyboard.begin();
  
  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) 
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}
 


void loop()
{
  //Check Signal lost.
  unsigned long now = millis();
  if ( now - lastRecvTime > SIGNAL_TIMEOUT ) 
  {
    setInputDefaultValues();
    mapAndWriteValues();  
  }

  if ((receiverData.switch1Value == HIGH) && (keyState == 0)){
    // E-Stop KEYBOARD COMMAND
    //Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press(' ');
    Keyboard.releaseAll();
    keyState =1;
  }
  
  if ((receiverData.switch2Value == HIGH) && (keyState == 0)){
    // Cycle Stop KEYBOARD COMMAND ALT-S
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press('s');
    Keyboard.releaseAll();
    keyState =1;
  }
  
    if ((receiverData.switch3Value == HIGH) && (keyState == 0)){
    // Cycle Pause KEYBOARD COMMAND (SPACE)
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press('p');
    Keyboard.releaseAll();
    keyState =1;
  }

  if ((receiverData.switch4Value == HIGH) && (keyState == 0)){
    // Cycle Start KEYBOARD COMMAND ALT-R
    Keyboard.press(KEY_LEFT_ALT);
    Keyboard.press('r');
    Keyboard.releaseAll();
    keyState =1;
  }
  

  if ((receiverData.switch1Value == LOW) && (receiverData.switch2Value == LOW) && (receiverData.switch3Value == LOW) && (receiverData.switch4Value == LOW) && (keyState == 1))
  {
    keyState = 0;
  }
  
}
