//Bishal Giri

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define HASHTABLESIZE 30
//#define HASHTABLESIZE 37
 
/* Node for storing information */

typedef struct chelseaPlayer
{
    char *name;
    char *country;
    float market_value;
    int fifa22_rating;
    char position;
    struct chelseaPlayer *next_ptr;
}
CHELSEAPLAYER;
 
/* This function creates an index corresponding to the input key */
int CalculateHashIndex(char *key)
{
    int i=0, hash=0;
    for (i; i<strlen(key);i++){
        hash+=(key[i]);
    }
    hash+=(key[strlen(key)]*69);
    return hash%HASHTABLESIZE;
}


void AddNode(CHELSEAPLAYER *NewNode, CHELSEAPLAYER *chelseaplayer[])
{
	int HashIndex = CalculateHashIndex(NewNode->name);
	
	/* a linked list does not exist for this cell of the array */
	if (chelseaplayer[HashIndex] == NULL)
	{
		#if PRINTINSERT
		printf("\nInserting %s at index %d\n", NewNode->name, HashIndex);
		#endif
		chelseaplayer[HashIndex] = NewNode;
	}
	else   /* A Linked List is present at given index of Hash Table */ 
	{
		CHELSEAPLAYER *TempPtr = chelseaplayer[HashIndex];
	
		/* Traverse linked list */
		while (TempPtr->next_ptr != NULL) 
		{
			TempPtr = TempPtr->next_ptr;
		}
		TempPtr->next_ptr = NewNode;
		#if PRINTINSERT
		printf("\nInserting %s at index %d\n", NewNode->name, HashIndex);
		#endif
	}
}

void FreeDynamicMemory(CHELSEAPLAYER *chelseaplayer[])
{
	CHELSEAPLAYER *TempPtr = NULL, *NextPtr = NULL;
	
	for (int i = 0; i < HASHTABLESIZE; i++)
	{
		TempPtr = chelseaplayer[i];
 
		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL) 
			{
				free(TempPtr->name);
				free(TempPtr->country);
				NextPtr = TempPtr->next_ptr;
				free(TempPtr);
				TempPtr = NextPtr;
			}	
		}
	}
}


/* Remove an element from Hash Table */ 
int DeleteNode(CHELSEAPLAYER *chelseaplayer[])
{
	char LookupName[100] = {};
	int result = 0;
	
	printf("Enter the name of the Player you'd like to release from the Squad ");
	scanf("%s", LookupName);

	int HashIndex = CalculateHashIndex(LookupName);

	/* Get linked list at key in array */
	CHELSEAPLAYER *TempPtr = chelseaplayer[HashIndex];
	CHELSEAPLAYER *PrevPtr = NULL;
 
	/* This array index does not have a linked list; therefore, no keys */
	if (TempPtr == NULL) 
	{
		printf("\n\nPlayer %s does not exist in the current Squad\n\n", LookupName);
		result = 0;
	}
	else 
	{
		while (TempPtr != NULL) 
		{
			if (strcmp(TempPtr->name, LookupName) == 0)
			{
				/* If the node being deleted is the head node */
				if (TempPtr == chelseaplayer[HashIndex])
				{
					/* The node the head was pointing at is now the head */
					chelseaplayer[HashIndex] = TempPtr->next_ptr;
					printf("\nPlayer %s has been released from the Squad\n\n", TempPtr->name);
					free(TempPtr);
					TempPtr = NULL;
				}
				/* Found node to be deleted - node is not the head */
				else
				{
					PrevPtr->next_ptr = TempPtr->next_ptr;
					printf("\nPlayer %s has been released from the Squad\n\n", TempPtr->name);
					free(TempPtr);
					TempPtr = NULL;
				}
				result = 1;
			}
			/* this is not the node that needs to be deleted but save */
			/* its info and move to the next node in the linked list  */
			else
			{
				PrevPtr = TempPtr;
				TempPtr = TempPtr->next_ptr;
			}
		}
		if (result == 0)
		{
			printf("\n\nPlayer %s does not exist in the current Squad\n\n", LookupName);
		}
	}
	return result;
}

