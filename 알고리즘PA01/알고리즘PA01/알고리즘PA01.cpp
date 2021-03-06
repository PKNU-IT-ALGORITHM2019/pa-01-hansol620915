#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define BUFFER_SIZE 100
#define numofwords 200000

typedef struct words {
	char * word_mean; 
	char * word; 
	char * word_POS;
}Words;

Words dict[numofwords];

int n = 0;
int read_line(FILE *fp, char str[], int n);
void find();
void load();
int binarySearch(char target[], int begin, int end);

int main()
{
	char buffer[BUFFER_SIZE];
	while (1) {
		printf("$ ");
		scanf("%s", buffer);
		if (strcmp(buffer, "read") == 0)
			load();
		else if (strcmp(buffer, "size") == 0)
			printf("%d\n", n);
		else if (strcmp(buffer, "find") == 0)
			find();	
		else if (strcmp(buffer, "exit") == 0)
			break;
	}
    return 0;
}


int read_line(FILE *fp, char str[], int n) {
	int ch, i = 0;
	while ((ch = fgetc(fp)) != '\n' && ch != EOF)
		if (i < n - 1)
			str[i++] = ch;

	str[i] = '\0';
	return i;
}

void load() {
	char fileName[BUFFER_SIZE];
	char buffer[BUFFER_SIZE];
	char buf2[BUFFER_SIZE];
	scanf("%s", fileName);
	FILE *fp = fopen(fileName, "r");
	if (fp == NULL) {
		printf("Open failed.\n");
		return;
	}
	while (read_line(fp, buffer, BUFFER_SIZE) != 0) {  
		if (buffer[0] == '\n') continue;
		dict[n].word_mean = strdup(buffer);
		strcpy(buf2, buffer);
		for (int i = 0; i < BUFFER_SIZE; i++) {
			if (buf2[i] == '(') {
				buf2[i - 1] = '\0';
				strlwr(buf2);
				dict[n].word = strdup(buf2);			
				break;
			}
		}
		for (int i = 0; i < BUFFER_SIZE; i++) {
			if (buffer[i] == ')') {
				buffer[i + 1] = '\0';
				dict[n].word_POS = strdup(buffer);
				break;
			}
		}
		n++;
		read_line(fp, buffer, BUFFER_SIZE);
	}
	fclose(fp);
}

void find() {
	int numofequal = 1;
	char buf[BUFFER_SIZE];
	scanf("%s", buf);
	strlwr(buf);
	int k = binarySearch(buf, 0, n);

	if (strcmp(dict[k].word, buf) != 0) {
		printf("Not found.\n");
		printf("%s\n", dict[k - 1].word_POS);
		printf("- - -\n");
		printf("%s\n", dict[k].word_POS);
		return;
	}
	else {	
		while (k != 0 && strcmp(dict[k].word, dict[k-1].word) == 0) k--;
		while (strcmp(dict[k].word, dict[k + numofequal].word) == 0) numofequal++;
		printf("Found %d items.\n", numofequal);
		for (int i = 0; i < numofequal; i++)
			printf("%s\n", dict[k+i].word_mean);
		return;
	}
}

int binarySearch(char target[], int begin, int end) {
	int middle = (begin + end) / 2;
	if (strcmp(dict[middle].word, target) == 0)
		return middle;
	else if (begin == end) return middle;
	else if (strcmp(dict[middle].word, target) > 0)
		return binarySearch(target, begin, middle - 1);
	else
		return binarySearch(target, middle + 1, end);
}