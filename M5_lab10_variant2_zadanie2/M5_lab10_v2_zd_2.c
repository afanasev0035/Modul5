#include <pthread.h>
#include <sys/types.h> 
#include <sys/stat.h> 
#include <wait.h> 
#include <fcntl.h> 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#define column 3
#define string 3


struct DATA{
	int matrix [column];
	int vector [column];
};
typedef struct DATA Data;

struct {
    pthread_mutex_t mutex;
    int buff[string];
    int nput;
}   shared = {
    PTHREAD_MUTEX_INITIALIZER
};

void *produce (void *arg)
{   
    Data* a = (Data*)arg;   
   
   pthread_mutex_lock(&shared.mutex);
    for (int i = 0; i < column; i++)
    {
        shared.buff[shared.nput] = shared.buff[shared.nput]  + a->matrix[i] * a->vector[i];
    }
    pthread_mutex_unlock(&shared.mutex);
    shared.nput++;
}

void *consume(void *arg){
    printf("Резульат:\n");
	for (int i = 0; i <= (string-1); i++)
    {   for(;;)
        {   
            pthread_mutex_lock(&shared.mutex);
            if (i < shared.nput) 
            {
		        printf("[%d]=%d\n", i,  shared.buff[i]);
			    pthread_mutex_unlock(&shared.mutex);
			    break;
            }
            //printf("Waiting %d element\n",i);
            pthread_mutex_unlock(&shared.mutex);    
        }
    }
}

int main(int argc, char * argv[])
{
    int matrix [column][string];
    int vector [column];
    Data data[string];
    pthread_t tid_produce[string], tid_consume;
       
    printf("Матрица: и Вектор:\n");

    for (int i = 0; i < string; i++)
    {
        vector [i] = i + 1;
        for (int j = 0; j < column; j++)
        {
            matrix[i][j] = i * 2 + j + 1;
            printf("%d ", matrix[i][j]);
        }
        printf("     %d ", vector[i]);
        printf("\n");
    }
       
    for (int i = 0; i < string; i++)
    {   
        for (int j = 0; j < column; j++)
        {
            data[i].vector[j] = vector[j];
            data[i].matrix[j] = matrix[i][j];
            
        }
    pthread_create(&tid_produce[i], NULL, produce, &data[i]);    
    }

    pthread_create(&tid_consume, NULL, consume, NULL);

    for (int i = 0; i < string; i++)
    {
	pthread_join(tid_produce[i], NULL);
    }

    pthread_join(tid_consume, NULL);
    
    exit(0);
}


