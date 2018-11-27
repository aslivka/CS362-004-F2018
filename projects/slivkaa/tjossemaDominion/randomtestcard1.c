/* -----------------------------------------------------------------------
 * To compile this file include the following lines in your makefile:
 *
 *  gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o testLib.o $(CFLAGS)
 * -----------------------------------------------------------------------
 */

#include "testLib.h"
#define TESTCARD "Smithy"
void runSmithyUnitTests(struct gameState* initG, struct gameState* testG, int thisPlayer, int k[10], int* testResults);
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
    printf("EXPECTED OUTPUT: All random tests should fail due to introduced bugs in Asst 2.\n");

    char** unitTestDesc = calloc(10, sizeof(char*));
    //Saving unit test descriptions:
    unitTestDesc[0] = "UTEST 1: player should receive exactly 3 cards";
    unitTestDesc[1] = "UTEST 2: player 1's card should come from his own deck";
    unitTestDesc[2] = "UTEST 3: player 2's deck/hand shouldn't change";
    unitTestDesc[3] = "UTEST 4: played smithy card was discarded";
    unitTestDesc[4] = "UTEST 5: No state change should occur to the victory card piles";
    unitTestDesc[5] = "UTEST 6: No state change should occur to the kingdom card piles";

    // ---------------------------------------------------------------------
    printf("RANDOM TEST 1: Randomizing number of players\n");
    numRuns = 10;
    numTests = 6;
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
        cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
        runSmithyUnitTests(&initG, &testG, thisPlayer, k, testResults[i]);
    }
    printTestResults(testResults, numTests, numRuns, 0, unitTestDesc);
    delete2dArray(testResults, numRuns, numTests + 1);

    // // ---------------------------------------------------------------------
    // printf("RANDOM TEST 2: Randomizing deck piles, max number of cards = 100\n");
    // numRuns = 1000;
    // numTests = 6;
    // testResults = init2dArray(numRuns, numTests + 1);
    // thisPlayer = 0;
    // numPlayers = 2;
    // for(m = 0; m < numRuns; m++)
    // {
    //     //Initializing game states
    //     memset(&initG, 0, sizeof(struct gameState));
    //     memset(&testG, 0, sizeof(struct gameState));
    //     initializeGame(numPlayers, k, seed, &initG);  
    //     //Setting random numbers of victory and treasure cards
    //     for (i = 0; i < numPlayers; i++){
    //         initG.deckCount[i] = 0;
    //         for (j = 0; j < 100; j++){
    //             initG.deck[i][j] = randInt(estate, treasure_map); //1 = estate, 3 = province
    //             initG.deckCount[i]++;
    //         }
    //     }       
    //     // copy the game state to a test case
    //     memcpy(&testG, &initG, sizeof(struct gameState));
    //     // //Playing card
    //     choice3 = thisPlayer;
    //     cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
    //     runSmithyUnitTests(&initG, &testG, thisPlayer, k, testResults[m]);
    // }
    // printTestResults(testResults, numTests, numRuns, 0, unitTestDesc);
    // delete2dArray(testResults, numRuns, numTests + 1);

    // // ---------------------------------------------------------------------
    // printf("RANDOM TEST 3: Randomizing hand piles, max num of cards = 10\n");
    // numRuns = 1000;
    // numTests = 6;
    // testResults = init2dArray(numRuns, numTests + 1);
    // thisPlayer = 0;
    // numPlayers = 2;
    // for(m = 0; m < numRuns; m++)
    // {
    //     //Initializing game states
    //     memset(&initG, 0, sizeof(struct gameState));
    //     memset(&testG, 0, sizeof(struct gameState));
    //     initializeGame(numPlayers, k, seed, &initG);
    //     //Setting random number of cards in hand pale
    //      for (i = 0; i < numPlayers; i++){
    //         initG.handCount[i] = 0;
    //         for (j = 0; j < 10; j++){
    //             initG.hand[i][j] = randInt(estate, treasure_map); //1 = estate, 3 = province
    //             initG.handCount[i]++;
    //         }
    //     }             
    //     // copy the game state to a test case
    //     memcpy(&testG, &initG, sizeof(struct gameState));
    //     // //Playing card
    //     choice3 = thisPlayer;
    //     cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
    //     runSmithyUnitTests(&initG, &testG, thisPlayer, k, testResults[m]);
    // }
    // printTestResults(testResults, numTests, numRuns, 0, unitTestDesc);
    // delete2dArray(testResults, numRuns, numTests + 1);

    // // ---------------------------------------------------------------------
    // printf("RANDOM TEST 4: Randomizing discard piles, max num of cards = 10\n");
    // numRuns = 1000;
    // numTests = 6;
    // testResults = init2dArray(numRuns, numTests + 1);
    // thisPlayer = 0;
    // numPlayers = 2;
    // // int m;
    // for(m = 0; m < numRuns; m++)
    // {
    //     //Initializing game states
    //     memset(&initG, 0, sizeof(struct gameState));
    //     memset(&testG, 0, sizeof(struct gameState));
    //     initializeGame(numPlayers, k, seed, &initG);
    //     //Setting random number of cards in discard pile
    //      for (i = 0; i < numPlayers; i++){
    //         initG.discardCount[i] = 0;
    //         for (j = 0; j < 10; j++){
    //             initG.discard[i][j] = randInt(gold + 1, treasure_map); 
    //             initG.discardCount[i]++;
    //         }
    //     }             
    //     // copy the game state to a test case
    //     memcpy(&testG, &initG, sizeof(struct gameState));
    //     // //Playing card
    //     choice3 = thisPlayer;
    //     cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
    //     runSmithyUnitTests(&initG, &testG, thisPlayer, k, testResults[m]);
    // }
    // printTestResults(testResults, numTests, numRuns, 0, unitTestDesc);
    // delete2dArray(testResults, numRuns, numTests + 1);

    // // ---------------------------------------------------------------------
    // printf("RANDOM TEST 5: Randomizing kingdom cards, max num of cards = 10\n");
    // numRuns = 1000;
    // numTests = 6;
    // testResults = init2dArray(numRuns, numTests + 1);
    // thisPlayer = 0;
    // numPlayers = 2;
    // int card;
    // for(m = 0; m < numRuns; m++)
    // {
    //     //Initializing game states
    //     memset(&initG, 0, sizeof(struct gameState));
    //     memset(&testG, 0, sizeof(struct gameState));
    //     //Assigning random kingdom cards to k array
    //     for(i = 0; i < 10; i++){
    //         do{
    //             card = randInt(adventurer, sea_hag);  
    //         }while( isDupCard(k, 10, card) == 1);
    //         k[i] = card;
    //     }    
    //     initializeGame(numPlayers, k, seed, &initG);  
    //     // copy the game state to a test case
    //     memcpy(&testG, &initG, sizeof(struct gameState));
    //     // //Playing card
    //     choice3 = thisPlayer;
    //     cardEffect(smithy, choice1, choice2, choice3, &testG, handpos, &bonus);
    //     runSmithyUnitTests(&initG, &testG, thisPlayer, k, testResults[m]);
    // }
    // printTestResults(testResults, numTests, numRuns, 0, unitTestDesc);
    // delete2dArray(testResults, numRuns, numTests + 1);

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

