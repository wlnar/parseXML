#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/stat.h>

int getFileSize(char*);
char* readData(char*, char*, int);
void printArchDetails(void);

int main(int argc, char **argv) {
  int fileSize;
  int i, j, c;
  char *fileName;
  char *data;

 /* parse command line options
  */
  while ((c=getopt(argc,argv,"f:")) != -1) {
    switch (c) {
      case 'f':
        fileName = optarg;
        break;
      case '?':
        printf("\nWelcome to the generic xml parser!\n");
        return 1;
      default:
        abort();
    }
  }


 /* get file size
  */
  fileSize = getFileSize(fileName);

  printf("fileName[%s]\nfileSize[%d]\n", fileName, fileSize);


 /* allocate memory & read data into local array 
  */
  data = (char*) malloc(fileSize); 
  data = readData(data, fileName, fileSize);


 /* print rule ID & name
  */
  for (i=0; i<fileSize; i++) {
    if ((data[i] == '<') && (data[i+1] != '/')) {
      j = i;
      printf("\n");
      while ((data[j] != ' ') && (data[j] !='>')) {
        printf("%c", data[j]);
        j++;
      }
    }

  }

  i = 6;
  j = 354;
  c = 12432;

  int *p;
  p = &i;

  int *k;
  k = &j;
  
  int **arr = malloc(48);
  arr[0] = &p;
  arr[1] = &k;

  int **arr2 = malloc(24);
  arr2[0] = &p;
  arr2[2] = &k;


  printArchDetails();

  return 0;
}


char* readData(char *data, char *fileName, int fileSize) {
  FILE *fp;
  int i=0;

  fp = fopen(fileName, "r");
  if (fp) {
    for (i=0; i<fileSize; i++) {
      data[i]=fgetc(fp);
    }
    fclose(fp);
  }
  return data;
}


int getFileSize(char *fileName) {
  int size;
  struct stat st;
  if(stat(fileName, &st) != -1) {
    size=st.st_size;
  } else {
    size=-1;
  }
  return size;
}

void printArchDetails() {
  int num = 1;
  if (*(char*)&num == 1) {
    printf("\nLittle Endian");
  } else {
    printf("\nBig Endian");
  }
  printf("\nsizeof(int)=%d", sizeof(int));
  printf("\nsizeof(int*)=%d", sizeof(int*));
  printf("\nsizeof(int**)=%d", sizeof(int**));
  printf("\nsizeof(char)=%d", sizeof(char));
  printf("\nsizeof(char*)=%d", sizeof(char*));
  printf("\nsizeof(char**)=%d", sizeof(char**));
  printf("\n");

}
