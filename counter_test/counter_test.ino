void setup() {
  // put your setup code here, to run once:
  pinMode(23, INPUT);
  pinMode(22, OUTPUT);
  Serial.begin(115200);
}
const float china_counter = 0.0005; // потом можно константу для невы добавить
bool china_flag = true; // флаг
int counter=0; // счетчик 

void loop() {
  // put your main code here, to run repeatedly:
  int res = digitalRead(23);
  float power = 0; // потребленная энергия на данный момент
  if(res==1){
    digitalWrite(22, HIGH);
    delay(5000);
    digitalWrite(22, LOW);
    counter += 1;
    Serial.println(counter);
    if(china_flag == true){
      power = counter*china_counter;
    }
    Serial.print(power, 4); // вывод 4 знаков после запятой
    Serial.println(" kWh per hour");
  }
}
