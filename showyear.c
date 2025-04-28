int sys_showyear(void){
return 2025;
}

#include "types.h"
#include "user.h"

int main(void) {
  int year = showyear();
  printf(1, "The current year is %d\n", year);
  exit();
}

