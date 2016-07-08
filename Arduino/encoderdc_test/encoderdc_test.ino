 int pinA = 3;  // Connected to CLK on KY-040
 int pinB = 4;  // Connected to DT on KY-040
 int encoderPosCount = 0;  //To determine the position of encoder
 int pinALast;  
 int aVal;

 void setup() { 
   pinMode (pinA,INPUT);
   pinMode (pinB,INPUT);
   /* Read Pin A
   Whatever state it's in will reflect the last position   
   */
   pinALast = digitalRead(pinA);   
   Serial.begin (115200);
 } 

 void loop()
 { 
   aVal = digitalRead(pinA);
   if (aVal != pinALast)
   { // Means the knob is rotating
     // if the knob is rotating, we need to determine direction
     // We do that by reading pin B.
     if (digitalRead(pinB) != aVal) {  // Means pin A Changed first - We're Rotating Clockwise
       encoderPosCount ++;
       Serial.print("clockwise    ");
       Serial.println(encoderPosCount);
       // Speed control of DC motor
       if (encoderPosCount>0 && encoderPosCount<15)  
       {
       analogWrite(9,100);    // CW rotation of DC motor
       analogWrite(10,0);
       delay(2000);
       analogWrite(9,0);
       analogWrite(10,0);
       delay(1000);
       }
       if (encoderPosCount>=15 && encoderPosCount<30)
       {
       analogWrite(9,150);    // CW rotation of DC motor
       analogWrite(10,0);
       delay(2000);
       analogWrite(9,0);
       analogWrite(10,0);
       delay(1000);
       }
       if (encoderPosCount<0)
       {
       analogWrite(9,50);  // CW rotation of DC motor
       analogWrite(10,0);
       delay(2000);
       analogWrite(9,0);
       analogWrite(10,0);
       delay(1000);
       }
     } 
     else {// Otherwise B changed first and we're moving CCW
       encoderPosCount--;
       Serial.print("counterclockwise  ");
       Serial.println(encoderPosCount);
       if (encoderPosCount>=-15 && encoderPosCount<0)
       {
       analogWrite(9,0);    //CCW rotation of DC motor
       analogWrite(10,100);
       delay(2000);
       analogWrite(9,0);
       analogWrite(10,0);
       delay(1000);
     }
     if (encoderPosCount>-30 && encoderPosCount<-15)
     {
      analogWrite(9,0);       //CCW rotation of DC motor
       analogWrite(10,150);
       delay(2000);
       analogWrite(9,0);
       analogWrite(10,0);
       delay(1000);
     }
     if (encoderPosCount>0)
     {
      analogWrite(9,0);       //CCW rotation of DC motor
       analogWrite(10,50);
       delay(2000);
       analogWrite(9,0);
       analogWrite(10,0);
       delay(1000);
     }
   } 
   }
   pinALast = aVal;
 }

