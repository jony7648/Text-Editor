#ifndef FILE_H
#define FILE_H

typedef struct FileBuffer FileBuffer;

struct FileBuffer {
	char **lineArr;
	int maxLineCount;
	int lineCount;
};

extern FileBuffer *newFileBuffer(char *filePath);
#endif
