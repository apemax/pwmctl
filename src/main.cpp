/*
    This file is part of pwmctl.

    pwmctl is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    pwmctl is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with pwmctl.  If not, see <http://www.gnu.org/licenses/>.
*/
// Copyright (C) 2024 Peter Wright
// Author: Peter "apemax" Wright
// pwmctl

#include "pwmctl.h"

int main(int argc, char const *argv[])
{
  if(argc <= 1)
  {
    std::cout << "No options specified, Type -h for usage information." << std::endl;
  }
  else
  {
    std::string first_option = argv[1];
    if(first_option == "-h")
    {
      std::cout << "Usage:" << std::endl;
      std::cout << "pwmctl [-lh]" << std::endl;
      std::cout << "pwmctl [-f] fan-path [-mp] number" << std::endl;
      std::cout << std::endl;
      std::cout << "Options:" << std::endl;
      std::cout << "-l   List all hwmon devices and connected fans." << std::endl;
      std::cout << "-f   Select which fan to control." << std::endl;
      std::cout << "-m   Set the mode for the selected fan." << std::endl;
      std::cout << "-p   Set pwm value for selected fan." << std::endl;
      std::cout << "-h   Display this help." << std::endl;
      std::cout << std::endl;
      std::cout << "Example:" << std::endl;
      std::cout << "Enable manual mode for pwm1:" << std::endl;
      std::cout << "pwmctl -f /sys/class/hwmon/hwmon1/pwm1 -m 1" << std::endl;
      std::cout << "Set pwm1 speed to 100:" << std::endl;
      std::cout << "pwmctl -f /sys/class/hwmon/hwmon1/pwm1 -p 100" << std::endl;
    }
    else if(first_option == "-l")
    {
      //List all hwmon devices and connected fans.

      std::cout << "Detected hwmon devices:" << std::endl;

      hwmon_list();
    }
    else if(first_option == "-f")
    {
      //Set pwm value for selected hwmon device and fan.

      std::string first_option_value = argv[2];
      std::string second_option = argv[3];
      std::string second_option_value = argv[4];

      if(second_option == "-m")
      {
        set_pwm_mode(first_option_value, second_option_value);
      }
      else if(second_option == "-p")
      {
        set_pwm(first_option_value, second_option_value);
      }
    }
  }

  return 0;
}