Program:
*/
#include <Servo.h> #include <SPI.h> #include <MFRC522.h> #include <Wire.h>
#include <LiquidCrystal_I2C.h> LiquidCrystal_I2C lcd(0x27, 16, 2);


Servo myservo;
Servo myservo2;	
#define RST_PIN layout above	9	// Configurable, see typical pin
#define SS_PIN layout above	10	// Configurable, see typical pin
#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000
 
MFRC522 mfrc522(SS_PIN, RST_PIN); // Create MFRC522
instance

Void setup() {
Serial.begin(9600);	// Initialize serial communications with the PC
While (!Serial);	// Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
SPI.begin();	// Init SPI bus Mfrc522.PCD_Init();		// Init MFRC522
Delay(4);	// Optional delay. Some board do need more time after init to be ready, see Readme
Mfrc522.PCD_DumpVersionToSerial();	// Show details of PCD – MFRC522 Card Reader details
Serial.println(F(“Scan PICC to see UID, SAK, type, and data blocks…”));
Lcd.init(); Lcd.backlight(); pinMode(3,INPUT);//ir1 pinMode(4,INPUT);//ir2
 
pinMode(7,OUTPUT); pinMode(8,OUTPUT); lcd.setCursor(0,0);
lcd.println(“MOVABLE ROAD”);
lcd.setCursor(0,1); lcd.print(“DIVIDER”); delay(2000); lcd.clear();

myservo2.attach(2);
myservo.attach(6);//attaches the servo on pin 9 to the servo object
myservo.write(0); myservo2.write(0); delay(500); myservo.write(180); myservo2.write(180); delay(500); myservo.write(90); myservo2.write(90);
 
Serial.println(“Put your card to the reader…”);
Serial.println();
}

Void loop() {
// Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
If ( ! mfrc522.PICC_IsNewCardPresent()) { Return;
}

// Select one of the cards
If ( ! mfrc522.PICC_ReadCardSerial()) { Return;
}

// Dump debug info about the card; PICC_HaltA() is automatically called
Mfrc522.PICC_DumpToSerial(&(mfrc522.uid)); Delay(1000);
 
Serial.println(); Serial.println();
Serial.print(“UID tag :”); String content= “”;
Byte letter;
For (byte I = 0; I < mfrc522.uid.size; i++)
{
Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? “ 0” : “ “);
Serial.print(mfrc522.uid.uidByte[i], HEX);
Content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? “ 0” : “ “));
Content.concat(String(mfrc522.uid.uidByte[i], HEX));
}
Serial.println();
Serial.print(“Message : “);
Content.toUpperCase();
If (content.substring(1) == “C9 E3 7C B2”) //change here the
UID of the card/cards that you want to give access
{
Serial.println(“Authorized access”);
 
Serial.println(); digitalWrite(8, LOW);
digitalWrite(7,HIGH);//GREEN LED chk();
lcd.setCursor(0,0);
lcd.print(“MOVE FORWARD”);
lcd.clear(); delay(1000);
lcd.print(“AUTO LOCKING IN “);
lcd.setCursor(0,1); lcd.println(“	5 SEC “); delay(5000);
digitalWrite(8,HIGH);//RED LED digitalWrite(7,LOW);//GREEN LED
}

Else	{
Serial.println(“ Access denied”);
digitalWrite(8, HIGH);
lcd.print(“ACCESS DENIED”);
 
delay(1000);
}
Lcd.clear();
}
Void chk()
{
Int a=digitalRead(3); Int b=digitalRead(4); Serial.print(“a=”); Serial.print(a);
Serial.print(“b=”);
Serial.print(b); If(a==0 && b==0)
{
Myservo.write(90); Myservo2.write(90); Lcd.print(“DON’T MOVE”); Delay(4000);

}
 
Else if(a==1&&b==0)
{
Myservo.write(0); Myservo2.write(0);
Lcd.print(“DIV MOVES LEFT”);
Delay(5000);
}
Else if(a==0&&b==1)
{
Myservo.write(180); Myservo2.write(180); Lcd.print(“MOVES RIGHT”);
Delay(5000);
}
Else if (a==1&&b==1)
{
Myservo.write(90); Myservo2.write(90);
Lcd.print(“DO NOT MOVE”);
Delay(5000);
 
}
Myservo.write(90); Myservo2.write(90);
}