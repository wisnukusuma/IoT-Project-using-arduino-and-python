#include "DHT.h"  //Memasukan Library DHT ke Program

#define DHTPIN 2  //menggunakan pin 2 untuk pemasangan sensornya
#define DHTTYPE DHT11 //memilih tipe DHT11, bisa diubah menjadi DHT22, DHT21


DHT dht(DHTPIN, DHTTYPE);  //setting pin yang dipilih dan tipe DHT

int blue = 0, red = 0, hasil;
String inString;
char masuk;


void setup() {
  Serial.begin(9600);  //komunikasi Serial dengan komputer
  dht.begin(); //Komunikasi DHT dengan Arduino
    
}

void loop() {

  float kelembaban = dht.readHumidity(); //menyimpan nilai Humidity pada variabel kelembaban
  float suhu = dht.readTemperature(); //menyimpan nilai Temperature pada variabel suhu

  inString="";
  Serial.print(kelembaban); //menampilkan nilai kelembaban
  Serial.print("_"); //menampilkan tulisan suhu
  Serial.println(suhu); //menampilkan nilai suhu
  while ((Serial.available() > 0) && ((masuk = Serial.read()) != '\n')){ //baca feedback dr thingspeak
      inString += masuk;
  }
  
  if (inString == "ggl")    //validasi feedback
  {
    Serial.print("Hasil = ");
    Serial.print(inString);
    Serial.println(" .Ga Sukses!");
  }
  else
  {
    hasil = inString.toInt();
     Serial.print("Hasil = ");
    Serial.print(inString);
    Serial.println(" .Sukses!");
  }
  
  delay(1000); //memberi jeda waktu baca selama 500 mili detik
}
