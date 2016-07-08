 int pinA = 3;  //Connected to CLK pin
 int pinB = 4;  // Connected to DT pin
 int encoderPosCount = 0;  // Determine position of encoder. Encoder completes full rotation after 30 clicks 
 int pinALast;  
 int aVal;
 boolean bCW;

 void setup() { 
   pinMode (pinA,INPUT);
   pinMode (pinB,INPUT);
 
   pinALast = digitalRead(pinA);   
   Serial.begin (115200);
 } 

 void loop() { 
   aVal = digitalRead(pinA);
   if (aVal != pinALast){ // Means the knob is rotating
     // if the knob is rotating, we need to determine direction
     // We do that by reading pin B.
     if (digitalRead(pinB) != aVal) {  // Means pin A Changed first - We're Rotating Clockwise
       encoderPosCount ++;
       bCW = true;
     } else {// Otherwise B changed first and we're moving CCW
       bCW = false;
       encoderPosCount--;
     }
     Serial.print ("Rotated: ");
     if (bCW){
       Serial.println ("clockwise");
     }else{
       Serial.println("counterclockwise");
     }
     Serial.print("Encoder Position: ");
     Serial.println(encoderPosCount);
     
   } 
   pinALast = aVal;
 } 

