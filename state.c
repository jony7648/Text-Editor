#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "state.h"
#include "file.h"

EditorState *newEditorState() {
	EditorState *editorState = malloc(sizeof(EditorState));

	editorState->running = 1;
	editorState->editMode = EDITOR_NORMAL_MODE;
	editorState->dirPath = NULL;
	editorState->filePath = NULL;
	editorState->textLineCount = 0;
	editorState->currentLine = 180;
	editorState->currentChar = 0;
	editorState->cursorChar = '&';

	editorState->fileBuffer = NULL;

	return editorState;
}

void editorStateFree(EditorState *editorState) {
	free(editorState);
}

void editorAssignFileBuffer(EditorState *editorState, FileBuffer *fileBuffer) {
	editorState->fileBuffer = fileBuffer;				

	editorState->textLineCount = fileBuffer->lineCount;

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

void editorEditLine(EditorState *editorState, char userKey) {
	
}
