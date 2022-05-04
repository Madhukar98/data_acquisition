
const int sampleTime = 50; 

unsigned int a, b, c, d;
void setup() {
  Serial.begin(230400);
}

void loop() {
   unsigned long startTime= millis();
    
    unsigned int PTPAmp1 =0,maxAmp1=0,minAmp1=1023;
    unsigned int PTPAmp2 =0,maxAmp2=0,minAmp2=1023;
    unsigned int PTPAmp3 =0,maxAmp3=0,minAmp3=1023;
    unsigned int PTPAmp4 =0,maxAmp4=0,minAmp4=1023;
    
    
    while(millis() - startTime < sampleTime){
    
    a = analogRead(A0); // 000000aaaaaaaaaa
    b = analogRead(A1); // 000000bbbbbbbbbb
    c = analogRead(A2); // 000000cccccccccc
    d = analogRead(A3); // 000000dddddddddd

      if(a<1023){
        if(a>maxAmp1){maxAmp1 = a;}
        else if(a<minAmp1){minAmp1 = a;}    
      }

      if(b<1023){
        if(b>maxAmp2){maxAmp2 = b;}
        else if(b<minAmp2){minAmp2 = b;}    
      }

      if(c<1023){
        if(c>maxAmp3){maxAmp3 = c;}
        else if(c<minAmp3){minAmp3 = c;}    
      }

      if(d<1023){
        if(d>maxAmp4){maxAmp4 = d;}
        else if(d<minAmp4){minAmp4 = d;}    
      }
    }
    Serial.print(maxAmp1 - minAmp1);
    Serial.print(",");
    Serial.print(maxAmp2 - minAmp2);
    Serial.print(",");
    Serial.print(maxAmp3 - minAmp3);
    Serial.print(",");
    Serial.print(maxAmp4 - minAmp4);
    Serial.print("\n");    
}
