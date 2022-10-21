//ros part
#include <ros.h>
#include <std_msgs/Int64.h>
ros::NodeHandle n;
std_msgs::Int64 count_msg;
ros::Publisher encoder_pub ("counts", &count_msg); 
// encoder part
unsigned long angle_L = 0;
unsigned long angle_R = 0;
int A =19;
int B =18;
int EN=17;//ENABLE PIN OF DRIVER
int input_1=16;//?
int input_2=15;
long long count=0;
void ISR_A (void);
void ISR_B (void);
HardwareSerial serial1(PB7, PB6);
void setup() {
  n.initNode();
  n.advertise(encoder_pub);
  serial1.begin(115200);
  pinMode(A,INPUT_PULLUP); 
  pinMode(B,INPUT_PULLUP);
  pinMode(EN,OUTPUT); 
  pinMode(input_1,OUTPUT);
  pinMode(input_2,OUTPUT);
  attachInterrupt(A,ISR_A,CHANGE);
  attachInterrupt(B,ISR_B,CHANGE);
}

void loop() {
serial1.println(count);
count_msg.data = count;
encoder_pub.publish( &count_msg );
n.spinOnce();
delay(100);
}
void ISR_A(void){
 if(digitalRead(A)!= digitalRead(B))
  count++;
  else
  count--;
  }
void ISR_B(void){
  if(digitalRead(A) == digitalRead(B))
  count++;
  else
  count--;
  }
