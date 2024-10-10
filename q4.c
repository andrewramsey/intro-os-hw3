    #include <pthread.h> 
    #include <stdio.h>
    #include <stdlib.h>

    #define NUM_THREADS 10 // The number of threads is 10
    #define NUMBERS_PER_THREAD 1000 // Num of ints that threads calculate sum of is 1000

    // Structure to pass data to threads 
    typedef struct 
    {
        int start;
        int end;
        long long sum;
    } ThreadData; 

    // Function that calculates sum in each thread
    void* calculate_sum(void* arg) // arg can pass any type of data as void*
    {
        ThreadData* data = (ThreadData*) arg; // Cast arg to ThreadData
        data->sum = 0; // Initializes sum to 0 for specific thread

        // Adds each index to sum
        for (int i = data->start; i <= data->end; i++) 
        {
            data->sum += i; 
        }

        printf("Sum from thread: %lld\n", data->sum); // I tried printing the thread id during this, but they run concurrently so there was no point

        return NULL;
    }

    int main() 
    {
        pthread_t threads[NUM_THREADS]; // Holds thread IDs
        ThreadData thread_data[NUM_THREADS]; // Holds data for each thread
        long long total_sum = 0;
        int start = 0;

        // Loop creates and launches threads
        for (int i = 0; i < NUM_THREADS; i++) {
            thread_data[i].start = start;
            thread_data[i].end = start + NUMBERS_PER_THREAD - 1;
            start += NUMBERS_PER_THREAD; // Changes start for the next thread

            if (pthread_create(&threads[i], NULL, calculate_sum, &thread_data[i]) != 0) // pthread_create returns 0 on success
            {
                perror("Failed to create thread");
                return 1;
            }
        }

        // Join threads and get total sum by adding data of threads
        for (int i = 0; i < NUM_THREADS; i++) {
            pthread_join(threads[i], NULL);
            total_sum += thread_data[i].sum;
        }

        printf("Sum from 0-9999: %lld\n", total_sum);

        return 0;
    }