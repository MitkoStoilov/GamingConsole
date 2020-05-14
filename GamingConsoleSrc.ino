
//За всеки диод в LED матрицата има съответстващо поле в двумерен масив. Ако полето е със стойност 1 съответния диод ще свети 
bool matrix[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0}
}; 


bool sad_matrix[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 1, 0, 0, 1, 0, 0}, 
  {0, 0, 1, 0, 0, 1, 0, 0}, 
  {0, 0, 1, 0, 0, 1, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 1, 1, 1, 1, 0, 0},
  {0, 1, 0, 0, 0, 0, 1, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0}
}; 

bool snake_matrix[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 1, 0, 0, 0, 0, 0, 0}, 
  {0, 1, 0, 1, 0, 1, 1, 0}, 
  {0, 1, 0, 0, 0, 0, 1, 0}, 
  {0, 1, 0, 0, 0, 0, 1, 0}, 
  {0, 1, 1, 1, 1, 1, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0}
}; 


bool tetris_matrix[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 1, 1, 1, 0, 0}, 
  {0, 0, 0, 0, 0, 1, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 0, 0, 0, 1, 1}, 
  {1, 1, 1, 1, 1, 0, 1, 1}
};

bool ball_matrix[8][8] = {
  {1, 1, 1, 1, 1, 1, 1, 1}, 
  {1, 1, 1, 1, 1, 1, 1, 1}, 
  {1, 1, 1, 1, 1, 1, 1, 1}, 
  {0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}, 
  {0, 0, 1, 1, 1, 0, 0, 0}
}; 


int x = 0;
int y = 0;

bool start = false;
//когато играта приключи (змията умре) стойността става "true"
bool ended = false;

bool gameMenu[3];

void setup() {

  Serial.begin(9600);
  //Чрез пиновете А0, А1, А2 и А3 се обработват сигналите изпращани от джойстика
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  pinMode(49, INPUT);

  //Към тези пинове са свързани анодите на на светодиодите
  for(int i = 2; i < 10; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }

  //Към тези пинове са свързани катодите на на светодиодите
  for(int i = 23; i < 31; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }

  //turnOnAll();
  //turnOnDiode();
  //startSnake();
  //generateFood();
  gameMenu[0] = true;
  gameMenu[1] = false;
  gameMenu[2] = false;
}

int startCounter = 0;

void loop() {

  //moveDot();
  //snakeMovement();
  if(!start && !ended || start && ended){
    for(int i = 0; i < 8; i++){
      digitalWrite(i+2, HIGH);
      for(int n = 0; n < 8; n++){
        if(gameMenu[0]){
          if(snake_matrix[i][n] == 1){            
             digitalWrite(n+23, LOW);
          }
        }else if(gameMenu[1]){
          if(tetris_matrix[i][n] == 1){
             digitalWrite(n+23, LOW);
          }
        }else if(gameMenu[2]){
          if(ball_matrix[i][n] == 1){
             digitalWrite(n+23, LOW);
          }
        }      
      }
      menuSelect();
      gameSelect();
      turnOffAll();
    }
  }else{
    if(gameMenu[0]){
      snakeMovement(); 
    }else if(gameMenu[1]){
      tetris();  
    }else if(gameMenu[2]){
      snakeMovement();    
    }
  }
}

void menuSelect(){


  
  if(analogRead(A0) == 1023){
    for(int i = 2; i >= 0; i--){
      if(gameMenu[i]){
        gameMenu[i] = false;
        if(i!=0){
          gameMenu[i-1] = true;
        }else{
          gameMenu[2] = true;
        }
        break;
      }
    }
    turnOffAll();
    delay(300);
    //Serial.println("LEFT");
  }else if(analogRead(A1) == 1023){
    //turnOffAll();
    for(int i = 0; i < 3; i++){
      if(gameMenu[i]){
        gameMenu[i] = false;
        if(i!=2){
          gameMenu[i+1] = true;
        }else{
          gameMenu[0] = true;
        }
        break;
      }
    }
    turnOffAll();
    delay(300);
    //Serial.println("RIGHT");
  }  
  
  
    
}


