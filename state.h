#ifndef STATE_H
#define STATE_H

#include "file.h"

#define ESCAPE_KEYCODE 27
#define EDITOR_NORMAL_MODE 0
#define EDITOR_INSERT_MODE 1
#define EDITOR_VISUAL_MODE 2

typedef struct EditorState EditorState;
struct EditorState {
	int running;
	char *dirPath;
	char *filePath;
	char cursorChar;
	int textLineCount;
	int currentLine;
	int currentChar;

	int editMode;

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
