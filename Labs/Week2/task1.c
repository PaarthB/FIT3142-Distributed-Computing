#include <stdio.h>
#include <stdbool.h>

int main(){
   int i;
   bool yes = true;
   for (i = 0; i < 5; i++){
      printf("%d\n", i);
   }

   while (yes){
      printf("true\n");
      yes = false;
   }

  return 0;

}
