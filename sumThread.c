#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
//sum computed by backgruond thread
struct sum_runner_struct
{
  long long limit;
  long long answer;
};
/* thread function sums 0 to N */
void* sum_runner(void* arg)
{
  //cast the void
  struct sum_runner_struct *arg_struct = (struct sum_runner_struct*) arg;
  long long sum = 0;
  for (long long i = 0; i <= arg_struct->limit; i++)
  {
    sum += i;
  }//end for sum
  
  arg_struct->answer = sum;
  //sum is global var so threads can access
  pthread_exit(0);//exit
}//end thread runner

int main(int argc, char **argv)
{
  if (argc < 2)
  {
    printf("Usage: %s <num 1> <num 2> ...<num -n>\n", argv[0]);
    exit(-1);
  }//end if wrong num args
  int num_args = argc - 1;//arg count minus name of file 

   struct sum_runner_struct args[num_args];
 //thread id
 pthread_t tids[num_args];


 for (int i = 0; i < num_args; i++)
 {
   args[i].limit = atoll(argv[i + 1]);
   //create attributes
   pthread_attr_t attr;
   pthread_attr_init(&attr);
   pthread_create(&tids[i], &attr, sum_runner, &args[i]);
 }//
 
  //could do other work here...
 //dont exit immediately.. wait till thred works
 for (int i = 0; i < num_args; i++)
 {
   pthread_join(tids[i], NULL);
   printf("Sum for thread %d is %lld\n",i, args[i].answer);//long long decimal
 }

}//end main
