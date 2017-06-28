  //SENSORES
  //-------ULTRASONIDO-----------------
  //*******Ultrasonido 1***************LUGAR 3
    const int pinEchoU1=12;//recibe
    const int pinTriggerU1 = 13;//envía
    unsigned int distanciaU1;//distancia del ultrasonido 1 al objeto
    long int tiempoU1=0;//tiempo hasta volver a medir distancia.
    const int ledBlancoU1=5;//analogico0
    const int ledVerdeU1=11;//A1
    const int ledRojoU1=10;//A2
    long int tilbu1=0; //tiempo de inicio del led blanco del ultrasonido 1
    long int tflbu1; //tiempo de fin del led blanco del ultrasonido 1
    long int tilru1=0;//tiempo de inicio del led rojo del ultrasonido 1 ante una reserva
    long int tflru1;//tiempo de fin del led rojo del ultrasonido 1 ante una reserva
    long int tilvu1=0; //tiempo de inicio del parpadeo del led verde para ver que lugar se reservo
    long int tflvu1; //el led verde deja de parpadear cuando el usuario ocupo su lugar
    int banderaU1;
    int distAuxU1;//aux para saber si estoy pasando de ocupado/libre o de libre/ocupado.
    long int durAuxU1;//tiempo que se mantiene prendido el led blanco
  //***********************************
  //*******Ultrasonido 2***************LUGAR 4
    const int pinEchoU2=A2;//10
    const int pinTriggerU2 = A1;//11
    unsigned int distanciaU2;
    long int tiempoU2=25;
    const int ledBlancoU2=A3;
    const int ledVerdeU2=A4;
    const int ledRojoU2=A5;
    long int tilbu2=0; //tiempo de inicio del led blanco del ultrasonido 1
    long int tflbu2; //tiempo de fin del led blanco del ultrasonido 1
    long int tilru2=0;//tiempo de inicio del led rojo del ultrasonido 1 ante una reserva
    long int tflru2;//tiempo de fin del led rojo del ultrasonido 1 ante una reserva
    long int tilvu2=0; //tiempo de inicio del parpadeo del led verde para ver que lugar se reservo
    long int tflvu2; //el led verde deja de parpadear cuando el usuario ocupo su lugar, 0: puede parpadear; 1: deja de parpadear
    int banderaU2;
    int distAuxU2;
    long int durAuxU2;//tiempo que se mantiene prendido el led blanco
  //***********************************
  //-----------------------------------
  //-------INFRAROJO-------------------
  //*******Infrarrojo 1****************
  const int infr1=9;
  long int tiempoI1=500;//I=infrarrojo, en 500mseg va a comenzar a leer
  long int tiempoFI1;
  //***********************************
  //*******Infrarrojo 2****************
  const int infr2=8;
  long int tiempoI2=500;
  long int tiempoFI2;
  //***********************************
  //-----------------------------------
  //---------MOTOR---------------------
  const int motorP=7; //VERDE - positivo
  const int motorN=6; //AMARILLO - negativo

  //***********************************
  //-----------------------------------
  //---------LUGARES-------------------
  int pinLugar1=4; //switch
  int pinLugar2=3; //switch
  int lugar1=1; //1= libre; 2=reservado; 3=ocupado
  int lugar2=1;
  int lugar3=1;
  int lugar4=1;
  long int finReservaLugar1;
  long int finReservaLugar2;
  long int finReservaLugar3;
  long int finReservaLugar4;

  int fotoresistencia=A0;
  
  //FUNCIONES
  unsigned int getDistancia(int, int);
  void mandarDatos(int, int, int, int);

  //VARIABLES AUXILIARES
  long int tiempoMS=0;
  //long int tiempoEnviarDatos=0;
  char caracter=0;
  String cadena="";
  int auxHayDatos=0;
  int intensidad=80;
  
void setup() {
  Serial.begin(9600); //Comunicación serial
  //CONFIGURACION DE SENSORES
    //ULTRASONIDO 1
    pinMode(pinEchoU1, INPUT);
    pinMode(pinTriggerU1, OUTPUT);
    pinMode(ledBlancoU1, OUTPUT);
    pinMode(ledRojoU1,OUTPUT);
    pinMode(ledVerdeU1,OUTPUT);

    //ULTRASONIDO 2
    pinMode(pinEchoU2, INPUT);
    pinMode(pinTriggerU2, OUTPUT);
    pinMode(ledBlancoU2, OUTPUT);
    pinMode(ledRojoU2,OUTPUT);
    pinMode(ledVerdeU2,OUTPUT);

    //INFRARROJO 1
    pinMode(infr1,INPUT);

    //INFRARROJO 2
    pinMode(infr2,INPUT);

    //MOTOR
    pinMode(motorP,OUTPUT);
    pinMode(motorN,OUTPUT);

    //LUGARES
    pinMode(pinLugar1,INPUT);
    pinMode(pinLugar2,INPUT);

    
    
}

