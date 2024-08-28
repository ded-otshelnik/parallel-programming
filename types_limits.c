#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(int argc, char** argv) {
   printf("Storage size for char : %zu \n", sizeof(char));
   printf("CHAR_BIT    :   %d\n", CHAR_BIT);
   printf("CHAR_MAX    :   %d\n", CHAR_MAX);
   printf("CHAR_MIN    :   %d\n", CHAR_MIN);
   printf("------\n");
   printf("Storage size for int : %zu \n", sizeof(int));
   printf("INT_MAX     :   %d\n", INT_MAX);
   printf("INT_MIN     :   %d\n", INT_MIN);
   printf("------\n");
   printf("Storage size for short : %zu \n", sizeof(short));
   printf("SHRT_MAX    :   %d\n", (short) SHRT_MAX);
   printf("SHRT_MIN    :   %d\n", (short) SHRT_MIN);
   printf("------\n");
   printf("Storage size for long : %zu \n", sizeof(long));
   printf("LONG_MAX    :   %ld\n", (long) LONG_MAX);
   printf("LONG_MIN    :   %ld\n", (long) LONG_MIN);
   printf("------\n");
   printf("SCHAR_MAX   :   %d\n", (signed char) SCHAR_MAX);
   printf("SCHAR_MIN   :   %d\n", (signed char) SCHAR_MIN);
   printf("SHRT_MAX    :   %d\n", (signed short) SHRT_MAX);
   printf("SHRT_MIN    :   %d\n", (signed short) SHRT_MIN);
   printf("------\n");
   printf("UCHAR_MAX   :   %d\n", (unsigned char) UCHAR_MAX);
   printf("UINT_MAX    :   %u\n", (unsigned int) UINT_MAX);
   printf("ULONG_MAX   :   %lu\n", (unsigned long) ULONG_MAX);
   printf("USHRT_MAX   :   %d\n", (unsigned short) USHRT_MAX);
   printf("------\n");
   printf("Storage size for float : %zu \n", sizeof(float));
   printf("Precision value: %d\n", FLT_DIG);
   printf("FLT_MAX     :   %g\n", (float) FLT_MAX);
   printf("FLT_MIN     :   %g\n", (float) FLT_MIN);
   printf("-FLT_MAX    :   %g\n", (float) -FLT_MAX);
   printf("-FLT_MIN    :   %g\n", (float) -FLT_MIN);
   printf("------\n");
   printf("Storage size for double : %zu \n", sizeof(double));
   printf("Precision value: %d\n", DBL_DIG);
   printf("DBL_MAX     :   %g\n", (double) DBL_MAX);
   printf("DBL_MIN     :   %g\n", (double) DBL_MIN);
   printf("-DBL_MAX     :  %g\n", (double) -DBL_MAX);
   printf("-DBL_MAX     :  %g\n", (double) -DBL_MIN);

   return 0;
}