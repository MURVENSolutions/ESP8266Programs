/*
 Title: ESP8266 with MQ-6 program in C
 Components: MQ-6 Gas Sensor
 Description: Connect MQ-6 with ESP8266.
 Company: MURVEN Infotech Design Solutions LLP (www.murven.in) 
*/
 
int Buzzer = D3;        
int Gas_analog = A0;    
int Gas_digital = D0;   



void setup() {
  Serial.begin(115200);
  pinMode(Buzzer, OUTPUT);      
  pinMode(Gas_digital, INPUT);
}

void loop() {
  int gassensorAnalog = analogRead(Gas_analog);
  int gassensorDigital = digitalRead(Gas_digital);

  Serial.print("Gas Sensor: ");
  Serial.print(gassensorAnalog);
  Serial.print("\t");
  Serial.print("Gas Class: ");
  Serial.print(gassensorDigital);
  Serial.print("\t");
  Serial.print("\t");
  
  if (gassensorAnalog > 400) {
    Serial.println("Gas");
    digitalWrite (Buzzer, HIGH) ; //send tone
    delay(1000);
    digitalWrite (Buzzer, LOW) ;  //no tone
  }
  else {
    Serial.println("No Gas");
  }
  delay(100);
