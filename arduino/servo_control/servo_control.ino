#include <Arduino.h>
#include <Servo.h>
#include <ros.h>
#include <std_msgs/Float64MultiArray.h>

#define JOINT0 8
#define JOINT1 9
#define JOINT2 10

Servo servo_joint0;
Servo servo_joint1;
Servo servo_joint2;
void servo_cb( const std_msgs::Float64MultiArray& msg )
{
  const float min = 0;
  const float range = 180;
  float angle0 = msg.data[0];
  float angle1 = msg.data[1];
  float angle2 = msg.data[2];
  
  if( angle0 > 1 ) angle0 = 1;
  if( angle0 < 0 ) angle0 = 0;
  if( angle1 > 1 ) angle1 = 1;
  if( angle1 < 0 ) angle1 = 0;
  if( angle2 > 1 ) angle2 = 1;
  if( angle2 < 0 ) angle2 = 0;
  
  servo_joint0.write(min + (range * angle0));
  servo_joint1.write(min + (range * angle1));
  servo_joint2.write(min + (range * angle2));
}

ros::Subscriber<std_msgs::Float64MultiArray> sub("/servo_actuator", servo_cb );
ros::NodeHandle nh;

void setup()
{
  // set the attached pin of each joint
  servo_joint0.attach(JOINT0);
  servo_joint1.attach(JOINT1);
  servo_joint2.attach(JOINT2);
  // set an initial value for all the joints
  servo_joint0.write(90);
  servo_joint1.write(90);
  servo_joint2.write(90);
  // cerate and initialize a ROS node that subscibes the topic /servo_actuator
  nh.initNode();
  nh.subscribe(sub);
}

void loop()
{
  nh.spinOnce();
  delay(1); 
}
