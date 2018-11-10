/* -----------------------------------------------------------------------
 * To compile this file include the following lines in your makefile:
 *
 * testUpdateCoins: cardtest1.c dominion.o rngs.o testLib.o
 *      	gcc -o cardtest1 -g cardtest1.c dominion.o rngs.o testLib.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */
#include "testLib.h"

#define TESTCARD "Smithy"
int main(){

    /* Basic requirements for smithy
    1. Current player should receive exact 3 cards.
    2. 3 cards should come from his own pile.
    3. No state change should occur for other players.
    4. No state change should occur to the victory card piles and kingdom card piles.

     */  
    int actual, expected, numPasses = 0;
    int newCards = 0;
    int discarded = 1;
    int i, j;
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
	cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);

	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
	// ----------- TEST 1: player should receive exactly 3 cards --------------
    newCards = 3;
    actual = testG.handCount[thisPlayer];
    expected = initG.handCount[thisPlayer] + newCards;
    if(actual == expected){
        printf("TEST 1: PASS player 1 received exactly 3 cards\n");
        printf("\thand count = %d, expected = %d\n", actual, expected);
        numPasses++;
    }
    else{
        printf("TEST 1: FAIL current player didnt' receive exactly 3 cards\n");
        printf("\thand count = %d, expected = %d\n", actual, expected);
    }

	// ----------- TEST 2: player 1's card should come from his own deck --------------
    actual = testG.deckCount[thisPlayer];
    expected = initG.deckCount[thisPlayer] - newCards;
    if(actual == expected){
        printf("TEST 2: PASS drawn 3 cards came from player 1's own deck\n");
        printf("\tdeck count = %d, expected = %d\n", actual, expected);
        numPasses++;
    }
    else{
        printf("TEST 2: FAIL drawn 3 cards didn't come from player 1's own deck\n");
        printf("\tdeck count = %d, expected = %d\n", actual, expected);

    }

	// ----------- TEST 3: player 2's deck/hand shouldn't change --------------
    actual = testG.deckCount[thisPlayer+1] + testG.handCount[thisPlayer+1];
    expected = initG.deckCount[thisPlayer+1] + initG.handCount[thisPlayer+1];
    if(actual == expected){
        printf("TEST 3: PASS player 2's deck and hand count didn't change\n");
        printf("\tdeck+hand count = %d, expected = %d\n", actual, expected);
        numPasses++;
    }
    else{
        printf("TEST 3: FAIL player 2's deck and hand count changed\n");
        printf("\tdeck+hand count = %d, expected = %d\n", actual, expected);
    }

    // ----------- TEST 4: played smithy card was discarded --------------
    expected = 1;
    actual = ((initG.playedCardCount + discarded) == testG.playedCardCount) &&  ((initG.handCount[thisPlayer] - discarded)  == testG.handCount[thisPlayer]);
    if(actual == expected){
        printf("TEST 4: PASS smithy card was discarded after play\n");
        printf("\tdiscarded?= %d, expected = %d\n", actual, expected);
        numPasses++;
    }
    else{
        printf("TEST 4: FAIL smithy card wasn't discarded after play\n");
        printf("\tdiscarded?= %d, expected = %d\n", actual, expected);
    }

    // ----------- TEST 5: No state change should occur to the victory card piles --------------
    actual = testG.supplyCount[estate] + testG.supplyCount[duchy] + testG.supplyCount[province];
    expected = initG.supplyCount[estate] + initG.supplyCount[duchy] + initG.supplyCount[province];
    if(actual == expected){
        printf("TEST 5: PASS No state change occurred to the victory card piles\n");
        printf("\ttotal V cards  = %d, expected = %d\n", actual, expected);
        numPasses++;
    }
    else{
        printf("TEST 5: FAIL state change occured to the victory card piles\n");
        printf("\ttotal V cards  = %d, expected = %d\n", actual, expected);
    }

    // ----------- TEST 6: No state change should occur to the kingdom card piles --------------
    actual = expected = 0;
    for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
    {
        for (j = 0; j < 10; j++)           		//loop chosen cards
        {
            if (k[j] == i)
            {
                actual +=testG.supplyCount[i];
                expected += initG.supplyCount[i];
                break;
            }
        }
    }
    if(actual == expected){
        printf("TEST 6: PASS No state change occurred to the kingdom card piles\n");
        printf("\ttotal K cards  = %d, expected = %d\n", actual, expected);
        numPasses++;
    }
    else{
        printf("TEST 6: FAIL state change occured to the kingdom card piles\n");
        printf("\ttotal K cards  = %d, expected = %d\n", actual, expected);
    }

    if(numPasses == 6){
       printf("TEST SUCCESSFULLY COMPLETED\n");
    }
    else{
        printf("TEST FAILED\n");
    }

   return 0;
}