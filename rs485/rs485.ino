#include <ModbusMaster.h>

ModbusMaster node;

#define DE_RE 4 // Пин для управления DE/RE

void preTransmission() { // устанавливает уровень HIGH на пине DE_RE, что включает режим передачи на модуле RS485. этот тот самый gpio-pin
  digitalWrite(DE_RE, HIGH);
}

void postTransmission() { // Эта функция будет вызываться после отправки данных. Она устанавливает уровень LOW на пине DE_RE, что включает режим приема на модуле RS485.
  digitalWrite(DE_RE, LOW);
}

void setup() {
  Serial.begin(115200);
  Serial1.begin(38400, SERIAL_8N1, 16, 17); // Настройка Serial1 для RS485
  //Пины 16 и 17 используются для RX и TX соответственно, что позволяет ESP32 общаться с модулем RS485.

  pinMode(DE_RE, OUTPUT);
  // Настройка пина DE_RE: Устанавливается режим работы пина DE_RE как выходной, чтобы управлять режимами передачи и приема.
  digitalWrite(DE_RE, LOW); // Начинаем в режиме приема

  node.begin(255, Serial1); // 1 - Адрес устройства EKEPC2-C
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}

void loop() {
  uint8_t result;
  uint16_t data[60];
  /*for(int i=0; i<160; i++){
  data[i]=0;
  }*/

  // Чтение регистров
  /* int start_registr = 110;
   int col = 1;
  result = node.readInputRegisters(start_registr, col); // Чтение 10 регистров начиная с адреса 0

  if (result == node.ku8MBSuccess) {
    for (int i = start_registr; i < (start_registr + col); i++) {
      data[i-start_registr] = node.getResponseBuffer(i); // Сохранение полученных данных
    }
    // Обработка полученных данных
  }

  for (int i = 0; i < col; i++) {
    Serial.println(data[i]);
  }*/
 result = node.readInputRegisters(100, 60);
if (result == node.ku8MBSuccess) {
    for (int i =0; i < 60; i++) {
      data[i] = node.getResponseBuffer(i+100); // Сохранение полученных данных
    }
    // Обработка полученных данных
  }

  Serial.println(data[55]);
  Serial.println(data[56]);
  Serial.println(data[57]);
  Serial.println(data[58]);
  Serial.println("");
  delay(1000); // Задержка перед следующим чтением
}



/* // не читает данные
#include <ModbusMaster.h>

ModbusMaster node;

#define DE_RE 4 // Пин для управления DE/RE

void preTransmission() { // устанавливает уровень HIGH на пине DE_RE, что включает режим передачи на модуле RS485.
  digitalWrite(DE_RE, LOW);
}

void postTransmission() { // Эта функция будет вызываться после отправки данных. Она устанавливает уровень LOW на пине DE_RE, что включает режим приема на модуле RS485.
  digitalWrite(DE_RE, HIGH);
}

void setup() {
  Serial.begin(115200);
  Serial1.begin(38400, SERIAL_8N1, 16, 17); // Настройка Serial1 для RS485

  pinMode(DE_RE, OUTPUT);
  digitalWrite(DE_RE, LOW); // Начинаем в режиме приема

  node.begin(1, Serial1); // 1 - Адрес устройства EKEPC2-C
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}

void loop() {
  uint8_t result;
  uint16_t data[10];

  // Чтение регистров
  result = node.readInputRegisters(0, 10); // Чтение 10 регистров начиная с адреса 0
  int registr = 10;

  if (result == node.ku8MBSuccess) {
    for (int i = 0; i < registr; i++) {
      data[i] = node.getResponseBuffer(i); // Сохранение полученных данных
    }
    // Обработка полученных данных
  }

  for (int i = 0; i < registr; i++) {
    Serial.println(data[i]);
  }
  delay(1000); // Задержка перед следующим чтением
}*/


/*
#define MAX485_RE_NEG  4 //D4 RS485 has a enable/disable pin to transmit or receive data. Arduino Digital Pin 2 = Rx/Tx 'Enable'; High to Transmit, Low to Receive
#define Slave_ID       1
#define RX_PIN      16 //RX2 
#define TX_PIN      17  //TX2 
// instantiate ModbusMaster object
ModbusMaster modbus;
void preTransmission()
{
  digitalWrite(MAX485_RE_NEG, HIGH); //Switch to transmit data
}
void postTransmission()
{
  digitalWrite(MAX485_RE_NEG, LOW); //Switch to receive data
}
void setup()
{
  pinMode(MAX485_RE_NEG, OUTPUT);
  // Init in receive mode
  digitalWrite(MAX485_RE_NEG, LOW);
  // Modbus communication runs at 9600 baud
  Serial.begin(9600, SERIAL_8N1);
  Serial2.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);
  modbus.begin(Slave_ID, Serial2);
  // Callbacks allow us to configure the RS485 transceiver correctly
  modbus.preTransmission(preTransmission);
  modbus.postTransmission(postTransmission);
}
long lastMillis = 0;
void loop() 
{
  long currentMillis = millis();
  if (currentMillis - lastMillis > 1000) 
  {
    uint8_t result = modbus.readInputRegisters(0x01, 2);
    
    if (getResultMsg(&amp;modbus, result)) 
    {
      Serial.println();
      double res_dbl = modbus.getResponseBuffer(0) / 10;
      String res = "Temperature: " + String(res_dbl) + " C\r\n";
      res_dbl = modbus.getResponseBuffer(1) / 10;
      res += "Humidity: " + String(res_dbl) + " %";
      Serial.println(res);
    }
    lastMillis = currentMillis;
  }
}
bool getResultMsg(ModbusMaster *node, uint8_t result) 
{
  String tmpstr2 = "\r\n";
  switch (result) 
  {
  case node->ku8MBSuccess:
    return true;
    break;
  case node->ku8MBIllegalFunction:
    tmpstr2 += "Illegal Function";
    break;
  case node->ku8MBIllegalDataAddress:
    tmpstr2 += "Illegal Data Address";
    break;
  case node->ku8MBIllegalDataValue:
    tmpstr2 += "Illegal Data Value";
    break;
  case node->ku8MBSlaveDeviceFailure:
    tmpstr2 += "Slave Device Failure";
    break;
  case node->ku8MBInvalidSlaveID:
    tmpstr2 += "Invalid Slave ID";
    break;
  case node->ku8MBInvalidFunction:
    tmpstr2 += "Invalid Function";
    break;
  case node->ku8MBResponseTimedOut:
    tmpstr2 += "Response Timed Out";
    break;
  case node->ku8MBInvalidCRC:
    tmpstr2 += "Invalid CRC";
    break;
  default:
    tmpstr2 += "Unknown error: " + String(result);
    break;
  }
  Serial.println(tmpstr2);
  return false;
}*/