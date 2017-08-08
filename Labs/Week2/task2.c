#include <stdio.h>
#include <stdbool.h>

int main()
{
   bool yes = true;
   int i = 0;
   if (i == 0)
   {
       i++;
       printf("%d\n", i);
   }
   if (i == 1)
   {
       //i++;
       printf("%d\n", i);
   }

   if (i == 2)
   {
       i++;
       printf("%d\n", i);
   }
      

   switch (i)
   {
        case 3:
            printf("if and switch working fine\n");
            break;
        default:
            printf("Some error\n");
            break;
   }

    return 0;
}
