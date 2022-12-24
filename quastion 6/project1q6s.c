 #include <stdio.h>
 #include <stdlib.h>
 #include <pthread.h>

 int array[100];

 void readfile(char * file_name) {
   char ch;
   FILE * fp;
   fp = fopen(file_name, "r");

   if (fp == NULL) {
     perror("Error while opening the file.\n");
     exit(EXIT_FAILURE);
   }

   char line[5];

   int j = 0;
   fputs(file_name, stdout);
   printf("\n\n");
   while (fgets(line, sizeof line, fp) != NULL) {
     if (j < 100) {
       array[j] = atoi(line);
     }
     j++;
   }

   fclose(fp);
 }

 struct numbers {
   int sum;
   int avg;
 };

 struct numbers numbers[2];
 pthread_t tid[2];
 void * sum(void * arg) {
   struct numbers * numbers = (struct numbers * ) arg;
   for (int i = 0; i < 100; i++) {
     numbers -> sum = numbers -> sum + array[i];
   }
   return NULL;
 }

 void * avg(void * arg) {
   struct numbers * numbers = (struct numbers * ) arg;
   for (int i = 0; i < 100; i++) {
     numbers -> avg = numbers -> avg + array[i];
   }
   numbers -> avg = numbers -> avg / 100;
   return NULL;
 }
 int main(int argc, char * argv[]) {
   int i = 0;
   if (argc != 2) {
     fprintf(stderr, "usage: a.out <file name>\n");
     return -1;
   }

   readfile(argv[1]);
   numbers[0].sum = 0;
   pthread_create( & tid[0], NULL, sum, & numbers[0]);
   numbers[1].avg = 0;
   pthread_create( & tid[1], NULL, avg, & numbers[1]);
   pthread_join(tid[0], NULL);
   pthread_join(tid[1], NULL);

   printf("[1]Thread -> sum: %d", numbers[0].sum);
   printf("[2]Thread -> avg: %d", numbers[1].avg);

   return 0;
 }

