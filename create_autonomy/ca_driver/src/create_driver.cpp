/**
Software License Agreement (BSD)
\file      create_driver.cpp
\authors   Jacob Perron <jacobmperron@gmail.com>
\copyright Copyright (c) 2015, Autonomy Lab (Simon Fraser University), All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
 * Neither the name of Autonomy Lab nor the names of its contributors may
   be used to endorse or promote products derived from this software without
   specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/
#include "ca_libraries/ca_libraries.h"
#include <tf/transform_datatypes.h>
#include <string>

using namespace std;

int main(int argc, char** argv)
{
  ros::init(argc, argv, "ca_driver");
  ros::NodeHandle nh;

  CreateDriver create_driver(nh);

  //ustawianie znakow na wyswietlaczu
  ros::Publisher Set_Text_ = nh.advertise<std_msgs::UInt8MultiArray>("set_ascii", 30);
  std_msgs::UInt8MultiArray screen;
  //numery znaków ASCII
  screen.data.push_back(95);
  screen.data.push_back(95);
  screen.data.push_back(95);
  screen.data.push_back(95);
  ros::Rate(200);
  Set_Text_.publish(screen);
  ros::spinOnce();

  Move_ = nh.advertise<geometry_msgs::Twist>("cmd_vel", 30);
  geometry_msgs::Twist msg;
  msg.linear.x = 0;
  msg.angular.z = 0;
  Move_.publish(msg);
  ros::spinOnce();

  ros::Subscriber Odometry_ = nh.subscribe("odom", 10, OdometryCallBack);
  //aby odczytać potrzeba zmiennej typu nav_msgs::Odometry msg
  //odczytuje się je w CallBack i tam można przypisać do zmiennej globalnej
  //np x=msg->pose.pose.position.x;
  //   z=msg->pose.pose.orientation.z;

  //zapalanie niebieskiej diody debris
  ros::Publisher Set_BlueLED_ = nh.advertise<std_msgs::Bool>("debris_led", 10);
  /*
  std_msgs::Bool BlueLED_status;
  BlueLED_status.data = true;
  Set_BlueLED_.publish(BlueLED_status);
  */

  //zapalanie diody POWER na czerwono
  ros::Publisher Set_PowerLED_ = nh.advertise<std_msgs::UInt8MultiArray>("power_led", 30);
  std_msgs::UInt8MultiArray PowerLED_status;
  PowerLED_status.data.push_back(255);
  Set_PowerLED_.publish(PowerLED_status);

  //nieudana próba nauczenia i odtworzenia piosenki
  ros::Publisher Define_song_ = nh.advertise<ca_msgs::DefineSong>("define_song", 10);
  ca_msgs::DefineSong song1;
  song1.song = 0;
  song1.length = 2;
  /*
  song1.notes[0] = 32;
  song1.notes[1] = 56;
  song1.notes[2] = 32;

  song1.durations[0] = 64;
  song1.durations[1] = 64;
  song1.durations[2] = 64;

  Define_song_.publish(song1);

  ros::Publisher Play_song_ = nh.advertise<ca_msgs::PlaySong>("play_song", 10);
  ca_msgs::PlaySong Song_number;
  Song_number.song = 0;
  */

  //wywolanie funkcji z plik.h wyswietlajacej w terminalu "Dzialam."
  Dzialam();

  try
  {
    create_driver.spin();
  }
  catch (std::runtime_error& ex)
  {
    ROS_FATAL_STREAM("[CREATE] Runtime error: " << ex.what());
    return 1;
  }
  return 0;
}
