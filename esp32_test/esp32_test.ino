/*#include  <Arduino.h>
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  //pinMode(34, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(34)); //34
  delay(500);
}*/





int analogPin = 34;                 // Указываем порт OUT датчика ACS712
 
 
const int averageValue = 500;       // Переменная для хранения значения количества считывания циклов 
long int sensorValue = 0;           // Переменная для хранения значения с датчика
 
float voltage = 0;                  // Переменная для хранения значения напряжения
float current = 0;                  // Переменная для хранения значения тока
 
void setup() 
{
  Serial.begin(115200);               //  Открываем последовательную связь на скорости 9600
}
 
void loop() 
{
  for (int i = 0; i < averageValue; i++)    // Повторяем цикл
  {
    sensorValue += analogRead(analogPin);   // Считываем и записываем показания
    delay(2);                               // Пауза 2 мкс
  }
 
  sensorValue = sensorValue / averageValue; // Делим полученное значение 
  voltage = sensorValue * 5.0 / 1024.0;     // Расчет напряжения
  current = (voltage - 2.5) / 0.185;        // Расчет тока
 
  Serial.print("ADC Value: ");              // Отправка данных в последовательный порт
  Serial.print(sensorValue);
 
  Serial.print("   ADC Voltage: ");         // Отправка данных в последовательный порт
  Serial.print(voltage);                    // Отправка напряжения
  Serial.print("V");                        // Отправка данных в последовательный порт
 
  Serial.print("   Current: ");             // Отправка данных в последовательный порт
  Serial.print(current);                    // Отправка тока
  Serial.println("A");                      // Отправка данных в последовательный порт
}
