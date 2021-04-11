#include<Servo.h>
#include <Wire.h>
#include<TimeLib.h>
#include <DS1307RTC.h>

const char *monthName[12] = {
  "Jan", "Feb", "Mar", "Apr", "May", "Jun",
  "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};
  tmElements_t tm;
   int Hour, Min, Sec;
int distance;
long duration;
#define ENABLE1  2
#define IN1  5
#define IN2  6
#define ENABLE2  3
#define IN3  7
#define IN4  8
#define TRIG 10
#define ECHO 9
#define SPEAKER 4
#define SERVO_1  11
#define SERVO_2  12
#define SERVO_3  13
#define S11  16
#define S01  15
#define S31  18
#define S21  17
#define OUT1 14
#define S12  21
#define S02  20
#define S32  23
#define S22  22
#define OUT2 19
#define S13  27
#define S03  25
#define S33  29
#define S23  28
#define OUT3 24
#define SDA A4
#define SCL A5
char color1;
char color2;
char color3;

int red1;
int blu1;
int grn1;

int red2;
int blu2;
int grn2;

int red3;
int blu3;
int grn3;

Servo servo1;
Servo servo2;
Servo servo3;

void setup()
{
  Serial.begin(9600);
   bool parse=false;
  bool config=false;

  // get the date and time the compiler was run
  if (getDate(__DATE__) && getTime(__TIME__)) {
    parse = true;
    // and configure the RTC with this info
    if (RTC.write(tm)) {
      config = true;
    }
  }

  Serial.begin(9600);
  while (!Serial) ; // wait for Arduino Serial Monitor
  delay(200);
  if (parse && config) {
    Serial.print("DS1307 configured Time=");
    Serial.print(__TIME__);
    Serial.print(", Date=");
    Serial.println(__DATE__);
  } else if (parse) {
    Serial.println("DS1307 Communication Error :-{");
    Serial.println("Please check your circuitry");
  } else {
    Serial.print("Could not parse info from the compiler, Time=\"");
    Serial.print(__TIME__);
    Serial.print("\", Date=\"");
    Serial.print(__DATE__);
    Serial.println("\"");
  }
 while (!Serial) ; // wait for serial
  delay(200);
  Serial.println("DS1307RTC Read Test");
  Serial.println("-------------------");
  
 
 
  pinMode(ENABLE1, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(S01, OUTPUT);
  pinMode(S11, OUTPUT);
  pinMode(S21, OUTPUT);
  pinMode(S31, OUTPUT);
  pinMode(OUT1, INPUT);
    pinMode(S02, OUTPUT);
  pinMode(S12, OUTPUT);
  pinMode(S22, OUTPUT);
  pinMode(S32, OUTPUT);
  pinMode(OUT2, INPUT);
    pinMode(S03, OUTPUT);
  pinMode(S13, OUTPUT);
  pinMode(S23, OUTPUT);
  pinMode(S33, OUTPUT);
  pinMode(OUT3, INPUT);
  pinMode(ENABLE2, OUTPUT);
  pinMode(SPEAKER, OUTPUT);
  servo1.attach(SERVO_1);
  servo2.attach(SERVO_2);
  servo3.attach(SERVO_3);


  servo1.write(0);
    servo2.write(0);
  servo3.write(0);

 

}
bool getTime(const char *str)
{
 

  if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
  tm.Hour = Hour;
  tm.Minute = Min;
  tm.Second = Sec;
  return true;
}
bool getDate(const char *str)
{
  char Month[12];
  int Day, Year;
  uint8_t monthIndex;

  if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3) return false;
  for (monthIndex = 0; monthIndex < 12; monthIndex++) {
    if (strcmp(Month, monthName[monthIndex]) == 0) break;
  }
  if (monthIndex >= 12) return false;
  tm.Day = Day;
  tm.Month = monthIndex + 1;
  tm.Year = CalendarYrToTm(Year);
  return true;
}

void loop()
{ tmElements_t tm;

  if (RTC.read(tm)) {
    Serial.print("Ok, Time = ");
    print2digits(tm.Hour);
    Serial.write(':');
    print2digits(tm.Minute);
    Serial.write(':');
    print2digits(tm.Second);
    Serial.print(", Date (D/M/Y) = ");
    Serial.print(tm.Day);
    Serial.write('/');
    Serial.print(tm.Month);
    Serial.write('/');
    Serial.print(tmYearToCalendar(tm.Year));
    Serial.println();
  } else {
    if (RTC.chipPresent()) {
      Serial.println("The DS1307 is stopped.  Please run the SetTime");
      Serial.println("example to initialize the time and begin running.");
      Serial.println();
    } else {
      Serial.println("DS1307 read error!  Please check the circuitry.");
      Serial.println();
    }
    delay(9000);
  }
  delay(1000);
  

    digitalWrite(TRIG,LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG,HIGH);
  delayMicroseconds(10);
  duration=pulseIn(ECHO,HIGH);
  distance=(duration/2)*(0.034);
  Serial.println(distance);
  Serial.print(" cm");
  

int  Hour = Hour;

     digitalWrite(S03,HIGH);
  digitalWrite(S13,HIGH);
   digitalWrite(S03,HIGH);
  digitalWrite(S13,HIGH);
       digitalWrite(S03,HIGH);
  digitalWrite(S13,HIGH);
      
      
    digitalWrite(S21, LOW);
    digitalWrite(S31, LOW);
    red1 = pulseIn(OUT1, LOW); 
      digitalWrite(S21, HIGH);
    digitalWrite(S31, HIGH);
    grn1 = pulseIn(OUT1, LOW); 
      digitalWrite(S21, LOW);
    digitalWrite(S31, HIGH);
    blu1 = pulseIn(OUT1, LOW);

     digitalWrite(S22, LOW);
    digitalWrite(S32, LOW);
    red2 = pulseIn(OUT2, LOW); 
      digitalWrite(S22, HIGH);
    digitalWrite(S32, HIGH);
    grn2 = pulseIn(OUT2, LOW); 
      digitalWrite(S22, LOW);
    digitalWrite(S32, HIGH);
    blu2 = pulseIn(OUT2, LOW);

     digitalWrite(S23, LOW);
    digitalWrite(S33, LOW);
    red3 = pulseIn(OUT3, LOW); 
      digitalWrite(S23, HIGH);
    digitalWrite(S33, HIGH);
    grn3 = pulseIn(OUT3, LOW); 
      digitalWrite(S23, LOW);
    digitalWrite(S33, HIGH);
    blu3 = pulseIn(OUT3, LOW);
getColor1();
getColor2();
getColor3();

 if( Hour == 9 &&  Min == 25) //Comparing the current time with the Alarm time
{
to_room_A();
}

if( Hour == 9 &&  Min == 35)
{
servo1.write(0);
}

if( Hour == 9 &&  Min == 45)
for (int i=0;i<5;i++)
{ analogWrite(ENABLE1,127);
  analogWrite(ENABLE2,127);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(500)
   }  
 to_room_B();  
 }
if( Hour == 10 &&  Min == 30) // back to base
{
  servo2.write(0);
  for (int i=0;i<5;i++)
  { analogWrite(ENABLE1,127);
  analogWrite(ENABLE2,127);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(500);
   }
   to_base();
}
if( Hour == 11 &&  Min == 55) // to C
{
  to_roon_c();
}

   if( Hour == 12 &&  Min == 30) // to C
    {
      servo3.write(0);
        for (int i=0;i<5;i++)
  { analogWrite(ENABLE1,127);
  analogWrite(ENABLE2,127);
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
  delay(500);
   }
   
to_base_from_room_C()
      
    }
}
void digitalClockDisplay(){
  // digital clock display of the time
  Serial.print(hour());
  printDigits(minute());
  printDigits(second());
  Serial.print(" ");
  Serial.print(day());
  Serial.print(" ");
  Serial.print(month());
  Serial.print(" ");
  Serial.print(year()); 
  Serial.println(); 
}

