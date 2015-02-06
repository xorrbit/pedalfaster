# pedalfaster

Project photos here: https://www.dropbox.com/sc/nccnrpblhtot4mf/AADt2ng0oxG0XzIYsRdLwDJ_a

A little Arduino project to monitor stationary cycling. It keeps track of the how long it takes to rotate the pedals and if this value is less than a specific threshold it will chirp a buzzer to let you know to pedal faster. I calibrated this with a heart trate tracker (fitbit charge HR) so that it beeps when my heart rate goes below 135 (which is the recommended cardio range for excersizing for my age).

This project was designed around an arduino duo with a lcd+button shield from dr robot. The pedal sensor is wired in to +5v on one pin and the other pin goes into D3 and through a pullup resistor to ground. The buzzer is wired to ground on one pin and A2 on the other.

The inter-pedal times in milliseconds are logged to the serial port so you can graph your cadence.

This uses the new liquidcrystal library from https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads.
