int ldrDO = 2;

String shiftReg = "00000000";

int bitTime = 500;

// toggle debug mode
bool DEBUG = false;

void setup() {
  Serial.begin(9600);
  Serial.println("\nReceiver Ready");
  pinMode(ldrDO, INPUT);
}

// read bit (mid sampling)
char readBit() {
  delay(bitTime / 2);
  int state = digitalRead(ldrDO);
  delay(bitTime / 2);

  if (state == LOW) return '1';
  else return '0';
}

void updateShiftRegister(char bit) {
  shiftReg = shiftReg.substring(1) + bit;

  if (DEBUG) {
    Serial.print("ShiftReg: ");
    Serial.println(shiftReg);
  }
}

String readByte(String label) {
  String byteStr = "";

  if (DEBUG) Serial.print(label + ": ");

  for (int i = 0; i < 8; i++) {
    char bit = readBit();
    byteStr += bit;

    if (DEBUG) Serial.print(bit);
  }

  if (DEBUG) Serial.println();

  return byteStr;
}

int binaryToDecimal(String bin) {
  return strtol(bin.c_str(), NULL, 2);
}

char binaryToChar(String bin) {
  return (char)binaryToDecimal(bin);
}

void loop() {
  char bit = readBit();
  updateShiftRegister(bit);

  if (shiftReg == "10101010") {

    Serial.println("\nPACKET RECEIVING");

    // ---- START ----
    String start = readByte("Start");
    if (start != "11110000") {
      Serial.println("❌ Invalid Start");
      shiftReg = "00000000";
      return;
    }

    // ---- LENGTH ----
    int length = binaryToDecimal(readByte("Length"));

    // STORE MESSAGE HERE
    String message = "";

    // ---- DATA ----
    for (int i = 0; i < length; i++) {
      String data = readByte("Data");
      message += binaryToChar(data);
    }

    // ---- END ----
    String endByte = readByte("End");

    if (endByte == "00001111") {
      Serial.println("✅ Valid Packet");

      // FINAL CLEAN OUTPUT
      Serial.print("Message: ");
      Serial.println(message);

    } else {
      Serial.println("❌ End Error");
    }

    shiftReg = "00000000";
    Serial.println("----------------------");
  }
}