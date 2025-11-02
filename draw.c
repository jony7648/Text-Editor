#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "file.h"
#include "state.h"

static void clearScreen() {
	#ifdef _WIN32
		system("cls");
	#elif __APPLE__
		system("clear");
	#elif __linux__
		system("clear");
	#endif

}

static void printTabSpaces(int tabSpaceCount) {
	for (int i=0; i<tabSpaceCount; i++) {
		printw(" ");
	}
}

void drawTextFromBuffer(EditorState *editorState) {
	int tabSpaceCount = 3;
	int drawLineCount = 34;

	int drawStartLine = editorState->currentLine - drawLineCount / 2;
	int drawStopLine = editorState->currentLine + drawLineCount / 2;

	clearScreen();

	FileBuffer *fileBuffer = editorState->fileBuffer;

	//ensure the start line doesn't go outside of array bounds
	if (drawStartLine < 0) {
		drawStartLine = 0;
	}

	//draw text
	//loop thorugh each line
	for (int i=drawStartLine; i<drawStopLine; i++) {
		//check if we are printing beyond array bounds
		
		if (i >= fileBuffer->lineCount) {
			break;
		}

		//loop thorugh each char in line
		for (int j=0; j<strlen(editorState->fileBuffer->lineArr[i]); j++) {
			char currentChar = fileBuffer->lineArr[i][j];

			//if the cursor is at this position do these things
			if (i == editorState->currentLine && j == editorState->currentChar) {
				//if we are at an empty line
				if (strlen(fileBuffer->lineArr[i]) <= 1) {
					printw("%c\n", editorState->cursorChar);
					continue;
				}

				//if we are at a tab print one less space to accominate
				if (currentChar == '\t') {
					printTabSpaces(tabSpaceCount - 1);
				}

				printw("%c", editorState->cursorChar);
				continue;
			}

			// if cursor isn't at this position do these things
			if (currentChar == '\t') {
				printTabSpaces(tabSpaceCount);
				continue;
			}


			printw("%c", fileBuffer->lineArr[i][j]);
		}

	}

}

	