void gameSelect(){
  if(analogRead(A3) == 1023){
    turnOffAll();
    clearMatrix();
    delay(1000);
    if(ended && !start){
       
       start = true;
    }else{
      start = true;
      ended = false;
      
    }  
    if(gameMenu[0]){
      resetSnake();
    }
    
    

  }
    
}

//включва всички светодиоди в матрицата
void turnOnAll(){
  for(int i = 2; i < 10; i++){
    digitalWrite(i, HIGH);
  }
  for(int i = 23; i < 31; i++){
    digitalWrite(i, LOW);
  } 
}

//изключва всички светодиоди в матрицата
void turnOffAll(){
  for(int i = 2; i < 10; i++){
    digitalWrite(i, LOW);
  }
  for(int i = 23; i < 31; i++){
    digitalWrite(i, HIGH);
  } 
}

void clearMatrix(){
  for(int i = 0; i < 8; i++){
    for(int n = 0; n < 8; n++){
      matrix[i][n] = 0;  
    }  
  }  
}

////////////////////Simple dot moving////////////////////////
void moveDot(){
   if(analogRead(A0) == 1023){
    moveLeft();
    Serial.println("LEFT");
  }else if(analogRead(A1) == 1023){
    moveRight();
    Serial.println("RIGHT");
  }else if(analogRead(A2) == 1023){
    moveDown();
    Serial.println("DOWN");
  }else if(analogRead(A3) == 1023){
    moveUp();
    Serial.println("UP");
  }

  delay(200);
}


void turnOnDiode(){
  digitalWrite(y+2, HIGH);
  digitalWrite(x+23, LOW);
  matrix[y][x] = 1;
}


void moveDown(){
  if(y<7){
      digitalWrite(y+2, LOW);
      matrix[y][x] = 0;
      y = y + 1;
      turnOnDiode();
  }  
}

void moveUp(){
  if(y>0){
      digitalWrite(y+2, LOW);
      matrix[y][x] = 0;
      y = y - 1;
      turnOnDiode();
  }  
}

void moveRight(){
  if(x<7){
      digitalWrite(x+23, HIGH);
      matrix[y][x] = 0;
      x = x + 1;
      turnOnDiode();
  }  
}

void moveLeft(){
  if(x>0){
      digitalWrite(x+23, HIGH);
      matrix[y][x] = 0;
      x = x - 1;
      turnOnDiode();
  }  
}


////////////////////Snake////////////////////////

//Взависимост от стойността на velocityX и velocityY се определя посоката в коята се движи змията
int velocityX = 1;
int velocityY = 0;

//Двата масива пазят координатите на всяка точка от змията.
int snakeDotsX[50];
int snakeDotsY[50];

int snakeLength = 0;

//координати на храната
int foodX, foodY;


int delayCounter = 0;


void resetSnake(){
    velocityX = 1;
    velocityY = 0;
    for(int i = 0; i++; i <50){
      snakeDotsX[i] = 0;
      snakeDotsY[i] = 0;
    }
    snakeLength = 0;
    delayCounter = 0;

    for(int i = 0; i<8; i++){
      for(int n = 0; n < 8; n++){
        matrix[i][n] = 0;  
      }  
    }
    startSnake();
    generateFood();
}

//записва първите две точки от змията
void startSnake(){
  x = 0;
  y = 0;
  matrix[y][x] = 1;
  snakeDotsX[1] = x;
  snakeDotsY[1] = y;
  x = x + 1;

  matrix[y][x] = 1;
  snakeDotsX[0] = x;
  snakeDotsY[0] = y;

  snakeLength++;
}

