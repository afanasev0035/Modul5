#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <pthread.h>
#define column 3
#define string 3
#define x 3
struct DATA{
	int matrix [column];
	int vector [column];
};
typedef struct DATA Data;


void *multiplication (void *arg){
	Data* a = (Data*)arg;
	double *ps = (double*)malloc(sizeof(double)); 
	*ps = 0;
    for (int i = 0; i < column; i++)
    {
        *ps = *ps + a->matrix[i] * a->vector[i];
    }
	pthread_exit((void*)ps);
	
}

int main(int argc, char * argv[])
{
	int result;
    int matrix [column][string];
    int vector [column];
    Data data[string];
    pthread_t threads[string];
    void *status[column];
    
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
        result = pthread_create(&threads[i], NULL, multiplication, &data[i]);
        if (result != 0) {
			perror("Creating the first thread");
			return EXIT_FAILURE;
		}
    }
    printf("Резульат:\n");
    for (int i = 0; i < string; i++){
		result = pthread_join(threads[i], &status[i]);
		if (result != 0) {
			perror("Joining the first thread");
			return EXIT_FAILURE;
		} else {
			printf("[%d]=%d\n", i+1,  (int)*((double*)status[i]));
		}
		free(status[i]);
	}

	printf("Done..\n");
	return EXIT_SUCCESS;
  
}
