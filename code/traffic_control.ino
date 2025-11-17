// ================== SMART TRAFFIC LIGHT SYSTEM (5s / 10s / 15s + PEDESTRIAN MODE) ==================

// ---- Traffic lights ----
const int A_R = 13,  A_Y = 12,  A_G = 11;   // Road A
const int B_R = 2,   B_Y = 3,   B_G = 4;    // Road B

// ---- IR sensors ----
const int Afar  = 10;
const int Anear = 9;
const int Bfar  = 6;
const int Bnear = 5;

// ---- Pedestrian buttons ----
const int PedA = 7;
const int PedB = 8;

// ---- Timings (milliseconds) ----
unsigned long baseTime   = 5000;   // 5 s (no traffic)
unsigned long mediumTime = 10000;  // 10 s (near only)
unsigned long highTime   = 15000;  // 15 s (far + near)
unsigned long yellowTime = 2000;   // 2 s yellow
unsigned long allRedGap  = 1000;   // 1 s all-red
unsigned long walkTime   = 5000;   // 5 s pedestrian crossing

// -------------------------------------------------------------------------
void setup() {
  // Lights
  pinMode(A_R, OUTPUT); pinMode(A_Y, OUTPUT); pinMode(A_G, OUTPUT);
  pinMode(B_R, OUTPUT); pinMode(B_Y, OUTPUT); pinMode(B_G, OUTPUT);

  // Sensors
  pinMode(Afar, INPUT);
  pinMode(Anear, INPUT);
  pinMode(Bfar, INPUT);
  pinMode(Bnear, INPUT);

  // Pedestrian buttons
  pinMode(PedA, INPUT_PULLUP);
  pinMode(PedB, INPUT_PULLUP);

  Serial.begin(9600);
  allRed();
}

bool detected(int pin) { return digitalRead(pin) == LOW; } // LOW = vehicle detected
bool pedPressed() { return (digitalRead(PedA) == LOW || digitalRead(PedB) == LOW); }

// -------------------------------------------------------------------------
void loop() {
  if (pedPressed()) activatePedestrianMode();

  // Calculate density levels for A and B
  int densA = getDensityLevel(Anear, Afar);
  int densB = getDensityLevel(Bnear, Bfar);

  Serial.print("Density A Level: "); Serial.print(densA);
  Serial.print(" | Density B Level: "); Serial.println(densB);

  unsigned long timeA = getGreenTime(densA);
  unsigned long timeB = getGreenTime(densB);

  // If equal, both get same time
  if (densA == densB) {
    runTrafficCycle(timeA, timeB);
  } else if (densA > densB) {
    runTrafficCycle(timeA, timeB);
  } else {
    runTrafficCycle(timeA, timeB);
  }
}

// ================== Density Logic ==================
int getDensityLevel(int nearPin, int farPin) {
  bool near = detected(nearPin);
  bool far  = detected(farPin);

  if (!near && !far) return 0;     // no traffic
  else if (near && !far) return 1; // near only
  else return 2;                   // near + far
}

unsigned long getGreenTime(int level) {
  if (level == 0) return baseTime;
  else if (level == 1) return mediumTime;
  else return highTime;
}

// ================== Traffic sequence ==================
void runTrafficCycle(unsigned long timeA, unsigned long timeB) {
  // ---- A green, B red ----
  setA(false, false, true);
  setB(true,  false, false);
  Serial.print("A → GREEN ("); Serial.print(timeA / 1000); Serial.println("s) | B → RED");
  waitWithPedCheck(timeA);

  // A yellow
  setA(false, true, false);
  delay(yellowTime);

  allRed(); delay(allRedGap);

  // ---- B green, A red ----
  setA(true,  false, false);
  setB(false, false, true);
  Serial.print("B → GREEN ("); Serial.print(timeB / 1000); Serial.println("s) | A → RED");
  waitWithPedCheck(timeB);

  // B yellow
  setB(false, true, false);
  delay(yellowTime);

  allRed(); delay(allRedGap);
}

// ================== Pedestrian Mode ==================
void activatePedestrianMode() {
  Serial.println("🚶 PEDESTRIAN MODE ACTIVE — All RED for 5s");
  allRed();
  delay(walkTime);
  Serial.println("Pedestrian crossing done — resuming traffic");

  while (digitalRead(PedA) == LOW || digitalRead(PedB) == LOW);
  delay(300);
}

void waitWithPedCheck(unsigned long duration) {
  unsigned long start = millis();
  while (millis() - start < duration) {
    if (pedPressed()) {
      activatePedestrianMode();
      break;
    }
    delay(50);
  }
}

// ================== Helper functions ==================
void setA(bool R, bool Y, bool G) {
  digitalWrite(A_R, R);
  digitalWrite(A_Y, Y);
  digitalWrite(A_G, G);
}
void setB(bool R, bool Y, bool G) {
  digitalWrite(B_R, R);
  digitalWrite(B_Y, Y);
  digitalWrite(B_G, G);
}
void allRed() {
  setA(true, false, false);
  setB(true, false, false);
} the two traffic lights are connected at d13,d12,d11 and d2,d3,d4
the ir sensors are connected to d5,d6,d9,d10 for output 

ir sensor ki 3 wires hai GND , VCC and OUTPUT toh output arduino digital pin ko jati hai jaise d9 aur gnd-gnd , vcc-5v ko jati hai

traffic light mai 4 cables hai gnd,rer,yellow,green toh gnd goes to gnd , the colors goes to the digital pins of arduino like D11,d12,d13

pedestrian ka button is connected to Gnd and d7,d8 as there are two of them breadboard bas wo connection easily krne mein madat krta hai and sab components ko 5v aur gnd deta hai 

like breadboard ke gnd ko sab components connected hai and then wo arduino ke gnd ko jaate hai 

similar for 5v
