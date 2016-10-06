#include <stdio.h>
#include <string.h>
#include <stdlib.h>

FILE* openFile(){
	FILE* fp = fopen("./users.dat", "r");
	if(fp == NULL) {
		printf("Could not open file.\n");
	}
	return fp;
}

char ** allocateStrings(int numberOfStrings, int strLength){
	int i;

	char** retVal = (char**)malloc(sizeof(char*) * numberOfStrings);
	
	for (i = 0; i < numberOfStrings; i++){
		retVal[i] = (char*)malloc(sizeof(char) * (strLength + 1));
	}
	return retVal;
}

int getNumLogins(FILE* fp){
	int numLines = 0;
	char temp;
	while((temp = fgetc(fp)) != EOF) {
		if(temp == '\n') {
			numLines++;
		}
	}
	return (numLines/2);
}

char** getUsernames(FILE* fp, int numLogins) {
	fseek(fp, 0, 0);

	char line[64];
	char** usernames = allocateStrings(numLogins, 255);

	int currentLine = 0;
	while(fgets(line, sizeof(line), fp)) {
		if (currentLine % 2 == 0){
			strcpy(usernames[currentLine/2], line);
		}
		currentLine++;
	}
	return usernames;
}

char** getPasswords(FILE* fp, int numLogins) {
	fseek(fp, 0, 0);

	char line[64];
	char** passwords = allocateStrings(numLogins, 255);
		
	int currentLine = 0;
	while(fgets(line, sizeof(line), fp)) {
		if (currentLine % 2 == 1){
			strcpy(passwords[currentLine/2], line);
		}
		currentLine++;	
	}	
	return passwords;
}

char* getUsernameInput(){
	char* username = (char*)malloc(256);	
	printf("Enter Username: ");
	scanf("%s", username);
	return username;
}

char* getPasswordInput(){
	char* password = (char*)malloc(256);
	printf("Enter Password: ");
	scanf("%s", password);
	return password;
}

char* evaluateOutput(char** usernames, char** passwords, char* usernameInput, char* passwordInput, int numLogins){
	int usernameIndex = -1;
	int i;
	char* givenUName = strcat(usernameInput, "\n");
	char* givenPass = strcat(passwordInput, "\n");
	for(i = 0; i < numLogins; i++){
		if(strcmp(usernames[i], givenUName) == 0){
			usernameIndex = i;
			break;
		}
	}
	if(usernameIndex == -1)
		return "Login failed!";
	if(strcmp(passwords[usernameIndex], givenPass) == 0)
		return "Successfully logged in!";
	return "Login failed!";
}

void printUsernames(char** usernames, char** passwords, int numLogins){
	printf("Num Logins: %d\n", numLogins);
	int i;
        for(i = 0; i < numLogins; i++)
                printf("u: %s ~> p: %s\n", usernames[i], passwords[i]);
	return;
}

void main(int argc, char** argv){
	FILE* fp = openFile();
	int numLogins = getNumLogins(fp);
	char** usernames = getUsernames(fp, numLogins);
	char** passwords = getPasswords(fp, numLogins);	
	//printUsernames(usernames, passwords, numLogins);
	char*  usernameInput = getUsernameInput();
	char*  passwordInput = getPasswordInput();
	char*  output = evaluateOutput(usernames, passwords, usernameInput, passwordInput, numLogins);

	printf("%s\n", output);

	//Close file
	fclose(fp);
	//Free the allocated variables for practice
	free(usernames);
	free(passwords);
	free(usernameInput);
	free(passwordInput);
}
