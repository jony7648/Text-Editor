#ifndef FILE_H
#define FILE_H

typedef struct FileBuffer FileBuffer;

struct FileBuffer {
	char **lineArr;
	char *filePath;
	int maxLineCount;
	int lineCount;
	int maxChars;
};

extern FileBuffer *newFileBuffer(char *filePath);
extern int fileBufferSaveToFile(FileBuffer *fileBuffer, char *filePath);
#endif
