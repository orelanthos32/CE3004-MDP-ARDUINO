/*
 * 
34 5 6
2[][][]
 [][][]
1[][][]

Short Sensor - 1,2,3,5,6
Long Sensor - 4

*/ 

float readIR1Cali() {
  float arr[20] = {};
  int i;
  for(i=0; i<20; i++){
    arr[i] = analogRead(irR1);
  }
  float middle = median(arr, 20);
  return 5284.293 / middle - 4.76315 ;
}
float readIR2Cali() {
  float arr[20] = {};
  int i;
  for(i=0; i<20; i++){
    arr[i] = analogRead(irR2);
  }
  float middle = median(arr, 20);
  return 5235.695 / middle- 6.27884 ;
}
float readIR3Cali() {
  float arr[20] = {};
  int i;
  for(i=0; i<20; i++){
    arr[i] = analogRead(irR3);
  }
  float middle = median(arr, 20);
  return 6058.366 / middle -5.56352 ;
}
float readIR5Cali() {
  float arr[20] = {};
  int i;
  for(i=0; i<20; i++){
    arr[i] = analogRead(irR5);
  }
  float middle = median(arr, 20);
  return 7594.868 / middle -6.27884 ;
}
float readIR6Cali() {
  float arr[20] = {};
  int i;
  for(i=0; i<20; i++){
    arr[i] = analogRead(irR6);
  }
  float middle = median(arr, 20);
  return 4428.176/ middle -4.97369 ;
}





float readIR1() {
  float arr[20] = {};
  int i;
  for(i=0; i<20; i++){
    arr[i] = analogRead(irR1);
  }
  float middle = median(arr, 20);
  return 5878.029417/ middle - 5.803099434 ;
}


float readIR2() {
  float arr[20] = {};
  int i;
  for(i=0; i<20; i++){
    arr[i] = analogRead(irR2);
  }
  float middle = median(arr, 20);
  return 6095.253552 / middle -8.913739151;
}

 
float readIR3() {
  float arr[20] = {};
  int i;
  for(i=0; i<20; i++){
    arr[i] = analogRead(irR3);
  }
  float middle = median(arr, 20);
  return 6103.836767 / middle -5.83038484;
}


float readIR4() {
  float arr[20] = {};
  int i;
  for(i=0; i<20; i++){
    arr[i] = analogRead(irR4);
  }
  float middle = median(arr, 20);
  if (middle <= 490){
    return (600 - middle)/10;
    }
  return 14195.40269/middle - 18.893932;
}

float readIR5() {
  float arr[20] = {};
  int i;
  for(i=0; i<20; i++){
    arr[i] = analogRead(irR5);
  }
  float middle = median(arr, 20);
  return 5818.93871/middle- 4.488938716;
}

float readIR6() {
  float arr[20] = {};
  int i;
  for(i=0; i<20; i++){
    arr[i] = analogRead(irR6);
  }
  float middle = median(arr, 20);
  return 4559.963287/middle -4.511744752;
}


void checkRawValues (){

    Serial.println("X"+String(readIR1())+";"
                      +String(readIR2())+";"
                      +String(readIR3())+";"
                      +String(readIR4())+";"
                      +String(readIR5())+";"
                      +String(readIR6())
                 );
//        Serial.println("X"+String(median(irArr1,irsampleSize))+";"
//                      +String(median(irArr2,irsampleSize))+";"
//                      +String(median(irArr3,irsampleSize))+";"
//                      +String(median(irArr4,irsampleSize))+";"
//                      +String(median(irArr5,irsampleSize))+";"
//                      +String(median(irArr6,irsampleSize)));
       
  }

//CheckList
float navIR5 (){
return readIR5();
  }

float navIR1 (){
return readIR1();
  }

 


//collects samples for ir Array
//void irSamples(int maxnum) {
//  for (int i = 0; i < maxnum; i++) {
//    irArr1[i] = analogRead(irR1);
//    irArr2[i] = readIR2();
//    irArr3[i] = readIR3();
//    irArr4[i] = readIR4();
//    irArr5[i] = readIR5();
//    irArr6[i] = readIR6();
//    delay(5);
//  }
//}
///////////////////////////////////////////////////////////////
/*Sorting*/

