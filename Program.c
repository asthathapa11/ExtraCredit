#include <stdio.h>

int update_array(int (*prefsArray)[5], int cur, int pair)
{
	cur++;
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (i == 0 && j == 0)
			{
				j = cur;
			}
			if (prefsArray[i][j] == pair)
			{
				prefsArray[i][j] = 0;
			}
		}
	}
	return 0;
}

int* find_match(int (*prefsArray)[5], int dept)
{
	int rank = 5;
	static int pair[2];
	for (int i = 0; i < 5; i++)
	{
		int start = 0;
		int compare = 0;
		while (prefsArray[start][dept] == 0)
		{
			start++;
		}
		while (prefsArray[compare][i] == 0)
		{
			compare++;
		}
		if (prefsArray[start][dept] == prefsArray[compare][i] && dept != i)
		{
			int prog = (prefsArray[start][dept]) - 1;
			while (prefsArray[rank][prog] != dept || prefsArray[rank][prog] != i)
			{
				if (prefsArray[rank][prog] == dept + 1)
				{
					prefsArray[0][dept] = prefsArray[start][dept];
					pair[0] = dept;
					pair[1] = prefsArray[start][dept];
					return pair;
				}
				if (prefsArray[rank][prog] == i + 1)
				{
					prefsArray[0][i] = prefsArray[compare][i];
					pair[0] = i;
					pair[1] = prefsArray[compare][i];
					return pair;
				}
				rank++;
			}
		}
	}
	pair[0] = -1;
	pair[1] = 0;
	return pair;
}

int main()
{
	// open file or error if unable
	FILE *filePtr;
	filePtr = fopen("matching-data.txt", "r");
	if (filePtr == NULL)
	{
		printf("File cannot be opened.\n");
		return 1;
	}

	// read lines from file and store values in array
	char fileString[15];
	int prefsArray[10][5];
	int lineCount = 0;
	while (fgets(fileString, 15, filePtr))
	{
		sscanf(fileString, "%d %d %d %d %d", &prefsArray[lineCount][0], &prefsArray[lineCount][1], &prefsArray[lineCount][2], &prefsArray[lineCount][3], &prefsArray[lineCount][4]);
		lineCount++;
	}

	// close file
	fclose(filePtr);

	int deptCount = 15;
	int progCount = 15;

	// for every department
	for (int i = 0; i < 5; i++)
	{
		// find matching programmer and store as pair in array
		int *match;
		match = find_match(prefsArray, i);

		// update counts
		deptCount -= (*(match + 0) + 1);
		progCount -= *(match + 1);

		// if a match was found
		if ((*(match + 0) + 1) != 0)
		{
			// update array
			update_array(prefsArray, *(match + 0), *(match + 1));
		}
		else
		{
			// if match was not found, array empty
			prefsArray[0][deptCount - 1] = progCount;

			// for every department
			for (int j = 0; j < 5; j++)
			{
				// print match
				printf("Department #%d will get Programmer #%d\n", (j + 1), prefsArray[0][j]);
			}
			break;
		}
	}
	return 0;
}
