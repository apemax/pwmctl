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
#include "pwmctl.h"

void hwmon_list()
{
  std::filesystem::path root_hwmon_dir{"/sys/class/hwmon"};

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

        if (is_symlink(hwmon_dir_entry.path()))
        {
          std::filesystem::path hwmon_dir_new;

          hwmon_dir_new = read_symlink(hwmon_dir_entry.path());
        }

        if (hwmon_dir_entry.path().filename() == pwm_filename)
        {
          std::cout << hwmon_dir_entry.path().string() << std::endl;
        }
      }
    }
  }
}

void set_pwm(std::string pwm_fan, std::string pwm_value)
{
  std::ofstream pwm_file(pwm_fan, std::ios::out);

  pwm_file << pwm_value;
}

void set_pwm_mode(std::string pwm_fan, std::string pwm_mode_value)
{
  pwm_fan.append("_enable");

  std::ofstream pwm_file(pwm_fan, std::ios::out);

  pwm_file << pwm_mode_value;
}