#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[] = "example.txt";
    char ch;

    // open file for writing
    file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return EXIT_FAILURE;
    }

    // write some text to the file
    fprintf(file, "Hello, World!\n");
    fprintf(file, "This is a test file.\n");

    // close the file
    fclose(file);

    // open file for reading
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return EXIT_FAILURE;
    }

    // read and display the content of the file
    printf("Contents of %s:\n", filename);
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    // close the file
    fclose(file);

    return EXIT_SUCCESS;
}