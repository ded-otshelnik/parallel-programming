#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N 100000

int main() {
    int num_threads;

    // simple parallel region
    #pragma omp parallel
    {
        #pragma omp single
        num_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        printf("Hello from thread %d out of %d threads\n", thread_id, num_threads);
    }

    int *array = (int *)malloc(N * sizeof(int));
    for (int i = 0; i < N; i++) {
        // fill the array with values 1 to 10
        array[i] = i % 10 + 1;
    }

    long long sum = 0;

    // first approach with critical section (or atomic operation)
    #pragma omp parallel
    {
        long long private_sum = 0;
        #pragma omp for
        for (int i = 0; i < N; i++) {
            private_sum += array[i];
        }

        #pragma omp atomic
        sum += private_sum;
    }

    printf("Sum: %lld\n", sum);


    // second approach with reduction
    sum = 0;
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < N; i++) {
        sum += array[i];
    }

    printf("Sum: %lld\n", sum);

    free(array);


    // time measurement example
    double start_time = omp_get_wtime();
    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        // simulate some work
        for (int j = 0; j < 1000; j++);
    }
    double end_time = omp_get_wtime();
    printf("Elapsed time: %f seconds\n", end_time - start_time);

    // parallel sections example
    #pragma omp parallel sections
    {
        #pragma omp section
        {
            printf("Section 1 executed by thread %d\n", omp_get_thread_num());
        }
        #pragma omp section
        {
            printf("Section 2 executed by thread %d\n", omp_get_thread_num());
        }
        #pragma omp section
        {
            printf("Section 3 executed by thread %d\n", omp_get_thread_num());
        }
    }


    // master and single example
    #pragma omp parallel
    {
        #pragma omp master
        {
            printf("Master thread %d\n", omp_get_thread_num());
        }
        #pragma omp single
        {
            printf("Single thread %d\n", omp_get_thread_num());
        }
        #pragma omp sections
        {
            #pragma omp section
            {
                printf("Section 1 executed by thread %d\n", omp_get_thread_num());
            }
            #pragma omp section
            {
                printf("Section 2 executed by thread %d\n", omp_get_thread_num());
            }
            #pragma omp section
            {
                printf("Section 3 executed by thread %d\n", omp_get_thread_num());
            }
        }
    }

    // lock example
    omp_lock_t lock;
    omp_init_lock(&lock);
    int counter = 0;

    #pragma omp parallel for
    for (int i = 0; i < 10000; i++) { 
        omp_set_lock(&lock);
        counter++;
        omp_unset_lock(&lock);
    }

    omp_destroy_lock(&lock);
    printf("Counter: %d\n", counter);

    // nested parallel regions
    omp_set_nested(1);
    #pragma omp parallel
    {
        int thread_id = omp_get_thread_num();
        #pragma omp parallel
        {
                int nested_thread_id = omp_get_thread_num();
                printf("Outer thread %d, Inner thread %d\n", thread_id, nested_thread_id);
        }
    }
     // disable nested parallelism
    omp_set_nested(0);

    // task example
    #pragma omp parallel
    {   
        // here only master thread creates tasks
        #pragma omp master
        {   
            // taskgroup ensures that all tasks are completed before proceeding
            #pragma omp taskgroup
            {
                #pragma omp task
                {
                    printf("Task 1 executed by thread %d\n", omp_get_thread_num());
                }
                #pragma omp task
                {
                    printf("Task 2 executed by thread %d\n", omp_get_thread_num());
                }
                #pragma omp task
                {
                    printf("Task 3 executed by thread %d\n", omp_get_thread_num());
                }
            }
        printf("All tasks completed\n");
        }
    }

    // advantage of tasks when number of tasks is not known in advance

    while (1) {
        int rand_num = rand() % 10;
        if (rand_num == 0) {
            break;
        }
        #pragma omp taskgroup
        {   
            printf("Processing ");
            #pragma omp task firstprivate(rand_num)
            {
                printf("number %d in thread %d\n", rand_num, omp_get_thread_num());
            }
            #pragma omp task
            {
                // simulate some processing
                sleep(1);
            }
        }
    }

    int *list = (int *)calloc(100, sizeof(int));
    for (int i = 0; i < 100; i++) {
        list[i] = i;
    }
    
    // example of task usage: list processing
    printf("List processing with tasks:\n");

    #pragma omp parallel
    {
        #pragma omp master
        {
            for (int i = 0; i < 100; i++) {
                #pragma omp task firstprivate(i)
                {
                    // simulate some processing
                    printf("Processing item %d in thread %d\n", i, omp_get_thread_num());

                    // example processing: squaring the index
                    list[i] = i * i;
                }
            }
        }
    }

    // the same example with for
    printf("List processing with parallel for:\n");    
    #pragma omp parallel for schedule(dynamic)
    for (int i = 0; i < 100; i++) {
        /// simulate some processing
        printf("Processing item %d in thread %d\n", i, omp_get_thread_num());
        // simulate time-consuming task
        // example processing: squaring the index
        list[i] = i * i;
    }

    free(list);

    // linked list processing with tasks
    struct list_node {
        int value;
        struct list_node *next;
    };

    struct list_node *head = (struct list_node *)malloc(sizeof(struct list_node));
    head->value = 0;
    head->next = NULL;

    struct list_node *current = head;
    for (int i = 1; i < 10; i++) {
        struct list_node *new_node = (struct list_node *)malloc(sizeof(struct list_node));
        new_node->value = i;
        current->next = new_node;
        current = new_node;
    }

    printf("Linked list processing with tasks:\n");
    #pragma omp parallel
    {
        #pragma omp master
        {
            struct list_node *node = head;
            while (node != NULL) {
                #pragma omp task firstprivate(node)
                {
                    // simulate some processing
                    printf("Processing node with value %d in thread %d\n", node->value, omp_get_thread_num());
                    // example processing: squaring the value
                    node->value = node->value * node->value;
                }
                node = node->next;
            }
        }
    }
    return 0;
}