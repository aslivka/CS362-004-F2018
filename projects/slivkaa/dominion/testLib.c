#include "testLib.h"

int compareInts(int a, int b){
  if (a > b)
    return 1;
  if (a < b)
    return -1;
  return 0;
}

int compareGameStates(struct gameState *state1, struct gameState *state2){
    int i;
    if(state1->numPlayers != state2->numPlayers){ return 1; }
    for(i = 0; i < treasure_map+1; i++){
        if(state1->supplyCount[i] != state2->supplyCount[i]){
            return 1;
        }
         if(state1->embargoTokens[i] != state2->embargoTokens[i]){
            return 1;
        }
    }
    if(state1->outpostPlayed != state2->outpostPlayed){ return 1; }
    if(state1->outpostTurn != state2->outpostTurn){ return 1; }
    if(state1->whoseTurn != state2->whoseTurn){ return 1; }
    if(state1->phase != state2->phase){ return 1; }
    if(state1->numActions != state2->numActions){ return 1; }
    if(state1->coins != state2->coins){ return 1; }
    if(state1->numBuys != state2->numBuys){ return 1; }
    for(i = 0; i < MAX_PLAYERS; i++){
         if(state1->hand[i][0] != state2->hand[i][0]){ return 1; }
         if(state1->handCount[i] != state2->handCount[i]){ return 1; }
         if(state1->deck[i][0] != state2->deck[i][0]){ return 1; }
         if(state1->deckCount[i] != state2->deckCount[i]){ return 1; }
         if(state1->discard[i][0] != state2->discard[i][0]){ return 1; }
         if(state1->discardCount[i] != state2->discardCount[i]){ return 1; }
    }
    
    for(i = 0; i < MAX_DECK; i++){
        if(state1->playedCards[i] != state2->playedCards[i]){ return 1; }
    }
    if(state1->playedCardCount != state2->playedCardCount){ return 1; }
    return 0;
}

void initGameState(struct gameState *state){
    int i;

    state->outpostPlayed = 0;
    state->outpostTurn = 0;
    state->whoseTurn = 0;
    state->phase = 0;
    state->numActions = 0;
    state->coins = 0;
    state->numBuys = 0;
    state->playedCardCount = 0;
    state->numPlayers = 0;

    for(i = 0; i < treasure_map+1; i++){
        state->supplyCount[i] = 0;
        state->embargoTokens[i] =0;
    }
    for(i = 0; i < MAX_PLAYERS; i++){
        state->hand[i][0] = 0;
        state->handCount[i] = 0;
        state->deck[i][0] = 0; 
        state->deckCount[i] = 0;
        state->discard[i][0] = 0;
        state->discardCount[i] = 0;
    }

    for(i = 0; i < MAX_DECK; i++){
        state->playedCards[i] = 0; 
    } 
}

void printGameState(struct gameState *state){
    int i;

    printf("outpostPlayed: %d\n", state->outpostPlayed);
    printf("outpostTurn: %d\n", state->outpostTurn);
    printf("whoseTurn: %d\n",  state->whoseTurn);

    printf("phase: %d\n", state->phase);
    printf("numActions: %d\n", state->numActions);
    printf("coins: %d\n",  state->coins);
    printf("numBuys: %d\n", state->numBuys);
    printf("playedCardCount: %d\n", state->playedCardCount);
    printf("numPlayers: %d\n", state->numPlayers);

    for(i = 0; i < treasure_map+1; i++){
        printf("supplyCount[%d]: %d, ", i, state->supplyCount[i]);
        if(i % 4 == 0){printf("\n");}
    }
    for(i = 0; i < 2; i++){
        printf("\nhand[%d][0]: %d ", i, state->hand[i][0]);
        printf("handCount[%d]: %d ", i, state->handCount[i]);
        printf("deck[%d][0]: %d ", i, state->deck[i][0]);
        printf("deckCount[%d]: %d ", i, state->deckCount[i]);
        printf("discard[%d][0]: %d ", i, state->discard[i][0]);
        printf("discardCount[%d]: %d", i, state->discardCount[i]); 
    }

    printf("\nplayedCards\n");
    for(i = 0; i < state->playedCardCount; i++){
        state->playedCards[i] = 0; 
        printf("playedCards[%d]:%d ", i, state->playedCards[i]);      
    } 
}

int randInt(int min, int max){
	int randomVal = (rand() % (max - min + 1)) + min;
	return randomVal;
}

int** init2dArray(int rows, int cols){
    int i; 
    int** array = calloc(rows, sizeof(int*));
    for(i = 0; i < rows; i++){
        array[i] = calloc(cols, sizeof(int));
    }
}

void delete2dArray(int** array, int rows, int cols){
    int i; 
    if(array != 0){
         for(i = 0; i < rows; i++){
            if(array[i] != 0){
                free(array[i]);
                array[i] = 0;
            }
        }
        free(array);
    }
}

void clear2dArray(int** array, int rows, int cols){
    int i; 
    for(i = 0; i < rows; i++){
        memset(array[i], 0, cols * sizeof(int));
    }
}


