#include "unity.h"
#include <stdio.h>
#include "TimeTabling.h"
#include "ErrorCode.h"
#include "Random.h"
#include "CException.h"

void setUp(void){
	int venue = 0;
  int day = 0, time = 0;
	int i;
  
  for(venue = 0; venue < MAX_VENUE; venue++) {
    for(day = 0; day < MAX_DAY; day++) {
      for(time = 0; time < MAX_TIME_SLOTS; time++) {
				class[venue][day][time].lecturer = NULL;
				class[venue][day][time].course = NULL;
				class[venue][day][time].typeOfClass = 0;
				for(i = 0 ; i < 5 ; i++){
					class[venue][day][time].group[i] = NULL;
				}
			}
		}
	}
}

void tearDown(void){}


void test_crossoverToOffspring_should_copy_to_target_class(){
	
	int leftStop = 0;
	Class targetClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS];
	clearClass(targetClass);
	
	crossoverToOffspring(classList[0], targetClass, 0, 0, 0, &leftStop);
	
	TEST_ASSERT_EQUAL(1, compareClass(classList[0], targetClass[0][0][0]));
	TEST_ASSERT_EQUAL(0, leftStop);
}

void test_crossoverToOffspring_should_not_copy_and_update_leftStop(){
	int leftStop = 0;
	Class targetClass[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS];
	clearClass(targetClass);
	
	targetClass[0][0][0] = copyClassSlot(classList[0]);
	targetClass[0][0][1] = copyClassSlot(classList[0]);
	
	crossoverToOffspring(classList[0], targetClass, 0, 0, 2, &leftStop);
	
	TEST_ASSERT_EQUAL(1, compareClass(classList[0], targetClass[0][0][0]));
	TEST_ASSERT_EQUAL(1, compareClass(classList[0], targetClass[0][0][1]));
	TEST_ASSERT_EQUAL(0, compareClass(classList[0], targetClass[0][0][2]));
	TEST_ASSERT_EQUAL(1, leftStop);
}



void test_performCrossover_should_fill_in_offSpring(){
	//declaration fixture of topFitness population, and randomize ClassList
	Class topFitness[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS];
	Class topFitness2[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS];
	Class testList[52];
	int topFitnessScore, topFitnessScore2;
	clearClassList(sizeof(testList)/sizeof(Class) , testList);
	
	//randomizeClassList (assume this is top 1 fitness among the population)
	randomizeClassList(sizeof(testList)/sizeof(Class),testList);
	clearClass(topFitness);
	fillInTheChromosomeWithReducingViolation(testList, sizeof(testList)/sizeof(Class));
	copyClass(class, topFitness);
 
	clearClass(class);
 
 	//randomizeClassList (assume this is top 2 fitness among the population)
	clearClassList(sizeof(testList)/sizeof(Class) , testList);
	randomizeClassList(sizeof(testList)/sizeof(Class),testList);
	clearClass(topFitness2);
	fillInTheChromosomeWithReducingViolation(testList, sizeof(testList)/sizeof(Class));
	copyClass(class, topFitness2);
	
	//record down fitness score of each
	topFitnessScore = calculateFitnessScore(topFitness);
	topFitnessScore2 = calculateFitnessScore(topFitness2);
	
	//offSpring result (class[][][])
	Class offSpring[MAX_VENUE][MAX_DAY][MAX_TIME_SLOTS];
	
	performCrossover(topFitness,topFitness2,offSpring);
	TEST_ASSERT_EQUAL(sizeof(topFitness)/sizeof(Class), sizeof(offSpring)/sizeof(Class));
	
	/**
  *   To make sure the elements are same.
  *   Not able to test assert because it is swapped randomly when crossover
  *   Swap is too complicated to mock
  *   List should contains:
  *   - 10 Mathematics
  *   -  6 English
  *   -  6 History
  *   -  6 Add Math
  *   - 14 Test Driven Development
  *   - 10 Electromagnetics
  *   - 52 filled, 8 empty.
  *
  *   create counter[6]
  *   counter[0] = Mathematics,
  *   counter[1] = English,
  *   counter[2] = History,
  *   counter[3] = Add Math,
  *   counter[4] = Test Driven Development,
  *   counter[5] = Electromagnetics,
  *   counter[6] = empty
  **/
  
  int counter[7] = {0};
	int i,j,retLoopVenue = 0, retLoopDay = 0, retLoopTime = 0;
	for( i = 0 ; i < (MAX_VENUE*MAX_DAY*MAX_TIME_SLOTS) ; i++){
		if(offSpring[retLoopVenue][retLoopDay][retLoopTime].course != NULL){
      for(j=0;j<7;j++){
        if(offSpring[retLoopVenue][retLoopDay][retLoopTime].course->courseName == course[j].courseName)
          counter[j]++;
      }
		}
    else
      counter[6]++;
		indexForward(&retLoopVenue,&retLoopDay,&retLoopTime);	
	}
  
  TEST_ASSERT_EQUAL(10,counter[0]);
  TEST_ASSERT_EQUAL(6,counter[1]);
  TEST_ASSERT_EQUAL(6,counter[2]);
  TEST_ASSERT_EQUAL(6,counter[3]);
  TEST_ASSERT_EQUAL(14,counter[4]);
  TEST_ASSERT_EQUAL(10,counter[5]);
  TEST_ASSERT_EQUAL(8,counter[6]);
}
