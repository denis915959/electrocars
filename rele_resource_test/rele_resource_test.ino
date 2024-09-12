void setup() {
  // put your setup code here, to run once:
  pinMode(25, OUTPUT); //выход подопытного реле1
  pinMode(26, OUTPUT); //выход подопытного реле1

}

void loop() { // за сутки теста реле отработает 43000 срабатываний. Этого нам достаточно. Надо провести на 2 реле
  // put your main code here, to run repeatedly:
  digitalWrite(25, HIGH); // чтобы нагрузка на есп32 была равномерной в течение суток
  digitalWrite(26, LOW);  
  delay(1000);
  digitalWrite(25, LOW);
  digitalWrite(26, HIGH);
  delay(1000);
}
