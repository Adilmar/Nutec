//pinos das cores
int yellon = 5; 
int green = 4; 
int blue = 3; 
int red = 6;  
int pink = 7;

//sensor de som
int pinoSensor = A2;
int val = 0 ;

void setup () {
          Serial.begin (9600);
          pinMode(red, OUTPUT);
          pinMode(green, OUTPUT);
          pinMode(blue, OUTPUT);
          pinMode(yellon, OUTPUT);
          pinMode(pink, OUTPUT);
          pinMode (pinoSensor, INPUT);
          
}
void loop () {
  //logica para acionamento obs: deve regular a sensibilidade do sensor
  val = analogRead(pinoSensor);
         Serial.println(val, DEC);
         delay(50);
        if (val > 100 && val < 200 ) {
                digitalWrite (red, HIGH);
                delay(100);
        }
        
        if (val >= 200 && val <300 ) {
                digitalWrite (pink, HIGH);
                delay(100);
        }
        
        if (val >= 300 && val <400 ) {
                digitalWrite (yellon, HIGH);
                delay(100);
        }
        
        if (val >= 300 && val <400 ) {
                digitalWrite (yellon, HIGH);
                delay(100);
        }if (val >= 400 && val <500 ) {
                digitalWrite (green, HIGH);
                delay(100);
        }
        if (val >= 500 && val <700 ) {
                digitalWrite (blue, HIGH);
                delay(100);
        }
        
        else {
          
          digitalWrite (yellon, LOW);
          digitalWrite (green, LOW);
          digitalWrite (red, LOW);
          digitalWrite (yellon, LOW);
          digitalWrite (pink, LOW);
          digitalWrite (blue, LOW);
          
          
        }
  
  //digitalWrite (yellon, HIGH);
  //digitalWrite (green, HIGH);
  //digitalWrite (red, HIGH);
  //digitalWrite (yellon, HIGH);
  //digitalWrite (pink, HIGH);
         
}
