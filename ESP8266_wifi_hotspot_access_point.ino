
/*
  Title: ESP8266 Wifi Hotspot access point Program in Lua
  Configure and enable the wifi Hotspot AP in the ESP8266 chip and connect remote device to the new AP.
  Now run the webserver on this Hotspot AP and serve the remote client requests
  Print the mac and ip address of newly connected clients
  https://github.com/MURVENSolutions/ESP8266Programs (Public)
  MURVEN Infotech Design Solutions LLP (www.murven.in) 
*/


#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

// Include the plain C library
extern "C" {
#include "user_interface.h"
}


/* Set these to your desired credentials. */
const char *ssidAP = "ESP8266WifiAP";
const char *passAP = "12345678";

IPAddress myAPIP(192,168,4,254);
IPAddress gateway(192,168,4,254);
IPAddress subnet(255,255,255,0);

char wifiClientMac[20] ={0};
String wifiClientIp;
String wifiServerIp;
int wifiClientIPfound = 0;
int wifiClientCnt = 0;
int LEDvalue = LOW;

#define LED 2 //Define connection of LED - glows when ESP8266WifiAP Hotspot is up
ESP8266WebServer server(80);


static const char PROGMEM HTMLIndex[] = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
<style>
</style>
</head>

<body>
<h3>You are connected to ESP8266WifiAP Hotspot wifi hotspot AP</h3> 
</body>
</html>

)rawliteral";


void handleReq() {
    server.send_P(200, "text/html", HTMLIndex);
    //server.send(200, "text/html", "
You are connected to ESP8266WifiAP Hotspot wifi hotspot AP
");
}



boolean getdeviceIP(char* mac_device, String &rIp_Addr) {

  struct station_info *station_list = wifi_softap_get_station_info();
  while (station_list != NULL) {
    char station_mac[18] = {0}; 
    sprintf(station_mac, "%02X:%02X:%02X:%02X:%02X:%02X", MAC2STR(station_list->bssid));
    String station_ip = IPAddress((&station_list->ip)->addr).toString();

    if (strcmp(mac_device,station_mac)==0) {
      wifiClientIPfound=1;
      rIp_Addr = station_ip;
      return true;
    } 

    station_list = STAILQ_NEXT(station_list, next);
  }

  wifi_softap_free_station_info();
  //Serial.printf("Wifi client IP address not found or bad MAC address"); => this line gets printed for failure or no client connection 
  return false;
} 

/* Print thee incoming device connection on ESP access point */
void onNewWifiClientConnection(WiFiEventSoftAPModeStationConnected sta_info) {
  
  Serial.println("\n");
  Serial.println("New wifi client details:");
  sprintf(wifiClientMac,"%02X:%02X:%02X:%02X:%02X:%02X", MAC2STR(sta_info.mac));
  Serial.printf("MAC address : %s\n",wifiClientMac);
  Serial.printf("Wlan Idx : %d\n", sta_info.aid);
  Serial.printf("Wifi clients connected to Hotspot = %d\n", WiFi.softAPgetStationNum());
  
}

 

void setup() {
  delay(1000);
  Serial.begin(9600);
  Serial.print("Connecting to esp8266 serial 9600");
  pinMode(LED, OUTPUT);     // Initialize the LED_BUILTIN pin as an output
  delay(100);
  digitalWrite(LED, HIGH); // Turn off the LED by making the voltage HIGH
  
  Serial.println();
  Serial.print("Configuring wifi hotspot access point in your ESP8266...");
  Serial.println();

  static WiFiEventHandler wifiEvent;

  WiFi.mode(WIFI_AP); //==>Configure only Access point
  //WiFi.mode(WIFI_AP_STA);  ==>Congigure as both hotspotAP and client

  /* configure the AP IP, GW and Subnet */
  WiFi.softAPConfig(myAPIP, gateway, subnet);

  /* start hotspot - if you want your AP to be remain open, do skip passing the password value to this call */
  WiFi.softAP(ssidAP, passAP);
  
  IPAddress myAPIP = WiFi.softAPIP();
  Serial.print("Your ESP8266WifiAP Hotspot IP address is: ");
  Serial.println(myAPIP);
  wifiServerIp = IPAddress(myAPIP).toString();
  Serial.printf("MAC address of Hotspot= %s\n", WiFi.softAPmacAddress().c_str());

  /* Add wifi Event subscription */
  wifiEvent = WiFi.onSoftAPModeStationConnected(onNewWifiClientConnection);


  /* Function where the web request from the client to server are handled */
  server.on("/", handleReq);

  /* Start the web server */
  server.begin();
  Serial.println("Now the HTTP server started in your ESP8266 chipset");
  Serial.println();

  /* Switch on the LED to indicate Hotspot and server up status */
  digitalWrite(LED, LOW); // Turn the LED on by making the voltage LOW

}

void loop() {

  /* Handle all the client response */
  server.handleClient();

  int wifiClientCur = WiFi.softAPgetStationNum();
  if(wifiClientCnt != wifiClientCur){
    wifiClientCnt = wifiClientCur;
    //Serial.println("Current wifi cnt:");
    //Serial.println(wifiClientCnt);
    
    if (getdeviceIP(wifiClientMac,wifiClientIp)) {   
      Serial.println("Ip address of the wifi client:");
      Serial.println(wifiClientIp);
      wifiClientIPfound = 0;
    } else {
      //Serial.println("Problem getting ip address details:"); ==> This line gets printed until a client gets connected     
    }
    
  }


}
