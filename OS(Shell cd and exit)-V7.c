/*
LAST UPDATED : 19:46,13/05/2020 By Vivek M R






X-----------------CHANGE LOGS------------------X

V1.0 Log :
			1.Bug : cd not functioning as expected.Debugging needs to take place at main and parameter passsing to cd function.
			2.Bug : Commands need to be entered with a space at the end always. Ex: exit command,pwd,etc.

V2.0 Log :
			1.Bug : Commands like exit and pwd not recognised. Seems to be a problem with main function.Debugging is necessary.
			2.Bug : cd still not functional . Debugging at main and parameter passing is completed. Check if getcwd is changing the value of
					s in main before passing.

V3.0 Log :
			1. Bug : chdir changes the working directory of just the process/the function and not the working directory of main. There is no
					 way to get around this. So We have to call all chdir functions inside the main itself else doesn't work. So,We have to
					 change cd function,maybe return a directory and then call chdir inside the main.
			2. exit and pwd finally works.

V4.0 Log :
			1. Bug : chdir finally changes directory.It returns 0 if success and -1 if failed.
					 The Culprit was that the string input to the function shouldn't have a \n character. So,Had to Remove it.
					 However cd root,..,/ and error messages are not displayed.
			2. Bug : pwd seems to store the previous directory although no directory change is done.

V5.0 Log :
			1. Help Created.
			2. cd works like almost completely now.Everything from root,..,/ works. pwd fixed.Works and Stores Previous Working Directory as
			   intented.
			3. Bug : cd pwd command doesn't seem to work.

V6.0 Log :
			1. Support for mkdir command updated.Help Updated.
			2. Added ls command to display files in working directory.
			3. cd pwd command fixed.

V7.0 Log :
			1.Removed various debugging functions,printf statements and example functions.
			2.Used Indentation and improved code readability.
			3.Added Comments for Each Function and Main.
			4.Added Some Printf Statements in MAIN to Guide the USER.
*/

#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<dirent.h>
#include<dir.h>
#include<process.h>



char rootdir[100];
char predir[100];


//Function to Create Directory When mkdir command is called.

void createfolder(char* dirname)
{
    int check;
	dirname[strlen(dirname)-1]='\0';
    check = mkdir(dirname);
    if (!check)
        printf("Directory created\n");
    else {
        printf("Unable to create directory\n");
        exit(1);
    };
}



//Function to seperate the "cd" and the directory name when cd command is used.Returns the Directory value to which current has to be updated.

char* cd(char newdir[100])
{
	int i=0;
	while(newdir[i+3]!=NULL)
	{
		newdir[i]=newdir[i+3];
		i++;
	};
	newdir[i]=NULL;
	return(newdir);
}



//Function to seperate the mkdir and name of the directory when mkdir command is used.Returns the Name of the Folder/Directory which has to be created.

char* getname(char a[100])
{
	int i=0;
	while(a[i+6]!=NULL)
	{
		a[i]=a[i+6];
		i++;
	};
	a[i]=NULL;
	return(a);
}



//Function to Display the list of all folders & folders when ls command is used.

int ls()
{
	// Pointer for directory entry
    struct dirent *de;

    // opendir() returns a pointer of DIR type.
    DIR *dr = opendir(".");

	// opendir returns NULL if couldn't open directory
    if (dr == NULL)
    {
        printf("Could not open current directory" );
        return 0;
    }


    while ((de = readdir(dr)) != NULL)
            printf("%s\n", de->d_name);

    closedir(dr);
    return 0;
}


//Function to Display the Details of all available commands.

void help()
{
	printf("\nX------HELP------X\n\nRoot Directory is the directory where this file is present.\n\nAvailable Commands :\n\n1.cd(Change Directory) : \n          'cd root' or 'cd /':changes directory to root directory.\n");
	printf("          'cd ..':changes directory to one main directory above the current directory\n          'cd pwd':changes directory to previous working directory\n");
	printf("          'cd [path_value]':changes directory to [path_value] if it exists\n");
	printf("2.pwd(Previous Working Directory) : \n           'pwd':Displays the previous working directory\n");
	printf("3.ls(List Files and Folders) :\n          'ls':Displays a list of names of all files and folders in the current directory\n");
	printf("4.mkdir(Make Directory) :\n          'mkdir [dir_name]':Creates a Folder//Directory by the name of [dir_name] in the working directory\n");
	printf("5.help\n          'help':Displays the set of all possible commands\n");
	printf("6.exit\n          'exit':Exits the program/shell\n");
}



//MAIN FUNCTION

void main()
{
	char s[100];
	char dir[100];
	char com[100];
	chdir("//");
	strcpy(predir,getcwd(rootdir,100));
	strcpy(rootdir,predir);
	printf("This C program Simulates & Performs a variety of Linux Shell Commands.For a list of implemented commands,use 'help'\n\n");
	printf("WARNING!! \nThis program allows creation of actual Folders during execution in the directories just like a shell.\n");
	printf("And Even After Exiting the Program,The Folders Created are NOT Deleted.\n");
	printf("\nTested On CodeBlocks IDE. Compiler Used : GNU GCC Compiler.\n\n");
	while(1)
	{
		printf("\n%s>>",getcwd(s,100));//Prints Current Working Directory and waits for command.
		fgets(com,100,stdin);
		strcpy(s,com);
		if(strcmp(strtok(com," "),"cd")==0)//Checks if the letters before space are cd.Hence Checks for cd command
		{
			strcpy(dir,cd(s));
			dir[strlen(dir)-1]='\0';
			if((strcmp(dir,"root")==0)||(strcmp(dir,"Root")==0)||(strcmp(dir,"ROOT")==0)||((strcmp(dir,"/")==0)))
				strcpy(dir,rootdir);
			if((strcmp(dir,"pwd")==0)||(strcmp(dir,"Pwd")==0)||((strcmp(dir,"PWD")==0)))
				strcpy(dir,predir);
			strcpy(predir,getcwd(predir,100));
			if(chdir(dir)==0)
			chdir(dir);
			else printf("Invalid Directory");
			continue;
		}
		else if(strcmp(s,"exit\n")==0)//Checks for exit command
		{
			printf("Exiting...Press any key\n");
			getch();
			exit(0);
		}
		else if(strcmp(com,"help\n")==0)//Checks for help command
			help();
		else if(strcmp(s,"pwd\n")==0)//Checks for pwd command
		{
			printf("%s",predir);
		}
		else if(strcmp(s,"ls\n")==0)//Checks for ls command
			ls();
		else if(strcmp(strtok(com," "),"mkdir")==0)//Checks for mkdir command
			createfolder(getname(s));
		else printf("Invalid command\n");
	};
}




