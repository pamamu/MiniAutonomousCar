

#define trigPin 8 // Pin de emisión del pulso de ultrasonido
#define echoPin 9 // Pin de obtención del pulso de ultrasonido

int actder=2,      //Activar derecha en PIN 2
actizq=3,          //Activar izquierda en PIN 3
dA=6,            //Derecha POL1 en PIN 6
dB=7,            //Derecha POL2 en PIN 7
iA=4,            //Izquierda en POL1 en PIN 4
iB=5;            //Izquierda en POL2 en PIN 5

int grados; // Variable para establecer los grados del servo
const int rgIzq=150,rgDer=35,inGra=1; // Variables para establecer el rango de grados a recorrer por el servo y el valor con el que se modifican lo grados
void setup() {

  Serial.begin(9600);
  pinMode(trigPin, OUTPUT); // Establecer el pin de trigger (emision) como salida
  pinMode(echoPin, INPUT); // Establecer el pin de echo (recepcion) como entrada
  pinMode(actder, OUTPUT);
  pinMode(actizq, OUTPUT);
  pinMode(dA, OUTPUT);
  pinMode(dB, OUTPUT);
  pinMode(iA, OUTPUT);
  pinMode(iB, OUTPUT);

  }
  
/*
motor([1(der),2(izq),3(der-izq)], [true(encendido, false(apagado)], [true(alante), false(atras)], tiempo(segundos)]
*/

void motor(int m1, int m2, int sent){

  if(m1=='1'){
      digitalWrite(actder, HIGH);
      if (sent==true){
        digitalWrite(dA, LOW);
        digitalWrite(dB, HIGH);
      }
      else{
        digitalWrite(dA, HIGH);
        digitalWrite(dB, LOW);
      } 
    }
    else{
      digitalWrite(actder, LOW);
    }
  
   if(m2=='1'){
      digitalWrite(actizq, HIGH);
      if (sent==true){
        digitalWrite(iA, LOW);
        digitalWrite(iB, HIGH);
      }
      else{
        digitalWrite(iA, HIGH);
        digitalWrite(iB, LOW);
      } 
    }
    else{
      digitalWrite(actizq, LOW);
    }
  
   if(m2=='1'&&m1=='1'){
      digitalWrite(actizq, HIGH);
      digitalWrite(actder, HIGH);
      if (sent==true){
        digitalWrite(iA, LOW);
        digitalWrite(iB, HIGH);
        digitalWrite(dA, LOW);
        digitalWrite(dB, HIGH);
      }
      else{
        digitalWrite(dA, HIGH);
        digitalWrite(dB, LOW);
        digitalWrite(iA, HIGH);
        digitalWrite(iB, LOW);
      } 
    }
    else{
      digitalWrite(actder, LOW);
      digitalWrite(actizq, LOW);
    }

}

long dist(){
  long duracion,distancia;
  digitalWrite(trigPin, LOW); // Se desactiva la emisión
  delayMicroseconds(2); // Espera de 2 microsegundos
  digitalWrite(trigPin, HIGH); // Activación de la emisión
  delayMicroseconds(10); // Espera de 10 microsegundos
  digitalWrite(trigPin, LOW); // Se desactiva la emisión

  duracion = pulseIn(echoPin, HIGH); // Se obtiene el tiempo hasta la recepción del pulso emitido
  distancia = (duracion/2) / 29.1; // Se calcula la distancia con constantes
  return distancia;
}

char header[4]={1,0,0,1};
char footer[4]={1,1,0,1};

char commands[3]={0,0,0};

void loop(){
  
  Serial.println(dist());
  
char inBuffer [11];
  
  while (Serial.available() > 0) {
    char c;
  for(int i=0;i<11;i++){
    c = Serial.read();
     inBuffer[i]=c;
     
  }
  }
  
for(int i=0;i<4;i++)
  if(inBuffer[4+i]!=commands[i])commands[i]=inBuffer[4+i];
  
  motor(commands[4],commands[5],commands[6]);

}
