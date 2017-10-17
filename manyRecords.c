#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
	
	Record *arr = malloc(sizeof(Record));
	if(arr == NULL) {
		fprintf(stderr, "ERROR: Failed malloc!\n");
		exit(1);
	}
	sizeOfArr = 1;
	
	while(1) {
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
			memcpy(temp, arr, countInArr*sizeof(Record));
			free(arr);
			arr = temp;
			
			printf("  After  extending the array, element 0 is: ");
			printRecord(arr);
		}
		
		res = fillRecord(arr + countInArr);
		if(res == 1) {
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
	
	free(arr);
	
	return retVal;
}

void printRecord(Record* rec) {
	printf("%d %d %s\n", rec->x, rec->y, rec->word);
}

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

