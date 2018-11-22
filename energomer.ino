long uptime = 0;
long uptime15 = 0;
long i = 0;
long current_consumption = 0;
long current_consumption15 = 0;
volatile long v = 0;
volatile long v15 = 0;
volatile long total = 0;
char c;

void inc(){
  v++;
  v15++;
  total++;
}

void setup() {
  pinMode(2,INPUT_PULLUP);
  pinMode(13,OUTPUT);
  attachInterrupt(0,inc,FALLING);
  Serial.begin(9600);
  delay(100);
  Serial.println("Program started.");
  Serial.println("Type \"?\" to get all readings.");
  Serial.println(">>");
  delay(100);
}

void loop() {
  if (digitalRead(2)==1) {
    digitalWrite(13,LOW);
  } 
  else {
    digitalWrite(13,HIGH);
  }
  i=millis();
  if (i - uptime >= 300000) {
    current_consumption=v*12;
    v=0;
    uptime=i;
  }
  i=millis();
  if (i - uptime15 >= 900000) {
    current_consumption15=v15*4;
    v15=0;
    uptime15=i;
  }
  if (Serial.available()){
    c=Serial.read();
    if (c=='?'){
      Serial.print("System uptime in ms:");
      Serial.print(millis());
      Serial.println("#");
      Serial.print("Average power consumption for the past 5 mins in W:");
      Serial.print(current_consumption);
      Serial.println("#");
      Serial.print("Average power consumption for the past 15 mins in W:");
      Serial.print(current_consumption15);
      Serial.println("#");
      Serial.print("Impulses since system start:");
      Serial.print(total);
      Serial.println("#");
    }
  }
  delay(10);
}
