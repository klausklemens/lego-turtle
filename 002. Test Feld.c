//HI

#pragma config(Sensor, S1,     Touch,          sensorEV3_Touch, modeEV3Bump)
#pragma config(Sensor, S2,     RS,             sensorEV3_Color)
#pragma config(Sensor, S3,     LS,             sensorEV3_Color)
#pragma config(Sensor, S4,     Gyro,           sensorEV3_GenericI2C)
#pragma config(Motor,  motorA,          Lager,         tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorB,          RM,            tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          LM,            tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorD,          Greifer,       tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

byte gyroWert;
int aktiv = 0;
int links;                          //Lichtsensorwert links
int rechts;                         //Lichtsensorwert rechts
int RightColor;                     //Farbe Rechts
int LeftColor;                      //Farbe Links
int n;
int encoder1;
int encoder2;
float Tp = 50;                      //Standardgeschwindigkeit Motor
float errorx;
float counter;
float counter2;



//////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////-Funktionen-///////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////


void schwarzRechts(){               //beide schwarz, rechts zuerst
  motor[LM] = -50;
  motor[RM] = 0;
  waitUntil(getColorReflected(LS) > 40);
  motor[RM] = -50;
  motor[LM] = 0;
  waitUntil((getColorReflected(RS) + 2) > 40);
  motor[RM] = 50;
  motor[LM] = 0;
  waitUntil(((getColorReflected(RS) + 2) < 15));
  motor[RM] = 20;
  motor[LM] = 50;
  waitUntil((getColorReflected(RS) + 2) > 40);
  motor[LM] = 50;
  motor[RM] = 0;
  waitUntil((getColorReflected(LS) < 15));
  return;
}


void schwarzLinks(){          //beide schwarz, links zuerst
  motor[RM] = -50;
  waitUntil((getColorReflected(RS) + 2) > 50);
  motor[LM] = -50;
  motor[RM] = 0;
  waitUntil(getColorReflected(LS) > 50);
  motor[LM] = 50;
  motor[RM] = 0;
  waitUntil((getColorReflected(LS) < 15));
  motor[RM] = 50;
  motor[LM] = 20;
  waitUntil(getColorReflected(LS) > 50);
  motor[RM] = 50;
  motor[LM] = 0;
  waitUntil(((getColorReflected(RS) + 2) < 15));
  return;
}


void beideGruen(){            //beide gr�n
  motor[RM] = 50;
  motor[LM] = -50;
  waitUntil((getColorReflected(RS) + 2) >= 50);
  motor[RM] = 50;
  motor[LM] = -50;
  waitUntil((getColorReflected(RS) + 2) <= 15);
  errorx = 0;
  return;
}


void reset(){                 //Encoder zur�cksetzen (f�r Endfeld)
  resetMotorEncoder(LM);
  resetMotorEncoder(RM);
  motor[RM] = 0;
  motor[LM] = 0;
  delay(250);
  return;
}


void clock90(){
  reset();
  setMotorTarget(LM, -585, 50);
  setMotorTarget(RM, -585, -50);
  waitUntilMotorStop(RM);
  reset();
  return;
}


void counterclock90(){
  reset();
  setMotorTarget(LM, 585, 50);
  setMotorTarget(RM, 585, -50);
  waitUntilMotorStop(RM);
  reset();
  return;
}


void drehen180(){
  reset();
  setMotorTarget(LM, -1150, 50);
  setMotorTarget(RM, -1150, -50);
  waitUntilMotorStop(RM);
  reset();
  return;
}


void hochGanz(){
  reset();
  setMotorTarget(LM, -170, 10);
  setMotorTarget(RM, -170, 10);
  setMotorTarget(motorD, 0, 50);
  waitUntilMotorStop(motorD);
  resetMotorEncoder(motorA);
  resetMotorEncoder(motorD);
  delay(250);
  reset();
  return;
}


void runterTeils(){
  motor[motorD] = 50;
  waitUntil(getTouchValue(S1) ==  1);
  motor[motorD] = -50;
  waitUntil(getTouchValue(S1) == 0);
  motor[motorD] = 0;
  delay(250);
  reset();
  return;
}


void vorwaertsBisWand(){
  motor[RM] = 100;
  motor[LM] = 100;
  waitUntil(getTouchValue(S1) == 1);
}


void stopp(){
  motor[RM] = 0;
  motor[LM] = 0;
}


void rueckwaertsKurz(){
  motor[LM] = -100;
  motor[RM] = -100;
  delay(500);
  stopp();
}


