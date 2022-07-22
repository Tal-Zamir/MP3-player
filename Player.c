//Tal Zamir
//ID 203528433
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>               // define the header file
#include<stdlib.h>
#include<string.h>

#define TRUE 1
#define FALSE 0

struct Songs
{
    int  ID;
	char ArtistName[30];
	char AlbumName[30];
	char TrackName[30];
    int  TrackNo;
}db;
// ID,Artist Name , Album Name , Track Name , Track No 
#define BUFFER_SIZE 1000

void clrscr()
{
    system("@cls||clear");
}

void DisplayRecord()
{

    FILE * fPtr;
    char ch;
    fPtr = fopen("songs.txt", "r");
    if(fPtr == NULL)
    {
        printf("Unable to open file.\n");
        printf("Please check whether file exists and you have read privilege.\n");
        exit(0);
    }
    printf("File opened successfully. Reading file contents character by character. \n\n");
    do 
    {
        /* Read single character from file */
        ch = fgetc(fPtr);

        /* Print character read on console */
        putchar(ch);

    } while(ch != EOF); /* Repeat this if last read character is not EOF */
    /* Done with this file, close file to release resource */
    fclose(fPtr);
}

//Add a song addID,addArtistName,addAlbumName,addTrackName,addTrackNo int  addID=0;
void insert()
{
int temp=0;
 FILE *fp;
 fp = fopen("songs.txt", "a");
				printf("Add a song \n");							// add to file also	
				printf("Enter ID:  ");								// Enter Record ID
				scanf("%d",&db.ID);								 	// Enter here
				printf("Enter Artist Name:  ");                     // Enter Artist Name  
				scanf("%s",&db.ArtistName);							// Enter here
				printf("Enter Album Name:  ");                      // Enter Album Name
				scanf("%s",&db.AlbumName);							// Enter here
				printf("Enter Track Name:  ");                      // Enter Track Name
				scanf("%s",&db.TrackName);							// Enter here
				printf("Enter Track No:  ");                        // Enter Track No
				scanf("%d",&db.TrackNo);							// Enter here		
                fprintf(fp, "\n");
				fwrite(&db, sizeof(db), 1, fp);
           		printf("Data Entered Successfully\n");
 fclose(fp);
 	printf("\nPress 1 to go to Main Menu\n");		        // Print content of song
    scanf("%d",&temp);		                            // Enter your Choice
    clrscr();
}

//Sort
void Sort()
{
	int temp=0;
 int a[20], count = 0, i, j, t, c;
 FILE *fpo;
 fpo = fopen("songs.txt", "r");
 while (fread(&db, sizeof(db), 1, fpo))
 {
  a[count] = db.ID;
  //printf("\n %d",a[count]);
  count++;
 }
 c = count;
 for (i = 0; i<count - 1; i++)
 {
  for (j = i + 1; j<count; j++)
  {
   if (a[i]>a[j])
   {
    t = a[i];
    a[i] = a[j];
    a[j] = t;
   }
  }
 }
 printf("ID \t ArtistName \t AlbumName \t TrackName \t TrackNumber \n");
 count = c;
 for (i = 0; i<count; i++)
 {
  rewind(fpo);
  while (fread(&db, sizeof(db), 1, fpo))
  {
   if (a[i] == db.ID)
    printf("\n %s\t %s \t %s \t %d",db.ArtistName, db.AlbumName, db.TrackName, db.TrackNo);
  }

 }
 printf("\nPress 1 to go to Main Menu\n");		        // Print content of song
 scanf("%d",&temp);		                            // Enter your Choice
    clrscr();
}

//Delete a song
void deleteRecordByArtist(char *a) 
{
	FILE *fp;
	FILE *fp_tmp;
	int found=0;
    int temp=0;
	fp=fopen("songs.txt", "rb");
	if (!fp) {
		printf("Unable to open file %s", a);
		exit(0);
	}
	fp_tmp=fopen("tmp.bin", "wb");
	if (!fp_tmp) {
		printf("Unable to open file temp file.");
		exit(0);
	}
	while((fread(&db,sizeof(struct Songs),1,fp)==1))
	{
		if ((strstr(db.ArtistName, a)) != NULL) {
			printf("A record with requested name found and deleted.\n\n");
			printf("%s",db.ArtistName);
			found=1;
		} else {
			fwrite(&db, sizeof(struct Songs), 1, fp_tmp);
		}
	}
	if (! found) {
		printf("No record(s) found with the requested name: %s\n\n", a);
	}

	fclose(fp);
	fclose(fp_tmp);

	remove(a);
	rename("tmp.bin", a);
    DisplayRecord();
	printf("\nPress 1 to go to Main Menu\n");		        // Print content of song
    scanf("%d",&temp);		                            // Enter your Choice
    clrscr();
}


