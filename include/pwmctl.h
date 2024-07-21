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

#include <iostream>

#ifndef PWMCTL_H
#define PWMCTL_H

void hwmon_list();
void set_pwm(std::string pwm_fan, std::string pwm_value);
void set_pwm_mode(std::string pwm_fan, std::string pwm_mode_value);

#endif //PWMCTL_H