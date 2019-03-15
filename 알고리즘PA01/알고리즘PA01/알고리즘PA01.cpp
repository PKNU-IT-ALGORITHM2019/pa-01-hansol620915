#include "stdio.h"
#include "string.h"
#include "stdlib.h"

#define BUFFER_SIZE 100
#define numofwords 200000
char * word[numofwords]; // word
char * ecp_mean[numofwords]; /* word's mean */
char * conc_part[numofwords];

int n = 0;
int read_line(FILE *fp, char str[], int n);
void find();
void load();
int binarySearch(char *w[], char target[], int begin, int end);

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

	while (read_line(fp, buffer, BUFFER_SIZE) != 0) {  // 미완
		//printf("%s\n", buffer);
		if (buffer[0] == '\n') continue;
		word[n] = strdup(buffer);
		strcpy(buf2, buffer);
		for (int i = 0; i < BUFFER_SIZE; i++) {
			if (buf2[i] == '(') {
				buf2[i - 1] = '\0';
				strlwr(buf2);
				ecp_mean[n] = strdup(buf2);			
				break;
			}
		}
		for (int i = 0; i < BUFFER_SIZE; i++) {
			if (buffer[i] == ')') {
				buffer[i + 1] = '\0';
				conc_part[n] = strdup(buffer);
				break;
			}
		}

		n++;
		read_line(fp, buffer, BUFFER_SIZE);
		//if (n > 176049) break;
	}
	fclose(fp);
}

void find() {
	int numofequal = 1;
	char buf[BUFFER_SIZE];
	scanf("%s", buf);
	strlwr(buf);
	int k = binarySearch(ecp_mean, buf, 0, n);

	if (strcmp(ecp_mean[k], buf) != 0) {
		printf("Not found.\n");
		printf("%s\n", conc_part[k - 1]);
		printf("- - -\n");
		printf("%s\n", conc_part[k]);
		return;
	}
	else {	
		while (k != 0 && strcmp(ecp_mean[k], ecp_mean[k - 1]) == 0) k--;
		while (strcmp(ecp_mean[k], ecp_mean[k + numofequal]) == 0) numofequal++;
		printf("Found %d items.\n", numofequal);
		for (int i = 0; i < numofequal; i++)
			printf("%s\n", word[k + i]);
		return;
	}
}

int binarySearch(char *w[], char target[], int begin, int end) {
	int middle = (begin + end) / 2;
	printf("%s %s\n", w[middle], target);
	if (strcmp(w[middle], target) == 0)
		return middle;
	else if (begin == end) return middle;
	else if (strcmp(w[middle], target) > 0)
		return binarySearch(w, target, begin, middle - 1);
	else
		return binarySearch(w, target, middle + 1, end);
}