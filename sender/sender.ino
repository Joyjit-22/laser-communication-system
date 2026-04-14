int laserPin = 8;

int bitTime = 500;
int resetTime = 100;

bool readyToSend = false;

void sendBit(char bit) {
  if (bit == '1') {
    digitalWrite(laserPin, HIGH);
    delay(bitTime - resetTime);
  } else {
    digitalWrite(laserPin, LOW);
    delay(bitTime - resetTime);
  }

  digitalWrite(laserPin, LOW);
  delay(resetTime);
}

// send 8-bit binary string
void sendByte(String byteStr) {
  for (int i = 0; i < 8; i++) {
    sendBit(byteStr[i]);
  }
}

// convert char → binary
String charToBinary(char c) {
  String bin = "";

  for (int i = 7; i >= 0; i--) {
    if (c & (1 << i)) bin += '1';
    else bin += '0';
  }

  return bin;
}

void sendPacket(String data) {

  sendByte("10101010"); // preamble
  sendByte("11110000"); // start

  sendByte(charToBinary(data.length()));

  for (int i = 0; i < data.length(); i++) {
    sendByte(charToBinary(data[i]));
  }

  sendByte("00001111"); // end
}

void setup() {
  pinMode(laserPin, OUTPUT);
  digitalWrite(laserPin, LOW);

  Serial.begin(9600);
  Serial.println("\nSender Ready");

  Serial.println("Type 'lon' to turn laser ON");
  Serial.println("Type 'loff' to start transmission mode");

  // Setup control loop
  while (!readyToSend) {
    if (Serial.available()) {
      String cmd = Serial.readStringUntil('\n');
      cmd.trim();

      if (cmd == "lon") {
        digitalWrite(laserPin, HIGH);
        Serial.println("🔴 Laser ON alignment mode");
      } 
      else if (cmd == "loff") {
        digitalWrite(laserPin, LOW);
        readyToSend = true;
        Serial.println("🟢 Transmission mode started");
        Serial.println("Enter text:");
      } 
      else {
        Serial.println("❌ Unknown command use 'lon' or 'loff' ");
      }
    }
  }
}

void loop() {

  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');

    Serial.print("Sending: ");
    Serial.println(input);

    sendPacket(input);

    delay(2000);
  }
}