#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  if(argc != 3 ) {
  fprintf(stderr,  "Wrong number of arguments given");
  exit(1);
  }

  char* arg1 = argv[1];
  char* arg2 = argv[2];
  
  int checkForNull = 0;
  while(arg1[checkForNull] != '\0' && arg2[checkForNull] != '\0')
    {
      checkForNull++;
    }
   if((arg1[checkForNull] == '\0' && arg2[checkForNull] != '\0') || (arg1[checkForNull] != '\0' && arg2[checkForNull] == '\0'))
    {
      fprintf(stderr, "Not a one-to-one mapping of arguments");
      exit(1);
    }
	 int noSameChar = 1;
	 int inc = 0;
	 int inc2 = 1;
	 while(arg1[inc] != '\0')
	   {
	     inc2 = inc +1;
	     while(arg1[inc2] != '\0')
	       {
		 if(arg1[inc] == arg1[inc2])
		   {
		     noSameChar = 0;
		   }
		 inc2++;
	       }
	     inc++;
	   }
	 if(noSameChar == 0)
	   {
	     fprintf(stderr, "Argument one contains duplicates");
	     exit(1);
	   }

	 char buffer;
	 while(read(0, &buffer, 1) > 0)
	   {
	     int i = 0;
	     int mapped = 0; /* Change to 1 if there was a mapping */
	     while(arg1[i] != '\0')
	       {
		 if(buffer == arg1[i])
		   {
		     write(1, arg2+i, 1);
		     mapped = 1;
		   }
		 i++;
	       }
	     if (mapped == 0)
	       {
		 write(1, &buffer, 1); 
	       }
	   }


	 
}
