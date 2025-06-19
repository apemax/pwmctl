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

#include <fstream>
#include <filesystem>
#include <set>
#include <thread>
#include <chrono>
#include "pwmctl.h"

void hwmon_list()
{
  std::filesystem::path root_hwmon_dir{"/sys/class/hwmon"};
  std::set<std::filesystem::path> pwm_sorted;
  std::set<std::filesystem::path> fan_sorted;

  for (auto const& root_hwmon_dir_entry : std::filesystem::directory_iterator{root_hwmon_dir})
  {
    for (auto const& hwmon_dir_entry : std::filesystem::directory_iterator{root_hwmon_dir_entry})
    {
      for (int i = 1; i <= 10; i++)
      {
        std::string pwm_filename = "pwm";
        std::string pwm_number;

        pwm_number = std::to_string(i);
        pwm_filename.append(pwm_number);

        if (hwmon_dir_entry.path().filename() == pwm_filename)
        {
          pwm_sorted.insert(hwmon_dir_entry.path().string());
        }
      }
      for (int i = 1; i <= 10; i++)
      {
        std::string pwm_filename = "pwm";
        std::string pwm_number;

        pwm_number = std::to_string(i);
        pwm_filename.append(pwm_number);
        pwm_filename.append("_enable");

        if (hwmon_dir_entry.path().filename() == pwm_filename)
        {
          pwm_sorted.insert(hwmon_dir_entry.path().string());
        }
      }
      for (int i = 1; i <= 10; i++)
      {
        std::string fan_filename = "fan";
        std::string fan_number;

        fan_number = std::to_string(i);
        fan_filename.append(fan_number);
        fan_filename.append("_input");

        if (hwmon_dir_entry.path().filename() == fan_filename)
        {
          fan_sorted.insert(hwmon_dir_entry.path().string());
        }
      }
    }
  }
  for (auto &pwm_file_path : pwm_sorted)
  {
    if (pwm_file_path.string().size() == 28)
    {
      std::ifstream pwm_file(pwm_file_path.string());
      std::string pwm_file_output;

      std::cout << pwm_file_path.string() << std::endl;

      getline(pwm_file, pwm_file_output);

      std::cout << " PWM Value: " << pwm_file_output << std::endl;
    }

    for (unsigned int position = 0; position < pwm_file_path.string().size(); position++)
    {
      if (pwm_file_path.string().substr(position, 7) == "_enable")
      {
        std::ifstream pwm_enable_file(pwm_file_path.string());
        std::string pwm_enable_output;

        getline(pwm_enable_file, pwm_enable_output);

        std::cout << " PWM Mode: " << pwm_enable_output << std::endl;

        for (auto &fan_file_path : fan_sorted)
        {
          if (fan_file_path.string().substr(22, 1) == pwm_file_path.string().substr(22, 1) && fan_file_path.string().substr(27, 1) == pwm_file_path.string().substr(27, 1))
          {
          std::ifstream fan_input_file(fan_file_path.string());
          std::string fan_input_output;

          getline(fan_input_file, fan_input_output);

          std::cout << " Fan RPM: " << fan_input_output << std::endl;
          }
        }
      }
    }
  }
}

void set_pwm(std::string pwm_fan, std::string pwm_value)
{
  std::string pwm_enable_file_name = pwm_fan;
  pwm_enable_file_name.append("_enable");

  std::ifstream pwm_enable_file(pwm_enable_file_name);
  std::string pwm_enable_file_output;

  getline(pwm_enable_file, pwm_enable_file_output);

  if (pwm_enable_file_output == "1")
  {
    std::ofstream pwm_file(pwm_fan, std::ios::out);

    if (pwm_file.is_open())
    {
      pwm_file << pwm_value;

      std::cout << "Waiting 5 seconds for fan speed to change..." << std::endl;

      std::this_thread::sleep_for(std::chrono::seconds(5));

      for (unsigned int position = 0; position < pwm_fan.size(); position++)
      {
        if (pwm_fan.substr(position, 3) == "pwm")
        {
          std::string fan_input_path = pwm_fan;
          fan_input_path.replace(24, 3, "fan");
          fan_input_path.append("_input");

          std::ifstream fan_input_file(fan_input_path);
          std::string fan_input_output;

          getline(fan_input_file, fan_input_output);

          std::cout << "Fan RPM: " << fan_input_output << std::endl;
        }
      }
    }
    else
    {
      std::cout << "Error: Unable to write to pwm file." << std::endl;
      std::cout << "Please make sure the specified pwm file exists and that you have run pwmctl as root or with sudo." << std::endl;
    }
  }
  else
  {
    std::cout << "Warning: Unable to set fan speed, PWM Mode not set to manual." << std::endl;
  }
}

void set_pwm_mode(std::string pwm_fan, std::string pwm_mode_value)
{
  pwm_fan.append("_enable");

  std::ofstream pwm_file(pwm_fan, std::ios::out);

  pwm_file << pwm_mode_value;
}