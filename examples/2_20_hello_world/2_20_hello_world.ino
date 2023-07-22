#include <PT6314.h>

#define SER 11
#define ST 8
#define CLK 13

PT6314 vfd(CLK, ST, SER);

void setup()
{
  vfd.begin(20, 2, 0);
  vfd.home();
  vfd.print("Hello World");
}


void loop()
{
}
