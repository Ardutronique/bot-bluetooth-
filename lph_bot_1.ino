#include <SoftwareSerial.h>
#include <Wire.h>
#include <Servo.h>  


SoftwareSerial BTSerial(4,8);  // TXD = 10 , RXD = 11
// create servo object to control a servo 
Servo myservoG;
Servo myservoD;

int vitesseG = 91;
int vitesseD = 91;

void setup() {  
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println("Entrer une commande:"); // ecrire Entrer une commande
  BTSerial.begin(9600); 
  myservoG.attach(11);
  myservoD.attach(10);
 

}

void loop() {

 String message;
    // Boucle de lecture sur le BT
  
    while (BTSerial.available()){
      // Lecture du message envoyé par le BT
        
        message = BTSerial.readString();
      // Ecriture du message dans le serial usb
        Serial.println(message);
       
    }
    // Boucle de lecture sur le serial usb
 
    while (Serial.available()){
      // Lecture du message envoyé par le serial usb
     
      message = Serial.readString();
      // Ecriture du message dans le BT
     
      BTSerial.println(message);
    }
    // AVANCER 
   if(message == "a"){
      myservoG.write(180);     
      myservoD.write(0); 
      
    }
    // RECULER
    else if(message == "r"){
      myservoG.write(0);     
      myservoD.write(180);
    } 
    // STOP
    if (message == "s"){
      myservoG.write(89);     
      myservoD.write(91);
    }
    //ALLER À DROITE 
     if (message == "d"){
      myservoG.write(110);     
      myservoD.write(110);
    }
    //ALLER A GAUCHE 
    else if (message == "g"){
      myservoG.write(70);     
      myservoD.write(70);
    }

    // RESET LES MOTEUR 
     if (message == "RESET "){
      vitesseG = 91 ;
      vitesseD = 91 ;
    }
    // MODE CONTROLE DE VITESSE +
    if (message == "av"){
      vitesseG = vitesseG + 10 ;
      vitesseD = vitesseD -10;
      Serial.print("la vitesse du servo moteur gauche est égal à ");
      Serial.println(vitesseG);
      Serial.print("la vitesse du servo moteur droite est égal à ");
      Serial.println(vitesseD);
      myservoD.write(vitesseD);
      myservoG.write(vitesseG);
     }

     // MODE CONTROLE DE VITESSE -
     if (message == "rv"){
      vitesseG = vitesseG - 10 ;
      vitesseD = vitesseD + 10 ;
       Serial.print("la vitesse du servo moteur gauche est égal à ");
      Serial.println(vitesseG);
      Serial.print("la vitesse du servo moteur droite est égal à ");
      Serial.println(vitesseD);
      myservoD.write(vitesseD);
      myservoG.write(vitesseG);
     }

     //STOP
     if (message == "stop"){
      vitesseG = 91 ;
      vitesseD = 91 ;
      Serial.print("la vitesse du servo moteur gauche est égal à ");
      Serial.println(vitesseG);
      Serial.print("la vitesse du servo moteur droite est égal à ");
      Serial.println(vitesseD);
      myservoD.write(vitesseD);
      myservoG.write(vitesseG);
     }
     // CONTROLE DES VITESSE 
    else if (vitesseG>180){
      vitesseG = 180 ;
      vitesseD = 0 ;
      Serial.print("la vitesse du servo moteur gauche est reinitialisé à ");
      Serial.println(vitesseG);
      Serial.print("la vitesse du servo moteur droite est reinitialisé à ");
      Serial.println(vitesseD);
     }  
}

