CFLAGS= -Wall -fpic -coverage -lm -std=c99

rngs.o: rngs.h rngs.c
	gcc -c rngs.c -g  $(CFLAGS)

dominion.o: dominion.h dominion.c rngs.o
	gcc -c dominion.c -g  $(CFLAGS)

playdom: dominion.o playdom.c
	gcc -o playdom playdom.c -g dominion.o rngs.o $(CFLAGS)
#To run playdom you need to entere: ./playdom <any integer number> like ./playdom 10*/
testDrawCard: testDrawCard.c dominion.o rngs.o
	gcc  -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

badTestDrawCard: badTestDrawCard.c dominion.o rngs.o
	gcc -o badTestDrawCard -g  badTestDrawCard.c dominion.o rngs.o $(CFLAGS)

testBuyCard: testDrawCard.c dominion.o rngs.o
	gcc -o testDrawCard -g  testDrawCard.c dominion.o rngs.o $(CFLAGS)

testAll: dominion.o testSuite.c
	gcc -o testSuite testSuite.c -g  dominion.o rngs.o $(CFLAGS)

interface.o: interface.h interface.c
	gcc -c interface.c -g  $(CFLAGS)

runtests: testDrawCard 
	./testDrawCard &> unittestresult.out
	gcov dominion.c >> unittestresult.out
	cat dominion.c.gcov >> unittestresult.out

randtestresults: testLib runCardTests

testLib: testLib.c testLib.h
	gcc -c testLib.c -g  $(CFLAGS)

runCardTests: randomtestadventurer.c  dominion.o rngs.o testLib.o
	echo "Test file: randomtestadventurer.c" > randomtestadventurer.out
	gcc -o randomtestadventurer -g randomtestadventurer.c  dominion.o rngs.o testLib.o $(CFLAGS)
	./randomtestadventurer >> randomtestadventurer.out
	gcov -b -f dominion.c | grep "playAdventurer" -B 0 -A 5 >> randomtestadventurer.out
	gcov -b dominion.c >> randomtestadventurer.out

	echo "Test file: randomtestcard1.c" > randomtestcard1.out
	gcc -o randomtestcard1 -g randomtestcard1.c dominion.o rngs.o testLib.o $(CFLAGS)
	./randomtestcard1 >> randomtestcard1.out
	gcov -b -f dominion.c | grep "playSmithy" -B 0 -A 5 >> randomtestcard1.out
	gcov -b dominion.c >> randomtestcard1.out

	echo "Test file: randomtestcard2.c" > randomtestcard2.out
	gcc -o randomtestcard2 -g randomtestcard2.c dominion.o rngs.o testLib.o $(CFLAGS)
	./randomtestcard2 >> randomtestcard2.out
	gcov -b -f dominion.c | grep "playVillage" -B 0 -A 4 >> randomtestcard2.out
	gcov -b dominion.c >> randomtestcard2.out


player: player.c interface.o
	gcc -o player player.c -g  dominion.o rngs.o interface.o $(CFLAGS)

all: playdom player randtestresults

clean:
	rm -f *.o playdom.exe playdom player player.exe  *.gcov *.gcda *.gcno *.so *.out testDrawCard testDrawCard.exe
