/*
* Name:    Jamie David
*
* Assignment #6 - manyRecords.c
* CSc 352 - Spring 2017
*
* This program stores records in form of structs
* in a dynamically allocated array. Records are
* read in from stdin. After entering the String
* "END", the user will enter indices of records
* to be printed.
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct for holding a record
struct Record {
	int x,y;
	char word[32];
};
typedef struct Record Record;

void printRecord(Record*);
int fillRecord(Record*);

int main() {

	int res, retVal = 0, sizeOfArr, countInArr = 0;
	char end[4];
	
	// Allocates a buffer at start of program.
	// Buffer is large enough for 1 record.
	Record *arr = malloc(sizeof(Record));
	if(arr == NULL) {
		fprintf(stderr, "ERROR: Failed malloc!\n");
		exit(1);
	}
	sizeOfArr = 1;
	
	// Fill up the array with user entry
	while(1) {
		// If array is full, double the size
		if(sizeOfArr == countInArr) {
			printf("Need to extend the array; the buffer is full (with %d records)\n", countInArr);
			sizeOfArr *= 2;
			printf("  Before extending the array, element 0 is: ");
			printRecord(arr);
			// Double the malloced array
			Record *temp = malloc(sizeOfArr * sizeof(Record));
			if(temp == NULL) {
				fprintf(stderr, "ERROR: Failed malloc!\n");
				exit(1);
			}
			// Copy the contents old array into temp
			// and free old allocated array.
			memcpy(temp, arr, countInArr*sizeof(Record));
			free(arr);
			arr = temp;
			
			printf("  After  extending the array, element 0 is: ");
			printRecord(arr);
		}
		
		// Push a record into the array
		res = fillRecord(arr + countInArr);
		if(res == 1) {
			// Check for END keyword
			scanf("%3s", end);
			if(strcmp(end, "END") == 0) {
				printf("...\"END\" found.  Will now read the indices...\n");
				break;
			}
			// Check error when res is 1 but not END
			else {
				fprintf(stderr, "ERROR: the string was not \"END\".  Ending the program!\n");
				exit(1);
			}
		}
		// Keep track of records in the array
		countInArr++;
	}
	
	// Print the array
	int i;
	while(1) {
		res = scanf("%d", &i);
		if(res == EOF) {
			break;
		}
		if(res == 0) {
			fprintf(stderr, "ERROR: scanf() rc=%d\n", res);
			exit(1);
		}
		printf("[%d] ", i);
		if(i < 0 || i > countInArr - 1) {
			printf("<invalid index>\n");
		} else {
			printRecord(arr + i);
		}
	}
	
	// Free the alloc'ed array
	free(arr);
	
	return retVal;
}

/*
 * Prints a record
 *
 * @param rec
 *               - A pointer to the record
*/
void printRecord(Record* rec) {
	printf("%d %d %s\n", rec->x, rec->y, rec->word);
}

/*
 * Fills a record with data from stdin
 *
 * @param rec
 *               - A pointer to the record
*/
int fillRecord(Record *rec) {
	int r, tempX, tempY;
	char tempWord[32];
	
	r = scanf("%d %d %31s", &tempX, &tempY, tempWord);
	if(r < 3) {
		printf("scanf() returned %d, so now we'll check to see if the string is \"END\"...\n", r);
		return 1;
	}
	
	rec->x = tempX;
	rec->y = tempY;
	memcpy(rec->word, tempWord, strlen(tempWord) + 1);
	
	return 0;
}

