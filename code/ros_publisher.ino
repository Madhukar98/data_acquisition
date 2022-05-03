#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>
std_msgs::String pub_msg;
std_msgs::Int32 v1_msg;
std_msgs::Int32 v2_msg;
std_msgs::Int32 v3_msg;
std_msgs::Int32 v4_msg;

ros::NodeHandle nh;
// Connect the MEMS AUD output to the Arduino A0 pin
int mic0 = A0,mic1=A1,mic2=A2,mic3=A3;


// Variables to find the peak-to-peak amplitude of AUD output
const int sampleTime = 50; 
int micOut[4];

//previous VU value
int preValue[] = {0,0,0,0}; 

ros::Publisher pub("myTopic", &pub_msg);
ros::Publisher pub1("value1", &v1_msg);
ros::Publisher pub2("value2", &v2_msg);
ros::Publisher pub3("value3", &v3_msg);
ros::Publisher pub4("value4", &v4_msg);

void setup() {
  nh.initNode();
  nh.advertise(pub);
  nh.advertise(pub1);
  nh.advertise(pub2);
  nh.advertise(pub3);
  nh.advertise(pub4);
  
  Serial.begin(9600);
}

void loop() {
   // Time variables to find the peak-to-peak amplitude
   unsigned long startTime= millis();  // Start of sample window
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

   String s = "", s1;

  for(int i=0;i<4;i++){
      PTPAmp[i] = maxAmp[i] - minAmp[i]; // (max amp) - (min amp) = peak-to-peak amplitude
//      Serial.print(PTPAmp[i]);
//      Serial.print(" ");

      s1 = String(PTPAmp[i]);
      s1 = String(s1 + " ");

      s = String(s + s1);
  }

  v1_msg.data= PTPAmp[0];
  v2_msg.data= PTPAmp[1];
  v3_msg.data= PTPAmp[2];
  v4_msg.data= PTPAmp[3];
  pub1.publish(&v1_msg);
  pub2.publish(&v2_msg);
  pub3.publish(&v3_msg);
  pub4.publish(&v4_msg);
//  char ch_arr[4] = {PTPAmp[0], PTPAmp[1], PTPAmp[2], PTPAmp[3]}; 
//  //String(z) = ch_arr; // these two line are from internet
//
//  // Method-1
//  pub_msg.data = ch_arr;
//  pub.publish(&pub_msg);

  

  /* Method - 2
  String(val) = ch_arr;
  val.toCharArray(ch_arr, 30);
  pub_msg.data = ch_arr;
  pub.publish(&pub_msg);*/
  
   Serial.println(" ");

   delay(30);
   nh.spinOnce();
}
