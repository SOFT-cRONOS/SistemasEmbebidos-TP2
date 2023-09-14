#Grupo 9
#include <LiquidCrystal.h>  //Carrega a biblioteca Pantalla
#include <DHT.h> //Carrega a biblioteca DHT
#define DHTPIN 13     // Pin donde está conectado el sensor

// trabajo de sistemas embebidos
#define DHTTYPE DHT22   // Sensor DHT22

DHT dht(DHTPIN, DHTTYPE);

/* Display         rs, e ,d4,d5 ,d6,d7*/    
LiquidCrystal lcd(10, 8, 5, 4, 3, 2);
#define COLS 16 // Columnas del LCD
#define ROWS 2 // Filas del LCD

//array de lectura
float lectura[3] = {100,0,0};

void setup() {
  Serial.begin(9600);
  dht.begin();
  //leds testigos
  pinMode(12, OUTPUT); //verde
  pinMode(11, OUTPUT); //rojo
  //motores
  pinMode(7, OUTPUT); //bomba
  pinMode(6, OUTPUT); //ventilador
  // filas y las columnas del LCD
  lcd.begin(COLS, ROWS);
  print_bienvenida("Iniciando...");
}

float lectura_dht() {
  lectura[0] = dht.readHumidity(); //Lee la Humedad
  lectura[1] = dht.readTemperature(); //Lee la temperatura en grados Celsius
}


void print_bienvenida(String texto) {
  // Limpiamos la pantalla
  lcd.clear();
  // Situamos el cursor en la columna 0 fila 0
  lcd.setCursor(0,0);
  //Escribe en pantalla
  lcd.print(texto);
}

//Void para escribir los datos de humedad y temp
void print_lcd() {
  lcd.clear();
  lcd.setCursor(0,0);  
  lcd.print("Humedad:");
  lcd.setCursor(9,0);
  lcd.print(lectura[0]);
  lcd.setCursor(14,0);
  lcd.print("%");
  lcd.setCursor(0,1);
  lcd.print("Temp.:");
  lcd.setCursor(8,1);
  lcd.print(lectura[1]);
  lcd.setCursor(13,1);
  lcd.print("*C");
}

float tiempoUltimaLectura=0; //Para guardar el tiempo de la última lectura

void loop() {
  //---------Lectura del Sensor--------------------------
  //toma la lectura cada 2 segundos
  if(millis()-tiempoUltimaLectura>2000){
    lectura_dht();
    print_lcd();             
  }
  //----Fin de la lectura---------------------------


  //---------Chequeo y arranque de motores--------
  if(lectura[1] >= 25) {
    digitalWrite(7, HIGH);
    delay(100); 
  } else {
    digitalWrite(7, LOW);
    delay(100);
  }
if (lectura[0]<=40){
    digitalWrite(6, HIGH);
    digitalWrite(12, HIGH); 
    digitalWrite(11, LOW);
    delay(100);
  } else{
    digitalWrite(6, LOW);
    digitalWrite(12, LOW); 
    digitalWrite(11, HIGH);
    delay(100);
  }
  //----Fin chequeo----------------
}
