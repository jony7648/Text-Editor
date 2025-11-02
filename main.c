#include <stdio.h>
#include <ncurses.h>
#include "draw.h"
#include "file.h"
#include "state.h"

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

	if (editorState->editMode == EDITOR_INSERT_MODE) {
	}

}

int main() {
	//create a struct that will manage text editor states 
	//and create an advance line function to disallow invalid lineArr
	//indexs

	FileBuffer *fileBuffer = newFileBuffer("example.c");
	initscr();


	EditorState *editorState = newEditorState();
	editorAssignFileBuffer(editorState, fileBuffer);

	while (editorState->running) {
		cbreak();
		noecho();

		drawTextFromBuffer(editorState);

		printw("\n\n\n");
		printw("EditMode: %d\n", editorState->editMode);
		printw("Current Line: %d\nMax Line: %d\n", editorState->currentLine, editorState->textLineCount - 1);
		printw("Current Char: %d\n", editorState->currentChar);

		handleEditorStates(editorState);


		clear();

	}


	closeProgram(editorState, fileBuffer);

	return 0;
}
