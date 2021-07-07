/*
 Title: ESP8266 Wifi client Program to control LED remotely in LAN network in Lua
 Configure and enable the wifi client in the ESP8266 chip and connect to your wifi network
 Now access the ESP8266 from another machine browser, as well as ping it using its TCP/IP stack.
 https://github.com/MURVENSolutions/ESP8266Programs (Public)
 MURVEN Infotech Design Solutions LLP (www.murven.in) 
 */

#include <ESP8266WiFi.h>
 
/* Enter your wifi network ssid and password here*/
const char* wifissid = "YOURWIFISSID";
const char* wifipass = "YOURWIFIPASSWORD";


#define LED 2          //Define connection of LED
WiFiServer server(80); //Server listen port

#define BLINK_RATE_1000  1000
#define BLINK_RATE_500  500
#define BLINK_RATE_250  250
#define BLINK_RATE_100  100

int wifiblinkcnt = 0;
int blinkmode = 0;
int blinkrate = 500;
 
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
    wifiblinkcnt++;
     
    /* Toggle the LED until wifi gets connected */
    if(wifiblinkcnt%2)
    {
      digitalWrite(LED, LOW);   // Turn the LED on by making the voltage LOW
    }
    else
    {
      digitalWrite(LED, HIGH);  // Turn the LED off by making the voltage HIGH
    }    
  }

  /* Now ESP8266 connected to wifi network */
  wifiblinkcnt = 0;
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

void blinkloop(int blink_rate) {
  
  digitalWrite(LED, LOW);   // Turn the LED on by making the voltage LOW
  delay(blink_rate);        // Wait for a given ms
  digitalWrite(LED, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(blink_rate);        // Wait for a given ms 
}
 
void loop() {
  
  /* put your main code here, to run repeatedly */

  /*Call the blink rate control routine with the selected blinkrate value */
   if (blinkmode == 1)
   {
      blinkloop(blinkrate);
   }
  
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
 
  /* Read the first line of the request fronm client*/
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();  
 
  // Match the request
  int value = LOW;

  if (request.indexOf("/BLED-ON") != -1)  {
    digitalWrite(LED, LOW);   // Turn the LED on by making the voltage LOW
    value = LOW;  
    blinkmode= 0;
  }

  /* Now button press event processing routines */
  if (request.indexOf("/BLED-OFF") != -1)  {
    digitalWrite(LED, HIGH);  // Turn the LED off by making the voltage HIGH
    value = HIGH;
    blinkmode= 0;    
  }

  if (request.indexOf("/DLED-ON") != -1)  {
    digitalWrite(LED, LOW);   // Turn the LED on by making the voltage LOW
    value = LOW;  
    blinkmode= 0;
  }

  /* Now dropdown select event processing routines */
  if (request.indexOf("/DLED-OFF") != -1)  {
    digitalWrite(LED, HIGH);  // Turn the LED off by making the voltage HIGH
    value = HIGH;
    blinkmode= 0;    
  }
  
  if (request.indexOf("/DLED-500") != -1)  {
    digitalWrite(LED, LOW);   // Turn the LED on by making the voltage HIGH    
    blinkmode= 1;
    blinkrate = BLINK_RATE_500;
  }

  if (request.indexOf("/DLED-100") != -1)  {
    digitalWrite(LED, LOW);   // Turn the LED on by making the voltage HIGH    
    blinkmode= 1;
    blinkrate = BLINK_RATE_100;
  }

  if (request.indexOf("/DLED-250") != -1)  {
    digitalWrite(LED, LOW);   // Turn the LED on by making the voltage HIGH    
    blinkmode= 1;
    blinkrate = BLINK_RATE_250;
  }
  
  if (request.indexOf("/DLED-1000") != -1)  {
    digitalWrite(LED, LOW);   // Turn the LED on by making the voltage HIGH    
    blinkmode= 1;
    blinkrate = BLINK_RATE_1000;
  }

  /* Return the response to client */
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); 
  client.println("");
  client.println("");

  
  client.print("
ESP8266 onboard LED control from remote machine
");
  client.print("<font size=\"3\" color=\"grey\">The current state of the Led: ");

  if (blinkmode == 1){
    client.print("<font size=\"3\" color=\"blue\">BLK :");
    if( blinkrate == BLINK_RATE_1000)
    { 
      client.print("<font size=\"3\" color=\"blue\"> 1000 ms ");
    }else if( blinkrate == BLINK_RATE_500)   
    { 
      client.print("<font size=\"3\" color=\"blue\"> 500 ms ");
    }else if( blinkrate == BLINK_RATE_250)
    { 
      client.print("<font size=\"3\" color=\"blue\"> 250 ms ");
    }else if( blinkrate == BLINK_RATE_100)
    { 
      client.print("<font size=\"3\" color=\"blue\"> 100 ms ");
    }
  }
  else if(value == LOW) {
    client.print("<font size=\"3\" color=\"red\"> On ");
  } else {
    client.print("<font size=\"3\" color=\"black\"> Off ");
  }

  
  /* HTML related code */
  /* Construct the button html feature */ 
  client.println("

");
  client.print("Button Tag:");
  client.println("
");
  client.println("<a href=\"/BLED-ON\"\">Turn On ");
  client.println("<a href=\"/BLED-OFF\"\">Turn Off ");  

  /* Construct the dropdown select html feature */ 
  client.println("

");
  client.print("Dropdown Select Tag:");
  client.println("
");
  client.println("<a href=\"#\" id=\"dynamicblinklink\">
");
  
  client.println("<select id=\"selTime\" onchange=\"mySelFunction()\">\
            <option selected=\"selected\" value=\"\">Select Time in ms\
            <option value=\"DLED-OFF\">Turn Off\
            <option value=\"DLED-ON\">Turn On\            
            <option value=\"DLED-100\">Blink 100ms\
            <option value=\"DLED-250\">Blink 250ms\
            <option value=\"DLED-500\">Blink 500ms\
            <option value=\"DLED-1000\">Blink 1000ms\
         </select>");

  /* This javaquery fuction is triggered during the change event of dropdown 
     Note the backslash \ char at the end of each line of script
     Do insert backslash \ char at ever instance of " char
     window.location.href is required to update the new event to server */
     
  client.println("\
      function mySelFunction() {\
    var seltimeval = document.getElementById(\"selTime\").value;\
    console.log(seltimeval);\
    document.getElementById('dynamicblinklink').href = '\' + seltimeval;\
    var href = '\' + seltimeval;\
    window.location.href = href;\
    }\
    </script>");         
         
  client.println("");
 
  delay(1);
  Serial.println("Now the Client got disconnected");
  Serial.println("");
 
}
 
