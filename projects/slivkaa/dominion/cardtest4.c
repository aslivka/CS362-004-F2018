/* -----------------------------------------------------------------------
 * To compile this file include the following lines in your makefile:
 *
 * testUpdateCoins: cardtest4.c dominion.o rngs.o testLib.o
 *      	gcc -o cardtest4 -g cardtest4.c dominion.o rngs.o testLib.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "testLib.h"

#define TESTCARD "Great Hall"
int main(){

    /* Basic testing for Great Hall
    1. +1 card draw from deck/discard pile 
    2. add +1 actions to game state
    3. great halld card discarded from hand, playedCardCount+1
    4. check state changes to other player's decks/hands     
     */  
    int numPasses = 0;
    int expected[3], actual[3];
    // int i, j;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2, thisPlayer = 0;
	struct gameState initG, testG;
	int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

	// initialize a game state and player cards
	initializeGame(numPlayers, k, seed, &initG);  
    // copy the game state to a test case
    memcpy(&testG, &initG, sizeof(struct gameState));
    //Playing card
    choice3 = thisPlayer;
	cardEffect(great_hall, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	// ----------- TEST 1: player gains +1 card draw from deck  --------------
    expected[0] = initG.deckCount[thisPlayer] - 1;
    actual[0] = testG.deckCount[thisPlayer];
    if( (expected[0] == actual[0])  ){ 
        printf("TEST 1: PASS player 1 draws +1 card from deck\n");
        printf("\tdeck card count = %d, expected = %d\n", actual[0], expected[0]);
        numPasses++;
    }
    else{
        printf("TEST 1: FAIL player 1 doesn't draw +1 card from deck\n");
        printf("\tdeck card count = %d, expected = %d\n", actual[0], expected[0]);
    }

	// ----------- TEST 2: player 1 gains +1 actions --------------
    expected[0] = initG.numActions + 1;
    actual[0] = testG.numActions;
    if(expected[0] == actual[0]){ 
        printf("TEST 2: PASS player 1 gains +1 action\n");
        printf("\tnum of actions = %d, expected = %d\n", actual[0], expected[0]);
        numPasses++;
    }
    else{
        printf("TEST 2: FAIL player 1 doesnt' gain +1 action\n");
        printf("\tnum of actions = %d, expected = %d\n", actual[0], expected[0]);
    }

    // ----------- TEST 3: player 1 discards card from hand --------------
    expected[0] = initG.playedCardCount + 1;
    expected[1] = 0;
    actual[0] = testG.playedCardCount;
    actual[1] = (initG.handCount[thisPlayer] - testG.handCount[thisPlayer]);
    if( (expected[0] == actual[0]) && (expected[1] == actual[1])){ 
        printf("TEST 3: PASS player 1 discards village card from hand\n");
        printf("\tnum of playedCards = %d, expected = %d\n", actual[0], expected[0]);
        printf("\tchange of cards in hand = %d, expected = %d\n", actual[1], expected[1]);
        numPasses++;
    }
    else{
        printf("TEST 3: FAIL player 1 doesn't discard village card from hand\n");
        printf("\tnum of playedCards = %d, expected = %d\n", actual[0], expected[0]);
        printf("\tchange of cards in hand = %d, expected = %d\n", actual[1], expected[1]);
    }

    // ----------- TEST 4: check state changes to other player's decks/hands --------------
    expected[0] = initG.handCount[thisPlayer+1];
    expected[1] = initG.deckCount[thisPlayer+1];
    actual[0] = testG.handCount[thisPlayer+1];
    actual[1] = testG.deckCount[thisPlayer+1];
    if((expected[0] == actual[0]) && (expected[1] == actual[1])){
        printf("TEST 4: PASS no state change occured to other player's deck/hand\n");
        printf("\thand count = %d, expected = %d\n", actual[0], expected[0]);
        printf("\tdeck count = %d, expected = %d\n", actual[1], expected[1]);
        numPasses++;
    }
    else{
        printf("TEST 4: FAIL state change occured to other player's deck/hand\n");
        printf("\thand count = %d, expected = %d\n", actual[0], expected[0]);
        printf("\tdeck count = %d, expected = %d\n", actual[1], expected[1]);
    }

    if(numPasses == 4){
       printf("TEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("TEST FAILED\n");
    }

   return 0;
}