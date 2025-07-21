#define ENC_A 2 // in usage
#define ENC_B 3 
#define LEFT_F1 8
#define LEFT_F2 9
#define LEFT_B1 10
#define LEFT_B2 11
#define RIGHT_F1 6
#define RIGHT_F2 7
#define RIGHT_B1 4
#define RIGHT_B2 5
#define Test_LED 12
#define voltege 13

int position = 0;
int x = 328; // One full lap
// one full lap = 25cm
// robot length is 26cm
// map sqer is 25cm
const int forward = 1;
const int backward = 2;
const int turnLeft = 3;
const int turnRight = 4;
int signal = 1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ENC_A,INPUT);
  pinMode(ENC_B,INPUT);
  attachInterrupt(digitalPinToInterrupt(ENC_A),readEncoder,RISING);
  pinMode(LEFT_F1, OUTPUT);
  pinMode(LEFT_F2, OUTPUT);
  pinMode(LEFT_B1, OUTPUT);
  pinMode(LEFT_B2, OUTPUT);
  pinMode(RIGHT_F1, OUTPUT);
  pinMode(RIGHT_F2, OUTPUT);
  pinMode(RIGHT_B1, OUTPUT);
  pinMode(RIGHT_B2, OUTPUT);
  pinMode(Test_LED, OUTPUT);
  pinMode(voltege, OUTPUT);
}

void loop() {
  digitalWrite(voltege,HIGH);
  Serial.println(position); // control check
  if (Serial.available() > 0){
    signal = Serial.read() - '0';
    position = 0;
  }
  if(signal == forward){
    Run(forward);
  }else if(signal == backward){
    Run(backward);
  }else if(signal == turnLeft){
    Run(turnLeft);
  }else if(signal == turnRight){
    Run(turnRight);
  }else{
    Stop();
  }
}

// 1 = go forward
// 2 = go back
void Run(int i){
  if(abs(position) < x){
    if(i == forward){
      digitalWrite(LEFT_F1,HIGH);
      digitalWrite(LEFT_B1,HIGH);
      digitalWrite(RIGHT_F1,HIGH);
      digitalWrite(RIGHT_B1,HIGH);

      digitalWrite(LEFT_F2,LOW);
      digitalWrite(LEFT_B2,LOW);
      digitalWrite(RIGHT_F2,LOW);
      digitalWrite(RIGHT_B2,LOW);
    }else if(i == backward){
      digitalWrite(LEFT_F1,LOW);
      digitalWrite(LEFT_B1,LOW);
      digitalWrite(RIGHT_F1,LOW);
      digitalWrite(RIGHT_B1,LOW);

      digitalWrite(LEFT_F2,HIGH);
      digitalWrite(LEFT_B2,HIGH);
      digitalWrite(RIGHT_F2,HIGH);
      digitalWrite(RIGHT_B2,HIGH);
    }else if(i == turnLeft){
      digitalWrite(LEFT_F1,LOW);
      digitalWrite(LEFT_F2,HIGH);
      
      digitalWrite(LEFT_B1,HIGH);
      digitalWrite(LEFT_B2,LOW);

      digitalWrite(RIGHT_F1,HIGH);
      digitalWrite(RIGHT_F2,LOW);

      digitalWrite(RIGHT_B1,LOW);
      digitalWrite(RIGHT_B2,HIGH);
    }else if(i == turnRight){
      digitalWrite(LEFT_F1,HIGH);
      digitalWrite(LEFT_F2,LOW);
      
      digitalWrite(LEFT_B1,LOW);
      digitalWrite(LEFT_B2,HIGH);

      digitalWrite(RIGHT_F1,LOW);
      digitalWrite(RIGHT_F2,HIGH);

      digitalWrite(RIGHT_B1,HIGH);
      digitalWrite(RIGHT_B2,LOW);
    }
  }else{
    Stop();
    signal = 0;
  }
}

void Stop(){
  digitalWrite(Test_LED,LOW);
  digitalWrite(LEFT_F1,LOW);
  digitalWrite(LEFT_B1,LOW);
  digitalWrite(RIGHT_F1,LOW);
  digitalWrite(RIGHT_B1,LOW);

  digitalWrite(LEFT_F2,LOW);
  digitalWrite(LEFT_B2,LOW);
  digitalWrite(RIGHT_F2,LOW);
  digitalWrite(RIGHT_B2,LOW);
}


void readEncoder(){
  int a = digitalRead(ENC_A);
  if(a>0){
    position++;
  }else{
    position--;
  }
}
