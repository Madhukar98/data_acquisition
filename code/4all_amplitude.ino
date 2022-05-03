
// Connect the MEMS AUD output to the Arduino A0 pin
int mic0 = A0,mic1=A1,mic2=A2,mic3=A3;

// Variables to find the peak-to-peak amplitude of AUD output
const int sampleTime = 5; 
int micOut[4];

//previous VU value
int preValue[] = {0,0,0,0}; 

void setup() {
  Serial.begin(115200);
}

void loop() {
   // Time variables to find the peak-to-peak amplitude
   unsigned long startTime= millis();  // Start of sample window
   //Serial.println(startTime);
   unsigned int PTPAmp[] = {0,0,0,0};

// Signal variables to find the peak-to-peak amplitude
   unsigned int maxAmp[] = {0,0,0,0};
   unsigned int minAmp[] = {1023,1023,1023,1023};

// Find the max and min of the mic output within the 50 ms timeframe
   while(millis() - startTime < sampleTime) 
   {
      micOut[0] = analogRead(mic0);
      micOut[1] = analogRead(mic1);
      micOut[2] = analogRead(mic2);
      micOut[3] = analogRead(mic3);
      //Serial.println(micOut);
      for(int i=0;i<4;i++){
        if( micOut[i] < 1023) //prevent erroneous readings
        {
          if (micOut[i] > maxAmp[i])
          {
            maxAmp[i] = micOut[i]; //save only the max reading
          }
          else if (micOut[i] < minAmp[i])
          {
            minAmp[i] = micOut[i]; //save only the min reading
          }
        }
      }
   }

  for(int i=0;i<4;i++){
      PTPAmp[i] = maxAmp[i] - minAmp[i]; // (max amp) - (min amp) = peak-to-peak amplitude
      if(PTPAmp[i]>2000){PTPAmp[i]=0;}
      Serial.print(PTPAmp[i]);
      Serial.print(" ");
  }
   Serial.println(" ");
}
