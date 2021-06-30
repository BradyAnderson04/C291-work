// Fig. 7.24: fig07_24.c
// Card shuffling and dealing.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>

#define SUITS 4
#define FACES 13
#define CARDS 52
#define HAND 5

// prototypes
void shuffle(unsigned int wDeck[][FACES]); // shuffling modifies wDeck
void deal(unsigned int wDeck[][FACES], char *wFace[], char *wSuit[]); // dealing doesn't modify the arrays
bool highCard(char *wFace[]); // ace king queen 9 7 that don't fit any other interaction
bool pairs(); // 2 of same face
bool threeOfKind(); // 3 of same face
bool straight(char *wFace[]); // 5 consecutive face values of any suit
bool fullHouse(); // 3 of 1 face 2 of another face
bool fourOfKind(); // four of 1 face
bool royalFlush(); // A, K, Q, J, 10 of the same suit


// structs
struct card {
   char *face;  // 2-A
   char *suit;  // one of the 4 suits
};

typedef struct card Card; // alias for my struct

// global vars
Card hand[HAND]; // array of Cards

int main(void)
{
   // initialize deck array
   unsigned int deck[SUITS][FACES] = { 0 };

   srand(time(NULL)); // seed random-number generator

   shuffle(deck); // shuffle the deck

   // initialize suit array                       
   char *suit[SUITS] =            
      {"Hearts", "Diamonds", "Clubs", "Spades"};
   
   // initialize face array                   
   char *face[FACES] =
      {"Ace", "Deuce", "Three", "Four",         
       "Five", "Six", "Seven", "Eight",         
       "Nine", "Ten", "Jack", "Queen", "King"};

   deal(deck, face, suit); // deal the deck

   printf("The output will be 0 or 1. 1 maps to true. 0 maps to false.\n");
   printf("Pairs: %d\n", pairs());
   printf("Three of Kind: %d\n", threeOfKind());
   printf("Straight: %d\n", straight(face));
   printf("Full House: %d\n", fullHouse());
   printf("Four of Kind: %d\n", fourOfKind());
   printf("Royal Flush: %d\n", royalFlush());
   printf("High Card: %d\n", highCard(face));
} 

// shuffle cards in deck
void shuffle(unsigned int wDeck[][FACES])
{
   // for each of the cards, choose slot of deck randomly
   for (size_t card = 1; card <= CARDS; ++card) {
      size_t row; // row number
      size_t column; // column number

      // choose new random location until unoccupied slot found
      do {                                                        
         row = rand() % SUITS;                                   
         column = rand() % FACES;                             
      } while(wDeck[row][column] != 0); // end do...while

      // place card number in chosen slot of deck
      wDeck[row][column] = card;
   } 
}

// deal cards in deck
void deal(unsigned int wDeck[][FACES], char *wFace[], char *wSuit[]){
   /*
      rewrote function to generate the deck
   */
   // deal 5 of the cards
   size_t card;
   for (card = 0; card < HAND; ++card) {
      // create a random var for face and suit
      int rand_suit = rand() % 4;
      int rand_face = rand() % 13;
      // create a temp Card var
      Card temp = {wFace[rand_face], wSuit[rand_suit]};
      // add to the hand
      hand[card] = temp;
      // print the temp card 
      printf("%5s of %-8s%c", temp.face, temp.suit, card % 2 == 0 ? '\n' : '\t'); // 2-column format
   }
}

/*
All of these functions should process the Hand global variable defined and initialized by the deck
I will not use deal in any of functions and assume that the deal has been done before hand...(pun)
*/

int cardIndex(char* val, char *wFrace[]){
   int i;
   for(i = 0; i < FACES; i++){
      if(strcmp(val, wFrace[i]) == 0){
         return i;
      }
   }
   return -1;
}

bool highCard(char *wFace[]){
   // ace king queen 9 7 that don't fit any other interaction
   // check for any other interactions using other functions
   if(!pairs() && !straight(wFace) && !fullHouse() && !royalFlush() && !threeOfKind() && !fourOfKind()){
      // loop through hand
      int i;
      for(i = 0; i < HAND; i++){
         // if the hand has a 9, 7, a, q, k return true
         if(strcmp(hand[i].face, "Nine") == 0 || strcmp(hand[i].face, "Seven") == 0 || strcmp(hand[i].face, "Ace") == 0 || strcmp(hand[i].face, "King") == 0 || strcmp(hand[i].face, "Queen") == 0){
            return true;
         }
      }
   }
   // catch all case....either conditions are met or hand doesn't contain anything of value
   return false;
   
} 

