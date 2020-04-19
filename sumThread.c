#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
//sum computed by backgruond thread
long long sum = 0;

/* thread function sums 0 to N */
void* sum_runner(void* arg)
{
  //cast the void
  long long *limit_ptr = (long long*) arg;
  long long limit = *limit_ptr;

  for (long long i = 0; i <= limit; i++)
  {
    sum += i;
  }//end for sum

  //sum is global var so threads can access
  pthread_exit(0);//exit
}//end thread runner

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    printf("Usage: %s <num>\n", argv[0]);
    exit(-1);
  }//end if wrong num args
  
  long long limit = atoll(argv[1]);

 //thread id
 pthread_t tid;

 //create attributes
 pthread_attr_t attr;
 pthread_attr_init(&attr);

 pthread_create(&tid, &attr, sum_runner, &limit);
  //could do other work here...
 //dont exit immediately.. wait till thred works
 pthread_join(tid, NULL);
 printf("Sum is %lld\n",sum);//long long decimal

}//end main
