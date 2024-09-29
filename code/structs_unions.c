#include <stdio.h>
#include <string.h>

// struct is a user defined data type
// that can hold multiple variables of different types
struct student{
    char* name;
    int course;
    double marks_average;
};
// typedef makes it easier to use the struct
// without using the keyword struct
typedef struct student Student;

// union is similar to struct but it shares the same memory
// location for all the variables
union student_union{
    char name[50];
    int course;
    double marks_average;
};

typedef union student_union StudentUnion;

// array of keywords and their counts
// that is stored in struct
struct key {
    char* word;
    int count;
} keytab[] = {
    "auto", 0,
    "break", 0,
    "case", 0,
    "char", 0,
    "const", 0,
    "continue", 0,
    "default", 0,
    "unsigned", 0,
    "void", 0,
    "volatile", 0,
    "while", 0
};

// we can also combine definitions
typedef struct point{
    int x;
    int y;
} Point;
typedef struct rectangle {
    Point p1;
    Point p2;
} Rectangle;

int main(){
    // standard initialization
    struct student s1;

    // initialization with values
    struct student s2 = {"John", 1, 99.9};

    // union initialization
    union student_union s3 = {"John"};

    // it also works with the other fields
    union student_union s4 = {1};
    union student_union s5 = {99.0};

    // union by typedef
    StudentUnion s6;

    // copy the field from one union to another
    // be sure that the field is initialized
    // otherwise it will copy garbage
    strcpy(s6.name, s3.name);

    // print the contents of the struct
    printf("Struct Student:\n");
    printf("Name: %s\n", s2.name);
    printf("ID: %d\n", s2.course);
    printf("Marks: %.2f\n", s2.marks_average);

    // print the contents of the union
    printf("Union StudentUnion s3:\n");
    printf("Name: %s\n", s3.name);

    printf("Union StudentUnion s6:\n");
    printf("Name: %s\n", s6.name);

    printf("Size of struct student: %zu\n", sizeof(s1));
    printf("Size of union student_union: %zu\n", sizeof(s3));

    return 0;
}