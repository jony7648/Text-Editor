#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "state.h"
#include "file.h"

EditorState *newEditorState() {
	EditorState *editorState = malloc(sizeof(EditorState));

	int x_add = 3;
	int y_add = 0;

	int maxX = 0;
	int maxY = 0;

	getmaxyx(stdscr, maxY, maxX);

	//maxX += x_add;

	editorState->running = 1;
	editorState->editMode = EDITOR_NORMAL_MODE;
	editorState->dirPath = NULL;
	editorState->filePath = NULL;
	editorState->textLineCount = 0;
	editorState->maxCharCount = maxX;
	editorState->maxDrawLineCount = maxY;
	editorState->statusBarSizeY = 2;
	editorState->mainWindowSizeY = editorState->maxDrawLineCount - editorState->statusBarSizeY;
	editorState->currentLine = 0;
	editorState->currentChar = 0;
	editorState->cursorChar = '&';
	editorState->editLineBuffer = NULL;
	editorState->fileBuffer = NULL;

	return editorState;
}

void editorStateFree(EditorState *editorState) {
	free(editorState);
}

void editorAssignFileBuffer(EditorState *editorState, FileBuffer *fileBuffer) {
	editorState->fileBuffer = fileBuffer;				

	editorState->textLineCount = fileBuffer->lineCount;

	if (editorState->editLineBuffer == NULL) {
		editorState->editLineBuffer = malloc(fileBuffer->maxChars * sizeof(char));
	}
}

void editorEnterNormalMode(EditorState *editorState) {
	editorState->editMode = EDITOR_NORMAL_MODE;	
}

void editorEnterInsertMode(EditorState *editorState) {
	editorState->editMode = EDITOR_INSERT_MODE;	
}



void editorCharScroll(EditorState *editorState, int charCount) {
	int resultIndex = editorState->currentChar + charCount;	

	char *line = editorState->fileBuffer->lineArr[editorState->currentLine];

	if (resultIndex < 0) {
		resultIndex = 0;
	}

	else if (resultIndex >= strlen(line) - 1) {
		resultIndex = strlen(line) - 2;
	}
	
	editorState->currentChar = resultIndex;
	
}

void editorLineScroll(EditorState *editorState, int lineCount) {
	int resultLine = editorState->currentLine + lineCount;

	if (resultLine < 0) {
		resultLine = 0;
	}
	else if (resultLine > editorState->textLineCount - 1) {
		resultLine = editorState->textLineCount - 1;
	}

	editorState->currentLine = resultLine;

	editorCharScroll(editorState, 0);
}

static void handleDelFirstChar(EditorState *editorState) {
	FileBuffer *fileBuffer = editorState->fileBuffer;

	char *currentLine = fileBuffer->lineArr[editorState->currentLine];
	char *previousLine = fileBuffer->lineArr[editorState->currentLine - 2];

	currentLine[strlen(currentLine) - 1] = '\0';
	strcat(previousLine, currentLine);
	currentLine[0] = '\n';
	currentLine[1] = '\0';
	editorState->currentLine -= 1;
	editorState->currentChar = 0;

}

void editorEditLine(EditorState *editorState, char userKey) {
	FileBuffer *fileBuffer = editorState->fileBuffer;
	char *currentLine = NULL;
	//Add limits and add backspace feature

	currentLine = fileBuffer->lineArr[editorState->currentLine];


	if (userKey == BACKSPACE_KEYCODE) {
		if (editorState->currentChar == 0) {
			handleDelFirstChar(editorState);
			return;
		}

		char *offsetPtr = currentLine + editorState->currentChar - 0;
		//do back space thing
		strcpy(editorState->editLineBuffer, offsetPtr);

		currentLine[editorState->currentChar - 1] = '\0';
		strcat(currentLine, editorState->editLineBuffer);

		editorState->currentChar -= 1;
		return;
	}	

	//ensure character doesn't go outside line bounds
	if (strlen(currentLine) + 1 >= fileBuffer->maxChars) {
		return;
	}


	int currentChar = editorState->currentChar;

	//char newLineBuffer[1000];
	//newLineBuffer[999] = '\0';


	editorState->editLineBuffer[0] = '\0';

	strncpy(editorState->editLineBuffer, currentLine, currentChar);

	editorState->editLineBuffer[editorState->currentChar] = userKey;
	editorState->editLineBuffer[editorState->currentChar+1] = '\0';

	strcat(editorState->editLineBuffer, currentLine+currentChar);

	strcpy(currentLine, editorState->editLineBuffer);
	editorState->currentChar+=1;
}
