#include <dht.h>
#include <LiquidCrystal.h>
#define DHT11_PIN 12
#define relay_pin 13
#define samples 10


LiquidCrystal lcd(7,6,5,4,3,2);

dht DHT;

int humidity[samples];
int temperature[samples];
int sum_temp;
int sum_hum;
int avg_temp;
int avg_hum;



byte degree[]={B00010,
                  B00101,
                  B00010,
                  B00000,
                  B00000,
                  B00000,
                  B00000,
                  B00000};

void setup(){
  Serial.begin(9600);
  
  lcd.createChar(0,degree);
  lcd.begin(16,2);
  pinMode(relay_pin, OUTPUT);
}

void get_temp_and_hum(){
  
  DHT.read11(DHT11_PIN);
 
  for (int i=0; i<samples; i++){
  
  temperature[i]=(DHT.temperature);
  humidity[i]=(DHT.humidity);
  delay(1000);
  }


  for (int j=0; j<samples; j++){
    sum_temp += temperature[j];
    }
avg_temp=sum_temp/samples;


sum_temp=0;  
  
  for (int j=0; j<samples; j++){
    sum_hum += humidity[j];
    }  
avg_hum=sum_hum/samples;  


sum_hum=0;  
  }


void heater_control(){
  if (avg_temp<25)digitalWrite(relay_pin,HIGH);
  else digitalWrite(relay_pin,LOW);
}



void Display(){

get_temp_and_hum();

lcd.setCursor(0,0);
lcd.print("Temperature=");
lcd.print(avg_temp);
lcd.write(byte(0));
lcd.print("C");

lcd.setCursor(0,1);
lcd.print("Humidity = ");
lcd.print(avg_hum);   
lcd.print("%"); 
heater_control();  
  }

void loop(){
Display();
}
