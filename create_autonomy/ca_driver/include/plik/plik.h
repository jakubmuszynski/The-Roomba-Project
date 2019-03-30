#ifndef PLIK_PLIK_H
#define PLIK_PLIK_H

#include "create_driver/create_driver.h"
#include <tf/transform_datatypes.h>
#include <string>

using namespace std;

//flagi do ruchow utawiane w publishButtonPresses
bool przod = 0;
bool lewo = 0;
//info: przycisk "MINUTE" chyba fizycznie nie dziala

//flagi do sekwencji 1
bool s1 = 0;
bool s1_przod = 0;

ros::Publisher Move_; //wysyła komendę do poruszania

void Dzialam()
{
  cout<<"Dzialam."<<endl;
}

void Stop(ros::NodeHandle nh)
{
  Move_ = nh.advertise<geometry_msgs::Twist>("cmd_vel", 30);
  geometry_msgs::Twist msg;
  msg.linear.x = 0;
  msg.angular.z = 0;
  Move_.publish(msg);
  ros::spinOnce();
}

void Set_PowerLED(ros::Publisher PowerLED_)
{
  std_msgs::UInt8MultiArray PowerLED_status;
  PowerLED_status.data.push_back(255); //kolor czerwony
  PowerLED_.publish(PowerLED_status);
}

void Set_BlueLED(ros::Publisher BlueLED_)
{
  std_msgs::Bool BlueLED_status;
  BlueLED_status.data = true;
  BlueLED_.publish(BlueLED_status);
}

void Set_Screen(ros::Publisher Text_)
{
  std_msgs::UInt8MultiArray screen;
  //numery znaków ASCII
  screen.data.push_back(95);
  screen.data.push_back(95);
  screen.data.push_back(95);
  screen.data.push_back(95);
  ros::Rate(200);
  Text_.publish(screen);
  ros::spinOnce();
}

#endif
