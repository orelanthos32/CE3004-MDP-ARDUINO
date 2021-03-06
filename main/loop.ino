/*
Control command send to serial port:

prefix: 'f' -> move forward
        'b' -> move backward
        'l' -> trun left
        'r' -> turn right

siffix: distance in cm or degreee in °


eg,
      f100 -> move forward 100cm
      b40  -> move back 40cm
      l70  -> turn left 70°
      r60  -> turn right 60°

*/




char cmd ='#';
String inString = "";  // string to hold input
int distance = 0;


//Direction Information
//const int DIRECTION_FORWARD[2] = {1, -1};
//const int DIRECTION_BACKWARD[2] = {-1, 1};
//const int DIRECTION_LEFT[2] = {1, 1};
//const int DIRECTION_RIGHT[2] = {-1, -1};


void loopReading(){

 
  while (Serial.available() > 0) {
    if (cmd != '#'){
      int inChar = Serial.read();
      if (isDigit(inChar)) {
        // convert the incoming byte to a char and add it to the string:
        inString += (char)inChar;
      }
      // if you get a newline, print the string, then the string's value:
      if (inChar == '\n') {

        Serial.print("Value:");
        Serial.println(inString.toInt());
        distance = inString.toInt();
        switch(cmd){
          case 'f':{ //Simple Move Forward for exploration
            if (distance > 10)
            {
              movewithfeedback(convertDistanceToTicks(distance),  DIRECTION_FORWARD);
            }
            else
            {
              move(convertDistanceToTicks(distance),  DIRECTION_FORWARD, false);
            }
            Serial.println("Xdone");
            break;
          }
          case 't':{ //Move forward for fastest path
            move(convertDistanceToTicks(distance),  DIRECTION_FORWARD, false);
            Serial.println("Xdone");
            break;
          }
          case 'T':{ //Move forward for fastest path at faster speed
            moveWithSpeed(convertDistanceToTicks(distance),  DIRECTION_FORWARD, 360);
            Serial.println("Xdone");
            break;
          }
          case 'F':{ //Move forward at diagnal for fastest path at faster speed
            moveWithSpeed(convertDiagDistanceToTicks(distance),  DIRECTION_FORWARD, 360);
            Serial.println("Xdone");
            break;
          } 
          case 'b':{ //Move backwardfor fastest path at faster speed
            moveWithSpeed(convertDistanceToTicks(distance),   DIRECTION_BACKWARD, 360);
            Serial.println("Xdone");
            break;
          }
          case 'B':{ //Move backward at diagnal for fastest path at faster speed
            moveWithSpeed(convertDiagDistanceToTicks(distance),   DIRECTION_BACKWARD, 360);
            Serial.println("Xdone");
            break;
          }
          case 'l':{
            move(convertLeftAngleToTicks(distance), DIRECTION_LEFT, false);
            Serial.println("Xdone");
            
            break;
          }
          case 'r':{
            move(convertRightAngleToTicks(distance), DIRECTION_RIGHT, false);
            Serial.println("Xdone");
            break;
          }

          case 's':{
            checkRawValues ();
            break;
          }
          
          case 'm':{
            checkRawValuesCali ();
            break;
          }

          case 'p':{
            caliLeft();
            Serial.println("Xdone");
            break;
          }
         
          case 'n':{
            caliNew();
            Serial.println("Xdone");
            break;
          }
          case 'e':{
            caliEdge();
            Serial.println("Xdone");
            break;
          }
           case 'u':{
            caliLeftBack();
            Serial.println("Xdone");
            break;
          }
          case 'x':{
            movetillwall(false);
            caliFront();
            Serial.println("Xdone");
            break;
          }
           case 'X':{
            movetillwall(true);
            caliFront();
            Serial.println("Xdone");
            break;
          }
          case 'o':{
            caliFront();
            Serial.println("Xdone");
            break;
          }          
          case 'g':{
            glideforwarddistance(convertDistanceToTicks(distance));
            Serial.println("Xdone");
            break;
         }
         case 'G':{
            glideforwarddistance_faster(convertDistanceToTicks(distance), 360);
            Serial.println("Xdone");
            break;
         }
         case 'h':{
            glidebackwarddistance(convertDistanceToTicks(distance));
            Serial.println("Xdone");
            break;
         }
         case 'H':{
            glidebackwarddistance_faster(convertDistanceToTicks(distance), 360);
            Serial.println("Xdone");
            break;
         }
         case 'j':{
            glideforwardtillwall_exp();
            Serial.println("Xdone");
            break;
         }
         case 'J':{
            glideforwardtillwall_exp_faster(360);
            Serial.println("Xdone");
            break;
         }
         case 'k':{
            glideforwardtillwall_fp();
            caliFront();
            Serial.println("Xdone");
            break;
         }
         case 'K':{
            glideforwardtillwall_fp_faster(360);
            caliFront();
            Serial.println("Xdone");
            break;
         }
        }
       
        // clear the string for new input:
        cmd ='#';
        inString = "";  // string to hold input
        distance = 0;
        
      }
    }
    else {
      cmd = (char)Serial.read();
      
     
    }
    
  }
  Serial.flush();
  
  
}
