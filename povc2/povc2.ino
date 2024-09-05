// ---------------------------------------
//                 POV CLOCK 2                 
//                            (c) JFD 2024
// ---------------------------------------
#include <RtcDS1302.h>
#define PIN_ENA 3
#define PIN_CLK 4
#define PIN_DAT 5

ThreeWire myWire(PIN_DAT,PIN_CLK,PIN_ENA); // IO, SCLK, CE
RtcDS1302<ThreeWire> Rtc(myWire);

#define LEDH 6
#define LEDM 7
#define CMOT 9
#define BM 11
#define BSTART 2
#define BH 8


int h=0;
int m;
int s;
int modifh=0;


int seuil=800;
//unsigned long periode;
float periode=0.0;
unsigned long t1;
unsigned long t2;
unsigned long t0=0;
unsigned long ts;
unsigned long tm;
int run=0;
int speed=50;
int ktours=0;  // Compteur pour lecture périodique de l'heure

// Détermine et affiche la période 
void writePeriode()
{
  periode=0;
   while(analogRead(A0)<seuil);
   while(analogRead(A0)>seuil);
  for (int i=0; i<10; i++)
  {
    t1=millis();
   while(analogRead(A0)<seuil);
   while(analogRead(A0)>seuil);
   periode=periode+(millis()-t1);
   
   digitalWrite(LEDH,HIGH);
   delay(2);
   digitalWrite(LEDH,LOW);
  }
   Serial.print(periode/10);
   Serial.println(" ms");
}

// --------------------------
// Ecrit l'heure dans le RTC
// --------------------------
void setTime(int h,int m, int s)
{
  Serial.print("SetTime");
  Serial.print(h);
  Serial.print(":");
  Serial.println(m);
        RtcDateTime now(24, 8, 17,h, m, s);
        Rtc.SetDateTime(now);
}
// --------------------------
// Lit l'heure dans le RTC
// --------------------------
void getTime()
{
  RtcDateTime now = Rtc.GetDateTime();
   //printDateTime(now);
    h=now.Hour();
    m=now.Minute();
    s=now.Second();

    if (h>12) h=h-12;
}

void mode()
{
  delay(1);  // filtrage parasites...
  if (digitalRead(BSTART)==0)
    switch (run)
    {
      case 0: if ((millis()-ts)>(unsigned long)2000) 
              {
                run=1; 
                analogWrite(CMOT,speed); 
                ts=millis();
                Serial.print(run);
                ktours=600;
              }
              break;
      case 1: if ((millis()-ts)>(unsigned long)2000) 
              {
                run=0; 
                analogWrite(CMOT,0); 
                ts=millis();
                Serial.print(run);
              }
              break;
    }
}

// ------------------
// Initialisations
// ------------------
void setup() 
{
  Rtc.Begin();
  getTime();
  Serial.begin(115200);
  while (!Serial) ;
  pinMode(LEDH,OUTPUT);
  pinMode(LEDM,OUTPUT);
  Serial.println("Start");
  Serial.print(h);
  Serial.print(":");
  Serial.println(m);
  // Commande moteur
   pinMode(CMOT, OUTPUT);
   // Boutons
   pinMode(BM, INPUT_PULLUP);
   pinMode(BH, INPUT_PULLUP);
   pinMode(BSTART, INPUT_PULLUP);

  // ICR1 = 639;     //640 ticks of 16MHz clock == 40uS == 25kHz
  // //OCR1A = 320;    //50% duty cycle
  // TCCR1A = _BV(COM1A1) | _BV(WGM11);
  // TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS10);  
  TCCR1B = TCCR1B & B11111000 | B00000001;
  
  analogWrite(CMOT,0);
  //writePeriode();
  attachInterrupt(digitalPinToInterrupt(BSTART), mode, FALLING);
}

int okh;  // Flag affichage aiguille des heures
int okm;  // Flag affichage aiguille des minutes

int kh=0; // Incrémentation des heures

void loop() 
{
   t0=millis();
   periode=0;
    okh=0;
    okm=0;
    
    if (digitalRead(BM)==0) 
    {
      m++;
      if (m>59) m=0;
      modifh=1;
      tm=millis();
      
    }

    if (digitalRead(BH)==0) 
    {
      kh++;
      if (kh==10)
      {
        kh=0;
      h++;
      if (h>11) h=0;
      modifh=1;
      tm=millis();
      }
      
    }
   while(analogRead(A0)>seuil);

   while(analogRead(A0)<seuil)
   {
      if ((millis()-t0)>t1)
      {
        if (okh==0)
        {
          digitalWrite(LEDH,HIGH);
          delay(1);
          digitalWrite(LEDH,LOW);
          okh=1;
        }

      }
      if ((millis()-t0)>t2)
      {
        if (okm==0)
        {
          digitalWrite(LEDM,HIGH);
          digitalWrite(LEDH,HIGH);
          delay(1);
          digitalWrite(LEDM,LOW);
          digitalWrite(LEDH,LOW);
          okm=1;
        }

        if (modifh==1) if ((millis()-tm)>1000) { setTime(h,m,0); modifh=0; }
        
      }
   }
   //periode=periode*0.5+(millis()-t1)*0.5;
   periode=(millis()-t0);
   t1=int(periode*(h+6+m/60.0)/12);
   if (t1>=periode) t1-=periode;
   t2=int(periode*(m+30)/60);
   if (t2>=periode) t2-=periode;

   if (t1>periode) t1-=periode;
   ktours++;
   if (ktours>600)
   {
    ktours=0;
    if (modifh==1) { setTime(h,m,0); modifh=0; }

    getTime();
    // Serial.print(h);
    // Serial.print(":");
    // Serial.println(m);
    // Serial.println(periode);

   }
}
