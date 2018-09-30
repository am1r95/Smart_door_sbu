/*
PINOUT:
RC522 MODULE    Uno/Nano     MEGA
SDA             D10          D9
SCK             D13          D52
MOSI            D11          D51
MISO            D12          D50
IRQ             N/A          N/A
GND             GND          GND
RST             D9           D8
3.3V            3.3V         3.3V
*/
/* Include the U8glib library */
#include "U8glib.h"
#include <SPI.h>
#include <SD.h>
#include <RFID.h>
#include <SoftwareSerial.h>  
/* Define the SPI Chip Select pin */
#define CS_PIN 10
#define SDA_DIO 10
#define RESET_DIO 9
#define CS_SD 4
/* Create an instance of the library for the 12864 LCD in SPI mode */
File myFile;
char r[3];  
bool rfid_flag;
String x;
char command;
byte key[5];
/* Create an instance of the RFID library */
RFID RC522(SDA_DIO, RESET_DIO); 
U8GLIB_ST7920_128X64_1X u8g(CS_PIN);

void setup()
{ 
  pinMode(7,OUTPUT); 
  RC522.init();  /* Initialise the RFID reader */
  SPI.begin();
  Serial.begin(9600);
  while (!Serial) {
    ; }

      delay(100);
    Serial.print("Initializing SD card...");
  if (!SD.begin(CS_SD)) {
    Serial.println("initialization failed!");
   // while (1);
  }
  Serial.println("initialization done.");
  // open the file. note that only one file can be open at a time,
  // so you have to close this one before opening another.
  //  myFile = SD.open("test.txt", FILE_WRITE);

}

void loop()
{

  /* Has a card been detected? */
  if (RC522.isCard())
  { 
    /* If so then get its serial number */
    RC522.readCardSerial();
    Serial.println("\nCard detected:");
   
    //x = (String)RC522.serNum[0]+(String)RC522.serNum[1]+(String)RC522.serNum[2]+(String)RC522.serNum[3]+(String)RC522.serNum[4];
     Serial.println(x);
    for(int i=0;i<5;i++)
         {      
          key[i]=RC522.serNum[i];
   //Serial.println(RC522.serNum[i]);
   // Serial.print(RC522.serNum[i],DEC);
    Serial.print(RC522.serNum[i],HEX); //to print card detail in Hexa Decimal format
          } 
          rfid_flag=1;
                      
  }
  /*
if( rfid_flag==1){
    myFile = SD.open("RFID.txt");
  if (myFile) {
    Serial.println("\nRFID.txt:");

    // read from the file until there's nothing else in it:
    while (myFile.available()) {
     int c=0;
         for(int i=0;i<5;i++)
         {  
          byte t=myFile.read();
          if(t=='\n')
           break;
      else if(t==key[i])
            c++;
         }
         Serial.println(c);
      if(c==5)
        Serial.println("Access Granted");
         break;
         
     //    Serial.print(String(int(myFile.read())));
          //Serial.println(x);
      
      //Serial.print(myFile.read());
    }
   // Serial.println("Access denied");
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening RFID.txt");
  }
  rfid_flag=0;
} 
*/
if( rfid_flag==1){
 myFile = SD.open("RFID2.txt", FILE_WRITE);

  // if the file opened okay, write to it:
  if (myFile) {
    Serial.print("Writing to RFID.txt...");
   
     for(int i=0;i<5;i++)
           
         myFile.println(key[i]);
    // close the file:
    myFile.close();
    Serial.println("done.");
  }
  else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
  }
  rfid_flag=0;
}
  
   u8g.firstPage();  
    do 
  {
    /* Set the font */
    u8g.setFont(u8g_font_unifont);   
    /* Display some text */
    u8g.drawStr( 32, 22, "Access");
    u8g.drawStr( 32, 42, "Denied");   
    /* Draw a simple border */
   // u8g.drawFrame(5,5,117,54);
   // u8g.drawFrame(3,3,121,58);
   //delay(600);
  }
  while(u8g.nextPage());
  //delay(1000);
  
  /* Start of a picture loop */
  u8g.firstPage();  
  /* Keep looping until finished drawing screen */
  do 
  {
    /* Set the font */
    u8g.setFont(u8g_font_courB14);
    
    /* Display some text */
    u8g.drawStr( 4, 14, "GIOT");
    u8g.drawStr( 58, 50, "giot");
    
    /* Draw a simple border */
   // u8g.drawFrame(5,5,117,54);
   // u8g.drawFrame(3,3,121,58);
  
  }
  while(u8g.nextPage());
 
        
 delay(1000);
}
