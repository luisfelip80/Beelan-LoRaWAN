#include <lorawan.h>

//ABP Credentials 
const char *devEui = "003F22F6723E38B1";
const char *appEui = "70B3D57ED003439A";
const char *appKey = "AFFFE84E8314E84044E0F75A4CDD940C";

const unsigned long interval = 20000;    // 10 s interval to send message
unsigned long previousMillis = 0;  // will store last time message sent
unsigned int counter = 0;     // message counter

char myStr[50];
char outStr[255];
byte recvStatus = 0;


const sRFM_pins RFM_pins = {
  .CS = 15,
  .RST = 16,
  .DIO0 = 5,
  .DIO1 = 4,
  .DIO2 = -1,
  .DIO5 = -1,
};


void setup() {
  // Setup loraid access
  Serial.begin(115200);
  delay(5000);
  Serial.println("Start..");
  if(!lora.init()){
    Serial.println("RFM95 not detected");
    delay(5000);
    return;
  }

  // Set LoRaWAN Class change CLASS_A or CLASS_C
  lora.setDeviceClass(CLASS_C);

  // Set Data Rate
  lora.setDataRate(SF7BW125);

  // set channel to random
  lora.setChannel(MULTI);
  
  // Put ABP Key and DevAddress here
  lora.setNwkSKey(nwkSKey);
  lora.setAppSKey(appSKey);
  lora.setDevAddr(devAddr);
}

void loop() {
  
  // Check interval overflow
  if(millis() - previousMillis > interval) {
    previousMillis = millis(); 

    sprintf(myStr, "Counter-%d", counter); 

    Serial.print("Sending: ");
    Serial.println(myStr);
    
    lora.sendUplink(myStr, 10, 0, 1);
    counter++;
  }

  recvStatus = lora.readData(outStr);
  if(recvStatus) {
    Serial.print("====>> ");
    Serial.println(outStr);
  }
  
  // Check Lora RX
  lora.update();
}