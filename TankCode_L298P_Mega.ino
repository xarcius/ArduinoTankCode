/*
 Name:    TankCode_L298P_Mega.ino
 Created: 1/25/2017 1:00:35 PM
 Author:  nick-
*/

char data;
int vel_max = 255;

//motore 1
int e1 = 3;//pin per la velocità
int m1 = 12;//pin PWN per il segnale digitale


//idem
//motore 2
int e2 = 11;
int m2 = 13;

//funzioni
void su();
void giu();
void sinistra();
void destra();
void fermo();

// the setup function runs once when you press reset or power the board
void setup() {
  Serial3.begin(9600);//inizializzo la tramissione seriale

  //inizializzo i pin PWM
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
}

// the loop function runs over and over again until power down or reset
void loop() {
  
  if (Serial3.available()) {//se la trasmissione seriale è abilitata
    data = Serial3.read();//leggi l'informazione trasferita
    Serial3.println(data);//stampala nel monitor seriale

    switch (data)//instrada i vari casi
    {
    case 'F':
      su();
      break;
    case 'B':
      giu();
      break;
    case 'S':
      fermo();
      break;
    case 'L':
      sinistra();
      break;
    case 'R':
      destra();
      break;
    }
  }
}


//M1 +-
//M2 -+

void su() {
  //in base a come sono collegati i fili +/-
  digitalWrite(m1, HIGH);
  digitalWrite(m2, LOW);
  //imposta la velocità di 255 (velocità massima nei motori dc)
  analogWrite(e1, vel_max);
  analogWrite(e2, vel_max);
}

void giu() {
  digitalWrite(m1, LOW);
  digitalWrite(m2, HIGH);
  analogWrite(e1, vel_max);
  analogWrite(e2, vel_max);
}

void fermo() {
  analogWrite(e1, 0);
  analogWrite(e2, 0);
}

void sinistra() {
  digitalWrite(m1, HIGH);
  analogWrite(e1, vel_max);
  analogWrite(e2, 0);//ferma il motore 2
}

void destra() {
  digitalWrite(m2, LOW);
  analogWrite(e2, vel_max);
  analogWrite(e1, 0);//ferma il motore 1
}
