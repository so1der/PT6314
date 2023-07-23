#include <PT6314.h>

#define SI 11
#define STB 8
#define SCK 13

PT6314 vfd(SCK, STB, SI);

void setup()
{
  vfd.begin(20, 2, 100);
  vfd.home();
  vfd.print("Hello World");
}


void loop()
{
}