bool pairs(){
   // 2 of same face
   int i,j;
   for(i = 0; i < HAND; i++){
      // local var reset every roation
      int count = 0;
      for(j = 0; j < HAND; j++){
         // only when comparing difference cards
         if(i != j){
            if(strcmp(hand[i].face, hand[j].face) == 0){
               count += 1;
            }
         }
      }
      // a pair exists
      if(count == 1){
         return true;
      }
   }
   // implicit else -> return false if no pairs
   return false;
} 

bool threeOfKind(){
   // 3 of same face - similar to 2 of a kind
   int i, j;
   for(i = 0; i < HAND; i++){
      // local var reset every roation
      int count = 0;
      for(j = 0; j < HAND; j++){
         // only when comparing difference cards
         if(i != j){
            // check if different cards have same value
            if(strcmp(hand[i].face, hand[j].face) == 0){
               count += 1;
            }
         }
      }
      // a trio exists
      if(count == 2){
         return true;
      }
   }
   // implicit else -> return false if no trio
   return false;
}

bool straight(char *wFace[]){
   // 5 consecutive face values of any suit
   // initial card will set the average - this is the vulnerbility in code
   // could improve by choosing the highest value -> code doesn't work for one very particular scenario so low probability of not working 1 / 52! pretty much
   Card comparable = hand[0];

   double average = cardIndex(comparable.face, wFace);

   // check conditions for rest of cards
   int i;
   for(i = 1; i < HAND; i++){
      // get index of new card
      double temp = cardIndex(hand[i].face, wFace);
      // check if the card value is too far away (> 3 distance)
      if(fabs(average - temp) > 3){
         return false;
      } else {
         // recalc average - 2 values of ace scenario going to apply when it matters
         if(strcmp(hand[i].face, "Ace") == 0 && average > 8){
            // ace is worth king + 1
            average = (average + FACES) / 2;
         } 
         else {
            // o.w. - ace and everything worth the same
            average = (average + temp) / 2;
         }
      }
   }
   // if code get here then all are fitting condition
   return true;
}

bool fullHouse(){
   // 3 of 1 face 2 of another face
   // check for trio - exclusively
   bool threeCombo = threeOfKind();
   // check for a duo - exclusively
   bool twoCombo = pairs();
   // return the and combination of the 2 results
   return threeCombo && twoCombo;
}

bool royalFlush(){
   // A, K, Q, J, 10 of the same suit 
   Card comparable = hand[0];
   // if comparable is not one of the face values then return false
   if(strcmp(comparable.face, "Ace") != 0 && strcmp(comparable.face, "King") != 0 && strcmp(comparable.face, "Queen") != 0 && strcmp(comparable.face, "Jack") != 0 && strcmp(comparable.face, "Ten") != 0){
      return false;
   }
   int i;
   for(i = 1; i < HAND; i++){
      // check if same suit
      if(strcmp(hand[i].suit, comparable.suit) == 0){
         // check the next card to be one of the values -> impossible to have repeats so not a concern
         if(strcmp(hand[i].face, "Ace") != 0 && strcmp(hand[i].face, "King") != 0 && strcmp(hand[i].face, "Queen") != 0 && strcmp(hand[i].face, "Jack") != 0 && strcmp(hand[i].face, "Ten") != 0){
            return false;
         }
      } else {
         return false;
      }
   }
   // made it to here therfore you have a royal flush - all conditions would have return false already if not a royal flush
   return true;
}

bool fourOfKind(){
   // four of 1 face - similar to 2 and 3 of a kind!
   int i, j;
   for(i = 0; i < HAND; i++){
      // local var reset every roation
      int count = 0;
      for(j = 0; j < HAND; j++){
         // only when comparing difference cards
         if(i != j){
            // check if different cards have same value
            if(hand[i].face == hand[j].face){
               count += 1;
            }
         }
      }
      // a quad exists
      if(count == 3){
         return true;
      }
   }
   // implicit else -> return false if no quad
   return false;
}