/* -----------------------------------------------------------------------
 * To compile this file include the following lines in your makefile:
 *
 * gcc -o randomtestadventurer -g randomtestadventurer.c  dominion.o rngs.o testLib.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "testLib.h"
#define TESTCARD "Adventurer"
void doAdventurerUnitTests(struct gameState* initG, struct gameState* testG, int thisPlayer, int k[10], int* testResults);

int main(){

    /* Basic testing for adventurer
    1. At end of play, player should have +2 treasure cards in his hand 
    2. All drawn cards besides 2 treasure cards should be moved to discard pile
    3. No state change should occur to kingdom card piles.
    4. No state change should occur to other's players hand and deck piles.
     */  
    int i, j, m;
    int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
    int seed = 1000;
    int numPlayers = 2, thisPlayer = 0;
	struct gameState initG, testG;
    int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
			sea_hag, tribute, smithy, council_room};

    int numRuns = 10, numTests = 4;
    int** testResults;

    srand((time(NULL)));
	printf("----------------- Testing Card: %s ----------------\n", TESTCARD);
    printf("EXPECTED: All random tests should fail due to introduced bugs in Asst 2.\n");
    printf("From Assignment 3, unit test 1 should fail\n\n");

    // ----------- TEST 1: Randomizing number of players  --------------
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
        cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
        doAdventurerUnitTests(&initG, &testG, thisPlayer, k, testResults[i]);
    }
    printTestResults(testResults, numTests, numRuns, 0);
    delete2dArray(testResults, numRuns, numTests + 1);

    // ----------- TEST 2: Randomizing player's decks --------------
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
        cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
        doAdventurerUnitTests(&initG, &testG, thisPlayer, k, testResults[m]);
    }
    printTestResults(testResults, numTests, numRuns, 0);
    delete2dArray(testResults, numRuns, numTests + 1);

    // // ----------- TEST 3: Randomizing player's hand piles --------------
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
        cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
        doAdventurerUnitTests(&initG, &testG, thisPlayer, k, testResults[m]);
    }
    printTestResults(testResults, numTests, numRuns, 0);
    delete2dArray(testResults, numRuns, numTests + 1);

    // ----------- TEST 3: Randomizing player's discard piles --------------
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
        cardEffect(adventurer, choice1, choice2, choice3, &testG, handpos, &bonus);
        doAdventurerUnitTests(&initG, &testG, thisPlayer, k, testResults[m]);
    }
    printTestResults(testResults, numTests, numRuns, 0);
    delete2dArray(testResults, numRuns, numTests + 1);

    return 0;
}

void doAdventurerUnitTests(struct gameState* initG, struct gameState* testG, int thisPlayer, int k[10], int* testResults){
    int i, j;
    int actual[4], expected[4];
    int card;

    // ----------- TEST 1: player should have +2 treasure cards in his hand  --------------
    int numTreasures = 0;
    for(i = initG->handCount[thisPlayer] - 1; i < testG->handCount[thisPlayer]; i++){
        card = testG->hand[thisPlayer][i];
        if(card == copper || card == silver || card == gold){
            numTreasures +=1;
        }
    }
    expected[0] = 2;
    expected[1] = (initG->handCount[thisPlayer] + 2);
    actual[0] = numTreasures;
    actual[1] = testG->handCount[thisPlayer];
    if( (actual[0] == expected[0]) && (actual[1] == expected[1]) ){ 
        // printf("TEST 1: PASS player 1 has +2 treasure cards in his hand \n");
        testResults[0] = 1;
        testResults[4]++;
    }
    else{
        // printf("TEST 1: FAIL player 1 doesn't have +2 treasure cards in his hand\n");
    }

    // ----------- TEST 2: All drawn cards (except 2 treasure cards) should be moved to discard pile --------------
    expected[0] = 0;
    actual[0] = testG->discardCount[thisPlayer] - initG->discardCount[thisPlayer];
    if(expected[0] <= actual[0]){
        // printf("TEST 2: PASS all non-treasure cards drawn were moved to discard pile\n");
        // printf("\tdiscarded count = %d, expected >= %d\n", actual[0], expected[0]);
        testResults[1] = 1;
        testResults[4]++;
    }
    else{
        // printf("TEST 2: FAIL all non-treasure cards drawn were not moved to discard pile\n");
        // printf("\tdiscarded count = %d, expected >= %d\n", actual[0], expected[0]);
    }

    // ----------- TEST 3: No state change should occur to kingdom card piles. --------------
    actual[0] = expected[0] = 0;
    for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
    {
        for (j = 0; j < 10; j++)           		//loop chosen cards
        {
            if (k[j] == i)
            {
                actual[0] +=testG->supplyCount[i];
                expected[0] += initG->supplyCount[i];
                break;
            }
        }
    }
    if(expected[0] == actual[0]){ 
        // printf("TEST 3: PASS No state change occured to kingdom card piles\n");
        testResults[2] = 1;
        testResults[4]++;
    }
    else{
        // printf("TEST 3: FAIL State change occured to kingdom card piles\n");
    }

    // ----------- TEST 4: No state change should occur to other's players hand and deck piles. --------------   
    expected[0] = initG->handCount[thisPlayer+1];
    actual[0]= testG->handCount[thisPlayer+1];
    expected[1] = initG->deckCount[thisPlayer+1];
    actual[1] = testG->deckCount[thisPlayer+1];
    actual[2] = actual[3] = 0;
    if(expected[0] == actual[0]){
        for(i = 0; i < expected[0]; i++){
            if(initG->hand[thisPlayer+1][i] != testG->hand[thisPlayer+1][i]){
                actual[2]++;
            }
        }
    }
    if(expected[1] == actual[1]){
        for(i = 0; i < expected[1]; i++){
            if(initG->deck[thisPlayer+1][i] != testG->deck[thisPlayer+1][i]){
                actual[3]++;
            }
        }
    }
    if( (actual[2] == 0) && (actual[3] == 0) && (expected[0] == actual[0]) && (expected[1] == actual[1]) ){ 
        // printf("TEST 4: PASS No state change occured to player 2's hand and deck piles\n");
        testResults[3] = 1;
        testResults[4]++;
    }
    else{
        // printf("TEST 4: FAIL State change occured to player 2's hand and deck piles\n");
    }
}

