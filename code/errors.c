#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
int main(void) {
    // 1. Program will try to open non-existent file and cause
    // an error stored in errno global value
    FILE *f = fopen("non_existent", "r");
    if (f == NULL) {
        // perror describes error that is saved in errno
        perror("fopen() failed");
        // or we can print errno value directly
        fprintf(stderr, "errno value: %s\n", strerror(errno));

        // We can check errno value against defined constants
        // defined in errno.h
        // ENOENT means "No such file or directory"
        // EACCES means "Permission denied"
        // ENOMEM means "Not enough space"
        // EINVAL means "Invalid argument"
        if (errno == ENOENT) {
            fprintf(stderr, "File does not exist\n");
        }
        else if (errno == EACCES) {
            fprintf(stderr, "No permission to open file\n");
        }
        else if (errno == ENOMEM) {
            fprintf(stderr, "Not enough space\n");
        }
        else if (errno == EINVAL) {
            fprintf(stderr, "Invalid argument\n");
        }
        else {
            fprintf(stderr, "Some other error\n");
        }


        // EXIT_FAILURE is interpeted as an error by OS
        exit(EXIT_FAILURE);
    } else {
        fclose(f);
    }

    // 2. Some simple example of checking
    // and printing in stderr stream
    if (0.1 + 0.2 != 0.3){
        fprintf(stderr, "0.1 + 0.2 != 0.3\n");
        exit(EXIT_FAILURE);
    }

    // 3. Assert looks like in Java
    // but it will give no explanation of assertion
    // failure, just "Abort (core dumped)"
    char* filename = NULL;
    assert(filename != NULL);

    return EXIT_SUCCESS;
}