float median(float nums[], int n) {
  int k = n % 2 == 0 ? n / 2 : n / 2 + 1;
  return qselect(nums, 0, n - 1, k - 1);
}

float qselect(float A[], int start, int end, int k) {
  if (start == end) {
    return A[start];
  }

  int left = start, right = end;
  int index = (left + right) / 2;
  float pivot = A[index];

  while (left <= right) {
    while (left <= right && A[left] > pivot) {
      left++;
    }

    while (left <= right && A[right] < pivot) {
      right--;
    }

    if (left <= right) {
      float tmp = A[left];
      A[left] = A[right];
      A[right] = tmp;

      left++;
      right--;
    }
  }

  if (k >= start && k <= right) {
    return qselect(A, start, right, k);
  }
  if (k >= left && k <= end) {
    return qselect(A, left, end, k);
  }
  return A[right + 1];
}



///////////////////////////////////////////////////////////////////

// Obstacle Avoidance

// ============= MOVEMENT =============
// void rightTest(){
//   for(int i =0; i<20; i++){
//     move(convertRightAngleToTicks(90), DIRECTION_RIGHT);
//     delay(2000);
//   }
// }

// void leftTest(){
//   for(int i =0; i<20; i++){
//     move(convertLeftAngleToTicks(90), DIRECTION_LEFT);
//     delay(2000);
//   }
// }

// ============= CHECKLIST OBSTACLE AVOIDANCE =============


void navObs(double ticks, const int direction[2]) 
{
    resetGlobalConstants();
    double pid = 0;


    md.setSpeeds((SPEED + pid) * direction[0]  , (SPEED - pid) * direction[1]);
    
    while (m1Ticks <= ticks)
    {   
        veryClose();
        
        if (deltaM1Ticks > 10)
        {
            computeDelta();
            pid = computePID();
            md.setSpeeds((SPEED + pid) * direction[0]  , (SPEED - pid) * direction[1]);
            // Serial.println("printing number of ticks");
            // Serial.println(deltaM1Ticks);
            // Serial.println(m1ticks);
                     
        }
    

        
        delay(1);     
    }
    md.setBrakes(400, 400);


    delay(70);

    
}


void veryClose(){
  
  if(navIR5() <= 10 && detect_obs == false){
    Serial.println("detected");
    detect_obs = true;
    obstacleInfront();
  }
  else if(detect_obs==true&&navIR5() <= 10) md.setBrakes(400, 400);
}


void obstacleInfront(){

  move(convertLeftAngleToTicks(90), DIRECTION_LEFT);
  Serial.println("Right 45 degrees!");
  delay(500);
  move(convertDistanceToTicks(20),  DIRECTION_FORWARD);
  Serial.println("Onwards!");
  move(convertRightAngleToTicks(90), DIRECTION_RIGHT);
   Serial.println("Goes along obstacle!");
   move(convertDistanceToTicks(35),  DIRECTION_FORWARD);

  
   Serial.println("Distance from left cam :"+String(navIR1()));


  while(navIR1() <= 15){

     delay(100);
     move(convertDistanceToTicks(10),  DIRECTION_FORWARD);
     Serial.println("Going Along !");

      //irLB = navIR1();
    //  Serial.println("Distance from left cam :"+String(navIR1()));
           
    }

   move(convertRightAngleToTicks(90), DIRECTION_RIGHT);

  Serial.println("Left 45 degrees!");
  delay(500);
 move(convertDistanceToTicks(20),  DIRECTION_FORWARD);
  Serial.println("Onwards!");
 
     move(convertLeftAngleToTicks(90), DIRECTION_LEFT);
while(1){if(navIR5() > 5){move(convertDistanceToTicks(10),  DIRECTION_FORWARD);delay(500);Serial.println("works");}else {md.setBrakes(400, 400);break;Serial.println("test");}}
//move(convertDistanceToTicks(15),  DIRECTION_FORWARD);

  Serial.println("Obstacle avoided!");

 
    Serial.println("100 finish");

 /*int estShort(float reading) {
  if (reading < 9.5) {
    return 1; 
  }
  else if (reading < 19) {
    return 2; 
  }
  else if (reading <= 30) {
    return 3;  
  }
  else {
    return 0;
  }
  */
     
   }