//Search song by Artist
void SearchRecord(char *a)
{
	
	int temp=0;
	FILE *fptr;
	int found=0;
	fptr=fopen("songs.txt","rb");	
if(fptr==NULL)
{
printf("File could not open");
exit(0);
}
while((fread(&db,sizeof(db),1,fptr)==1))
{
	if((strstr(db.ArtistName, a)) != NULL)
	{
	found=1;
	printf("---------------------------------------------------------------------\n");
	printf(":::::::::: Search Found Successfully ::::::::");
    printf("---------------------------------------------------------------------\n");
	break;
}
}
if(found==0)
   printf("\n Record Not found in this file!");
else
   DisplayRecord();

fclose(fptr);
printf("\nPress 1 to go to Main Menu\n");		        // Print content of song
    scanf("%d",&temp);		                            // Enter your Choice
    clrscr();
}

// Play song from  file
void PlaySong(int songno)
{
    int temp=0;
    char buffer[BUFFER_SIZE];
    int totalRead = 0;
    int rec=0;
    FILE *fp = fopen("songs.txt", "r");

	if(fp == NULL) 
	{
		printf("File does not exist! \n\n");
        exit(1);
	}
	
    while(fgets(buffer, BUFFER_SIZE, fp) != NULL)               // Repeat this until read line is not NULL 
    {
        totalRead = strlen(buffer);                             // Total character read count 
        buffer[totalRead - 1] = buffer[totalRead - 1] == '\n'  ? '\0' : buffer[totalRead - 1];          // Trim new line character from last if exists.
        if(rec == songno)
        {
            printf("%s\n", buffer);                         // Print line read on cosole
            break;
        }
        rec++;
    } 
    fclose(fp);
    printf("\nPress 1 to go to Main Menu\n");		        // Print content of song
    scanf("%d",&temp);		                            // Enter your Choice
    clrscr();							                // clear the screen
}

int main(void)                     // define the main function  
{  
	int menuselect, num, i;
    unsigned long int fact;
	char searchparam[30];		// use this for search parameters ( Artist name , Album name , Track name )
	int SongIndex =0;			// 0 means first song
	int  addID=0;
	char addArtistName[30];
	char addAlbumName[30];
	char addTrackName[30];
    int  addTrackNo=0;
    FILE *ptr;
    struct Songs aDD;

	FILE *fp = fopen("songs.txt", "r");
	if(fp == NULL) 
	{
		printf("File does not exist! \n\n");
        exit(1);
	}
	else 
	{
		printf("Playlist File open Successfully!\n");
	}    
	fclose(fp);

    while(1)
    {
        clrscr();
        printf("**** Music Player ****\n\n");
        printf("1. Play a Song \n");									// Print content of song
        printf("2. Next song \n");										// Forward song
		printf("3. Previous song\n");									// Reverse song
        printf("4. Search for song  (Artist - Song - Album)\n");		// Search song by Artist , Song or Album
        printf("5. Delete a song \n");									// Delete from file too
        printf("6. Add a song \n");										// Add to file also
        printf("7. Sort playlist (Artist - Song - Album)\n");			// Add to file also
        printf("8. Exit Player\n");										// Exit Player
        printf("Enter your choice :  ");								// Menu choice 
        scanf("%d",&menuselect);										// Enter your Choice
        
        switch(menuselect)												// As per menu choice Player action will be done
        {
            case 1:							    // Play song 
                clrscr();                       // clear screen        
                printf("Playing song:\n");		
				SongIndex=1;                    // SongIndex - 0 to track song no. in file
                PlaySong(SongIndex);            // Read file and play First song from File
                break;        
            case 2:
                clrscr();                       // clear screen        
                printf("Next Song:\n");			// Next song
				SongIndex++;                	// Go to Next record in File and Show and print in log file                
                PlaySong(SongIndex);            // Read file and play First song from File
                break;        
            case 3:
                clrscr();                       // clear screen        
                printf("Previous Song:\n");     // Previous song
				// Go to previous record in File and show and print in log file
                if(SongIndex > 0)
                {
                    PlaySong(SongIndex);        // Read file and play First song from File
				    SongIndex--;
                }
                break;        
            case 4:
                clrscr();                       // clear screen    
				printf("Search for song  (Artist) \n");	// Search song by Artist , Song or Album						
				scanf("%s", searchparam);
				SearchRecord(searchparam);
        		break;
            case 5:							
				printf("Delete a song  (Artist) \n");	// delete from file too						
				scanf("%s", searchparam);
				deleteRecordByArtist(searchparam);
				break;
            case 6:
            	insert();				
				break;
            case 7:
				printf("Sort playlist (Artist - Song - Album ) \n");	// Sort playlist
				Sort();
				break;
            case 8:
				printf("Exit\n");										// Sort playlist
				exit(1);
				break;
            default:
				printf("Enter Valid choice 1-7 \n");					// Sort playlist
				break;
        }
    }
    getch();
    return 0;
}
