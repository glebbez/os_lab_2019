#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mut_1, mut_2;

void *process1()
{
    printf("\nProcess A is using x");
    pthread_mutex_lock(&mut_1);
        sleep(1);
        printf("\nProcess A wants to use y"); 
        pthread_mutex_lock(&mut_2);

        printf("\nProcess A can use y now");    
        pthread_mutex_unlock(&mut_2);   
		
    pthread_mutex_unlock(&mut_1);  
     
return 0;
}

void *process2()
{
    printf("\nProcess B is using y");
    pthread_mutex_lock(&mut_2);
    
        sleep(1);
        
        printf("\nProcess B wants to use x"); 
        pthread_mutex_lock(&mut_1);

        printf("\nProcess B can use x now");    
        pthread_mutex_unlock(&mut_1);  
		
    pthread_mutex_unlock(&mut_2);  
     
return 0;

}

int main(){
    
    pthread_t threads[2];

    pthread_create(&threads[0], NULL, process1, NULL);
    pthread_create(&threads[1], NULL, process2, NULL);
    
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);

    return 0;
}