void snakeMovement(){
  
  //възоснова на това кои полета в двумерния масив са със стойност 1, включва диодите от LED матрицата
  if(!ended){
    for(int i = 0; i < 8; i++){
      digitalWrite(i+2, HIGH);
      for(int n = 0; n < 8; n++){
        if(matrix[i][n] == 1){
           //digitalWrite(i+2, HIGH);
           digitalWrite(n+23, LOW);
        }    
      }
      
      turnOffAll();
    }
  }else if(ended && !start){
    for(int i = 0; i < 8; i++){
      digitalWrite(i+2, HIGH);
      for(int n = 0; n < 8; n++){
        if(sad_matrix[i][n] == 1){
           //digitalWrite(i+2, HIGH);
           digitalWrite(n+23, LOW);
        }    
      }
      gameSelect();
      turnOffAll();
    } 
  } 
  

  
  delayCounter++;
  if(delayCounter == 150){
    delayCounter = 0;

    //Обработване на сигналите подавани от джойстика
    if(analogRead(A0) == 1023){
      if(velocityX == 0 && ended == false){
        velocityX = -1;
        velocityY = 0;
      }  
      Serial.println("LEFT");
    }else if(analogRead(A1) == 1023){
      if(velocityX == 0 && ended == false){
        velocityX = 1;
        velocityY = 0;
      }
      Serial.println("RIGHT");
    }else if(analogRead(A2) == 1023){
      if(velocityY == 0 && ended == false){
        velocityY = 1;
        velocityX = 0;
      }  
      Serial.println("DOWN");
    }else if(analogRead(A3) == 1023){
      if(velocityY == 0 && ended == false){
        velocityY = -1;
        velocityX = 0;
      }
      Serial.println("UP");
    }

    //Движение на змията
    matrix[snakeDotsY[snakeLength]][snakeDotsX[snakeLength]] = 0;
   
    for(int i = snakeLength; i > 0; i--){
      snakeDotsX[i] = snakeDotsX[i-1];
      snakeDotsY[i] = snakeDotsY[i-1];
    }

    //мести главата на змията по X 
    if(snakeDotsX[0] + velocityX < 8 && snakeDotsX[0] + velocityX > -1){
      snakeDotsX[0] = snakeDotsX[0] + velocityX;
    }else if(snakeDotsX[0] + velocityX == 8){
         snakeDotsX[0] = 0;
    }else if(snakeDotsX[0] + velocityX == -1){
         snakeDotsX[0] = 7;
    }

    //мести главата на змията по Y 
    if(snakeDotsY[0] + velocityY < 8 && snakeDotsY[0] + velocityY > -1){
      snakeDotsY[0] = snakeDotsY[0] + velocityY;
    }else if(snakeDotsY[0] + velocityY == 8){
         snakeDotsY[0] = 0;
    }else if(snakeDotsY[0] + velocityY == -1){
         snakeDotsY[0] = 7;
    }

    //засича колизии на змията със храна или с нейното тяло
    if(matrix[snakeDotsY[0]][snakeDotsX[0]] == 1){
      if(snakeDotsY[0]==foodY && snakeDotsX[0]==foodX){
        matrix[snakeDotsY[0]][snakeDotsX[0]] = 1;  
        addDotToSnake();
        generateFood();
      }else{
        ended = true;
        start = false;
        resetSnake();
        clearMatrix(); 
      }  
    }else{
      matrix[snakeDotsY[0]][snakeDotsX[0]] = 1;
    }
  }
}

//генерира храна за змията
void generateFood(){
  int x1 = random(7);
  int y1 = random(7);
  
  if(matrix[y1][x1]==0){
    foodX = x1;
    foodY = y1;
    matrix[foodY][foodX] = 1;  
  }else{
    generateFood();  
  }

}

//удължава змията като добавя нова точка към нея
void addDotToSnake(){
  snakeLength++;
  if(snakeDotsX[snakeLength-1] == snakeDotsX[snakeLength-2]){
    snakeDotsX[snakeLength] = snakeDotsX[snakeLength-1];
    if(snakeDotsY[snakeLength-1] < snakeDotsY[snakeLength-2]){
      snakeDotsY[snakeLength] = snakeDotsY[snakeLength-1] - 1;
    }else{
      snakeDotsY[snakeLength] = snakeDotsY[snakeLength-1] + 1;
    }
  }else if (snakeDotsY[snakeLength-1] == snakeDotsY[snakeLength-2]){
    snakeDotsY[snakeLength] = snakeDotsY[snakeLength-1];
    if(snakeDotsX[snakeLength-1] < snakeDotsX[snakeLength-2]){
      snakeDotsX[snakeLength] = snakeDotsX[snakeLength-1] - 1;
    }else{
      snakeDotsX[snakeLength] = snakeDotsX[snakeLength-1] + 1;
    }
  }

  matrix[snakeDotsY[snakeLength]][snakeDotsX[snakeLength]] = 1;
  
}



