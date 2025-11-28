#ifndef STATE_H
#define STATE_H

#include "file.h"

#define EDITOR_NORMAL_MODE 0
#define EDITOR_INSERT_MODE 1
#define EDITOR_VISUAL_MODE 2
#define EDITOR_COMMAND_MODE 3

#ifdef _WIN32
	#define BACKSPACE_KEYCODE 8
#elif __APPLE__
	#define BACKSPACE_KEYCODE 127
#elif __linux__
	#define BACKSPACE_KEYCODE 8
#endif

#define ESCAPE_KEYCODE 27

typedef struct EditorState EditorState;
struct EditorState {
	int running;
	char *dirPath;
	char *filePath;
	char cursorChar;
	int textLineCount;
	int maxCharCount; //the amount of chars the program can draw before wrapping
	int maxDrawLineCount;
	int mainWindowSizeY;
	int statusBarSizeY;
	int currentLine;
	int currentChar;

	int editMode;

	char *editLineBuffer;

	FileBuffer *fileBuffer;
};

extern EditorState *newEditorState();
extern void editorStateFree(EditorState *editorState);
extern void editorAssignFileBuffer(EditorState *editorState, FileBuffer *fileBuffer);
extern void editorEnterNormalMode(EditorState *editorState);
extern void editorEnterInsertMode(EditorState *editorState);
extern void editorLineScroll(EditorState *editorState, int lineCount);
extern void editorCharScroll(EditorState *editorState, int charCount);
extern void editorEditLine(EditorState *editorState, char userKey);

#endif
