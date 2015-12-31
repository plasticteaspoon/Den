//conflict resolved
#define DEN_PIN   6
#define BED_PIN   8

void setup() {
    pinMode(BED_PIN, OUTPUT);
    pinMode(DEN_PIN, OUTPUT);
    digitalWrite(BED_PIN, LOW);
    digitalWrite(DEN_PIN, LOW);
    setupRFID(); 
    setupNet();
}

void loop() {
    loopRFID();
    loopNet();
}