//////////////Tetris///////////////////
int tetrisVelocity = 1;

int fallDotsX[4];
int fallDotsY[4];

int oldDotsX[4];
int oldDotsY[4];

int controlCounter = 0;

int dotsCount = 0;
bool fallingBlock = false;

bool left;
bool right;



void generateLBlock(){
  fallingBlock = true;
  left = true;
  right = true;
  int startingX = 2; 

  for(int i = 0; i<3; i++){
    fallDotsX[i] = startingX;
    startingX++;
    fallDotsY[i] = -1;
  }

  fallDotsX[3] = 4;
  fallDotsY[3] = 0;
  dotsCount = 4;
  
}

void enableGenerationForNewBlock(){
  fallingBlock = false;
  for(int n = 0; n < dotsCount; n++){
    //matrix[oldDotsY[n]][oldDotsX[n]] = 1;
    oldDotsX[n] = 0;
    oldDotsY[n] = 0;
  }  
}

void filledRow(){
  
  for(int i = 0; i < 8; i++){
    int sum = 0;
    for(int n = 0; n < 8; n++){
        sum += matrix[i][n];
        if(sum == 8){
          for(int f = 0; f<8; f++){
            matrix[i][f] = 0;
          }

          for(int p = i-1; p >= 0; p--){
            for(int k = 0; k < 8; k++){
              if(matrix[p][k]==1){
                matrix[p+1][k] = 1;
                matrix[p][k] = 0;
              }
            }  
          }  
        }
    }  
  }  
}

