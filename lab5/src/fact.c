#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/time.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>

#include <getopt.h>
#include <pthread.h>


pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;

struct args_calc
{
    int     start;
    int     end;
    int     mod;
    int*    res;
};

int sync_fact(int k, int mod){
    
    for(int i = k-1; i > 1; i--){
        k = (k*i);
    }
    return k%mod;    
}

void* thread_factorial(void* args_f)
{
    struct args_calc* af = (struct args_calc*)args_f;
    int start = af -> start;
    int end =   af -> end;
    int mod =   af -> mod;

    int work = start;

    for(int i = start + 1; i <= end; i ++)
    {
        work = work*i%mod;
    }
    pthread_mutex_lock(&mut);
    *(af -> res) = work;
    pthread_mutex_unlock(&mut);
};

int main(int argc, char **argv)
{
    int k = -1;
    int mod = -1;
    int pnum = -1;
    
    while (true)
    {        
       int current_optind = optind ? optind : 1;

        static struct option options[] = {
            {"k", required_argument, 0, 0},
            {"mod", required_argument, 0, 0},
            {"pnum", required_argument, 0, 0},
            {0, 0, 0, 0}
        };

        int option_index = 0;
        int c = getopt_long(argc, argv, "", options, &option_index);

        if (c == -1) break;
            switch (c) {
                case 0:
                    switch (option_index) {
                        case 0:
                        {
                            k = atoi(optarg);

                            if (k <= 0) {
                                printf("k is a positive number\n");
                                return 1;
                            }
                            break;
                        }
                        case 1:
                        {
                            mod = atoll(optarg);

                            if (mod <= 0) {
                                printf("mod is a positive number\n");
                                return 1;
                            }
                            break;
                        }
                        case 2:
                        {
                            pnum = atoi(optarg); 

                            if(pnum <= 0)
                            {
                                printf("pnum is a positive number\n");
                                return 1;
                            }
                            
                            break;
                        }
                         
                        default:
                            printf("Index %d is out of options\n", option_index);
                    }
                    break;
                  
                case '?':
                    break;

                default:              
                    printf("getopt returned character code 0%o?\n", c);
            }
    }

    if (optind < argc)
    {
        printf("Has at least one no option argument\n");
        return 1;
    }

    if (pnum > k/2){
        pnum /= 2;
    }

    
    pthread_t* threads = malloc(pnum*sizeof(pthread_t));    
    struct args_calc* ac = malloc(pnum * sizeof(struct args_calc));
        
    int status;
    int final_res = 1;
    int block = k / pnum;
        
    for(int i = 0; i < pnum; i++)
    {
        ac[i].start = block*i + 1;
        ac[i].mod = mod;
        ac[i].res = &final_res;    

        if(i+1 == pnum)
        {
            ac[i].end = block * (i+1) + k % pnum;
        }
        else
        {
            ac[i].end = block * (i+1);
        }    
        pthread_create( &threads[i], NULL, thread_factorial, &ac[i]);
    }
    
    for(int i = 0; i < pnum; i++)
    {
        pthread_join( threads[i], NULL);
    }

    printf("\nAsync Factorial %lld mod %lld = %llu\n", k, mod, final_res);
    printf("Sync Factorial %lld mod %lld = %llu\n", k, mod, sync_fact(k,mod));
    
    free(threads);
    free(ac);

    return 0;
}