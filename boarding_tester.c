#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "boarding.h"

#define STUDENT_OUT stdout
#define STAFF_OUT stderr

/* A function (and global) that can trigger malloc fails on demand. */
int mallocFail = 0;
void* myMalloc(size_t size) {
	if (mallocFail) { return NULL; }
	else { return malloc(size); }
}

void test_createBoardingQueue();
void test_addPassenger();
void test_removePassenger();
void test_peekAtHeadPassenger();
int passengerDataCorrect(Passenger *p, char name[], double passportNumber, int seatNumber);

/* Prints a 'passed' message with the points awarded (value).
   Also adds 'value' to 'marks'. */
void printPass(const char* testName) {
	fprintf(STUDENT_OUT, "  passed test: %s\n", testName);
}
/* Prints a 'failed' message with 0 points awarded. */
void printFail(const char* testName) {
	fprintf(STUDENT_OUT, "  failed test: %s\n", testName);
}

// main program to run a series of testd
int main() {
	test_createBoardingQueue();
	test_addPassenger();
	test_removePassenger();
	test_peekAtHeadPassenger();

	return 0;
}

/* test 'createBoardingQueue' */
void test_createBoardingQueue() {
	fprintf(STUDENT_OUT, "\nTESTS FOR FUNCTION createBoardingQueue()...\n");

	// test null pointer to queue
	char* testName = "check that qPtr input parameter is valid - should be non-NULL";
	int rVal = createBoardingQueue(NULL);
	if (rVal == INVALID_INPUT_PARAMETER) { printPass(testName); }
	else { printFail(testName); }

	// OUT_OF_MEMORY
	testName = "check for memory allocation failure";
	mallocFail = 1;
	BoardingQueue *qPtr = NULL;
	rVal = createBoardingQueue(&qPtr);
	if (rVal == MEMORY_ALLOCATION_ERROR) { printPass(testName); }
	else { printFail(testName); }
	mallocFail = 0;

	// SUCCESS
	testName = "successful queue creation";
	qPtr = NULL;
	rVal = createBoardingQueue(&qPtr);
	if (rVal == SUCCESS) { printPass(testName); }
	else { printFail(testName); }

	// head==NULL
	testName = "head of queue is valid";
	if (qPtr!=NULL && qPtr->head == NULL) { printPass(testName); }
	else { printFail(testName); }

	// tail==NULL
	testName = "tail of queue is valid";
	if (qPtr!=NULL && qPtr->tail == NULL) { printPass(testName); }
	else { printFail(testName); }

}

/* test 'addPassenger' */
void test_addPassenger() {
	fprintf(STUDENT_OUT, "\nTESTS FOR FUNCTION addPassenger()...\n");

	// initialize a new (my) deq to mark on
	BoardingQueue* qPtr = NULL;
	int rVal = createBoardingQueue(&qPtr);
	if (rVal != SUCCESS) { printFail("  ******************* createBoardingQueue():1 FAILED *******************\n"); exit(1); }

	char name[] = "J Smith";
	double passportNumber = 12;
	int seatNumber = 37;

	// NULL passenger name passed to function
	char *testName = "check for NULL passenger name passed to function";
	rVal = addPassenger(qPtr, NULL, passportNumber, seatNumber);
	if (rVal == INVALID_INPUT_PARAMETER) { printPass(testName); }
	else { printFail(testName); }

	// reinitialize the (my) deq to mark on
	qPtr = NULL;
	rVal = createBoardingQueue(&qPtr);
	if (rVal != SUCCESS) { printFail("  ******************* createBoardingQueue():2 FAILED *******************\n"); exit(1); }

	// NULL passenger name passed to function
	testName = "check for valid passport number (should be > 0)";
	rVal = addPassenger(qPtr, name, 0, seatNumber);
	if (rVal == INVALID_INPUT_PARAMETER) { printPass(testName); }
	else { printFail(testName); }

	// reinitialize the (my) deq to mark on
	qPtr = NULL;
	rVal = createBoardingQueue(&qPtr);
	if (rVal != SUCCESS) { printFail("  ******************* createBoardingQueue():3 FAILED *******************\n"); exit(1); }

	// PUSH ONTO EMPTY DEQ
	rVal = addPassenger(qPtr, name, passportNumber, seatNumber);

	// SUCCESS 1
	testName = "successfully added passenger to empty queue";
	if (rVal == SUCCESS) { printPass(testName); }
	else { printFail(testName); }

	// head!=NULL
	testName = "queue status: head should be non-NULL";
	if (qPtr!=NULL && qPtr->head != NULL) { printPass(testName); }
	else { printFail(testName); }

	// tail!=NULL
	testName = "queue status: tail should be non-NULL";
	if (qPtr!=NULL && qPtr->tail != NULL) { printPass(testName); }
	else { printFail(testName); }

	// head->data==(&v2)
	testName = "checking data for head passenger in queue is correct";
	if ((qPtr!=NULL) && (qPtr->head!=NULL) && (passengerDataCorrect(qPtr->head, name, passportNumber, seatNumber))) { printPass(testName); }
	else { printFail(testName); }
}

