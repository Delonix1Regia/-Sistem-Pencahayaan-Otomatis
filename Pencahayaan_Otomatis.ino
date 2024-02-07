#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27,16,2); //deklarasi lcd
const int ledPin = 10;            //deklarasi led di pin 10
const int buzzerPin = 9;          //deklarasi buzzer di pin 9
const int ldrPin = A0;            //deklarasi ldr di pin A0
const int pirPin = 8;             //deklarasi pir di pin 8


int statusLdr = 0;         //deklarasi variabel value ldr
int statusPir = 0;         //deklarasi variabel value pir


void setup() {
  lcd.init();                   //inisialisasi tampilan lcd
  lcd.backlight();              //menyalakan lampu latar lcd


  Serial.begin(9600);           //menentukan kecepatan mengirim dan menerima data 
melalui port serial


  pinMode(ledPin, OUTPUT);      //mengkonfigurasi led untuk menjadi output
  pinMode(buzzerPin, OUTPUT);   //mengkonfigurasi buzzer untuk menjadi output
  pinMode(ldrPin, INPUT);       //mengkonfigurasi ldr untuk menjadi input
  pinMode(pirPin, INPUT);       //mengkonfigurasi pir untuk menjadi input
  digitalWrite(ledPin, HIGH);
}


void loop() {
  statusLdr = analogRead(ldrPin);         //membaca sinyal analog dari ldr pin


  if(statusLdr >= 400){                   //pengkondisian jika ruangan gelap
     
      gelap();                            //memanggil method gelap
      statusPir = digitalRead(pirPin);    //membaca sinyal digital dari pir pin
     
      if(statusPir == HIGH){              //pengkondisian jika pir menangkap 
 gerakan
        digitalWrite(buzzerPin, HIGH);    //membunyikan buzzer
        nyala();                          //memanggil method nyala
      }


  } else {                                //pengkondisian jika ruangan terang
    terang();                             //memanggil method terang
    delay(2000);
  }
}


void gelap(){                             //method bernama gelap
  lcd.clear();                            //menghapus semua teks yang ada pada 
 lcd
  lcd.setCursor(0, 0);                    //mengarahkan lcd ke kolom 0 baris 0
  lcd.print("Ruangan Gelap");             //menampilkan teks di lcd
}


void terang(){                            //method bernama terang
  lcd.clear();                            //menghapus semua teks yang ada pada 
 lcd
  lcd.setCursor(0, 0);                    //mengarahkan lcd ke kolom 0 baris 0
  lcd.print("Ini Terang");                //menampilkan teks di lcd
  lcd.setCursor(0, 1);                    //mengarahkan lcd ke kolom 0 baris 1
  lcd.print("Tidak Perlu Lampu");         //menampilkan teks di lcd
}


void nyala(){                             //method bernama nyala
  digitalWrite(ledPin, LOW);             //menyalakan lampu  
  lcd.setCursor(0, 1);                    //mengarahkan lcd ke kolom 0 baris 1
  lcd.print("Lampu Dinyalakan");          //menampilkan teks di lcd
  delay(200);                             //memberi jeda
  digitalWrite(buzzerPin, LOW);           //mematikan buzzer
 
  while (statusPir == HIGH){              //pengkondisian akan terus berjalan 
 hingga tidak ada gerakan
    statusPir = digitalRead(pirPin);      //membaca sinyal digital dari pir
    delay(5000);                          //memberi jeda 5 detik
  }


  lcd.setCursor(0, 1);                    //mengarahkan lcd ke kolom 0 baris 1
  lcd.print("                ");          //menghapus teks di seluruh kolom pada 
 baris 1
  lcd.setCursor(0, 1);                    //mengarahkan lcd ke kolom 0 baris 1
  digitalWrite(ledPin, HIGH);		//mematikan lampu
  lcd.print("Lampu Dimatikan");           //menampilkan teks di lcd
}
