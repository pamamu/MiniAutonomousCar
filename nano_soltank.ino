#include <Servo.h> 
Servo servo; //Declaracin del servo
int grados; // Variable para establecer los grados del servo
const int rgIzq=150,rgDer=35,inGra=1; // Variables para establecer el rango de grados a recorrer por el servo y el valor con el que se modifican lo grados
long distancia;
bool cerca=true;
void setup() {
  Serial.begin(9600);
  servo.attach(10); // Establecer el servo en el pin 8  
}


void loop(){
  Serial.println('1');
  for(grados=rgDer;grados<=rgIzq;(grados+=inGra)){
    if(Serial.available()){  
      distancia=Serial.read();
      if(distancia>30 && cerca){
        Serial.print('9');
        Serial.print('1');
        Serial.print('1');
        Serial.print('1');
        Serial.print('13');
        cerca=false; 
      }
      else if(distancia >30 && !cerca && grados>97){
        Serial.print('9');
        Serial.print('1');
        Serial.print('0');
        Serial.print('0');
        Serial.print('13');
        cerca=true;
      }
      else if(distancia >30 && !cerca && grados<97){
        Serial.print('9');
        Serial.print('0');
        Serial.print('1');
        Serial.print('0');
        Serial.print('13');
        cerca=true;
      }


    }
    servo.write(grados);
    delay(3);
  }

  for(grados=rgIzq;grados>=rgDer;grados-=inGra){
    if(Serial.available()){  
      distancia=Serial.read();
      if(distancia>30 && cerca){
        Serial.print('9');
        Serial.print('1');
        Serial.print('1');
        Serial.print('1');
        Serial.print('13'); 
      }
      else if(distancia >30 && !cerca && grados>97){
        Serial.print('9');
        Serial.print('1');
        Serial.print('0');
        Serial.print('0');
        Serial.print('13');
      }
      else if(distancia >30 && !cerca && grados<97){
        Serial.print('9');
        Serial.print('0');
        Serial.print('1');
        Serial.print('0');
        Serial.print('13');
      }


    }
    servo.write(grados);
    delay(3);
  }

}











