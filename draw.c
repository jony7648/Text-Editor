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

static int getCharStartPoint(char *line, int currentX, int drawWidth) {
	int startPos = (float)currentX - (float)drawWidth / 2;

	size_t lineLen = strlen(line);


	if (startPos < 0) {
		startPos = 0;
	}
	else if (startPos >= lineLen) {
		startPos = lineLen - 1;
	}

	return startPos;
}

static int lineIsToLong(char *line, int maxLength, int tabSpaceCount) {
	int lineLength = 0;

	for (int i=0; i<strlen(line); i++) {
		int oldLineLength = lineLength;

		if (line[i] == '\t') {
			lineLength += tabSpaceCount;
		}

		lineLength += 1;

		if (lineLength > maxLength) {
			return i;
		}
	}
	
	return 0;
}

static int drawTabSpaces(char *line, int index, int locationArr[], int arrSize, int arrIndex) {
	int foundTab = 0;
	int searchLen = 2;

	for (int i=0; i<searchLen + 1; i++) {
		int charIndex = index - i;

		if (foundTab == 1) {
			printw(" ");
			continue;
		}

		if (charIndex < 0) {
			break;
		}

		if (line[charIndex] != '\t') {
			continue;
		}


		for (int i=0; i<arrSize; i++) {
			if (locationArr[i] == charIndex) {
				return arrIndex;
			}
		}

		locationArr[0] = charIndex;
		arrIndex++;

		foundTab = 1;
		printw(" ");
	}

	return arrIndex;
}

void drawTextFromBuffer(EditorState *editorState) {
	// create a function that will scroll the screen to the left/right
	// create something that will keep the positon of the cursor

	FileBuffer *fileBuffer = editorState->fileBuffer;

	int tabSpaceCount = 3;
	int drawLineCount = editorState->mainWindowSizeY;

	int drawStartLine = editorState->currentLine - drawLineCount / 2;
	int drawStopLine = editorState->currentLine + drawLineCount / 2;

	int drawSpaceCount = 0;




	clearScreen();


	//ensure the start line doesn't go outside of array bounds
	if (drawStartLine < 0) {
		drawStartLine = 0;
	}



	//draw text
	//loop thorugh each line

	for (int i=drawStartLine; i<drawStopLine; i++) {
		char *currentLine = fileBuffer->lineArr[i];
		int charDrawStartPoint = getCharStartPoint(currentLine, editorState->currentChar, editorState->maxCharCount);
		int charDrawStopPoint = strlen(fileBuffer->lineArr[i]);

		int lineTooLong = lineIsToLong(currentLine, editorState->maxCharCount, tabSpaceCount);
		int additionalCharOffset = 0; //used for tab chars
									  //check if we are printing beyond array bounds

		if (i >= fileBuffer->lineCount) {
			break;
		}

		//temperary make this better
		int matchArr[100];
		int matchArrIndex = 0;

		for (int i=0; i<100; i++) {
			matchArr[i] = -1;
		}


		//loop thorugh each char in line
		for (int j=charDrawStartPoint; j<charDrawStopPoint; j++) {
			/*
			   while (drawSpaceCount > 0) {
			   printw(" ");
			   drawSpaceCount--;
			   }
			   */



			

			matchArrIndex = drawTabSpaces(currentLine, j, matchArr, 100, matchArrIndex);
			/*
			   for (int g=0; g < 1; g++) {
			   int charIndex = j-g;
			   if (charIndex < 0) {
			   break;
			   }

			   if (fileBuffer->lineArr[i][charIndex] == '\t') {
			   printw("   ");
			   break;
			   }
			   }
			   */


			char currentChar = fileBuffer->lineArr[i][j];

			int totalDrawCharCount = j + additionalCharOffset;

			if (lineTooLong != 0 && j >= lineTooLong)   {
				break;
			}

			//if the cursor is at this position do these things
			if (i == editorState->currentLine && j == editorState->currentChar) {
				//if we are at an empty line
				if (strlen(fileBuffer->lineArr[i]) <= 1) {
					printw("%c\n", editorState->cursorChar);
					continue;
				}

				// do tab stuff
				if (currentChar == '\t') {
					if (totalDrawCharCount + tabSpaceCount <= editorState->maxCharCount) {
						//printTabSpaces(tabSpaceCount);
						drawSpaceCount = tabSpaceCount;
						additionalCharOffset += tabSpaceCount + 2;

					}

					continue;
				}

				printw("%c", editorState->cursorChar);
				continue;
			}

			//if cursor isn't at this position do these things
			if (currentChar == '\t') {
				drawSpaceCount = tabSpaceCount;
				continue;
			}

			printw("%c", fileBuffer->lineArr[i][j]);
		}

	}


}

void drawStatusRow(EditorState *editorState) {
	for (int i=0; i<editorState->maxCharCount; i++) {
		printw("-");
	}

	printw("%d, %d", editorState->currentChar, editorState->currentLine);
}



