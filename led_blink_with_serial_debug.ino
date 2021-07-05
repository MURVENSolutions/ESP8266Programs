/*
 Title: LED blink program in Lua
  ESP8266 Blink Program
 Blink the on board blue LED on the ESP-12 module connected to GPIO2 pin.
 https://github.com/MURVENSolutions/ESP8266Programs (Public)
 MURVEN Infotech Design Solutions LLP (www.murven.in) 
 */
 
#define LED 2   //Define connection of LED

void setup() {
  Serial.begin(9600);
  delay(10);

  Serial.println();
  Serial.print("Connecting to esp8266 serial 9600");
  
  // put your setup code here, to run once:
   pinMode(LED, OUTPUT);     // Initialize the LED_BUILTIN pin as an output to drive the LED
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LED, LOW);   // Turn the LED ON by making the voltage LOW
  Serial.print("LOW-LED-ON");
  Serial.println();
  delay(500);              // Wait for a 500ms
  digitalWrite(LED, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(500);               // Wait for 500ms
  Serial.print("HIGH-LED-OFF");
  Serial.println();
}
