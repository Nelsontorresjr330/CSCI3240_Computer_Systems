#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <pthread.h>

using namespace std;

#define NUM_OF_THREADS 2

int counts[NUM_OF_THREADS];
int iter=0;
pthread_mutex_t counts_mutex;

struct thread_data{
    int thread_id;
    string message;
};

void* count_from_file(void *threadarg){

   struct thread_data *my_data;
   my_data = (struct thread_data *) threadarg;

    ifstream file1; file1.open(my_data->message);

    string s1;
    char ch = 'a';
 
    int count1 = 0;

    while(!file1.eof()){

        if(file1.eof()){
            break;
        }

        file1 >> s1;

        if(file1.eof()){
            break;
        }
        
        count1 += count(s1.begin(),s1.end(),ch);
    }

    pthread_mutex_lock(&counts_mutex);

    counts[iter] = count1;
    iter = iter + 1;

    pthread_mutex_unlock(&counts_mutex);

    pthread_exit(NULL);
}

int main (int argc, char **argv){

    if (argc < 3 ){
        cout << "Include file names in command line!" << endl;
        return 0;
    }

    pthread_t threads[NUM_OF_THREADS];
    pthread_attr_t attr;

    pthread_mutex_init(&counts_mutex, NULL);
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    struct thread_data td[NUM_OF_THREADS];
    int rc;

    for(int i = 0; i < NUM_OF_THREADS; i++) {
        //cout <<"main() : creating thread, " << i << endl;
        td[i].thread_id = i;
        td[i].message = argv[i + 1];
        rc = pthread_create(&threads[i], NULL, count_from_file, (void *)&td[i]);
        if (rc) {
             cout << "Error:unable to create thread," << rc << endl;
             exit(-1);
        }
   }

    for(int i = 0; i < NUM_OF_THREADS; i++){
           pthread_join(threads[i],NULL);
    }

    cout << argv[1] << ": " << counts[0] << endl;
    cout << argv[2] << ": " << counts[1] << endl;

    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&counts_mutex);
    pthread_exit(NULL);
    
    return 0;
}