#include "unity.h"
#include <stdio.h>
#include "TimeTabling.h"
#include "ErrorCode.h"
#include "CException.h"
#include "Random.h"   
    
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
void test_indexForward_should_throw_error_when_exceeded_index_inserted(){
	CEXCEPTION_T e;
	int venue = 0, day = 0, time = 6;
	
	Try{
	indexForward(&venue, &day, &time);
	}Catch(e){
		TEST_ASSERT_EQUAL( ERR_EXCEEDED_INDEX, e);
    }
}

void test_indexForward_should_return_0_1_0(){

	int venue = 0, day = 0, time = 4;
	
	indexForward(&venue, &day, &time);
	
	TEST_ASSERT_EQUAL( 0, venue);
	TEST_ASSERT_EQUAL( 1, day);
	TEST_ASSERT_EQUAL( 0, time);
}

void test_indexForward_should_return_1_0_0(){

	int venue = 0, day = 2, time = 4;
	
	indexForward(&venue, &day, &time);
	
	TEST_ASSERT_EQUAL( 1, venue);
	TEST_ASSERT_EQUAL( 0, day);
	TEST_ASSERT_EQUAL( 0, time);
}

void test_indexForward_should_return_0_0_0_for_reset(){

	int venue = 3, day = 2, time = 4;
	
	indexForward(&venue, &day, &time);
	
	TEST_ASSERT_EQUAL( 0, venue);
	TEST_ASSERT_EQUAL( 0, day);
	TEST_ASSERT_EQUAL( 0, time);
}

void test_indexBackward_should_throw_error_when_exceeded_index_inserted(){
	CEXCEPTION_T e;
	int venue = 0, day = 0, time = 18;
	
	Try{
	indexBackward(&venue, &day, &time);
	}Catch(e){
		TEST_ASSERT_EQUAL( ERR_EXCEEDED_INDEX, e);
	}
}

void test_indexBackward_should_return_0_0_2(){
	int venue = 0, day = 0, time = 3;
	
	indexBackward(&venue, &day, &time);
	
	TEST_ASSERT_EQUAL( 0, venue);
	TEST_ASSERT_EQUAL( 0, day);
	TEST_ASSERT_EQUAL( 2, time);
	
}

void test_indexBackward_should_return_1_0_4(){
	int venue = 1, day = 1, time = 0;
	
	indexBackward(&venue, &day, &time);
	
	TEST_ASSERT_EQUAL( 1, venue);
	TEST_ASSERT_EQUAL( 0, day);
	TEST_ASSERT_EQUAL( 4, time);

}

void test_indexBackward_should_return_3_1_4(){
	int venue = 3, day = 2, time = 0;
	
	indexBackward(&venue, &day, &time);
	
	TEST_ASSERT_EQUAL( 3, venue);
	TEST_ASSERT_EQUAL( 1, day);
	TEST_ASSERT_EQUAL( 4, time);

}

void test_checkChromosomeIsEmpty_given_a_chromosome_that_is_not_empty_should_return_class001(void) {
 class[0][0][0].course = &course[0];
 class[0][0][0].lecturer = &lecturer[0];

  Class *result;

  result = checkChromosomeIsEmpty(class);
  TEST_ASSERT_EQUAL_PTR(&class[0][0][1],result);
}

void test_checkChromosomeIsEmpty_given_a_chromosome_that_is_not_empty_should_return_class002(void) {
	class[0][0][0].course = &course[0];
	class[0][0][0].lecturer = &lecturer[0];
	class[0][0][1].course = &course[1];
	class[0][0][1].lecturer = &lecturer[1];
	
  Class *result;
  result = checkChromosomeIsEmpty(class);
  TEST_ASSERT_EQUAL_PTR(&class[0][0][2],result);
}


