#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

FileBuffer *newFileBuffer(char *filePath) {
	//Get text data from a file and store it in a buffer
	FILE *fptr = NULL;
	FileBuffer *fileBuffer = NULL;
	char *lineBuffer;
	int maxChars = 200;

	fileBuffer = malloc(sizeof(FileBuffer));

	fileBuffer->maxLineCount = 500;
	fileBuffer->lineArr = NULL;


	fptr = fopen(filePath, "r");

	if (fptr == NULL) {
		return NULL;
	}



	//allocate memory to hold number of file lines
	fileBuffer->lineArr = malloc(sizeof(char*) * fileBuffer->maxLineCount);

	//allocate memory for each char in line
	for (int i=0; i<fileBuffer->maxLineCount; i++) {
		for (int j=0; j<maxChars; j++) {
			fileBuffer->lineArr[i] = malloc(sizeof(char) * maxChars);
		}
	}

	lineBuffer = malloc(sizeof(char) * maxChars);

	//fill up that memory with the characters from the file
	while (fgets(lineBuffer, maxChars, fptr)) {
		//fileBuffer->lineArr[fileBuffer->lineCount] = malloc(sizeof(char) * strlen(lineBuffer));
		strcpy(fileBuffer->lineArr[fileBuffer->lineCount], lineBuffer);
		fileBuffer->lineCount++;
	}

	free(lineBuffer);
	return fileBuffer;
}

