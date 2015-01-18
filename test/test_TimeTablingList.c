#include "unity.h"
#include <stdio.h>
#include "TimeTabling.h"
#include "ErrorCode.h"
#include "mock_Random.h"
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

void test_fillInTheChromosome_should_throw_when_list_oversized(){

	Class list[100];
	CEXCEPTION_T e;
	
	Try{
	fillInTheChromosome(list, sizeof(list)/sizeof(Class));}
	Catch(e){
		TEST_ASSERT_EQUAL(ERR_EXCEEDED_INDEX,e);
	}
	
}

void test_fillInTheChromosomeWithReducingViolation_should_less_violation_than_normal_fillInTheChromosome(){
	int normalFill, reducedViolationFill;
	int compare;
	
	fillInTheChromosome(classList, sizeof(classList)/sizeof(Class));
	normalFill = calculateFitnessScore(class);
	
	setUp();
	
	fillInTheChromosomeWithReducingViolation(classList, sizeof(classList)/sizeof(Class));
	reducedViolationFill = calculateFitnessScore(class);
	
	// proofed that fillInTheChromosomeWithReducingViolation is better
	if( normalFill > reducedViolationFill)
		compare = 1;
	else
		compare = 0;
	 
	TEST_ASSERT_EQUAL(1 , compare);
}

void test_fillInTheChromosomeWithReducingViolation_should_throw_when_list_oversized(){
	Class list[100];
	CEXCEPTION_T e;
	
	Try{
	fillInTheChromosomeWithReducingViolation(list, sizeof(list)/sizeof(Class));}
	Catch(e){
		TEST_ASSERT_EQUAL(ERR_EXCEEDED_INDEX,e);
	}
	
}

void test_copyClassSlot_should_able_to_copy_1_class_to_another(){

	Class testClass;
	
	testClass = copyClassSlot(classList[0]);

	TEST_ASSERT_EQUAL_PTR( classList[0].course, testClass.course);
	TEST_ASSERT_EQUAL_PTR( classList[0].lecturer, testClass.lecturer);
	TEST_ASSERT_EQUAL_PTR( classList[0].group[0], testClass.group[0]);
	TEST_ASSERT_EQUAL_PTR( classList[0].group[1], testClass.group[1]);
	TEST_ASSERT_EQUAL_PTR( classList[0].group[2], testClass.group[2]);
	TEST_ASSERT_EQUAL_PTR( classList[0].group[3], testClass.group[3]);
	TEST_ASSERT_EQUAL_PTR( classList[0].group[4], testClass.group[4]);
	TEST_ASSERT_EQUAL( classList[0].typeOfClass, testClass.typeOfClass);
	
}

void test_copyClass_should_able_to_copy_entire_class(){
	fillInTheChromosome(classList, sizeof(classList)/sizeof(Class));
	copyClass(class,populationOfClasses[0].class);
	
	TEST_ASSERT_EQUAL_PTR(class[0][0][0].course, populationOfClasses[0].class[0][0][0].course);
	TEST_ASSERT_EQUAL_PTR(class[0][0][0].lecturer, populationOfClasses[0].class[0][0][0].lecturer);
	TEST_ASSERT_EQUAL(class[0][0][0].typeOfClass, populationOfClasses[0].class[0][0][0].typeOfClass);	
	TEST_ASSERT_EQUAL_PTR(class[1][2][3].course, populationOfClasses[0].class[1][2][3].course);
	TEST_ASSERT_EQUAL_PTR(class[1][2][3].lecturer, populationOfClasses[0].class[1][2][3].lecturer);
	TEST_ASSERT_EQUAL(class[1][2][3].typeOfClass, populationOfClasses[0].class[1][2][3].typeOfClass);
}

void test_clearClassSlot_should_able_to_remove_elements(){

	Class testClass;
	
	testClass = copyClassSlot(classList[0]);
	testClass = clearClassSlot(testClass);
	TEST_ASSERT_EQUAL_PTR( NULL, testClass.course);
	TEST_ASSERT_EQUAL_PTR( NULL, testClass.lecturer);
	TEST_ASSERT_EQUAL_PTR( NULL, testClass.group[0]);
	TEST_ASSERT_EQUAL_PTR( NULL, testClass.group[1]);
	TEST_ASSERT_EQUAL_PTR( NULL, testClass.group[2]);
	TEST_ASSERT_EQUAL_PTR( NULL, testClass.group[3]);
	TEST_ASSERT_EQUAL_PTR( NULL, testClass.group[4]);
	TEST_ASSERT_EQUAL( 0, testClass.typeOfClass);
	
}

void test_clearClass_should_able_to_remove_elements(){
	fillInTheChromosome(classList, sizeof(classList)/sizeof(Class));
	clearClass(class);
	
	TEST_ASSERT_EQUAL_PTR( NULL, class[0][0][0].course);
	TEST_ASSERT_EQUAL_PTR( NULL, class[0][0][0].lecturer);
	TEST_ASSERT_EQUAL_PTR( NULL, class[0][0][0].group[0]);
	TEST_ASSERT_EQUAL_PTR( NULL, class[0][0][0].group[1]);
	TEST_ASSERT_EQUAL_PTR( NULL, class[0][0][0].group[2]);
	TEST_ASSERT_EQUAL_PTR( NULL, class[0][0][0].group[3]);
	TEST_ASSERT_EQUAL_PTR( NULL, class[0][0][0].group[4]);
	TEST_ASSERT_EQUAL( 0, class[0][0][0].typeOfClass);
	
}

void test_compareClass_should_return_1_if_all_elements_are_same(){
	Class test = classList[0];
	Class test1 = classList[0];

	TEST_ASSERT_EQUAL(1, compareClass(test,test1));
}

void test_compareClass_should_return_0_if_one_elements_not_same(){
	Class test = classList[0];
	Class test1 = classList[0];
	test1.lecturer = &lecturer[2];

	TEST_ASSERT_EQUAL(0, compareClass(test,test1));
}

/**
*   The purpose of this function is to make sure all the elements are copied
*   accordingly from the classList to newList(randomList)
*   In this function, mock is used to make sure it works
*   Mock the value from sizeofList - 1, to 0 (totally inverted order)
*   And then test whether the elements are equals in both list.
*/
void test_randomizeClassList_can_create_newList(){
 Class testList[52];
 clearClassList(sizeof(testList)/sizeof(Class) , testList);

 int i, j;
 i =  sizeof(testList)/sizeof(Class) - 1;
 
 /**
 *  Mock from 51 to 0
 *  result will be this
 *  classList       testList
 *     51      >       0
 *     50      >       1
 *     .       >       .
 *     .       >       .
 *     0       >       51
 **/
 while( i >= 0){
  random_ExpectAndReturn(sizeof(testList)/sizeof(Class), i);
  i--;
 }
 
 //run the function
 randomizeClassList(sizeof(testList)/sizeof(Class),testList);
 
 i = sizeof(testList)/sizeof(Class) - 1;
 j = 0;
 // TEST_ASSERT weather the courses are same
 while( i >= 0 && j < sizeof(testList)/sizeof(Class)){
   TEST_ASSERT_EQUAL(1, compareClass(testList[i], classList[j]));
   i--;
   j++;
 }
 
}