void test_addDetailsIntoChromosome_given_the_details_should_be_able_to_add_into_the_class000(void) {
                                            
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], &group[0], 'l');
  
  TEST_ASSERT_EQUAL_STRING("AAMP2041", class[0][0][0].course->courseCode);
  TEST_ASSERT_EQUAL_STRING("Mathematics", class[0][0][0].course->courseName);
  TEST_ASSERT_EQUAL_STRING("RMB2", class[0][0][0].course->programme[0]->programmeName);
  TEST_ASSERT_EQUAL_STRING("A1", class[0][0][0].course->programme[0]->group[0]->groupName);
  TEST_ASSERT_EQUAL_STRING("A2", class[0][0][0].course->programme[0]->group[1]->groupName);
  TEST_ASSERT_EQUAL(2, class[0][0][0].course->hoursOfLecture);
  TEST_ASSERT_EQUAL(2, class[0][0][0].course->hoursOfPractical);
  TEST_ASSERT_EQUAL(1, class[0][0][0].course->hoursOfTutorial);
  TEST_ASSERT_EQUAL(12, class[0][0][0].group[0]->groupSize);
  TEST_ASSERT_EQUAL(20, class[0][0][0].course->sizeOfProgramme);
  TEST_ASSERT_EQUAL_STRING("Poh TV", class[0][0][0].lecturer->lecturerName);
  TEST_ASSERT_EQUAL_STRING("FASC", class[0][0][0].lecturer->department);
  TEST_ASSERT_EQUAL('l', class[0][0][0].typeOfClass);
}

void test_addDetailsIntoChromosome_given_the_details_should_be_able_to_add_into_the_class001(void) {                                          
  addDetailsIntoChromosome(class, &course[0], &lecturer[0], &group[0], 'l');
  addDetailsIntoChromosome(class, &course[1], &lecturer[1], &group[1], 't');
  
  TEST_ASSERT_EQUAL_STRING("AAMP2041", class[0][0][0].course->courseCode);
  TEST_ASSERT_EQUAL_STRING("Mathematics", class[0][0][0].course->courseName);
  TEST_ASSERT_EQUAL_STRING("RMB2", class[0][0][0].course->programme[0]->programmeName);
  TEST_ASSERT_EQUAL_STRING("A1", class[0][0][0].course->programme[0]->group[0]->groupName);
  TEST_ASSERT_EQUAL_STRING("A2", class[0][0][0].course->programme[0]->group[1]->groupName);
  TEST_ASSERT_EQUAL(2, class[0][0][0].course->hoursOfLecture);
  TEST_ASSERT_EQUAL(2, class[0][0][0].course->hoursOfPractical);
  TEST_ASSERT_EQUAL(1, class[0][0][0].course->hoursOfTutorial);
  TEST_ASSERT_EQUAL(12, class[0][0][0].course->programme[0]->group[0]->groupSize);
  TEST_ASSERT_EQUAL(20, class[0][0][0].course->sizeOfProgramme);
  TEST_ASSERT_EQUAL_STRING("Poh TV", class[0][0][0].lecturer->lecturerName);
  TEST_ASSERT_EQUAL_STRING("FASC", class[0][0][0].lecturer->department);
	TEST_ASSERT_EQUAL('l', class[0][0][0].typeOfClass);
  
  TEST_ASSERT_EQUAL_STRING("AAMB2034", class[0][0][1].course->courseCode);
  TEST_ASSERT_EQUAL_STRING("English", class[0][0][1].course->courseName);
  TEST_ASSERT_EQUAL_STRING("RMB3", class[0][0][1].course->programme[0]->programmeName);
  TEST_ASSERT_EQUAL_STRING("B1", class[0][0][1].course->programme[0]->group[0]->groupName);
  TEST_ASSERT_EQUAL_STRING("B2", class[0][0][1].course->programme[0]->group[1]->groupName);
  TEST_ASSERT_EQUAL(2, class[0][0][1].course->hoursOfLecture);
  TEST_ASSERT_EQUAL(1, class[0][0][1].course->hoursOfTutorial);
  TEST_ASSERT_EQUAL(0, class[0][0][1].course->hoursOfPractical);
  TEST_ASSERT_EQUAL(15, class[0][0][1].course->programme[0]->group[0]->groupSize);
  TEST_ASSERT_EQUAL(30, class[0][0][1].course->sizeOfProgramme);
  TEST_ASSERT_EQUAL_STRING("Chan CK", class[0][0][1].lecturer->lecturerName);
  TEST_ASSERT_EQUAL_STRING("FASC", class[0][0][1].lecturer->department);
	TEST_ASSERT_EQUAL('t', class[0][0][1].typeOfClass);
}