/* test 'removePassenger' */
void test_removePassenger() 
{
	fprintf(STUDENT_OUT, "\nTESTS FOR FUNCTION removePassenger()...\n");

	// initialize a new (my) deq to mark on
	BoardingQueue* qPtr = NULL;
	int rVal = createBoardingQueue(&qPtr);
	if (rVal != SUCCESS) { fprintf(STAFF_OUT, "  ******************* createBoardingQueue():1 FAILED *******************\n"); exit(1); }

	// NULL PARAM 1
	char* testName = "check that the pointer to the queue provided to remove from is valid, i.e. non-NULL";
	Passenger passengerData;
	rVal = removePassenger(NULL, &passengerData);
	if (rVal == INVALID_INPUT_PARAMETER) { printPass(testName); }
	else { printFail(testName); }

	// reinitialize the (my) deq to mark on
	qPtr = NULL;
	rVal = createBoardingQueue(&qPtr);
	if (rVal != SUCCESS) { fprintf(STAFF_OUT, "  ******************* createBoardingQueue():2 FAILED *******************\n"); exit(1); }

	// reinitialize the (my) deq to mark on with two items on it
	char name[] = "Bert number 1";
	double passportNumber = 1;
	int seatNumber = 1;
	char name2[] = "Bert number 2";
	double passportNumber2 = 2;
	int seatNumber2 = 2;
	rVal = addPassenger(qPtr, name, passportNumber, seatNumber);
	if (rVal != SUCCESS) { fprintf(STAFF_OUT, "  ******************* addPassenger():3 FAILED *******************\n"); exit(1); }
	rVal = addPassenger(qPtr, name2, passportNumber2, seatNumber2);
	if (rVal != SUCCESS) { fprintf(STAFF_OUT, "  ******************* addPassenger():4 FAILED *******************\n"); exit(1); }

	// test pop from 2-item (to make it a 1-item)
	rVal = removePassenger(qPtr, &passengerData);
	// SUCCESS
	testName = "attempt to remove passenger from head of queue - 2 passenger queue";
	if (rVal == SUCCESS) { printPass(testName); }
	else { printFail(testName); }

	// DATA POINTER
	testName = "checking data for removed passenger is correct";
	if (passengerDataCorrect(&passengerData, name, passportNumber, seatNumber)) { printPass(testName); }
	else { printFail(testName); }

	// head!=NULL
	testName = "queue status: head should not be NULL after removing 1 passenger from 2 passenger queue";
	if (qPtr!=NULL && qPtr->head != NULL) { printPass(testName); }
	else { printFail(testName); }

	// tail!=NULL
	testName = "queue status: tail should not be NULL after removing 1 passenger from 2 passenger queue";
	if (qPtr!=NULL && qPtr->tail != NULL) { printPass(testName); }
	else { printFail(testName); }

	// DATA POINTER
	testName = "checking data for remaining passenger at the head of the queue is correct";
	if (passengerDataCorrect(qPtr->head, name2, passportNumber2, seatNumber2)) { printPass(testName); }
	else { printFail(testName); }
}

/* test 'peekAtHeadPassenger' */
void test_peekAtHeadPassenger() 
{
	fprintf(STUDENT_OUT, "\nTESTS FOR FUNCTION peakAtHeadPassenger()...\n");

	// initialize a new (my) deq to mark on
	BoardingQueue* qPtr = NULL;
	int rVal = createBoardingQueue(&qPtr);
	if (rVal != SUCCESS) { fprintf(STAFF_OUT, "  ******************* createBoardingQueue():1 FAILED *******************\n"); exit(1); }

	// NULL PARAM 1
	char* testName = "check that the pointer to the queue provided to peek from is valid, i.e. non-NULL";
	Passenger passengerData;
	rVal = peekAtHeadPassenger(NULL, &passengerData);
	if (rVal == INVALID_INPUT_PARAMETER) { printPass(testName); }
	else { printFail(testName); }

	// reinitialize the (my) deq to mark on
	qPtr = NULL;
	rVal = createBoardingQueue(&qPtr);
	if (rVal != SUCCESS) { fprintf(STAFF_OUT, "  ******************* createBoardingQueue():2 FAILED *******************\n"); exit(1); }

	// add two passengers to queue
	char name[] = "Bert number 1";
	double passportNumber = 1;
	int seatNumber = 1;
	char name2[] = "Bert number 2";
	double passportNumber2 = 2;
	int seatNumber2 = 2;
	rVal = addPassenger(qPtr, name, passportNumber, seatNumber);
	if (rVal != SUCCESS) { fprintf(STAFF_OUT, "  ******************* addPassenger():3 FAILED *******************\n"); exit(1); }
	rVal = addPassenger(qPtr, name2, passportNumber2, seatNumber2);
	if (rVal != SUCCESS) { fprintf(STAFF_OUT, "  ******************* addPassenger():4 FAILED *******************\n"); exit(1); }

	// peek at head item on queue
	rVal = peekAtHeadPassenger(qPtr, &passengerData);

	// SUCCESS
	testName = "peek at head item on 2 item queue";
	if (rVal == SUCCESS) { printPass(testName); }
	else { printFail(testName); }

	// DATA POINTER
	testName = "check that data for (peeked-at) head item in queue is correct";
	if (passengerDataCorrect(&passengerData, name, passportNumber, seatNumber)) { printPass(testName); }
	else { printFail(testName); }
}

/* helper function, used during test functions above to compare the data for one passenger against anothers */
int passengerDataCorrect(Passenger *p, char name[], double passportNumber, int seatNumber)
{
	if (strncmp(p->name, name, 30) != 0)
		return 0;

	if (p->passportNumber != passportNumber)
		return 0;

	if (p->seatNumber != seatNumber)
		return 0;

	return 1;

}