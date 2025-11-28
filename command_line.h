#ifndef COMMAND_LINE
#define COMMAND_LINE


typedef struct commLineParseData {
	void (*argFunc)(char*, char*, char*, void*);
	void (*paramFunc)(char*, char*, char*, void*);
	void (*paramArgFunc)(char*, char*, char*, void*);
	char *currentParam;
	char *lastParam;
	char *nextParam;

	void *signalData;
} commLineParseData;

extern void parseCommandLineArgs(int argc, char **argv, commLineParseData *commLineData);

#endif