void printDigits(int digits){
  // utility function for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}

/*  code to process time sync messages from the serial port   */
#define TIME_HEADER  "T"   // Header tag for serial time sync message

unsigned long processSyncMessage() {
  unsigned long pctime = 0L;
  const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2013 

  if(Serial.find(TIME_HEADER)) {
     pctime = Serial.parseInt();
     return pctime;
     if( pctime < DEFAULT_TIME) { // check the value is a valid time (greater than Jan 1 2013)
       pctime = 0L; // return 0 to indicate that the time is not valid
     }
  }
  return pctime;
}
void print2digits(int number) {
  if (number >= 0 && number < 10) {
    Serial.write('0');
  }
  Serial.print(number);
}

void getColor1()
{  
  readRGB1();
    
 if (red1 > 80 && red1 < 125  &&  grn1 > 90 && grn1 < 125   &&  blu1 > 80 && blu1 < 125)  {
    color1 = "BLACK";
  }
  else if (red1 > 12 && red1 < 30   &&  grn1 > 40 && grn1 < 70    &&  blu1 > 33 && blu1 < 70) {
    color1 = "RED";
  }
  else if (red1 > 50 && red1 < 95   &&  grn1 > 35 && grn1 < 70    &&  blu1 > 45 && blu1 < 85) {
    color1 = "GREEN";
  }
  else if (red1 > 10 && red1 < 20   &&  grn1 > 10 && grn1 < 25    &&  blu1 > 20 && blu1 < 38)  {
    color1 = "YELLOW";
  }
  else if (red1 > 65 && red1 < 125  &&  grn1 > 65 && grn1 < 115   &&  blu1 > 32 && blu1 < 65)  {
    color1 = "BLUE";
  }
  else if (red1 > 35 && red1 < 75  &&  grn1 > 65 && grn1 < 115   &&  blu1 > 32 && blu1 < 65){
    color1 = "VIOLET";
  }
  else 
  {
    color1 = "NO_COLOR";
  }
}
void readRGB1() 
{
  red1 = 0;
  grn1 = 0;
  blu1 = 0;
  int n = 10;
  for (int i = 0; i < n; ++i)
  {
    //read red component
    digitalWrite(S21, LOW);
    digitalWrite(S31, LOW);
    red1 = red1 + pulseIn(OUT1, LOW);
  
   //read green component
    digitalWrite(S21, HIGH);
    digitalWrite(S31, HIGH);
    grn1 = grn1 + pulseIn(OUT1, LOW);
    
   //let's read blue component
    digitalWrite(S21, LOW);
    digitalWrite(S31, HIGH);
    blu1 = blu1 + pulseIn(OUT1, LOW);
  }
  red1 = red1/n;
  grn1 = grn1/n;
  blu1 = blu1/n;
}



void getColor2()
{  
  readRGB2();
    
 if (red2 > 80 && red2 < 125  &&  grn2 > 90 && grn2 < 125   &&  blu2 > 80 && blu2 < 125)  {
    color2 = "BLACK";
  }
  else if (red2 > 12 && red2 < 30   &&  grn2 > 40 && grn2 < 70    &&  blu2 > 33 && blu2 < 70) {
    color2 = "RED";
  }
  else if (red2 > 50 && red2 < 95   &&  grn2 > 35 && grn2 < 70    &&  blu2 > 45 && blu2 < 85) {
    color2 = "GREEN";
  }
  else if (red2 > 10 && red2 < 20   &&  grn2 > 10 && grn2 < 25    &&  blu2 > 20 && blu2 < 38)  {
    color2 = "YELLOW";
  }
  else if (red2 > 65 && red2 < 125  &&  grn2 > 65 && grn2 < 115   &&  blu2 > 32 && blu2 < 65)  {
    color2 = "BLUE";
  }
  else if (red2 > 35 && red2 < 75  &&  grn2 > 65 && grn2 < 115   &&  blu2 > 32 && blu2 < 65){
    color2 = "VIOLET";
  }
  else 
  {
    color2 = "NO_COLOR";
  }
}
void readRGB2() 
{
  red2 = 0;
  grn2 = 0;
  blu2 = 0;
  int m = 10;
  for (int  j= 0; j < m; ++j)
  {
    //read red component
    digitalWrite(S22, LOW);
    digitalWrite(S32, LOW);
    red2 = red2 + pulseIn(OUT2, LOW);
  
   //read green component
    digitalWrite(S22, HIGH);
    digitalWrite(S32, HIGH);
    grn2 = grn2 + pulseIn(OUT2, LOW);
    
   //let's read blue component
    digitalWrite(S22, LOW);
    digitalWrite(S32, HIGH);
    blu2 = blu2 + pulseIn(OUT2, LOW);
  }
  red2 = red2/m;
  grn2 = grn2/m;
  blu2 = blu2/m;
}


void getColor3()
{  
  readRGB3();
    
 if (red3 > 80 && red3 < 125  &&  grn3 > 90 && grn3 < 125   &&  blu3 > 80 && blu3 < 125)  {
    color3 = "BLACK";
  }
  else if (red3 > 12 && red3 < 30   &&  grn3 > 40 && grn3 < 70    &&  blu3 > 33 && blu3 < 70) {
    color3 = "RED";
  }
  else if (red3 > 50 && red3 < 95   &&  grn3 > 35 && grn3 < 70    &&  blu3 > 45 && blu3 < 85) {
    color3 = "GREEN";
  }
  else if (red3 > 10 && red3 < 20   &&  grn3 > 10 && grn3 < 25    &&  blu3 > 20 && blu3 < 38)  {
    color3 = "YELLOW";
  }
  else if (red3 > 65 && red3 < 125  &&  grn3 > 65 && grn3< 115   &&  blu3 > 32 && blu3 < 65)  {
    color3 = "BLUE";
  }
  else if (red3 > 35 && red3 < 75  &&  grn3 > 65 && grn3 < 115   &&  blu3 > 32 && blu3 < 65){
    color3 = "VIOLET";
  }
  else 
  {
    color3 = "NO_COLOR";
  }
}
void readRGB3() 
{
  red3 = 0;
  grn3 = 0;
  blu3 = 0;
  int l = 10;
  for (int  k= 0; k < l; ++k)
  {
    //read red component
    digitalWrite(S23, LOW);
    digitalWrite(S33, LOW);
    red3 = red3 + pulseIn(OUT3, LOW);
  
   //read green component
    digitalWrite(S23, HIGH);
    digitalWrite(S33, HIGH);
    grn3 = grn3 + pulseIn(OUT3, LOW);
    
   //let's read blue component
    digitalWrite(S23, LOW);
    digitalWrite(S33, HIGH);
    blu3 = blu3 + pulseIn(OUT3, LOW);
  }
  red3 = red3/l;
  grn3 = grn3/l;
  blu3 = blu3/l;
}

void to_room_A()
{
   if(color1=='RED' && color2!='RED' && color3!='RED')
 {
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
 analogWrite(ENABLE1,255);
  analogWrite(ENABLE2,255);

 
 }
 if(color1!='RED' && color2!='RED' && color3=='RED')
 {
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
   analogWrite(ENABLE1,255);
  analogWrite(ENABLE2,255);
 }
 if(color1!='RED' && color2=='RED' && color3!='RED')
 {
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
   analogWrite(ENABLE1,255);
  analogWrite(ENABLE2,255);
 }
 if(distance<=10)
 {
   digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
   analogWrite(ENABLE1,255);
  analogWrite(ENABLE2,255);

 servo1.write(90)
  tone(speaker,500);
  delay(1000);
  
  tone(speaker,500);
  delay(1000);
  
  tone(speaker,500);
  delay(1000);
  
  tone(speaker,500);
  delay(1000);
  
  tone(speaker,500);
  delay(1000)
  
}

void to_room_B()
{
   if(color1=='BLACK' && color2!='BLACK' && color3!='BLACK')
 {
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
 analogWrite(ENABLE1,255);
  analogWrite(ENABLE2,255);

 
 }
 if(color1!='BLACK' && color2!='BLACK' && color3=='BLACK')
 {
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
   analogWrite(ENABLE1,255);
  analogWrite(ENABLE2,255);
 }
 if(color1!='BLACK' && color2=='BLACK' && color3!='BLACK')
 {
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
   analogWrite(ENABLE1,255);
  analogWrite(ENABLE2,255);
 }
 if(distance<=10)
 {
   digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
   analogWrite(ENABLE1,0);
  analogWrite(ENABLE2,0);

 servo2.write(90)
  tone(speaker,500);
  delay(1000);
  
  tone(speaker,500);
  delay(1000);
  
  tone(speaker,500);
  delay(1000);
  
  tone(speaker,500);
  delay(1000);
  
  tone(speaker,500);
  delay(1000)
  
}
void to_base()
{
   if(color1=='BLUE' && color2!='BLUE' && color3!='BLUE')
 {
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
 analogWrite(ENABLE1,255);
  analogWrite(ENABLE2,255);

 
 }
 if(color1!='BLUE' && color2!='BLUE' && color3=='BLUE')
 {
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
   analogWrite(ENABLE1,255);
  analogWrite(ENABLE2,255);
 }
 if(color1!='BLUE' && color2=='BLUE' && color3!='BLUE')
 {
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
   analogWrite(ENABLE1,255);
  analogWrite(ENABLE2,255);
 }
 if(distance<=10)
 {
   digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
   analogWrite(ENABLE1,0);
  analogWrite(ENABLE2,0);
 }
}
void to_room_C()
{
   if(color1=='GREEN' && color2!='GREEN' && color3!='GREEN')
 {
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
 analogWrite(ENABLE1,255);
  analogWrite(ENABLE2,255);

 
 }
 if(color1!='GREEN' && color2!='GREEN' && color3=='GREEN')
 {
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
   analogWrite(ENABLE1,255);
  analogWrite(ENABLE2,255);
 }
 if(color1!='GREEN' && color2=='GREEN' && color3!='GREEN')
 {
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
   analogWrite(ENABLE1,255);
  analogWrite(ENABLE2,255);
 }
 if(distance<=10)
 {
   digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
   analogWrite(ENABLE1,0);
  analogWrite(ENABLE2,0);

 servo3.write(90)
  tone(speaker,500);
  delay(1000);
  
  tone(speaker,500);
  delay(1000);
  
  tone(speaker,500);
  delay(1000);
  
  tone(speaker,500);
  delay(1000);
  
  tone(speaker,500);
  delay(1000)
  
}
)
void to_base_from_room_C()
{
   if(color1=='GREEN' && color2!='GREEN' && color3!='GREEN')
 {
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
 analogWrite(ENABLE1,255);
  analogWrite(ENABLE2,255);

 
 }
 if(color1!='GREEN' && color2!='GREEN' && color3=='GREEN')
 {
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
   analogWrite(ENABLE1,255);
  analogWrite(ENABLE2,255);
 }
 if(color1!='GREEN' && color2=='GREEN' && color3!='GREEN')
 {
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
   analogWrite(ENABLE1,255);
  analogWrite(ENABLE2,255);
 }
 if(distance<=10)
 {
   digitalWrite(IN1,LOW);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,LOW);
   analogWrite(ENABLE1,0);
  analogWrite(ENABLE2,0);
 }
 }
