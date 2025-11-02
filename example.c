#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <strings.h>

#define AIRMANINDEX 0
#define QUICKMANINDEX 1
#define WOODMANINDEX 2
#define CRASHMANINDEX 3
#define FLASHMANINDEX 4
#define METALMANINDEX 5
#define HEATMANINDEX 6
#define BUBBLEMANINDEX 7
#define ETANKINDEX 8

int getPassPos(char row, int column, int eTankCount) {
	int wrapOffset = 5;
	int maxValue = 25;
	int retValue = column + eTankCount;

	switch (row) {
		case 'B':
			retValue += 5;
			break;
		case 'C':
			retValue += 10;
			break;
		case 'D':
			retValue += 15;
			break;
		case 'E':
			retValue += 20;
			break;
	}

	// wrapping functionality
	if (retValue > maxValue) {
		retValue = retValue - maxValue + wrapOffset;
	}

	//convert the retValue to an array index format
	retValue -= 1;

	return retValue;
}

void userInputToData(int userArr[20], int userArrLength, int dataArr[25], int eTankCount) {
	int loopCount = sizeof(userArr[20])/sizeof(int);
	int dataArrIndex = 0;

	const int ALIVE = 0;
	const int DEAD = 1;


	//printf("%d\n", userArrLength);
	
	int bossLength = userArrLength - 1;

	for (int i=0; i<bossLength; i++) {
		if (userArr[i] == DEAD) {
			switch(i) {
				case AIRMANINDEX:
					dataArrIndex = getPassPos('E', 3, eTankCount);
					break;
				case QUICKMANINDEX:
					dataArrIndex = getPassPos('B', 4, eTankCount);
					break;
				case WOODMANINDEX:
					dataArrIndex = getPassPos('D', 3, eTankCount);
					break;
				case CRASHMANINDEX:
					dataArrIndex = getPassPos('C', 5, eTankCount);
					break;
				case FLASHMANINDEX:
					dataArrIndex = getPassPos('C', 1, eTankCount);
					break;
				case METALMANINDEX:
					dataArrIndex = getPassPos('E', 5, eTankCount);
					break;
				case HEATMANINDEX:
					dataArrIndex = getPassPos('B', 2, eTankCount);
					break;
				case BUBBLEMANINDEX:
					dataArrIndex = getPassPos('D', 1, eTankCount);
					break;
				default:
					dataArrIndex = -1;
					break;
			}
		}

		if (userArr[i] == ALIVE) {
			switch(i) {
				case AIRMANINDEX:
					dataArrIndex = getPassPos('D', 2, eTankCount);
					break;
				case QUICKMANINDEX:
					dataArrIndex = getPassPos('C', 4, eTankCount);
					break;
				case WOODMANINDEX:
					dataArrIndex = getPassPos('B', 5, eTankCount);
					break;
				case CRASHMANINDEX:
					dataArrIndex = getPassPos('E', 2, eTankCount);
					break;
				case FLASHMANINDEX:
					dataArrIndex = getPassPos('E', 4, eTankCount);
					break;
				case METALMANINDEX:
					dataArrIndex = getPassPos('E', 1, eTankCount);
					break;
				case HEATMANINDEX:
					dataArrIndex = getPassPos('D', 5, eTankCount);
					break;
				case BUBBLEMANINDEX:
					dataArrIndex = getPassPos('C', 3, eTankCount);
					break;
				default:
					dataArrIndex = -1;
					break;
			}
		}

		if (dataArrIndex == -1) {
			continue;
		}

		printf("%d: %d\n", i, dataArrIndex + 1);
		dataArr[dataArrIndex] = 1;
	}

}

void generatePassword(int userArr[9], int userArrLength, int dataArr[25], int dataArrLength) {
	int eTankCount = userArr[8];
	int maxETankCount = 4;

	if (eTankCount > maxETankCount) {
		eTankCount = maxETankCount;
	}

	for (int i=0; i<dataArrLength; i++) {
		dataArr[i] = 0;
	}


	userInputToData(userArr, userArrLength, dataArr, eTankCount);
	dataArr[eTankCount] = 1;
}

void drawPassword(int dataArr[25], int dataArrLength) {
	char letterArr[5] = {'A', 'B', 'C', 'D', 'E'};
	int row = 0;

	printf("\n  ");

	for (int i=0; i<5; i++) {
		printf(" %d ", i+1);
	}

	for (int i=0; i<dataArrLength; i++) {
		if (i % 5 == 0) {
			printf("\n%c ", letterArr[row]);
			row++;
		}

		if (dataArr[i] == 1) {
			printf(" X ");	
		}
		else {
			printf("   ");
		}
	}


	printf("\n");
}

void getUserInput(int userArr[9]) {
	printf("Type the first letter of the robot master you defeated\nAnd type the number of e-Tanks you have\n");

	printf("Air Man\n");
	printf("Bubble Man\n");
	printf("Quick Man\n");
	printf("Wood Man\n");
	printf("Crash Man\n");
	printf("Flash Man\n");
	printf("Metal Man\n");
	printf("Heat Man\n\n");

	printf("Input: ");

	char buffer[30];
	buffer[29] = '\0';

	scanf("%29s", buffer);

	for (int i=0; i<strlen(buffer); i++) {
		if (isdigit(buffer[i]) == 1) {
			char charToStr[2];
			charToStr[0] = buffer[i];
			charToStr[1] = '\0';
			userArr[ETANKINDEX] = atoi(charToStr);
			continue;
		}

		switch(buffer[i]) {
			case 'A':
				userArr[AIRMANINDEX] = 1;
				break;
			case 'Q':
				userArr[QUICKMANINDEX] = 1;
				break;
			case 'W':
				userArr[WOODMANINDEX] = 1;
				break;
			case 'C':
				userArr[CRASHMANINDEX] = 1;
				break;
			case 'F':
				userArr[FLASHMANINDEX] = 1;
				break;
			case 'M':
				userArr[METALMANINDEX] = 1;
				break;
			case 'H':
				userArr[HEATMANINDEX] = 1;
				break;
			case 'B':
				userArr[BUBBLEMANINDEX] = 1;
				break;
		}
	}
}
