#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "draw.h"
#include "file.h"
#include "state.h"
#include "command_line.h"

static void closeProgram(EditorState *editorState, FileBuffer *fileBuffer) {
	endwin();
	editorStateFree(editorState);
}

static void applyNormalModeControls(EditorState *editorState, char userKey) {
	switch (userKey) {
		//movement
		case 'e':
			editorLineScroll(editorState, 1);
			break;
		case 'i':
			editorLineScroll(editorState, -1);
			break;
		case 'o':
			editorCharScroll(editorState, 1);
			break;
		case 'n':
			editorCharScroll(editorState, -1);
			break;
		case '$':
			editorCharScroll(editorState, 1000);
			break;
		case '_':
			editorCharScroll(editorState, -1000);
			break;
		case 'u':
			editorEnterInsertMode(editorState);
			break;
		case 'q':
			editorState->running = false;
			break;
		case 'w':
			editorState->running = false;
			fileBufferSaveToFile(editorState->fileBuffer, "__OUTFILE__");
			break;
	}
}

static void applyInsertModeControls(EditorState *editorState, char userKey) {
	if (userKey == ESCAPE_KEYCODE) {
		editorEnterNormalMode(editorState);
		return;
	}

	editorEditLine(editorState, userKey);
}

static void handleEditorStates(EditorState *editorState) {

	switch(editorState->editMode) {
		case EDITOR_NORMAL_MODE:
			applyNormalModeControls(editorState, getch());
			break;
		case EDITOR_INSERT_MODE:
			applyInsertModeControls(editorState, getch());
			break;
	}
}

void argFunction(char *lastParam, char *currentParam, char *nextParam, void *signalData) {
	EditorState *editorState = (EditorState*)signalData;

	FileBuffer *fileBuffer = newFileBuffer(currentParam);

	editorAssignFileBuffer(editorState, fileBuffer);
}

int main(int argc, char **argv) {
	char *filePath = NULL;
	EditorState *editorState = NULL;


	initscr();

	editorState = newEditorState();

	commLineParseData commLineData;

	commLineData.argFunc = &argFunction;
	commLineData.paramFunc = NULL;
	commLineData.paramArgFunc = NULL;
	commLineData.signalData = editorState;

	parseCommandLineArgs(argc, argv, &commLineData);

	if (editorState->fileBuffer == NULL) {
		printf("ERROR: failed to read file\n");
		return 1;
	}


	while (editorState->running) {
		cbreak();
		noecho();

		//printw("\n\n\n");
		//printw("EditMode: %d\n", editorState->editMode);
		//printw("Current Line: %d\nMax Line: %d\n", editorState->currentLine, editorState->textLineCount - 1);
		//printw("Current Char: %d\n", editorState->currentChar);
		//printw("MaxCharCount: %d\n", editorState->maxCharCount);

		drawTextFromBuffer(editorState);
		drawStatusRow(editorState);

		handleEditorStates(editorState);

		clear();

	}

	closeProgram(editorState, editorState->fileBuffer);

	return 0;
}
