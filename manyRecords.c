#include <stdio.h>
#include <stdlib.h>

struct Record {
	int x,y;
	char *word;
};
typedef struct Record Record;

void printRecord(Record*);

int main() {

	
	int retVal = 0;
	
	Record *arr = malloc(sizeof(Record));
	
	while(1) {
		
		
	}
	
	return retVal;
}

void printRecord(Record* rec) {
	printf("%d %d %s\n", rec->x, rec->y, rec->word);
}

int fillRecord(Record *rec) {
	int res, tempX, tempY;
	char tempWord[32];
	
	res = scanf("%d %d %31s", &tempX, &tempY, tempWord);
	if(res < 3) {
		printf("scanf() returned %d, so now we'll check to see if the string is \"END\"...\n", res);
		return 1;
	}
	
	rec->x = tempX;
	rec->y = tempY;
	rec->word = tempWord;
	
	return 0;
}