/**
*   This function will determine whether the create population did create population
*   Before create, each of the course in class[0][0][0] is NULL
*   After created, the class[0][0][0].course will not be NULL
*   Due to the sorting algorithm, the first slot of class[][][] will be filled 
**/
void test_createPopulationOfChromosome_should_fill_in_the_populations(){
	int i = 0;
	
	clearPopulation(populationOfClasses);
  // to make sure all NULL before adding
  while(i < sizeof(populationOfClasses)/sizeof(Population)){
    TEST_ASSERT_NULL(populationOfClasses[i].class[0][0][0].course);
    i++;
  }
  
	createPopulationsOfChromosome(sizeof(classList)/sizeof(Class));
  
  i = 0;
  //to make sure all stuffed after create population
  while(i < sizeof(populationOfClasses)/sizeof(Population)){
    TEST_ASSERT_NOT_NULL(populationOfClasses[i].class[0][0][0].course);
    TEST_ASSERT_EQUAL(populationOfClasses[i].violation , calculateFitnessScore(populationOfClasses[i].class));
    i++;
  }
}

void test_copyPopulation_should_copy_population_over(){
	int i = 0 ,j = 0, k = 0, l;
	clearPopulation(populationOfClasses);
	createPopulationsOfChromosome(sizeof(classList)/sizeof(Class));
	
	Population resultPop = copyPopulation(populationOfClasses[0]);
	
	TEST_ASSERT_EQUAL(populationOfClasses[0].violation, resultPop.violation);
  
  //To check the population properly copied
  for( l = 0; l < (MAX_VENUE*MAX_DAY*MAX_TIME_SLOTS) ; l++){
    TEST_ASSERT_EQUAL(1, compareClass(populationOfClasses[0].class[i][j][k], resultPop.class[i][j][k]));
    indexForward(&i,&j,&k);
  }
}


void test_sortPopulationsAccordingToFitness_should_swap_population_fitness_in_ascending_order(){
	//Create 2 population
  clearPopulation(populationOfClasses);
	int pop0Violation, pop1Violation;
	Population pop[2];
	
  //Add the class list to chromosome and get the violation score > pop0Violation
	fillInTheChromosome(classList, sizeof(classList)/sizeof(Class));
	copyClass(class, pop[0].class);
	pop[0].violation = calculateFitnessScore(pop[0].class);
	pop0Violation = pop[0].violation;
	
	clearClass(class);
	
  //Add the class list to chromosome and get the violation score > pop1Violation
	fillInTheChromosomeWithReducingViolation(classList, sizeof(classList)/sizeof(Class));
	copyClass(class, pop[1].class);
	pop[1].violation = calculateFitnessScore(pop[1].class);
	pop1Violation = pop[1].violation;
	clearClass(class);
	
  //run and it should be swapped
	sortPopulationsAccordingToFitness(pop, sizeof(pop)/sizeof(Population));
	
  //The pop[0].violation replaced with pop1Violation's original class[][][]
  //And vice versa
	TEST_ASSERT_EQUAL(pop1Violation, pop[0].violation);
	TEST_ASSERT_EQUAL(pop0Violation, pop[1].violation);
	
}


void test_sortPopulationsAccordingToFitness_should_sort_fitness_in_ascending_order(){
	int i, compareResult;
	clearPopulation(populationOfClasses);
	createPopulationsOfChromosome(sizeof(classList)/sizeof(Class));
	
	sortPopulationsAccordingToFitness(populationOfClasses, sizeof(populationOfClasses)/sizeof(Population));
	
  //To shows that the population at the back should have more or equal violation to the current
	for(i= 0 ; i+1 < sizeof(populationOfClasses)/sizeof(Population) ; i++){
		if(populationOfClasses[i].violation <= populationOfClasses[i+1].violation)
			compareResult = 1;
		else
			compareResult = 0;
			
			TEST_ASSERT_EQUAL(1, compareResult);
	}
}


void xtest_solveTimeTabling_test_number_1_should_be_able_to_produce_an_offspring_with_lesser_violation(void) {
  // solveTimeTabling();
}