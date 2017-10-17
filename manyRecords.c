#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Record {
	int x,y;
	char word[32];
};
typedef struct Record Record;

void printRecord(Record*);
int fillRecord(Record*, int*);

int main() {

	
	int res, retVal = 0, sizeOfArr, countInArr;
	char end[4];
	
	Record *arr = malloc(sizeof(Record));
	sizeOfArr = 1;
	
	while(1) {
		if(sizeOfArr == countInArr) {
			printf("Need to extend the array; the buffer is full (with %d records)\n", countInArr);
			sizeOfArr *= 2;
			// Double the malloced array
		}
		
		res = fillRecord(arr, &countInArr);
		if(res == 1) {
			scanf("%3s", end);
			if(strcmp(end, "END") == 0) {
				printf("...\"END\" found. Will now read the indices...\n");
				break;
			}
			// Check error when res is 1 but not END
		}
	}
	
	// Print the array
	printRecord(arr);
	
	return retVal;
}

void printRecord(Record* rec) {
	printf("%d %d %s\n", rec->x, rec->y, rec->word);
}

int fillRecord(Record *rec, int *count) {
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
	count++;
	
	return 0;
}