void endfeld(){               //Feld mit Kugeln
  reset();
  runterTeils();
  vorwaertsBisWand();
  encoder1 = (getMotorEncoder(RM) + getMotorEncoder(LM))/2;
  stopp();
  reset();
  hochGanz();
  clock90();
  rueckwaertsKurz();
  runterTeils();
  vorwaertsBisWand();
  stopp();
  hochGanz();
  drehen180();
  rueckwaertsKurz();
  runterTeils();
  reset();
  vorwaertsBisWand();
  hochGanz();

  encoder2 = (getMotorEncoder(RM) + getMotorEncoder(LM))/2;
  reset();
  /////////////////////////////
  if(encoder1 < encoder2){
    n = 3;                      //quer
  }
  else if(encoder2 < encoder1){
    n = 5;                      //l�ngs
  }
  int u = (encoder1/n);
  /////////////////////////////
  counterclock90();
  rueckwaertsKurz();
  counterclock90();
  rueckwaertsKurz();
  runterTeils();
  vorwaertsBisWand();
  stopp();
  encoder2 = (getMotorEncoder(LM) + getMotorEncoder(RM))/2;
  hochGanz();
  setMotorTarget(RM, encoder2, -75);
  setMotorTarget(LM, encoder2, -75);
  waitUntilMotorStop(LM); waitUntilMotorStop(RM);
  clock90();
  setMotorTarget(RM, u, -100);
  setMotorTarget(LM, u, -100);
  waitUntilMotorStop(LM); waitUntilMotorStop(RM);
  rueckwaertsKurz();
  reset();
  int k = 0;
  ////////////////////////////
  while(true){
    while(getMotorEncoder(LM) < u){
      motor[LM] = 100;
      motor[RM] = 100;
      if((getColorReflected(RS) > 90) || (getColorReflected(LS) > 90)){
        motor[LM] = 0;
        motor[RM] = 0;
        delay(500);
        motor[RM] = -100;
        motor[LM] = -100;
        delay(500);
        reset();
        k = 1;
        break;
      }
      else if(getTouchValue(S1) == 1){
        motor[LM] = -100;
        motor[RM] = -100;
        waitUntil(getTouchValue(S1) == 0);
        reset();
        k = 1;
        break;
      }
    }
    counterclock90();
    rueckwaertsKurz();
    runterTeils();
    vorwaertsBisWand();
    stopp();
    encoder2 = (getMotorEncoder(LM) + getMotorEncoder(RM))/2;
    hochGanz();
    setMotorTarget(RM, encoder2, -100);
    setMotorTarget(LM, encoder2, -100);
    waitUntilMotorStop(LM); waitUntilMotorStop(RM);
    rueckwaertsKurz();
    clock90();
    setMotorTarget(RM, u, -100);
    setMotorTarget(LM, u, -100);
    waitUntilMotorStop(LM); waitUntilMotorStop(RM);
    rueckwaertsKurz();
    reset();
    u += (encoder1/n);
    if(k == 1){
      break;
    }
  }
  clock90();
  while(true){
    counterclock90();
    rueckwaertsKurz();
    motor[LM] = 100;
    motor[RM] = 100;
    waitUntil((getTouchValue(S1) == 1) || ((getColorReflected(RS) > 90) || (getColorReflected(LS) > 90)));
    motor[LM] = 0;
    motor[RM] = 0;
    if((getColorReflected(RS) < 15) || (getColorReflected(LS) < 15)){
      drehen180();
      motor[LM] = 0;
      motor[RM] = 0;
      motor[motorA] = 100;
      delay(1000000000000);
    }
    else if((getColorReflected(RS) > 90) || (getColorReflected(LS) > 90)){
      motor[LM] = 0;
      motor[RM] = 0;
      delay(250);
      motor[RM] = -100;
      motor[LM] = -100;
      delay(400);
      stopp();
    }
    else if(getTouchValue(S1) == 1){
      motor[LM] = 0;
      motor[RM] = 0;
      delay(250);
      motor[RM] = -100;
      motor[LM] = -100;
      delay(200);
      stopp();
    }
	}
}


void hindernis(){           //Hindernis
  motor[RM] = -50;
  motor[LM] = -50;
  delay(500);
  motor[RM] = -50;
  motor[LM] = 50;
  delay(1000);
  motor[RM] = 50;
  motor[LM] = 50;
  delay(1000);
  motor[RM] = 50;
  motor[LM] = 0;
  delay(1700);
  motor[RM] = 50;
  motor[LM] = 50;
  delay(500);
  motor[RM] = 50;
  motor[LM] = 0;
  delay(1700);
  motor[RM] = 50;
  motor[LM] = 50;
  waitUntil((getColorReflected(RS) + 2) < 20);
  motor[LM] = 50;
  motor[RM] = -50;
  waitUntil(getColorReflected(LS) < 20);
  return;
}