void runSmithyUnitTests(struct gameState* initG, struct gameState* testG, int thisPlayer, int k[10], int* testResults){
    int actual, expected, i, j;
    int newCards = 0;
    int discarded = 1;

    // ----------- TEST 1: player should receive exactly 3 cards --------------
    newCards = 3;
    actual = testG->handCount[thisPlayer];
    expected = initG->handCount[thisPlayer] + newCards;
    if(actual == expected){
        // printf("TEST 1: PASS player 1 received exactly 3 cards\n");
        // printf("\thand count = %d, expected = %d\n", actual, expected);
        testResults[0] = 1;
        testResults[6]++;
    }
    else{
        // printf("TEST 1: FAIL current player didnt' receive exactly 3 cards\n");
        // printf("\thand count = %d, expected = %d\n", actual, expected);
    }

	// ----------- TEST 2: player 1's card should come from his own deck --------------
    actual = testG->deckCount[thisPlayer];
    expected = initG->deckCount[thisPlayer] - newCards;
    if(actual == expected){
        // printf("TEST 2: PASS drawn 3 cards came from player 1's own deck\n");
        // printf("\tdeck count = %d, expected = %d\n", actual, expected);
        testResults[1] = 1;
        testResults[6]++;
    }
    else{
        // printf("TEST 2: FAIL drawn 3 cards didn't come from player 1's own deck\n");
        // printf("\tdeck count = %d, expected = %d\n", actual, expected);
    }

	// ----------- TEST 3: player 2's deck/hand shouldn't change --------------
    actual = testG->deckCount[thisPlayer+1] + testG->handCount[thisPlayer+1];
    expected = initG->deckCount[thisPlayer+1] + initG->handCount[thisPlayer+1];
    if(actual == expected){
        // printf("TEST 3: PASS player 2's deck and hand count didn't change\n");
        // printf("\tdeck+hand count = %d, expected = %d\n", actual, expected);
        testResults[2] = 1;
        testResults[6]++;
    }
    else{
        // printf("TEST 3: FAIL player 2's deck and hand count changed\n");
        // printf("\tdeck+hand count = %d, expected = %d\n", actual, expected);
    }

    // ----------- TEST 4: played smithy card was discarded --------------
    expected = 1;
    actual = ((initG->playedCardCount + discarded) == testG->playedCardCount) &&  ((initG->handCount[thisPlayer] - discarded)  == testG->handCount[thisPlayer]);
    if(actual == expected){
        // printf("TEST 4: PASS smithy card was discarded after play\n");
        // printf("\tdiscarded?= %d, expected = %d\n", actual, expected);
        testResults[3] = 1;
        testResults[6]++;
    }
    else{
        // printf("TEST 4: FAIL smithy card wasn't discarded after play\n");
        // printf("\tdiscarded?= %d, expected = %d\n", actual, expected);
    }

    // ----------- TEST 5: No state change should occur to the victory card piles --------------
    actual = testG->supplyCount[estate] + testG->supplyCount[duchy] + testG->supplyCount[province];
    expected = initG->supplyCount[estate] + initG->supplyCount[duchy] + initG->supplyCount[province];
    if(actual == expected){
        // printf("TEST 5: PASS No state change occurred to the victory card piles\n");
        // printf("\ttotal V cards  = %d, expected = %d\n", actual, expected);
        testResults[4] = 1;
        testResults[6]++;
    }
    else{
        // printf("TEST 5: FAIL state change occured to the victory card piles\n");
        // printf("\ttotal V cards  = %d, expected = %d\n", actual, expected);
    }

    // ----------- TEST 6: No state change should occur to the kingdom card piles --------------
    actual = expected = 0;
    for (i = adventurer; i <= treasure_map; i++)       	//loop all cards
    {
        for (j = 0; j < 10; j++)           		//loop chosen cards
        {
            if (k[j] == i)
            {
                actual +=testG->supplyCount[i];
                expected += initG->supplyCount[i];
                break;
            }
        }
    }
    if(actual == expected){
        // printf("TEST 6: PASS No state change occurred to the kingdom card piles\n");
        // printf("\ttotal K cards  = %d, expected = %d\n", actual, expected);
        testResults[5] = 1;
        testResults[6]++;
    }
    else{
        // printf("TEST 6: FAIL state change occured to the kingdom card piles\n");
        // printf("\ttotal K cards  = %d, expected = %d\n", actual, expected);
    }

}