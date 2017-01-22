int d0 = 0;
int d1 = 1;
int d2 = 2;
int d3 = 3;
int d4 = 4;
int d5 = 5;
int d6 = 6;
int d7 = 7;

int rs = 8;
int cs = 9;
int rd = 10;
int wr = 11;
int a0 = 12;

int led = 13;

void setup() {
  Serial.begin(9600);
  
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);

  pinMode(rs, OUTPUT);
  pinMode(cs, OUTPUT);
  pinMode(rd, OUTPUT);
  pinMode(wr, OUTPUT);
  pinMode(a0, OUTPUT);
  
  digitalWrite(rs, HIGH);
  digitalWrite(cs, LOW);
  digitalWrite(rd, HIGH);
  digitalWrite(wr, LOW);
  digitalWrite(a0, LOW);

  writeData(0x0);

  sendReset();
}

void sendReset() {
  digitalWrite(rs, LOW);
  delay(1);
  digitalWrite(rs, HIGH);
}

void loop() {
  delay(2500);
  basicTone();
  delay(3000);
  oplWrite(0xB0, B010100);
  delay(2500);
}

void oplWrite(byte address, byte val) {
  writeRegister(address);
  
  for(int i = 0; i < 100; i++) {
    __asm("nop\n");
  }
  
  writeValue(val);

  for(int i = 0; i < 500; i++) {
    __asm("nop\n");
  }
}

void writeRegister(byte address) {
  digitalWrite(a0, LOW);
  
  // write to data pins
  writeData(address);

  // signal to select register based on data pins
  digitalWrite(wr, LOW);
  digitalWrite(wr, HIGH);
}

void writeValue(byte data) {
  digitalWrite(a0, HIGH);
  
  // write to data pins
  writeData(data);

  // signal to write value to selected register
  digitalWrite(wr, LOW);
  digitalWrite(wr, HIGH);
}

void writeData(byte data) {
  pinMode(d0, OUTPUT);
  pinMode(d1, OUTPUT);
  pinMode(d2, OUTPUT);
  pinMode(d3, OUTPUT);
  pinMode(d4, OUTPUT);
  pinMode(d5, OUTPUT);
  pinMode(d6, OUTPUT);
  pinMode(d7, OUTPUT);
  
  digitalWrite(d0, data & 1);
  digitalWrite(d1, (data >> 1) & 1);
  digitalWrite(d2, (data >> 2) & 1);
  digitalWrite(d3, (data >> 3) & 1);
  digitalWrite(d4, (data >> 4) & 1);
  digitalWrite(d5, (data >> 5) & 1);
  digitalWrite(d6, (data >> 6) & 1);
  digitalWrite(d7, (data >> 7) & 1);
}

byte readData() {
  pinMode(d0, INPUT);
  pinMode(d1, INPUT);
  pinMode(d2, INPUT);
  pinMode(d3, INPUT);
  pinMode(d4, INPUT);
  pinMode(d5, INPUT);
  pinMode(d6, INPUT);
  pinMode(d7, INPUT);

  byte val = digitalRead(d0);
  val = val & (digitalRead(d1) << 1);
  val = val & (digitalRead(d2) << 2);
  val = val & (digitalRead(d3) << 3);
  val = val & (digitalRead(d4) << 4);
  val = val & (digitalRead(d5) << 5);
  val = val & (digitalRead(d6) << 6);
  val = val & (digitalRead(d7) << 7);
  return val;
}


void basicTone() {
  oplWrite(0x20, 0x81);
  oplWrite(0x23, 0x83);
  
  oplWrite(0x40, B00000000);
  oplWrite(0x43, B00000000);

  oplWrite(0x60, 0x20);
  oplWrite(0x63, 0x20);
  
  oplWrite(0x80, 0xF2);
  oplWrite(0x83, 0xF2);
  
  oplWrite(0xA0, 0x32);
  oplWrite(0xA3, 0x32);

  oplWrite(0xC0, 0x01);
  oplWrite(0xC3, 0x01);

  oplWrite(0xBD, 0x80);

  oplWrite(0xB0, B110100);
}

