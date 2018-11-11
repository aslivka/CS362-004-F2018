/* -----------------------------------------------------------------------
 * To compile this file include the following lines in your makefile:
 *
 *  gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o testLib.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "testLib.h"
#define TESTCARD "Village"
void runVillageUnitTests(struct gameState* initG, struct gameState* testG, int thisPlayer, int k[10], int* testResults);
int isDupCard(int* inArray, int size, int card);

int main(){

    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers, thisPlayer;
	struct gameState initG, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};
    int numRuns, numTests;
    int** testResults;

    srand((time(NULL)));
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    printf("EXPECTED OUTPUT: All random tests should PASS.\n\n");

    // ---------------------------------------------------------------------
    printf("TEST 1: Randomizing number of players\n");
    numRuns = 10;
    numTests = 4;
    testResults = init2dArray(numRuns, numTests + 1);
    thisPlayer = 0;
    for(i = 0; i < numRuns; i++)
    {
        numPlayers = randInt(2, 4);
        //Initializing game states
        memset(&initG, 0, sizeof(struct gameState));
        memset(&testG, 0, sizeof(struct gameState));
        initializeGame(numPlayers, k, seed, &initG);  
        // copy the game state to a test case
        memcpy(&testG, &initG, sizeof(struct gameState));
        //Playing card
        choice3 = thisPlayer;
        cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
        runVillageUnitTests(&initG, &testG, thisPlayer, k, testResults[i]);
    }
    printTestResults(testResults, numTests, numRuns, 0);
    delete2dArray(testResults, numRuns, numTests + 1);

    // ---------------------------------------------------------------------
    printf("TEST 2: Randomizing deck piles, max number of cards = 100\n");
    numRuns = 100;
    numTests = 4;
    testResults = init2dArray(numRuns, numTests + 1);
    thisPlayer = 0;
    numPlayers = 2;
    for(m = 0; m < numRuns; m++)
    {
        //Initializing game states
        memset(&initG, 0, sizeof(struct gameState));
        memset(&testG, 0, sizeof(struct gameState));
        initializeGame(numPlayers, k, seed, &initG);  
        //Setting random numbers of victory and treasure cards
        for (i = 0; i < numPlayers; i++){
            initG.deckCount[i] = 0;
            for (j = 0; j < 100; j++){
                initG.deck[i][j] = randInt(estate, treasure_map); //1 = estate, 3 = province
                initG.deckCount[i]++;
            }
        }       
        // copy the game state to a test case
        memcpy(&testG, &initG, sizeof(struct gameState));
        // //Playing card
        choice3 = thisPlayer;
        cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
        runVillageUnitTests(&initG, &testG, thisPlayer, k, testResults[m]);
    }
    printTestResults(testResults, numTests, numRuns, 0);
    delete2dArray(testResults, numRuns, numTests + 1);

    // ---------------------------------------------------------------------
    printf("TEST 3: Randomizing hand piles, max num of cards = 10\n");
    numRuns = 100;
    numTests = 4;
    testResults = init2dArray(numRuns, numTests + 1);
    thisPlayer = 0;
    numPlayers = 2;
    for(m = 0; m < numRuns; m++)
    {
        //Initializing game states
        memset(&initG, 0, sizeof(struct gameState));
        memset(&testG, 0, sizeof(struct gameState));
        initializeGame(numPlayers, k, seed, &initG);
        //Setting random number of cards in hand pale
         for (i = 0; i < numPlayers; i++){
            initG.handCount[i] = 0;
            for (j = 0; j < 10; j++){
                initG.hand[i][j] = randInt(estate, treasure_map); //1 = estate, 3 = province
                initG.handCount[i]++;
            }
        }             
        // copy the game state to a test case
        memcpy(&testG, &initG, sizeof(struct gameState));
        // //Playing card
        choice3 = thisPlayer;
        cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
        runVillageUnitTests(&initG, &testG, thisPlayer, k, testResults[m]);
    }
    printTestResults(testResults, numTests, numRuns, 0);
    delete2dArray(testResults, numRuns, numTests + 1);

    // ---------------------------------------------------------------------
    printf("TEST 4: Randomizing discard piles, max num of cards = 10\n");
    numRuns = 100;
    numTests = 4;
    testResults = init2dArray(numRuns, numTests + 1);
    thisPlayer = 0;
    numPlayers = 2;
    // int m;
    for(m = 0; m < numRuns; m++)
    {
        //Initializing game states
        memset(&initG, 0, sizeof(struct gameState));
        memset(&testG, 0, sizeof(struct gameState));
        initializeGame(numPlayers, k, seed, &initG);
        //Setting random number of cards in discard pile
         for (i = 0; i < numPlayers; i++){
            initG.discardCount[i] = 0;
            for (j = 0; j < 5; j++){
                initG.discard[i][j] = randInt(gold + 1, treasure_map); 
                initG.discardCount[i]++;
            }
        }             
        // copy the game state to a test case
        memcpy(&testG, &initG, sizeof(struct gameState));
        // //Playing card
        choice3 = thisPlayer;
        cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
        runVillageUnitTests(&initG, &testG, thisPlayer, k, testResults[m]);
    }
    printTestResults(testResults, numTests, numRuns, 0);
    delete2dArray(testResults, numRuns, numTests + 1);

    // ---------------------------------------------------------------------
    printf("TEST 5: Randomizing kingdom cards, max num of cards = 10\n");
    numRuns = 100;
    numTests = 4;
    testResults = init2dArray(numRuns, numTests + 1);
    thisPlayer = 0;
    numPlayers = 2;
    int card;
    for(m = 0; m < numRuns; m++)
    {
        //Initializing game states
        memset(&initG, 0, sizeof(struct gameState));
        memset(&testG, 0, sizeof(struct gameState));
        //Assigning random kingdom cards to k array
        for(i = 0; i < 10; i++){
            do{
                card = randInt(adventurer, sea_hag);  
            }while( isDupCard(k, 10, card) == 1);
            k[i] = card;
        }    
        initializeGame(numPlayers, k, seed, &initG);  
        // copy the game state to a test case
        memcpy(&testG, &initG, sizeof(struct gameState));
        // //Playing card
        choice3 = thisPlayer;
        cardEffect(village, choice1, choice2, choice3, &testG, handpos, &bonus);
        runVillageUnitTests(&initG, &testG, thisPlayer, k, testResults[m]);
    }
    printTestResults(testResults, numTests, numRuns, 0);
    delete2dArray(testResults, numRuns, numTests + 1);

     return 0;
}

int isDupCard(int* inArray, int size, int card){
    int j;
    for(j = 0; j < size; j++){
        if(inArray[j] == card){
            return 1;
        }
    }
    return 0;
}

void runVillageUnitTests(struct gameState* initG, struct gameState* testG, int thisPlayer, int k[10], int* testResults){
    int actual[3], expected[3]
    expected[0] = initG->deckCount[thisPlayer] - 1;
    actual[0] = testG->deckCount[thisPlayer];
    if( (expected[0] == actual[0])  ){ 
        // printf("TEST 1: PASS player 1 draws +1 card from deck\n");
        // printf("\tdeck card count = %d, expected = %d\n", actual[0], expected[0]);
        testResults[0] = 1;
        testResults[4]++;
    }
    else{
        // printf("TEST 1: FAIL player 1 doesn't draw +1 card from deck\n");
        // printf("\tdeck card count = %d, expected = %d\n", actual[0], expected[0]);
    }

	// ----------- TEST 2: player 1 gains +2 actions --------------
    expected[0] = initG->numActions + 2;
    actual[0] = testG->numActions;
    if(expected[0] == actual[0]){ 
        // printf("TEST 2: PASS player 1 gains +2 actions\n");
        // printf("\tnum of actions = %d, expected = %d\n", actual[0], expected[0]);
        testResults[1] = 1;
        testResults[4]++;
    }
    else{
        // printf("TEST 2: FAIL player 1 doesnt' gain +2 actions\n");
        // printf("\tnum of actions = %d, expected = %d\n", actual[0], expected[0]);
    }

    // ----------- TEST 3: player 1 discards village card from hand --------------
    expected[0] = initG->playedCardCount + 1;
    expected[1] = initG->handCount[thisPlayer];
    actual[0] = testG->playedCardCount;
    actual[1] = testG->handCount[thisPlayer];
    if( (actual[0] == expected[0]) && (actual[1] == expected[1]) ){ 
        // printf("TEST 3: PASS player 1 discards village card from hand\n");
        // printf("\tnum of playedCards = %d, expected = %d\n", actual[0], expected[0]);
        // printf("\tfinal hand count = %d, expected = %d\n", actual[1], expected[1]);
        testResults[2] = 1;
        testResults[4]++;
    }
    else{
        // printf("TEST 3: FAIL player 1 doesn't discard village card from hand\n");
        // printf("\tnum of playedCards = %d, expected = %d\n", actual[0], expected[0]);
        // printf("\tfinal hand count = %d, expected = %d\n", actual[1], expected[1]);
    }

    // ----------- TEST 4: check state changes to other player's decks/hands --------------
    expected[0] = initG->handCount[thisPlayer+1];
    expected[1] = initG->deckCount[thisPlayer+1];
    actual[0] = testG->handCount[thisPlayer+1];
    actual[1] = testG->deckCount[thisPlayer+1];

    if( (actual[0] == expected[0]) && (actual[1] == expected[1]) ){ 
        // printf("TEST 4: PASS no state change occured to other player's deck/hand\n");
        // printf("\thand count = %d, expected = %d\n", actual[0], expected[0]);
        // printf("\tdeck count = %d, expected = %d\n", actual[1], expected[1]);
        testResults[3] = 1;
        testResults[4]++;
    }
    else{
        // printf("TEST 4: FAIL state change occured to other player's deck/hand\n");
        // printf("\thand count = %d, expected = %d\n", actual[0], expected[0]);
        // printf("\tdeck count = %d, expected = %d\n", actual[1], expected[1]);
    }
}