void tetris(){
  if(!ended){
    filledRow();
    for(int i = 0; i < 8; i++){
      digitalWrite(i+2, HIGH);
      for(int n = 0; n < 8; n++){
        if(matrix[i][n] == 1){
           digitalWrite(n+23, LOW);
        }    
      }
      
      turnOffAll();
    }
  }else if(ended && !start){
    for(int i = 0; i < 8; i++){
      digitalWrite(i+2, HIGH);
      for(int n = 0; n < 8; n++){
        if(sad_matrix[i][n] == 1){
           //digitalWrite(i+2, HIGH);
           digitalWrite(n+23, LOW);
        }    
      }
      gameSelect();
      turnOffAll();
    } 
  } 

  controlCounter++;
  if(controlCounter == 200){
    controlCounter = 0;
    if(analogRead(A0) == 1023){
      if(ended == false){
        for(int i = 0; i<4; i++){
          if(left){
            fallDotsX[i]--;
            if(!right){
              right = true;  
            }
            
            if(fallDotsX[i]==0){
              left = false;
              for(i++; i<4; i++){
                fallDotsX[i]--;
              }
            }
          }   
        }
      }  
      //Serial.println("LEFT");
    }else if(analogRead(A1) == 1023){
      if(ended == false){
         for(int i = 0; i<4; i++){
            if(right){
              if(right){
                fallDotsX[i]++;
                if(!left){
                  left = true;  
                }
                if(fallDotsX[i]==7){
                  right = false;
                  for(i++; i<4; i++){
                    fallDotsX[i]++;
                  }
                }
              }  
            }
         } 
      }
      //Serial.println("RIGHT");
    }else if(analogRead(A2) == 1023){
      if(ended == false){
          
          if(fallDotsX[3] == fallDotsX[2]){
            if(fallDotsY[3] < fallDotsY[2]){
              fallDotsX[3] += 2;
              
              fallDotsX[2]++;
              fallDotsY[2]--; 

              fallDotsX[0]--;
              fallDotsY[0]++;                
              
            }else if(fallDotsY[3] > fallDotsY[2]){
              fallDotsX[3] -= 2;
              
              fallDotsX[2]--;
              fallDotsY[2]++;

              fallDotsY[0]--;
              fallDotsX[0]++;
            }
          }else if(fallDotsY[3] == fallDotsY[2]){
            if(fallDotsX[3] < fallDotsX[2]){
               fallDotsY[3] -= 2;

               fallDotsX[2]--;
               fallDotsY[2]--;

               fallDotsY[0]++;
               fallDotsX[0]++;                            
            }else if(fallDotsX[3] > fallDotsX[2]){
               fallDotsY[3]+=2;

               fallDotsX[2]++;
               fallDotsY[2]++;
               
               fallDotsX[0]--;
               fallDotsY[0]--;             
            }
          }
        
      }  
      delay(150);
      //Serial.println("DOWN");
      
    }else if(analogRead(A3) == 1023){
      if(ended == false){
         
         if(fallDotsX[3] == fallDotsX[2]){
            if(fallDotsY[3] < fallDotsY[2]){
              fallDotsX[3] += 2;
              
              fallDotsX[2]++;
              fallDotsY[2]++; 

              fallDotsX[0]--;
              fallDotsY[0]--;                
              
            }else if(fallDotsY[3] > fallDotsY[2]){
              fallDotsY[3]-=2;
              
              fallDotsX[2]--;
              fallDotsY[2]--;

              fallDotsY[0]++;
              fallDotsX[0]++;
            }
          }else if(fallDotsY[3] == fallDotsY[2]){
            if(fallDotsX[3] < fallDotsX[2]){
               fallDotsX[3] += 2;

               fallDotsX[2]++;
               fallDotsY[2]--;

               fallDotsY[0]++;
               fallDotsX[0]--;                            
            }else if(fallDotsX[3] > fallDotsX[2]){
               fallDotsX[3]-=2;

               fallDotsX[2]--;
               fallDotsY[2]++;
               
               fallDotsX[0]++;
               fallDotsY[0]--;             
            }
          }
      }
      delay(150);
      //Serial.println("UP");
    }
  }

  
  delayCounter++;
  if(delayCounter == 900){
    delayCounter = 0;
    if(!fallingBlock){
      generateLBlock();
    }

    //clearMatrix();
    for(int i = 0; i < dotsCount; i++){
       matrix[oldDotsY[i]][oldDotsX[i]] = 0;
    }

    
    for(int i = 0; i < dotsCount; i++){
      if(fallDotsY[i] >= 0){
        if(!matrix[fallDotsY[i]][fallDotsX[i]] == 1){
          matrix[fallDotsY[i]][fallDotsX[i]] = 1;
          oldDotsX[i] = fallDotsX[i];
          oldDotsY[i] = fallDotsY[i];
          if(matrix[fallDotsY[i]+1][fallDotsX[i]] == 1 ){
            bool isFromBlock = false;
            for(int n = 0; n < dotsCount; n++){
              if(fallDotsY[i]+1 == oldDotsY[n] && fallDotsX[i] == oldDotsX[n]){
                isFromBlock = true;
                break;
              }  
            }
            if(!isFromBlock){
              for(i++; i<dotsCount; i++){
                matrix[fallDotsY[i]][fallDotsX[i]] = 1;
              }
              enableGenerationForNewBlock();
            }  
          }
        }else{
          if(matrix[0][2] == 1 || matrix[0][3] == 1 || matrix[0][4] == 1){
            ended = true;
            start = false;
            delayCounter = 0;
            controlCounter = 0;
            clearMatrix(); 
          }else{
            enableGenerationForNewBlock();
          }
          
        }
      }
      
      if(fallDotsY[i]==7){  
        enableGenerationForNewBlock();
      }
      
      if(fallingBlock){
        fallDotsY[i] = fallDotsY[i] + 1;
      }
      
    }
    
    //Обработване на сигналите подавани от джойстика
    
  }    
}
