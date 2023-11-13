#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>

#include "process.h"
#include "util.h"

#define DEBUG 1			//change this to 1 to enable verbose output

/**
 * Signature for an function pointer that can compare
 * You need to cast the input into its actual 
 * type and then compare them according to your
 * custom logic
 */
typedef int (*Comparer) (const void *a, const void *b);

/**
 * compares 2 processes
 * You can assume: 
 * - Process ids will be unique
 * - No 2 processes will have same arrival time
 */
int my_comparer(const void *this, const void *that)
{
  // Cast the input pointers to their actual type
  const Process *p1 = (const Process *)this;
  const Process *p2 = (const Process *)that;

  // Compare the processes based on arrival time and priority
  if (p1->arrival_time < p2->arrival_time) {
    return -1;
  } else if (p1->arrival_time > p2->arrival_time) {
    return 1;
  } else {
    // If the arrival times are equal, compare the priorities
    if (p1->priority < p2->priority) {
      return 1;
    } else if (p1->priority > p2->priority) {
      return -1;
    } else {
      // If the arrival times and priorities are equal, the processes are considered equal
      return 0;
    }
  }
}


int main(int argc, char *argv[])
{

	if (argc < 2) {
		   fprintf(stderr, "Usage: ./func-ptr <input-file-path>\n");
		   fflush(stdout);
		   return 1;
	}

	/*******************/
	/* Parse the input */
	/*******************/
	FILE *input_file = fopen(argv[1], "r");
	if (!input_file) {
		   fprintf(stderr, "Error: Invalid filepath\n");
		   fflush(stdout);
		   return 1;
	}

	Process *processes = parse_file(input_file);

	/*******************/
	/* sort the input  */
	/*******************/
	Comparer process_comparer = &my_comparer;

#if DEBUG
	for (int i = 0; i < P_SIZE; i++) {
		    printf("%d (%d, %d) ",
				processes[i].pid,
				processes[i].priority, processes[i].arrival_time);
	}
	printf("\n");
#endif

	qsort(processes, P_SIZE, sizeof(Process), process_comparer);

	/**************************/
	/* print the sorted data  */
	/**************************/

	for (int i = 0; i < P_SIZE; i++) {
		    printf("%d (%d, %d)\n",
				processes[i].pid,
				processes[i].priority, processes[i].arrival_time);
	}
	fflush(stdout);
	fflush(stderr);

	/************/
	/* clean up */
	/************/
	free(processes);
	fclose(input_file);
	return 0;

	// Define the two pre-defined integers
  int a = 10;
  int b = 5;

  // Prompt the user for a character
  char op;
  printf("Enter an operation ('0' for add, '1' for subtract, '2' for multiply, '3' for divide, or '4' to exit): ");
  scanf("%c", &op);

  // Perform the corresponding operation on the two integers, without using any conditional statements
  // We can use the fact that the ASCII codes for the characters '0', '1', '2', '3', and '4' are consecutive
  // to perform the corresponding operation on the two integers.
  a = a + (op - '0') * b;

  // Print the result
  printf("The result is: %d\n", a);

  return 0;
}
