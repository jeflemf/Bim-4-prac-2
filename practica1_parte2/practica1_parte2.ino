/*
   Fundacion Kinal
   Centro educativo tecnico laboral Kinal
   Quinto perito
   Quinto electronica
   Codigo Tecnico: EB5AV 
   Curso: Taller de electronica digital y reparacion de computadoras I
   Proyecto: Parte 2 - Práctica 1
   Dev: Jefferson Gonzalez
   Fecha: 9 de julio. 
*/
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define IN1  9
#define IN2  6
#define IN3  5
#define IN4  3

#define ADC A0
#define sensor_obstaculos 2
#define shall 4

#define direccion_lcd 0x27
#define filas 2
#define columnas 16
#define tiempo  delay(1000);

LiquidCrystal_I2C lcdwey(direccion_lcd, columnas, filas); 

int contador = 0;
bool state_sensorob;   
bool state_sensorhall;
unsigned int valor_adc_pot;
unsigned char velocidad;

int paso [8][4] =
{
  {1, 0, 0, 0},
  {1, 1, 0, 0},
  {0, 1, 0, 0},
  {0, 1, 1, 0},
  {0, 0, 1, 0},
  {0, 0, 1, 1},
  {0, 0, 0, 1},
  {1, 0, 0, 1}
};
 
void setup()
{
  lcdwey.init();
  lcdwey.backlight();
  lcdwey.setCursor(0, 0);
  lcdwey.print("Contador de rev.");
  lcdwey.setCursor(0, 1);
  lcdwey.print("No. de rev: 0");

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ADC, INPUT);         
  pinMode(sensor_obstaculos, INPUT);
  pinMode(shall, INPUT); 
}

void loop()
{ 
  state_sensorob = digitalRead(sensor_obstaculos);
  state_sensorhall = digitalRead(shall); 

  if(state_sensorob == LOW){
  valor_adc_pot = analogRead(ADC);

  velocidad = map(valor_adc_pot,0,1023,0,10);    
  
    for (int i = 0; i < 8; i++)
    {
      digitalWrite(IN1, paso[i][0]);
      digitalWrite(IN2, paso[i][1]);
      digitalWrite(IN3, paso[i][2]);
      digitalWrite(IN4, paso[i][3]);
      delay(velocidad);
    }

    if(state_sensorhall == HIGH
    ){

      contador = contador+1;
      lcdwey.clear();
      lcdwey.setCursor(0, 0);
      lcdwey.print("Contador de rev.");
      lcdwey.setCursor(0, 1);
      lcdwey.print("No. de rev: ");
      lcdwey.print(contador);
      tiempo
    }
  }
}