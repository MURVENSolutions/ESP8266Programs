
/*
 Title: ESP8266 Wifi client Program in Lua
 Configure and enable the wifi client in the ESP8266 chip and connect to your wifi network
 Now access the ESP8266 from another machine browser, as well as ping it using its TCP/IP stack.
 https://github.com/MURVENSolutions/ESP8266Programs (Public)
 MURVEN Infotech Design Solutions LLP (www.murven.in) 
 */
 

#include <ESP8266WiFi.h>
 
/* Enter your wifi network ssid and password her*/
const char* wifissid = "YOURWIFISSID";
const char* wifipass = "YOURWIFIPASSWORD";

#define LED 2         //Define connection of LED - glows when wifi network is connected

WiFiServer server(80); //Server listen port

int blkcnt = 0;

void setup() {
  
  Serial.begin(9600);
  delay(10);
  
  Serial.print("Connecting to esp8266 serial 9600"); 
  pinMode(LED, OUTPUT);     // Initialize the LED_BUILTIN pin as an output 

  // Connect to your WiFi network
  Serial.println();
  Serial.print("Connecting to your wifi network....");
  Serial.println(wifissid);
 
  WiFi.begin(wifissid, wifipass);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    blkcnt++;
    
    /* Toggle the LED until wifi gets connected */
    if(blkcnt%2)
    {
      digitalWrite(LED, LOW);   // Turn the LED on by making the voltage LOW
    }
    else
	    {
      digitalWrite(LED, HIGH);  // Turn the LED off by making the voltage HIGH
    }
    
  }

  /* Now ESP8266 connected to wifi network */
  blkcnt = 0;
  digitalWrite(LED, LOW);   // Turn the LED on by making the voltage LOW
  
  Serial.println("");
  Serial.println("WiFi connected");
 
  /* Start the server */
  server.begin();
  Serial.println("Server started");
 
  /* Print the IP address of this device */
  Serial.print("This device URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}


void loop() {
 

  /* Check if a client has connected */
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  /* Wait until the client sends some data to server running on ESP*/
  
  while(!client.available()){
    delay(1);
  }
  Serial.println("New client data request received");

  /* Return the web response */
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); 
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
 
  client.print("<h3> You have now reached the server running on ESP8266 <h3>");     
  client.println("</html>");
 
  delay(1);
  Serial.println("Now the Client got disconnected");
  Serial.println("");
  
    /* Flicker the LED to indicate client access */
  digitalWrite(LED, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(100);
  digitalWrite(LED, LOW);   // Turn the LED on by making the voltage LOW
  

}
