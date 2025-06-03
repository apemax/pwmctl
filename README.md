# pwmctl

## WARNING: This software can turn your computers fans off and potentially cause your system to overheat, Which can cause damage to your hardware. Please only use this software if you know what you are doing.

pwmctl is a small command line program made to control the speed of the fans in your computer.

Currently pwmctl needs to be run as root or using sudo as it writes to files in the /sys/class/hwmon/ directory. Listing the hwmon devices present on your system does not require pwmctl to be run as root or using sudo.

## Usage

pwmctl [-lh]
pwmctl [-f] fan-path [-mp] number

Options:

-l   List all hwmon devices and connected fans.

-f   Select which fan to control.

-m   Set the mode for the selected fan.

-p   Set pwm value for selected fan.

-v   Display the version number of pwmctl.

-h   Display the help information.

Example:

Enable manual mode for pwm1:

~~~
pwmctl -f /sys/class/hwmon/hwmon1/pwm1 -m 1
~~~

Set pwm1 speed to 100:

~~~
pwmctl -f /sys/class/hwmon/hwmon1/pwm1 -p 100
~~~


## Building

To compile, clone the pwmctl repo:

~~~
git clone https://github.com/apemax/pwmctl.git
~~~

Then cd into the pwmctl directory and run make:

~~~
cd pwmctl
make
~~~