#include <Servo.h>
long temps = 0;
int degx;
int degy;
Servo servox;
Servo servoy;
#include "TM1637.h"   //Inclusion de la librairie appropriée
#define CLK 2    // Assigne la pin 2 du microcontrôleur à la pin CLK de l'afficheur. On peut utiliser une autre pin digitale.
#define DIO 3    // Assigne la pin 3 du microcontrôleur à la pin DIO de l'afficheur. On peut utiliser une autre pin digitale.
TM1637 afficheur1(CLK,DIO);

int PositionDuChiffre=0; // variable utilisée pour identifier la position du chiffre sur l'afficheur
int Chiffre=0; // variable utilisée pour identifier le chiffre à afficher

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  degx = 90;  //définit l'orientation de départ du paneau solaire
  degy = 90;
  Serial.begin(9600);
  afficheur1.init();  // Initialise l'afficheur et efface tout
  afficheur1.set(2);  //Ajuste l'intensité à une valeur intermédiaire
  servox.attach(9);// attache le premier servo à  la pin 9
  servoy.attach(10);  //attache le deuxieme servo à  la pin 10
}

void loop() {
  // put your main code here, to run repeatedly:
  float lecture = analogRead(A0);   //calcul le voltage généré par le paneau solaire
  float volt = (5*(lecture))/1023;
  volt = volt*100;
  afficheur1.displayNumber(volt); // affiche le voltage sur l'afficheur 
  afficheur1.point(1) ;
//  Serial.print("volt: ");
//  Serial.println(volt);
  delay(250);
  afficheur1.clearDisplay() ; //efface la valeur sur l'afficheur
  
  Serial.print("R1: ");
  Serial.print(analogRead(A5));
  Serial.print("   ");
  Serial.print("R2: ");
  Serial.print(analogRead(A4));
  Serial.print("   ");
  Serial.print("R3: ");
  Serial.print(analogRead(A3));
  Serial.print("   ");
  Serial.print("R4: ");
  Serial.println(analogRead(A2));
  if(temps < millis()){                           //test si 1/2 seconde a passer
     if(abs(analogRead(A4)-analogRead(A5)) > 10){   //test si le paneau solaire recoit plus de lumière à droite
      if (analogRead(A5) < analogRead(A4)){
        degy = degy + 2;                          // ajoute deux degré vers la droite à la valeur du paneau solaire
        Serial.println("droite");
      }
    }
    if(abs(analogRead(A4)-analogRead(A5)) > 10){  //test si le paneau solaire recoit plus de lumière à gauche
      if (analogRead(A4) < analogRead(A5)){
        degy = degy - 2;                          // ajoute deux degré vers la gauche à la valeur du paneau solaire
        Serial.println("gauche");
      }
    }
    if(abs(analogRead(A3)-analogRead(A2)) > 10){    //test si le paneau solaire recoit plus de lumière ver le bas
      if (analogRead(A3) < analogRead(A2)){
        degx = degx + 2;                        // ajoute deux degré vers le bas à la valeur du paneau solaire
        Serial.println("bas");
      }
    }
     if(abs(analogRead(A2)-analogRead(A3)) > 10){   //test si le paneau solaire recoit plus de lumière ver le haut
      if (analogRead(A2) < analogRead(A3)){
        degx = degx - 2;                          // ajoute deux degré vers le haut à la valeur du paneau solaire
        Serial.println("haut");
      }
    }
    temps = millis() + 500;                 //enregistre le temps pour vérification du temps écouler
  }
  servox.write(degx);       //ajustement des paneaux solaires
  servoy.write(degy);
}