//////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////-Hauptprogramm-//////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////

task main(){
  runterTeils();
  hochGanz();


  aktiv = 1;
  float Kp = 5.5;
  float error;        //Abweichung vom Sollwert
  float lastError;    //letzter Fehler
  float turn;         //Drehwert
  float powerL;       //spezifische Geschwindigkeit Motor Links
  float powerR;       //spezifische Geschwindigkeit Motor Rechts
  float colorLinks;
  float colorRechts;

  //Fahren
  while(aktiv == 1){
    gyroWert = SensorValue[S4];
    displayCenteredBigTextLine(3, "GyroWert: %d", gyroWert);
    links = getColorReflected(LS);
    rechts = (getColorReflected(RS) + 2);
    error = rechts - links;  //Fehler berechnen - tats�chliche Abweichung vom offsetwert
    counter = 0;                      //counter zur�cksetzen
    counter2 = 0;                     //counter2 zur�cksetzen


    if((gyroWert > 8)){
      while(gyroWert > 8){
        gyroWert = SensorValue[S4];
        if(getColorReflected(LS) < 20){
          motor[RM] = 15;
          motor[LM] = 0;
          waitUntil(getColorReflected(RS) < 40);
        }
        else if(getColorReflected(RS) < 20){
          motor[LM] = 15;
          motor[RM] = 0;
          waitUntil(getColorReflected(LS) < 40);
        }
        else{
          motor[RM] = 20;
          motor[LM] = 20;
        }
      }
    }



    //////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////-Endfeld-/////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    if(getColorReflected(LS) > 90){           //am Silberstreifen ausrichten
      motor[RM] = 50;
      motor[LM] = 0;
      waitUntil((getColorReflected(RS) + 2) > 90);
      endfeld();                              //Endfeld
    }
    else if((getColorReflected(RS) + 2) > 90){      //am Silberstreifen ausrichten
      motor[LM] = 50;
      motor[RM] = 0;
      waitUntil(getColorReflected(LS) > 90);
      endfeld();                              //Endfeld
    }


    //////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////-Beide schwarz/gr�n-///////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////



    if((links < 20) && (rechts < 20)){        //beide Sensoren entweder schwarz oder gr�n
      colorLinks = getColorName(LS);
      colorRechts = getColorName(RS);
      if((colorLinks == 1) && (colorRechts == 1)){    //beide schwarz
        if(errorx < 0){
          schwarzRechts();                            //rechts zuerst schwarz, also leicht nach links
        }
        else if(errorx > 0){
          schwarzLinks();                             //links zuerst schwarz, also leicht nach rechts
        }
      }
      else if((getColorName(RS) == 3) && (getColorName(LS) == 3)){  //beide gr�n
        beideGruen();     //umdrehen
      }
      counter2 = 1;       //counter2 auf 1, damit nicht 'einer gr�n' gemacht wird
    }


    //////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////-Einer gr�n-///////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////


    if((error > 20) && (counter2 == 0)){        //links gr�n
      errorx = error;
      LeftColor = getColorName(LS);
      if((LeftColor == 3)){
        while(counter == 0){
          if(getColorName(RS) == 3){            //gr�n best�tigt
            beideGruen();
          }
          else if(getColorName(RS) == 1){       //doch nicht gr�n
            counter = 1;
          }
          motor[RM] = 50;
          motor[LM] = -10;
        }
        motor[RM] = 50;
        motor[LM] = -10;
        waitUntil((getColorReflected(RS) + 2) > 40);  //Linie wiederfinden
        waitUntil(getColorReflected(LS) > 40);
      }
    }
    else if((error < -20) && (counter2 == 0)){  //rechts gr�n
      errorx = error;
      RightColor = getColorName(RS);
      if((RightColor == 3)){
        while(counter == 0){
          if(getColorName(LS) == 3){            //gr�n best�tigt
            beideGruen();
          }
          else if(getColorName(LS) == 1){       //doch nicht gr�n
            counter = 1;
          }
          motor[LM] = 50;
          motor[RM] = -10;
        }
        motor[LM] = 50;
        motor[RM] = -10;
        waitUntil(getColorReflected(LS) > 40);
        waitUntil((getColorReflected(RS) + 2) > 40);//Linie wiederfinden
      }
    }


    //////////////////////////////////////////////////////////////////////////////////
    ///////////////////////////////////-Hindernis-////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////


    if(getTouchValue(Touch) == 1){
      hindernis();
    }

    //////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////-PID-///////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////
    turn = (Kp*error);
    powerL = Tp - turn;
    powerR = Tp + turn;
    motor[LM] = powerL;
    motor[RM] = powerR;
    lastError = error;
  }
}
