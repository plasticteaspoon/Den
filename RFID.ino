/* Jessica Drury  09/07/15
Outcome:
to be able use a keycard to turn on my bedside light.
*/
#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN		9		
#define SS_PIN		7		

MFRC522 mfrc522(SS_PIN, RST_PIN);


void setupRFID(){
    Serial.begin(9600);
    SPI.begin();
    mfrc522.PCD_Init();	
    Serial.println("Ready");
}
void loopRFID() {   
    
    if ( ! mfrc522.PICC_IsNewCardPresent()) {
        return;
    }
    if ( ! mfrc522.PICC_ReadCardSerial()) {
	      return;
    }
    /*Serial.print("Size = ");
    Serial.println(mfrc522.uid.size);
    Serial.println(mfrc522.uid.uidByte[0], HEX);
    for(int n = 0; n < mfrc522.uid.size; n++) {
    
        Serial.print(mfrc522.uid.uidByte[n]);
        Serial.print(" ");   
    }
    Serial.println();
    */
    
    if(mfrc522.uid.uidByte[0] == 13 &&
       mfrc522.uid.uidByte[1] == 0 &&
       mfrc522.uid.uidByte[2] == 178 &&
       mfrc522.uid.uidByte[3] == 218){
        if(digitalRead(BED_PIN) == LOW) {
            digitalWrite(BED_PIN, HIGH);
        }else {
            digitalWrite(BED_PIN, LOW);
        }
        delay(1000);
    }
             
    if(mfrc522.uid.uidByte[0] == 224 &&
       mfrc522.uid.uidByte[1] == 40&&
       mfrc522.uid.uidByte[2] == 177 &&
       mfrc522.uid.uidByte[3] == 31){
        if(digitalRead(DEN_PIN) == LOW) {
            digitalWrite(DEN_PIN, HIGH);      
        }else {
            digitalWrite(DEN_PIN, LOW);
        }
        delay(1000);
    }  
}
