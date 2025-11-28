#include <stdio.h>
#include "command_line.h"

void parseCommandLineArgs(int argc, char **argv, commLineParseData *commLineData) {
	const int NORMAL_ARGUMENT = 0;
	const int HYPHEN_PARAMETER = 1;
	const int HYPHEN_ARGUMENT = 2;

	int parseMode = NORMAL_ARGUMENT;

	for (int i=1; i<argc; i++) {
		char *arg = argv[i];

		//set other params as well
		commLineData->nextParam = NULL;

		if (i+1 < argc) {
			commLineData->nextParam = argv[i+1];
		}

		commLineData->currentParam = arg;
		commLineData->lastParam = argv[i-1];

		if (arg[0] == '-') {
			printf("Parameter: %s\n", arg);
			//skip the hyphen character when passing hyphen char by adding 1
			(*commLineData->paramArgFunc)(commLineData->lastParam, commLineData->currentParam+1, commLineData->nextParam, commLineData->signalData);
			parseMode = HYPHEN_PARAMETER;
			continue;
		}

		if (parseMode == HYPHEN_PARAMETER) {
			printf("Argument: %s\n", arg);
			parseMode = NORMAL_ARGUMENT;
			continue;
		}

		(*commLineData->argFunc)(
			commLineData->lastParam,
			commLineData->currentParam,
			commLineData->nextParam,
			commLineData->signalData
		);

		printf("Arg: %s\n", arg);

	}
}

/*
int main(int argc, char **argv) {
	void (*a)();
	a = &testFunc;
	(*a)();


	commLineParseData commLineData;

	commLineData.argFunc = &argFunction;
	commLineData.paramFunc = &paramFunction;
	commLineData.paramArgFunc = &paramArgFunction;

	parseCommandLineArgs(argc, argv, &commLineData);
}
*/
