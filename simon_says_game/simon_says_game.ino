int Level = 1;
int Sequence[4] = {0, 0, 0, 0};
int Speed = 1000;
int ShowFlag = 1;
int PressDetected = 0;
int GameON = 0;

void setup() {
  // put your setup code here, to run once:
  for (int i=2; i<=5; i++){
    pinMode(i,OUTPUT);
  }
  for (int i=8; i<=11; i++){
    pinMode(i,INPUT);
  }
  Serial.begin(9600);
  Serial.println("Simon Says Game");
}

void loop() {
  // put your main code here, to run repeatedly:
 
  if(digitalRead(6) == 0){
    GameON = 1;
    delay(1000);
  }

  if(ShowFlag == 1 && GameON == 1){
    Serial.print("Level: ");
    Serial.println(Level);
    for (int i=0; i<=3; i++){
    Sequence[i] = random(2,6);
    digitalWrite(Sequence[i], HIGH);
    delay(Speed - Level*25);
    digitalWrite(Sequence[i], LOW);
    delay(Speed/10);
    }
    ShowFlag = 0;
    PressDetected = 0;
  }

  if(GameON == 1){
    for (int i=0; i<=3; i++){
      if(PressDetected == i && ShowFlag == 0){
        while(PressDetected == i){
          for (int j=2; j<=5; j++){
            if(digitalRead(j+6) == 0){
              digitalWrite(j, HIGH);
              delay(500);
              digitalWrite(j, LOW);
              PressDetected = i+1; 
              if(Sequence[i] != j){
                ShowFlag = 1;
                Level = 1;
                GameON = 0;
                Serial.println("Game Over");
                for(int l=0; l<3; l++){
                  for(int m=2; m<=5; m++){
                    digitalWrite(m, HIGH);
                  }
                  delay(500);
                  for(int m=2; m<=5; m++){
                    digitalWrite(m, LOW);
                  }
                  delay(500);
                }
              }
            }
          }
        }
      }
    }
  }

  if(ShowFlag == 0 && GameON == 1){
    ShowFlag = 1;
    Level++;
    delay(1000);
  }
}
