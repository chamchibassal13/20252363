# define PIN_LED 7
unsigned int count, toggle;

void setup() {
  pinMode(PIN_LED, OUTPUT);
  Serial.begin(115200);
  while (!Serial) {
    ;
  }
  Serial.println("Hello World!");
  count = toggle = 1;
  digitalWrite(PIN_LED, toggle);
}

void loop() {
  count = toggle = 1;
  Serial.println(--count);
  toggle = toggle_state(count);
  digitalWrite(PIN_LED, toggle);
  delay(1000);
  for( int i = 0; i <= 5; i++) {
  Serial.println(--count);
  toggle = toggle_state(count);
  digitalWrite(PIN_LED, toggle);
  delay(100);
  Serial.println(++count);
  toggle = toggle_state(count);
  digitalWrite(PIN_LED, toggle);
  delay(100);  
  }
 while(1){
    count = 1;
    Serial.println(count);
    toggle = toggle_state(count);
    digitalWrite(PIN_LED, toggle);
  }
}


int toggle_state(int togle) {
  return togle;
}
