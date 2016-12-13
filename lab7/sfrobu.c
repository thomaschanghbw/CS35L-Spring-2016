#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

int comparisons = 0;

int frobcmp(char const* a, char const* b)
{
  comparisons++;
  int i = 0;
  while(a[i] != ' ' && b[i] != ' ')
    {
  int first = a[i] ^ 42;
  int second = b[i] ^ 42;
  int result = 0;

  //special cases to prevent overflow
  if(first<0 && second>0)
    {
      result = -1;
      return result;
    }
  if(first>0 && second <0)
    {
      result = 1;
      return result;
    }
  result = first - second;
  if(result!=0)
    return result;
  i++;
  }
  if (a[i]==' ' && b[i] != ' ')
    return -1;
  if (a[i] != ' ' && b[i] == ' ')
    return 1;
  else return 0;
}

int frobcmp2(const void*  a, const void * b)
{
  char const * aa = *(char const **)a;
  char const * bb = *(char const **)b;
  return frobcmp(aa, bb);
}

void addToBuffer(char c,char** buffer,int *bufferSize, int *numInBuffer,
		 int* rightAfterSpace, int* numInSize, int* size, char** words)
{

  if(*numInBuffer == *bufferSize)
    {
      int tester = 2 * (*bufferSize);
           *buffer = (char*) realloc(*buffer,tester);
      if (*buffer == NULL){
	fprintf(stderr, "Realloc Error");
	exit(1);
      }
      (*bufferSize) *= 2;
   
            int inc = 0;
       while(inc < *numInSize)
      	{
	  if(inc==0)
	    words[inc] = *buffer;
	  else{
	    words[inc] = *buffer+(size[inc]-1);}
	  inc++;
      	}
    }
  *((*buffer)+(*numInBuffer))= c;
  (*numInBuffer)++;
  if(c==' ') {
    *rightAfterSpace =1;
  }
   //  printf("%c", buffer[(*numInBuffer)-1]);
}

void addPointer(char*** words,char* buffer,int* wordsSize,int* numInWords,int* numInBuffer)
{
  if(*numInWords == *wordsSize)
    {
      *words = (char**)realloc(*words, 2*(*wordsSize)*sizeof(char*));
      if (*words == NULL){
	fprintf(stderr, "Realloc Error");
	exit(1);
      }
      (*wordsSize) *= 2;
    }
  *((*words)+(*numInWords)) = &buffer[(*numInBuffer)-1];
  (*numInWords)++;
}

void addSize(int *currentSize, int** size, int *sizeSize, int* numInSize)
{
  if(*numInSize == *sizeSize)
    {
      *size = (int*)realloc(*size, 2*(*sizeSize)*sizeof(int));
      if (*size == NULL){
	fprintf(stderr, "Realloc Error");
	exit(1);
      }
      (*sizeSize) *= 2;
    }
  *((*size)+(*numInSize)) = *currentSize;
  (* numInSize)++;
}
int main(int argc, char* argv[])
{
  if(argc > 1)
    {
      fprintf(stderr, "Too Many Arguments");
      exit(1);
    }

  struct stat filestats;
  fstat(0, &filestats);
  int filesize = filestats.st_size;
  char* buffer;

  int bufferSize;
  int numInBuffer;
  int wordsSize;
  int numInWords;
  int currentSize;
  int sizeSize;
  int numInSize;
  char** words;
  int* size;
  
  if(!S_ISREG(filestats.st_mode))
    {
  buffer = (char*)malloc(10);
  if (buffer == NULL){
    fprintf(stderr, "Malloc Error");
    exit(1);
  }
  bufferSize = 10;
  numInBuffer =0;
  
 
  words = (char**)malloc(10*sizeof(char*));
  if (words == NULL){
    fprintf(stderr, "Malloc Error");
    exit(1);
  }
  wordsSize = 10;
  numInWords =0;

 
  size = (int*)malloc(sizeof(int));
  if (size == NULL){
    fprintf(stderr, "Malloc Error");
    exit(1);
  }
  currentSize = 0;
  sizeSize = 1;
  numInSize=0;
    }


  
  if(S_ISREG(filestats.st_mode))
    {
      
      buffer = (char*)malloc(filesize);
  if(buffer == NULL) {
    fprintf(stderr, "Malloc Error");
    exit(1);
  }
  bufferSize = filesize;
  numInBuffer = 0;

    words = (char**)malloc(filesize * sizeof(char*));
  if(words == NULL) {
    fprintf(stderr, "Malloc Error");
    exit(1);
  }
 wordsSize = filesize;
  numInWords = 0;

  
  size = (int*)malloc(sizeof(int) * filesize);
  if(words == NULL) {
    fprintf(stderr, "Malloc Error");
    exit(1);
  }
  currentSize = 0;
  sizeSize = filesize;
  numInSize=0;
    }

  
  //Update every time a value is put into words.
  int numOfRecords = 0;
  char c;
  //Functions as a boolean. Only point to the character if it equals 1
  int rightAfterSpace = 1;
  //Get rid of any opening spaces
  //c =getchar();  
  //read(0, &c, 1);
  //while(c == ' ')
    // {
      // c =getchar();
      //read(0, &c, 1);
      //   }
  while(read(0, &c, 1) >0){ 
	//	c!=EOF){
      //read(0, &c, 1) >0){
    addToBuffer(c, &buffer, &bufferSize, &numInBuffer, &rightAfterSpace, &numInSize, size, words);
    currentSize++;
    if(rightAfterSpace && c != ' ')
     {
    	addPointer(&words,buffer, &wordsSize, &numInWords, &numInBuffer);
    	addSize(&currentSize, &size, &sizeSize, &numInSize);
    	rightAfterSpace = 0;
     }
    //c = getchar();
    //    read(0, &c, 1);
  }
if(ferror(stdin))
    {
      fprintf(stderr, "Reading from file failed");
      exit(1);
    }
  //If no space at end of file, add it to the buffer manually
  if(buffer[numInBuffer-1] != ' ')
    addToBuffer(' ', &buffer, &bufferSize, &numInBuffer, &rightAfterSpace, &numInSize, size, words);
  qsort(words, numInWords, sizeof(char**), frobcmp2);

    int j =0;
    int k=0;
    while(j<numInWords)
      {
        k=0;
        while(k<numInBuffer && words[j][k] != ' ')
  	{
	  // printf("%c", words[j][k]);
  	  write(1, &words[j][k], 1);
  	  k++;
  	}
	char space = ' ';
	write(1, &space, 1);
	//	printf("%c", ' ');
    j++;
      }
  //Free allocated memory
  free(words);
  free(buffer);
  fprintf (stderr, "Comparisons: %d\n", comparisons);
}
