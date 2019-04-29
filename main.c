#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void substituteDecryptCipherOnly(){
	/*
	Input: none
	Return value: none
	Purpose: Reading from input file and doing substitute ciphering and then saving the cipher text into output file
	Flow:
	1) Declaring message alphabet and letterFreq array (that holds the set of letters based on occurrences in english literature in descending order).
	2) Creating file pointers
	3) Counting the occurrence of each char of english alphabet in the input file.
	4) Based on the number of occurrences, we ranked the letters and created a new array cipherLetter.
	5) now based on msgLetter[] and cipherLetter[], we have done substitute de-ciphering.
	6) Printing the character into output file
	7) Closing the file pointers
	*/
	FILE *file_in; //creating file pointers
	FILE *file_out;
	char ch;
	file_in = fopen("substituteDeCipherInput.txt", "r");
	if(file_in == NULL){
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}
	file_out = fopen("substituteDeCipherOutput.txt","w");

	char msgLetter[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //declaring message alphabet
	// declaring LetterFreq that holds the english letters in descending order based on the usual occurrence in english language
	//char letterFreq[]="ETAOINSRHDLUCMFYWGPBVKXQJZ"; //http://pi.math.cornell.edu/~mec/2003-2004/cryptography/subs/frequencies.html
	//char letterFreq[]="EARIOTNSLCUDPMHGBFYWKVXZJQ"; //oxforddictionaries.com/words/what-is-the-frequency-of-the-letters-of-the-alphabet-in-english
	char letterFreq[]="ETAOINSHRDLCUMWFGYPBVKJXQZ"; //https://en.wikipedia.org/wiki/Letter_frequency

	char cipherLetter[26]; //Array of characters that will hold the cipher letters
	int i=0,j =0;
	int letterCount[26]; //Array of int that will hold the count of each english alphabet
	for(i=0;i<26;i++) letterCount[i]=0; //initialising the value of letter count as 0
	int printChar;

	int maxLetter=-1;
	//counting the occurrences of english letters in the file and updating letterCount array
	while(( ch = fgetc(file_in)) != EOF ){
		for(i=0;i<strlen(msgLetter);i++){
			if(msgLetter[i] == toupper(ch)) letterCount[i]=letterCount[i]+1;
		}
	}
	int max =-1, currentMaxPos=-1;
	//finding the most frequent letter based on the values in letterCount array
	for(j=0;j<26;j++){
		for(i=0;i<26;i++){
			if(letterCount[i]>max){
				max = letterCount[i]; //updating the highest count
				currentMaxPos = i; //updating the most frequent char
				}
		}
	cipherLetter[currentMaxPos] = letterFreq[j]; //updating the cipherLetter array
	if(j==0) maxLetter = currentMaxPos;
	letterCount[currentMaxPos] = -2; //updating the current highest count to a negative value so that it does not compete in the the next iteration for finding the next most freq letter
	max = -1; //initialising max back to -1
	}
	rewind(file_in); //going back to the start of file
	char c;
	//reading characters from input file and deciphering the characters based on msgLetter[] and cipherLetter[] array the same way we did in substituteDecrypt() function.
	while((ch = fgetc(file_in)) != EOF ){ //reading the input file character by character
		c=toupper(ch);//converting to uppercase
		if(c>='A'&&c<='Z'){
			for(j=0;j<strlen(cipherLetter);j++){
				if(c==msgLetter[j]) break;
			}
			printChar = cipherLetter[j];
		}
		else printChar = ch;
		fprintf(file_out, "%c", printChar);
	}

	fclose(file_out); //closing the file
	fclose(file_in);
}

