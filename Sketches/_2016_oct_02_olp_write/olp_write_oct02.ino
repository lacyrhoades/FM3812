int AO = 3;
int RD = 4;
int CS = 5;

int d0 = 6;
int d1 = 7;
int d2 = 8;
int d3 = 9;
int d4 = 10;
int d5 = 11;
int d6 = 12;
int d7 = 13;

void delay() {
  delay(100);
}

void olp_wr(int addr, int val) {
  Serial.println("Write");
  Serial.println(addr);
  
  digitalWrite(RD, LOW);
  digitalWrite(AO, LOW);
  digitalWrite(CS, LOW);
  delay();
  digitalWrite(CS, HIGH);
  delay();
  digitalWrite(CS, LOW);
  delay();

  digitalWrite(d0, HIGH && (addr & B00000001));
  digitalWrite(d1, HIGH && (addr & B00000010));
  digitalWrite(d2, HIGH && (addr & B00000100));
  digitalWrite(d3, HIGH && (addr & B00001000));
  digitalWrite(d4, HIGH && (addr & B00010000));
  digitalWrite(d5, HIGH && (addr & B00100000));
  digitalWrite(d6, HIGH && (addr & B01000000));
  digitalWrite(d7, HIGH && (addr & B10000000));

  delay();
  digitalWrite(RD, HIGH);
  delay();
  digitalWrite(RD, LOW);
  delay();
  
  digitalWrite(d0, HIGH && (val & B00000001));
  digitalWrite(d1, HIGH && (val & B00000010));
  digitalWrite(d2, HIGH && (val & B00000100));
  digitalWrite(d3, HIGH && (val & B00001000));
  digitalWrite(d4, HIGH && (val & B00010000));
  digitalWrite(d5, HIGH && (val & B00100000));
  digitalWrite(d6, HIGH && (val & B01000000));
  digitalWrite(d7, HIGH && (val & B10000000));

  delay();
  digitalWrite(RD, HIGH);
  digitalWrite(A0, HIGH);
  delay();
  
  digitalWrite(RD, LOW);
  digitalWrite(AO, LOW);
  digitalWrite(CS, LOW);

  digitalWrite(d0, LOW);
  digitalWrite(d1, LOW);
  digitalWrite(d2, LOW);
  digitalWrite(d3, LOW);
  digitalWrite(d4, LOW);
  digitalWrite(d5, LOW);
  digitalWrite(d6, LOW);
  digitalWrite(d7, LOW);
}

void setup() {
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(3, OUTPUT);

  digitalWrite(CS, HIGH);
  delay();
  digitalWrite(CS, LOW);
  delay();

  olp_wr(0x20,0x01); // Set the modulator's multiple to 1
  olp_wr(0x40,0x10); // Set the modulator's level to about 40 dB
  olp_wr(0x60,0xF0); // Modulator attack: quick; decay: long
  olp_wr(0x80,0x77); // Modulator sustain: medium; release: medium
  olp_wr(0xA0,0x98); // Set voice frequency's LSB (it'll be a D#)
  olp_wr(0x23,0x01); // Set the carrier's multiple to 1
  olp_wr(0x43,0x00); // Set the carrier to maximum volume (about 47 dB)
  olp_wr(0x63,0xF0); // Carrier attack: quick; decay: long
  olp_wr(0x83,0x77); // Carrier sustain: medium; release: medium
  olp_wr(0xB0, 0x31); // Turn the voice on; set the octave and freq MSB
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("Running");

  while (true) {
    // stop output
  }
}