/* display the contents of the Hash Table */
void DisplayHashTable(CHELSEAPLAYER *chelseaplayer[])
{
	int i;
	CHELSEAPLAYER *TempPtr = NULL;
	
	for (i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = chelseaplayer[i];

		printf("\nSquad List[%d]-", i);
		
		if (TempPtr != NULL) 
        {
			while (TempPtr != NULL)
			{
				printf("%s|", TempPtr->name);
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
}

void ShowByLetter(CHELSEAPLAYER *chelseaplayer[])
{
	int i;
	//POKEMON *TempPtr = NULL;
    CHELSEAPLAYER *TempPtr = NULL;
	char LookupLetter = 'A';

	printf("\n\nEnter a letter of the alphabet ");
	scanf(" %c", &LookupLetter);
	LookupLetter = toupper(LookupLetter);

	for (i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = chelseaplayer[i];

		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL)
			{
				if (toupper(TempPtr->name[0]) == LookupLetter)
				{
					printf("%s\n", TempPtr->name);
				}
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
}


void ShowByName(CHELSEAPLAYER *chelseaplayer[])
{
    //name, country, market_value, fifa22_rating, position
	CHELSEAPLAYER *TempPtr = NULL;
	char LookupName[100] = {};
	int FoundIt = 0;
	
	printf("\n\nEnter Player's name ");
	scanf("%s", LookupName);
	
	#if TIMING
	clock_t start, end;
	start = clock();
	#endif
	for (int i = 0; i < HASHTABLESIZE; i++) 
	{
		TempPtr = chelseaplayer [i];

		if (TempPtr != NULL) 
		{
			while (TempPtr != NULL)
			{
				if (strcmp(TempPtr->name, LookupName) == 0)
				{
					#if TIMING
					end = clock();
					printf("\n\nSearch took %ld tics\n\n", end-start);
					#endif

					FoundIt = 1;
					printf("\n\n%s\n", TempPtr->name);
                    printf("Country\t%s\n", TempPtr->country);
                    printf("Market Value\t\t$%.1f mil\n", TempPtr->market_value);
                    printf("FIFA22 Rating\t%d\n", TempPtr->fifa22_rating);
                    printf("Position\t\t%c\n", TempPtr->position);
				}
				TempPtr = TempPtr->next_ptr;
			}
		}
	}
	
	if (FoundIt == 0)
		printf("\n\nCouldn't find %s in the current Squad List\n\n", LookupName);
}

void AddNewPokemon(CHELSEAPLAYER *chelseaplayer[])
{
	int HashIndex = 0;
	CHELSEAPLAYER *NewNode;
	char TempBuffer[100] = {};

    //name, country, market_value, fifa22_rating, position
	NewNode = malloc(sizeof(CHELSEAPLAYER));
	NewNode->next_ptr = NULL;

    //setting the player's name
	printf("\n\nEnter new Player's name ");
    fgets(TempBuffer, sizeof(TempBuffer)-1, stdin);
    TempBuffer[strlen(TempBuffer)-1] = '\0';
    NewNode->name = malloc(strlen(TempBuffer)*sizeof(char)+1);
	strcpy(NewNode->name, TempBuffer);

    //setting the player's country
    printf("\n\nEnter new Player's Country of Origin ");
    scanf("%s", TempBuffer);
    NewNode->country = malloc(strlen(TempBuffer)*sizeof(char)+1);
    strcpy(NewNode->country, TempBuffer);

    //
	printf("\n\nEnter %s's transfer market value in US Millions ", NewNode->name);
	scanf("%f", &(NewNode->market_value));
	
	printf("\n\nEnter %s's FIFA22 overall rating ", NewNode->name);
	scanf("%d", &(NewNode->fifa22_rating));
	
	printf("\n\nEnter %s's possible gender (M/F/B/U) ", NewNode->name);
    printf("\n\nEnter %s's position [G]oalKeeper/ [D]efender/ [M]idfielder/ [F]orward", NewNode->name);
	scanf(" %c", &(NewNode->position));
	NewNode->position = toupper(NewNode->position);

	AddNode(NewNode, chelseaplayer);
}

int ReadFileIntoHashTable(int argc, char *argv[], CHELSEAPLAYER *chelseaplayer[])
{
	FILE *FH = NULL;
	char FileLine[100] = {};
	char *token = NULL;
	int counter = 0;
	int HashIndex = 0;
    CHELSEAPLAYER *NewNode;

	/*if (argc > 1)
	{*/
		//FH = fopen(argv[1], "r");
        //FH = fopen("Pokedex.txt", "r");
        FH = fopen("InputFile.txt", "r");
		if (FH == NULL)
		{
			perror("Exiting ");
			exit(0);
		}
		
		while (fgets(FileLine, sizeof(FileLine)-1, FH))
		{
            if (FileLine[strlen(FileLine)-1] == '\n')
            {
                FileLine[strlen(FileLine)-1] = '\0';
            }
			//Pichu|1.00|4.4|B|Tiny Mouse|Static|1|172
            //Kepa|Spain|11.0|79|G
            token = strtok(FileLine, "|");

			NewNode = malloc(sizeof(CHELSEAPLAYER));
			NewNode->next_ptr = NULL;
			
			NewNode->name = malloc(strlen(token)*sizeof(char)+1);
			strcpy(NewNode->name, token);

			token = strtok(NULL, "|");
            NewNode->country = malloc(strlen(token)* sizeof(char)+1);
            strcpy(NewNode->country, token);
			
			token = strtok(NULL, "|");
            NewNode->market_value = atof(token);
			//NewNode->weight = atof(token);

            token = strtok(NULL, "|");
            NewNode->fifa22_rating = atoi(token);

			token = strtok(NULL, "|");
			NewNode->position = *token;

			AddNode(NewNode, chelseaplayer);

			counter++;
		}

	/*}
	else
	{
		printf("File must be provided on command line...exiting\n");
		exit(0);
	}*/
	
	fclose(FH);
	
	return counter;
}

int main(int argc, char *argv[]) 
{

	int MenuChoice = 0;
	int counter = 0;
	//POKEMON *Pokedex[HASHTABLESIZE] = {};
    CHELSEAPLAYER *chelseaplayer[HASHTABLESIZE] = {};

	enum Menu {SHOWBYLETTER=1, SHOWBYNAME, COUNT, DISPLAY, ADD, DELETE, EXIT};
 
	//counter = ReadFileIntoHashTable(argc, argv, Pokedex);
    counter = ReadFileIntoHashTable(argc, argv, chelseaplayer);
	do
	{
		printf("\n\nChelsea Player Menu\n\n"
			   "1. Show all Players in the Squad for a given letter\n"
			   "2. Look up a Chelsea Player by name\n"
			   "3. How many Players are in the Squad?\n"
			   "4. Display the Squad\n"
			   "5. Add a new player to Squad\n"
			   "6. Release a Player from the Squad\n"
			   "7. Exit\n\n"
			   "Enter menu choice ");
	
		scanf("%d", &MenuChoice);
		printf("\n\n");

		switch (MenuChoice)
		{	
			case SHOWBYLETTER:
                ShowByLetter(chelseaplayer);
                //ShowByLetter(Pokedex);
				break;
			case SHOWBYNAME:
				ShowByName(chelseaplayer);
				break;
			case COUNT:
				printf("Your Squad has %d Players\n", counter);
				break;
 			case DISPLAY:
				DisplayHashTable(chelseaplayer);
				break;
			case ADD:
				AddNewPokemon(chelseaplayer);
				counter++;
				break;
			case DELETE:
				if (DeleteNode(chelseaplayer))
				{
					counter--;
				}
				break;
			case EXIT:
				break;
			default : 
				printf("Invalid menu choice\n\n"); 
		}
	}
	while (MenuChoice != EXIT);
	
	FreeDynamicMemory(chelseaplayer);

	return 0;
}			  