void rotateDecryptCipherOnly(){
	/*
	Input: none
	Return value: none
	Purpose: Reading from input file and doing substitute ciphering and then saving the cipher text into output file
	Flow:
	1) Declaring message alphabet and cipher alphabet.
	2) Creating file pointers
	3) COunting the occurrence of each of the english letters in the input file and finding out the most frequently occured char in the file.
		- From this information, we are calculating the shift value
		- based on the shift value, we are de-ciphering the text.
	4) Printing the character into output file
	5) Closing the file pointers
	*/
	FILE *file_in; //creating file pointers
	FILE *file_out;
	char ch;
	file_in = fopen("shiftDeCipherInput.txt", "r");
	if(file_in == NULL){
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}
	file_out = fopen("shiftDeCipherOutput.txt","w");
	char msgLetter[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //declaring message alphabet
	int shift, printChar;

	int i=0,currentCount=0, maxCount = -1, maxLetter=-1;

	for(i=0;i<strlen(msgLetter);i++){ //taking the characters from message alphabet one by one
		currentCount=0;
		while((ch = fgetc(file_in)) != EOF ){ //Counting the current alphabet in input file
			if(msgLetter[i] == toupper(ch)) currentCount++;
		}

		if(currentCount>maxCount) { //updating the max count and highest occurred caharacter in the file
			maxCount=currentCount;
			maxLetter = i;
		}
		rewind(file_in); //going back to the start of file
	}

	//calculating value of shift
	if(msgLetter[maxLetter]>'E') shift = msgLetter[maxLetter] - 'E';
	else if (msgLetter[maxLetter]<'E') shift = 26-('E' - msgLetter[maxLetter]);
	else shift =0;

	char c;
	//based on the shift key, doing the deciphering
	while(( ch = fgetc(file_in)) != EOF ){ //reading the input file character by character
		c=toupper(ch); //converting to uppercase
		if(c>='A'&&c<='Z'){
			if((c-shift)<65) printChar = c-shift+26;
			else printChar = c-shift;
		}
		else printChar = ch;
		fprintf(file_out, "%c", printChar);
	}
	fclose(file_out); //closing the file
	fclose(file_in);
}

void rotateDecrypt(){
	/*
	Input: none
	Return value: none
	Purpose: Reading from input file and doing rotate de-ciphering and then saving the cipher text into output file
	Flow:
	1) creating file pointers
	2) Scanning the "shift" value
	3) reading characters from input file, converting to uppercase. If it is a english letter, then do the shifting (de-ciphering), otherwise leave the character as it is.
	4) printing the character into output file
	5) Closing the file pointers
	 */
	FILE *file_in; //creating file pointers
	FILE *file_out;
	int shift, printChar;
	char c , ch;
	file_in = fopen("shiftDeCipherInput.txt", "r");
	if( file_in == NULL )
		{
			perror("Error while opening the file.\n");
			exit(EXIT_FAILURE);
		}
	file_out = fopen("shiftDeCipherOutput.txt","w");
	printf("Enter a key."); //asking for shift key
	scanf("%d", &shift);
	while(( ch = fgetc(file_in) ) != EOF){ //reading the input file character by character
		c=toupper(ch); //converting to uppercase
		if(c>='A'&&c<='Z'){
			if((c-shift)<65) printChar = c-shift+26; //Getting the de-ciphered character
			else printChar = c-shift;
		}
		else printChar = ch;
		fprintf(file_out, "%c", printChar); //printing to output file
	}
	fclose(file_out); //closing the file
	fclose(file_in);
}

void rotateEncrypt(){
	/*
	Input: none
	Return value: none
	Purpose: reading input file and doing rotate ciphering and then saving the cipher text into output file
	Flow:
	1) creating file pointers
	2) Scanning the "shift" value
	3) reading characters from input file, converting to uppercase. If its is english letter, then do the shifting, otherwise leave the character as it is.
	4) printing the character into output file
	5) Closing the file pointers
	 */
	FILE *file_in, *file_out; //creating file pointers
	file_in = fopen("shiftCipherInput.txt", "r");
	if( file_in == NULL )
	    {
	        perror("Error while opening the file.\n");
	        exit(EXIT_FAILURE);
	    }

	file_out = fopen("shiftCipherOutput.txt","w");

	int shift, printChar;

	printf("Enter a key."); //asking for shift key
	setbuf(stdout, NULL);
	scanf("%d", &shift);

	setbuf(stdout, NULL);
	setbuf(stdin, NULL);
	char ch,c;
	while((ch = fgetc(file_in) ) != EOF ){ //reading the input file character by character
			c=toupper(ch); //converting to uppercase
			if(c>='A'&&c<='Z')
				printChar = (c+shift-65)%26+65; //Getting the ciphered character
			else printChar = ch;
			fprintf(file_out, "%c", printChar); //printing to output file

		    }
	fclose(file_out); //closing the files
	fclose(file_in);

}

void substituteEncrypt(){
	/*
	Input: none
	Return value: none
	Purpose: Reading from input file and doing substitute ciphering and then saving the cipher text into output file
	Flow:
	1) Declaring message alphabet and cipher alphabet.
	2) Creating file pointers
	3) Reading characters from input file, converting to uppercase.
		- If it is a english letter, then we are finding the location of the char in message alphabet and repalcing the char with the respective char from cipher alphabet.
		- Otherwise we are leaving the char as it is.
	4) Printing the character into output file
	5) Closing the file pointers
	*/

	char msgLetter[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //declaring message alphabet
	char cipherLetter[]="QWERTYUIOPASDFGHJKLZXCVBNM"; //declaring cipher alphabet

	FILE *file_in; //creating file pointers
	FILE *file_out;
	char ch, c;
	file_in = fopen("substituteCipherInput.txt", "r");
	if( file_in == NULL){
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}
	file_out = fopen("substituteCipherOutput.txt","w");
	int printChar, j;

	while((ch = fgetc(file_in)) != EOF){ //reading the input file character by character
		c=toupper(ch); //converting to uppercase
		if(c>='A'&&c<='Z'){
			for(j=0;j<strlen(msgLetter);j++){ //Getting the position of the character in the message alphabet
				if(c==msgLetter[j]) break;
			}
			printChar = cipherLetter[j]; //Saving the cipher letter in the same position in the cipher alphabet.
		}
		else printChar = ch; //if ch is non-letter
		fprintf(file_out, "%c", printChar); //printing to output file
	}
	fclose(file_out);//closing the files
	fclose(file_in);
}

void substituteDecrypt(){
	/*
	Input: none
	Return value: none
	Purpose: Reading from input file and doing substitute de-ciphering and then saving the de-ciphered text into output file
	Flow:
	1) Declaring message alphabet and cipher alphabet.
	2) Creating file pointers
	3) Reading characters from input file, converting to uppercase.
		- If it is a english letter, then we are finding the location of the char in cipher alphabet and replacing the char with the respective char from message alphabet.
		- Otherwise we are leaving the char as it is.
	4) Printing the character into output file
	5) Closing the file pointers
	*/
	char msgLetter[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ"; //declaring message alphabet
	char cipherLetter[]="QWERTYUIOPASDFGHJKLZXCVBNM";
	FILE *file_in; //creating file pointers
	FILE *file_out;
	char ch, c;
	file_in = fopen("substituteDeCipherInput.txt", "r");
	if( file_in == NULL){
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}
	file_out = fopen("substituteDeCipherOutput.txt","w");
	int printChar, j;

	while((ch = fgetc(file_in)) != EOF ){ //reading the input file character by character
		c=toupper(ch); //converting to uppercase
		if(c>='A'&&c<='Z'){
			for(j=0;j<strlen(cipherLetter);j++){ //finding position of the cipher letter in cipher alphabet
				if(c==cipherLetter[j]) break;
			}
			printChar = msgLetter[j]; //Saving the respective message letter into printChar
		}
		else printChar = ch; //if the read char is non-letter
		fprintf(file_out, "%c", printChar);//printing to output file
	}
	fclose(file_out);//closing the files
	fclose(file_in);
}

int main(){
	char optionCh;
	do{
		printf("Please select an option: \n");
		printf("a) rotation encryption\n");
		printf("b) rotation decryption\n");
		printf("c) substitution encryption\n");
		printf("d) substitution decryption\n");
		printf("e) rotation decryption cipher text only\n");
		printf("f) substitution decryption cipher text only\n");
		printf("g) Exit\n\n");
		printf("Selection: ");
		setbuf(stdout, NULL);
		scanf("%c", &optionCh);
		}while(optionCh < 'a' || optionCh > 'g');

	switch(optionCh) {
		case 'a': rotateEncrypt(); break;
		case 'b': rotateDecrypt(); break;
		case 'c': substituteEncrypt(); break;
		case 'd': substituteDecrypt(); break;
		case 'e': rotateDecryptCipherOnly(); break;
		case 'f': substituteDecryptCipherOnly(); break;
		case 'g': exit(1); break;
		default: printf("Unknown option. Please enter options between a to g\n");
		}
}

