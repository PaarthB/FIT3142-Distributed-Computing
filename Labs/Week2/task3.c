#include <stdio.h>
#include <stdlib.h>

int main()
{
   int count = 0;
   FILE *read;
   char ch,next;
   read = fopen("word.txt", "r");
   while ((ch=fgetc(read)) != EOF)
   {
       if (ch == ' ' || ch == '\n'){           
	   count++;
	   while((next = fgetc(read)) == ' ' || next == '\n'){}

       }
   }

   printf("Number of words: %d\n", count);
   return 0;
}