void loop() {

  if((tiempoMS%2000)==0){
    int valor=analogRead(fotoresistencia);
    //Serial.println(valor);
    if(valor>100)
      intensidad=100;
    else
      intensidad=250;
  }
  

  //LEO DEL PUERTO SERIAL
  if(Serial.available()>0){
    caracter=Serial.read(); //Leo lo que ingresa por el serial
    
    if(auxHayDatos==0 && caracter=='#'){ //El # indica comienzo de una cadena ESTO HABRIA QUE SACARLO
      auxHayDatos=1; //Entro una cadena de varios caracteres
      delay(2); //Delay minimo para que no lea datos basura
      caracter=Serial.read(); 
    } 
    if(auxHayDatos==0){ //Entró un dato de un caracter
      
      if(caracter=='1'){ //Si ingresa 1, 2, 3 o 4 son los lugares que hay que reservar
        if(lugar1==1){ //si el lugar estaba libre lo reservo-- si el lugar esta ocupado la aplicación no manda datos.
          lugar1=2; //Reservo el lugar
          finReservaLugar1=tiempoMS+10000; //La reserva dura 10 segundos
        }
        else
          lugar1=1; //Saco la reserva
      }
      else if(caracter=='2'){
        if(lugar2==1){
          lugar2=2; //Reservo el lugar
          finReservaLugar2=tiempoMS+10000;
        }
        else
          lugar2=1;
      }
      else if(caracter=='3'){
        if(lugar3==1){
          lugar3=2; //Reservo el lugar
          tilru1=tiempoMS+10;//en 10mseg empiezo a prender el led
          finReservaLugar3=tiempoMS+10000; //la reserva dura 10 segundos
        }
        else
          lugar3=1;
      }
      else if(caracter=='4'){
        if(lugar4==1){
          lugar4=2; //Reservo el lugar
          tilru2=tiempoMS+10;
          finReservaLugar4=tiempoMS+10000; //la reserva dura 10 segundos
        }
        else //si el lugar estuviera ocupado, la app no enviaría el valor, solo llega si está libre
          lugar4=1;
      }
      else if(caracter=='5'){
        tilvu1=tiempoMS+10;
        //tflvu1=0;//puede empezar a parpadear
        finReservaLugar3=tiempoMS+10;
      }
      else if(caracter=='6'){
        tilvu2=tiempoMS+10;
        finReservaLugar4=tiempoMS+10;
      }
      mandarDatos(lugar1, lugar2, lugar3, lugar4);
    }

    if(auxHayDatos==1 && caracter!='~'){
      cadena+=caracter;
    }
    else{
      cadena="";
      auxHayDatos=0;
    }
  
  }

  
  //analogWrite(ledBlancoU2,200);
  //Pregunto por el infrarrojo 1
 // if(tiempoI1==tiempoMS)
  //{
    if(tiempoI1==tiempoMS){
      if(digitalRead(infr1)==LOW){ //abre la barrera
        Serial.println("Hay contacto");
        digitalWrite(motorP,HIGH);
        digitalWrite(motorN,LOW);
        
        tiempoFI1=tiempoMS+2000; //2 segundos a partir del último contacto para cerrar la barrera
      }
      /*else{digitalWrite(motorP,LOW);
        digitalWrite(motorN,HIGH);
      }*/
      tiempoI1=tiempoMS+500;
    }
      if(tiempoFI1==tiempoMS){ //pregunta si tiene que cerrar la barrera
        digitalWrite(motorP,LOW);
        digitalWrite(motorN,HIGH);
      }
    
    //tiempoI1=tiempoMS+500;
    //tiempoFI1=tiempoMS+100;
  //}t

 //Pregunto por el infrarrojo 2
  //if(tiempoI2==tiempoMS)
  //{
    if(tiempoI2==tiempoMS){
      if(digitalRead(infr2)==LOW){
        Serial.println("                     Hay contacto");
        digitalWrite(motorP,HIGH);
        digitalWrite(motorN,LOW);
        tiempoFI2=tiempoMS+2000;
      }
      tiempoI2=tiempoMS+500;
    }
      if(tiempoFI2==tiempoMS){
        digitalWrite(motorP,LOW);
        digitalWrite(motorN,HIGH);
      }
    //tiempoI2=tiempoMS+500;
    //tiempoFI2=tiempoMS+100;
  //}
  
  //Tomo la distancia del ultrasonido 1
  if(tiempoU1==tiempoMS){
    distanciaU1=getDistancia(pinTriggerU1, pinEchoU1);
    Serial.println(distanciaU1);
    tiempoU1=tiempoMS+50;
  }

  //Tomo la distancia del ultrasonido 2
   if(tiempoU2==tiempoMS){
    distanciaU2=getDistancia(pinTriggerU2, pinEchoU2);
    Serial.print("                ");
    Serial.println(distanciaU2);
    tiempoU2=tiempoMS+50;
  }
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //controlo los valores del switch
  if(digitalRead(pinLugar1)==HIGH)
    lugar1=3;
  else {
    if(pinLugar1!=2)
      lugar1=1;
  }
  
  if(digitalRead(pinLugar2)==HIGH)
    lugar2=3;
  else {
    if(pinLugar2!=2)
      lugar2=1;
  }

  //Me fijo si tengo que prender o apagar los leds del ultrasonido 1
  if(lugar3==2 && caracter!='5' && tilru1==tiempoMS){
    analogWrite(ledRojoU1,intensidad);
    analogWrite(ledVerdeU1,0);
    tflru1=tiempoMS+500;
    tilru1=tiempoMS+1000;
  }

  if(caracter=='5' && tilvu1==tiempoMS){ //si el caracter es 5, si se permite que parpadee y si es el tiempo de que se inicie el parpadeo
    analogWrite(ledVerdeU1,intensidad);
    analogWrite(ledRojoU1,0);
    tflvu1=tiempoMS+500;
    tilvu1=tiempoMS+1000;
  }
  
  if(distanciaU1>18){
    analogWrite(ledBlancoU1,0);
    banderaU1=0;
    if(lugar3!=2){
      analogWrite(ledRojoU1,0);
      analogWrite(ledVerdeU1,intensidad);
      lugar3=1;
    }
  }
  else if(distanciaU1<=18 && distanciaU1>6)//Aca el led blanco tiene que parpadear
  {
    //digitalWrite(ledRojoU1,HIGH);
    analogWrite(ledRojoU1,intensidad);
    //digitalWrite(ledVerdeU1,LOW);
    analogWrite(ledVerdeU1,0);
    lugar3=3;
    //mandarDatos(lugar1, lugar2, lugar3, lugar4);
    if(banderaU1==0 || tiempoMS==tilbu1){
      //digitalWrite(ledBlancoU1,HIGH);
      analogWrite(ledBlancoU1,intensidad);
      banderaU1=1;
      tflbu1=tiempoMS+10;
      tilbu1=tiempoMS +((350/11)*distanciaU1-(1900/11)); //7:50 => 18:400
    }    
  }
  else if(distanciaU1<=6)
  {
    if(banderaU1==1){
      //digitalWrite(ledBlancoU1,HIGH);
      analogWrite(ledBlancoU1,intensidad);
      banderaU1=0;  
      //distAuxU1=distanciaU1;//guardo la distancia del vehículo
      //durAuxU1=tiempoMS+2000;//el led blanco se tiene que apagar en 2 segundos
      tflbu1=tiempoMS+2000;//el led blanco se tiene que apagar en 2 segundos
    }
    /*if(durAuxU1==tiempoMS && distanciaU1<=6){
      //digitalWrite(ledBlancoU1,LOW);
      analogWrite(ledBlancoU1,0);
    }*/
    //digitalWrite(ledRojoU1,HIGH);
    analogWrite(ledRojoU1,intensidad);
    //digitalWrite(ledVerdeU1,LOW);
    analogWrite(ledVerdeU1,0);
  }
  
  if(tflbu1==tiempoMS){//apago el led blanco por el parpadeo
    analogWrite(ledBlancoU1,0);
  }
  if(tflru1==tiempoMS){//apago el led rojo por la reserva
    analogWrite(ledRojoU1,0);
  }

  if(tflvu1==tiempoMS || lugar3=='3'){
    analogWrite(ledVerdeU1,0);
  }
  
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  //Me fijo si tengo que prender o apagar los leds del ultrasonido 2
  
  if(lugar4==2 && caracter!='6' && tilru2==tiempoMS){
    analogWrite(ledRojoU2,intensidad);
    analogWrite(ledVerdeU2,0);
    tflru2=tiempoMS+500;
    tilru2=tiempoMS+1000;
  }
  
  if(caracter=='6' && tilvu2==tiempoMS){ //si el caracter es 6, si se permite que parpadee y si es el tiempo de que se inicie el parpadeo
    analogWrite(ledVerdeU2,intensidad);
    analogWrite(ledRojoU2,0);
    tflvu2=tiempoMS+500;
    tilvu2=tiempoMS+1000;
  }
  
  if(distanciaU2>18){
    analogWrite(ledBlancoU2,0);
    banderaU2=0;
    if(lugar4!=2){
      analogWrite(ledRojoU2,0);
      analogWrite(ledVerdeU2,intensidad);
      lugar4=1;
    }
    //mandarDatos(lugar1, lugar2, lugar3, lugar4);
  }
  else if(distanciaU2<=18 && distanciaU2>6)//Aca el led blanco tiene que parpadear
  {
    //digitalWrite(ledRojoU2,HIGH);
    analogWrite(ledRojoU2,intensidad);
    //digitalWrite(ledVerdeU2,LOW);
    analogWrite(ledVerdeU2,0);
    lugar4=3;
    //mandarDatos(lugar1, lugar2, lugar3, lugar4);
    if(tiempoMS==tilbu2 ||banderaU2==0){
      //digitalWrite(ledBlancoU2,HIGH);
      analogWrite(ledBlancoU2,intensidad);
      banderaU2=1;
      tflbu2=tiempoMS+10;
      tilbu2=tiempoMS +((350/11)*distanciaU2-(1900/11)); //7:50 => 18:400
    }    
  }
  else if(distanciaU2<=6)
  {
    if(banderaU2==1){
      //digitalWrite(ledBlancoU2,HIGH);
      analogWrite(ledBlancoU2,intensidad);
      banderaU2=0;  
      //distAuxU2=distanciaU2;//guardo la distancia del vehículo
      //durAuxU2=tiempoMS+2000;//el led blanco se tiene que apagar en 2 segundos
      tflbu2=tiempoMS+2000;//el led blanco se tiene que apagar en 2 segundos
    }
    /*if(durAuxU2==tiempoMS && distanciaU2<=6){
      //digitalWrite(ledBlancoU2,LOW);
      analogWrite(ledBlancoU2,0);
    }*/
    //digitalWrite(ledRojoU2,HIGH);
    analogWrite(ledRojoU2,intensidad);
    //digitalWrite(ledVerdeU2,LOW);
    analogWrite(ledVerdeU2,0);
    
  }
  if(tflbu2==tiempoMS){
    //digitalWrite(ledBlancoU2,LOW);
    analogWrite(ledBlancoU2,0);
  }
  if(tflru2==tiempoMS){//apago el led rojo por la reserva
    analogWrite(ledRojoU2,0);
  }
  if(tflvu2==tiempoMS || lugar4=='3'){
    analogWrite(ledVerdeU2,0);
  }
  //-----------------FIN DE RESERVA--------------------
  if(finReservaLugar1==tiempoMS){//termina el tiempo límite de reserva
    lugar1=1;
  }
  if(finReservaLugar2==tiempoMS){//termina el tiempo límite de reserva
    lugar2=1;
  }
  if(finReservaLugar3==tiempoMS){//termina el tiempo límite de reserva
    if(caracter=='5')
      lugar3=2;
    else
    lugar3=1;
  }
  if(finReservaLugar4==tiempoMS){//termina el tiempo límite de reserva
    if(caracter=='6')
      lugar4=2;
    else
      lugar4=1;
  }
  
  
  if((tiempoMS%1000)==0)
    mandarDatos(lugar1, lugar2, lugar3, lugar4);
  
  delay(1);
  tiempoMS++;
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*
unsigned int getDistancia(int pinTrigger, int pinEcho){
  unsigned int tiempo;
  //Enviar pulso de disparo en el pin TRIGGER.
  digitalWrite(pinTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(pinTrigger, HIGH);
  //El pulso dura al menos 10 uS (microsegundos) en estado alto.
  delayMicroseconds(10);
  digitalWrite(pinTrigger, LOW);
  //Medir el tiempo en estado alto del pin ECHO. El pulso es proporcional a la distancia media.
  tiempo = pulseIn(pinEcho, HIGH);
  //La velocidad del sonido es de 340 Mts/Seg o 29 us/cm
  //Dividimos el tiempo del pulso en 58, tiempo que tarda en recorrer ida y vuelta un cenímetro la onda sonora.
  return(tiempo / 58);  
}

//-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*
void mandarDatos(int l1, int l2, int l3, int l4){
  Serial.print("#");
  Serial.print(l1);
  Serial.print("+");
  Serial.print(l2);
  Serial.print("+");
  Serial.print(l3);
  Serial.print("+");
  Serial.print(l4);
  Serial.print("~");
}

