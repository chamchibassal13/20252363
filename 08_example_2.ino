#define PIN_LED  9
#define PIN_TRIG 12
#define PIN_ECHO 13

#define SND_VEL   346.0
#define INTERVAL  25
#define PULSE_US  10
#define DIST_MIN  100.0
#define DIST_MID  200.0
#define DIST_MAX  300.0

#define TIMEOUT_US ((INTERVAL/2.0)*1000.0)
#define US_TO_MM   (0.001*0.5*SND_VEL)

unsigned long last_ms=0;

float USS_measure(int TRIG,int ECHO);
uint8_t dutyFromDistanceActiveLow(float d_mm);

void setup(){
  pinMode(PIN_LED,OUTPUT);
  pinMode(PIN_TRIG,OUTPUT);
  pinMode(PIN_ECHO,INPUT);
  digitalWrite(PIN_TRIG,LOW);

  Serial.begin(57600);
  unsigned long t0=millis();
  while(!Serial && (millis()-t0<3000)){}
  delay(200);
  Serial.println("READY");
}

void loop(){
  unsigned long now=millis();
  if(now-last_ms<INTERVAL) return;
  last_ms=now;

  float d=USS_measure(PIN_TRIG,PIN_ECHO);
  uint8_t duty=dutyFromDistanceActiveLow(d);
  analogWrite(PIN_LED,duty);

  static uint8_t k=0;
  if((k++&0x07)==0){
  Serial.print("d:");    Serial.print(d,1);   Serial.print('\t');
  Serial.print("duty:"); Serial.println(duty);
  }
}

float USS_measure(int TRIG,int ECHO){
  digitalWrite(TRIG,HIGH);
  delayMicroseconds(PULSE_US);
  digitalWrite(TRIG,LOW);
  unsigned long dur=pulseIn(ECHO,HIGH,(unsigned long)TIMEOUT_US);
  if(dur==0) return 1e9;
  return dur*US_TO_MM;
}

uint8_t dutyFromDistanceActiveLow(float d_mm){
  if(!(d_mm>0) || d_mm<=DIST_MIN || d_mm>=DIST_MAX) return 255;
  float b = (d_mm<=DIST_MID)
    ? (d_mm-DIST_MIN)/(DIST_MID-DIST_MIN)
    : (DIST_MAX-d_mm)/(DIST_MAX-DIST_MID);
  if(b<0) b=0; if(b>1) b=1;
  int duty=(int)((1.0-b)*255.0+0.5);
  if(duty<0) duty=0; if(duty>255) duty=255;
  return (uint8_t)duty;
}
