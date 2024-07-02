#include <Servo.h>

Servo servohori;  // horizontal servo (BOTTOM SERVO)
int servoh = 0;  // assign servo at 0 degree
int servohLimitHigh = 180;  // maximum range of servo is 180 degrees (variable, can be changed)
int servohLimitLow = 10;  // minimum range of servo is 10 degrees (variable, can be changed)

Servo servoverti;  // vertical servo (TOP SERVO)
int servov = 0;
int servovLimitHigh = 180;
int servovLimitLow = 10;

int ldrtopr = 1;  // top right LDR A1 pin
int ldrtopl = 3;  // top left LDR A3 pin

int ldrbotr = 0;  // bottom right LDR A0 pin
int ldrbotl = 2;  // bottom left LDR A2 pin

void setup() {
  servohori.attach(10);  // horizontal servo connected to Arduino pin 10
  servohori.write(0);
  servoh = servohori.read();
  servoverti.attach(9);  // vertical servo connected to Arduino pin 9
  servoverti.write(0);
  servov = servoverti.read();
  delay(500);  // delay
}

void loop() {
  int servoh = servohori.read();
  int servov = servoverti.read();
  
  int topl = analogRead(ldrtopl);  // read analog values from top left LDR
  int topr = analogRead(ldrtopr);  // read analog values from top right LDR
  int botl = analogRead(ldrbotl);  // read analog values from bottom left LDR
  int botr = analogRead(ldrbotr);  // read analog values from bottom right LDR

  int avgtop = (topl + topr) / 2;  // average of top LDRs
  int avgbot = (botl + botr) / 2;  // average of bottom LDRs
  int avgleft = (topl + botl) / 2;  // average of left LDRs
  int avgright = (topr + botr) / 2;  // average of right LDRs

  if (avgtop < avgbot) {
    servoverti.write(servov - 1);
    if (servov > servovLimitHigh) {
      servov = servovLimitHigh;
    }
    delay(8);
  }

  if (avgbot < avgtop) {
    servoverti.write(servov + 1);
    if (servov < servovLimitLow) {
      servov = servovLimitLow;
    }
    delay(8);
  }

  if (avgleft > avgright) {
    servohori.write(servoh - 1);
    if (servoh > servohLimitHigh) {
      servoh = servohLimitHigh;
    }
    delay(8);
  }

  if (avgright > avgleft) {
    servohori.write(servoh + 1);
    if (servoh < servohLimitLow) {
      servoh = servohLimitLow;
    }
    delay(8);
  }

  delay(50);
  if (avgright == 0 && avgleft == 0 && avgtop == 0 && avgbot == 0) {
    while (servoh > servohLimitLow) {
      servohori.write(servoh - 1);
    }
    while (servov > servovLimitLow) {
      servoverti.write(servov - 1);
    }
    delay(50000);
  }
}
