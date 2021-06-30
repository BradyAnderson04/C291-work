/*
TODO:
Write a Program that does the following: Spam Checker
Research online some of the most common spam e-mail messages and words, and check your own
junk e-mail folder. Create a list of 30 words and phrases commonly found in spam messages. Write
a program in which the user enters an e-mail message. Read the message into a large character array
and ensure that the program does not attempt to insert characters past the end of the array. Then
scan the message for each of the 30 keywords or phrases. For each occurrence of one of these within
the message, add a point to the message�s �spam score.� Next, rate the likelihood that the message
is spam, based on the number of points it received. Print your results in a tabulator format showing 
the words (highest likelihood first)
*/

#define word_count 30
#define max_word_length 20 

#include <stdio.h>
#include <string.h>

// function prototypes
int check_spam_words(char message[2000]);
void display_spam_word(void);

// global vars
char spam_word[word_count][max_word_length] = {"billion", "cash bonus", "debt", "free", "investment", "membership", "money", "trial", "price", "earnings", "prize", "risk", "promotion", "now", "instant", "limited", "winner", "buy", "direct", "marketing", "catch", "cost", "hidden", "fees", "spam", "approved", "mortage", "opportunity", "incredible", "deal"};

int main(void) 
{
	char message[2000];

	printf("Insert an email message to check if it is spam: ");
	fgets(message, 2000, stdin);


	printf("message: \n %s\n", message);

	int result = check_spam_words(message);

	if(3 < result && result <= 7){
		printf("There are %d spam words in your email. This is likely to be spam.\n", result);
	} else if(result > 7){
		printf("There are %d spam words in your email. This is very likely to be spam.\n", result);
	}else {
		printf("There are %d spam words in your email. This is not likely to be spam.\n", result);
	}

	display_spam_word();

	return 0;
}

int check_spam_words(char message[2000])
{
	// useful vars
	int spam_score = 0;
	char delim[2] = " ";

	// split input message by spaces -- can't initialize to a pointer so much use strcpy
   	char * word = strtok(message, delim);
   
	// iterate through all the words and compare
	while(word != NULL) {
		// iterate through the word list and compare it to processed word
		int i;
		for(i = 0; i < word_count; i++){
			if(strcmp(spam_word[i], word) == 0){
				// current word is spam word
				spam_score++;
			}
		}
		// go to the next word value
		word = strtok(NULL, delim);
	}
	return spam_score;
}

void display_spam_word(void)
{
	printf("Words used to filter for spam:\n");
	int i;
	for(i = 0; i < word_count; i++){
		if(i % 10 == 0)
		{
			printf("\n");
		}
		printf("%d.%-10s\t", i+1, spam_word[i]);
	}
	printf("\n");
}
