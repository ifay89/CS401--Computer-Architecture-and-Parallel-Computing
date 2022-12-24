 #include <stdio.h>
 #include <stdlib.h>
 #include <pthread.h>

 int array[3000];
 void testSum()
 {
   int sum = 0;
   int j;
   for (j = 0; j < 3000; j++){
     sum += array[j];
   }
   printf("Testing without threads, (sum): \n%d \n", sum);
 }
 
 void readfile(char * file_name) {
   char ch;
   FILE * fp;
   fp = fopen(file_name, "r");
    
   if (fp == NULL) {
     perror("Error while opening the file.\n");
     exit(EXIT_FAILURE);
   }
   
   char line[5];
   int i = 0;
   printf("Reading file: ");
   fputs(file_name, stdout);
   printf("\n");
   while (fgets(line, sizeof line, fp) != NULL)
   {
     if (i < 3000)
     array[i] = atoi(line);
     i++;
   }
   printf("Sucessfully read %d numbers\n", i);
   fclose(fp);
   printf("Reading file Complete, integers stored in array.\n\n");
 }

 struct numbers {
   int index;
   int sum;
 };
 struct numbers numbers[6];
 pthread_t tid[6];
 void * sum(void * arg) {
   struct numbers * numbers = (struct numbers * ) arg;
   int i = 0;
   for (i = numbers -> index; i < (numbers -> index + 500); i++) {
     numbers -> sum = numbers -> sum + array[i];
   }
   return NULL;
 }
 
 
 int main(int argc, char * argv[]) {
   int thrd = 0;
   int total = 0;
   if (argc != 2)
   {
     fprintf(stderr, "usage: a.out <file name>\n");
     return -1;
   }
   
   readfile(argv[1]);
   while(thrd < 6)
   {
   	numbers[thrd].index = (thrd * 500);
   	numbers[thrd].sum = 0;
   	while (pthread_create( & tid[thrd], NULL, sum, & numbers[thrd]));
   	thrd++;
   }
   
   int i = 0;
   while(i < 6)
   {
   	pthread_join(tid[i], NULL);
   	i++;
   }
   
   int j = 0;
   while(j < 6)
   {
   printf("Thread %d (sum) :\n %d\n", j + 1, numbers[j].sum);
   total = total + numbers[j].sum;
   j++;
   }
   printf("\ntotal of (sum) is:\n %d\n", total);
   testSum();
   return 0;
 }
