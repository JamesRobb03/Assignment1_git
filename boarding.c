#include "boarding.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//TODO - ADD INPUT VALIDATION FOR FIELDS.

int main()
{
	int rVal = 0;
	BoardingQueue *myBQ = NULL;

	//testing
	rVal = createBoardingQueue(&myBQ);
	printf("Initialisation output: %d\n", rVal);
	rVal = addPassenger(myBQ, "James", 9876, 12);
	printf("Add Passenger output: %d\n", rVal);
	rVal = addPriorityPassenger(myBQ,"Priority", 1111, 1);
	printf("Add Priority Passenger output: %d\n", rVal);

	return 0;
}
/* Create a new, empty boarding queue, storing a pointer to it in the variable 
   provided (e.g. qPtr) */
int createBoardingQueue(BoardingQueue **qPtr)
{
	if (qPtr == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}

	/*Check to see whether pointer is already pointing to something*/
	if (*qPtr != NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}

	/*Allocating memory for new BoardingQueue and storing in pointer qPtr*/
	(*qPtr) = (BoardingQueue*)myMalloc(sizeof(BoardingQueue));

	/*Checking for memory failure*/
	if ((*qPtr)==NULL)
	{
		return MEMORY_ALLOCATION_ERROR;
	}

	/*Setting values for queue*/
	(*qPtr)->head = NULL;
	(*qPtr)->tail = NULL;

	return SUCCESS;
}


/* Add a new Passenger to the END / tail of the boarding queue using the values provided */
int addPassenger(BoardingQueue *qPtr, char name[], double passportNumber, int seatNumber)
{
	//checking to see if pointer is pointing to valid queue
	if(qPtr == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}
	//creates a passenger to add to the queue
	Passenger *newPassenger = (Passenger*)myMalloc(sizeof(Passenger));

	//check to see whether memory has been succesfully allocated
	if (newPassenger == NULL)
	{
		return MEMORY_ALLOCATION_ERROR;
	}

	//initialise fields
	strcpy(newPassenger->name, name);
	newPassenger->passportNumber = passportNumber;
	newPassenger->seatNumber = seatNumber;
	//passengers next should initially be null
	newPassenger->next = NULL;

	//check to see if boardingqueue is empty
	if (qPtr->head == NULL && qPtr->tail == NULL)
	{
		qPtr->head = newPassenger;
		qPtr->tail = newPassenger;
	}

	qPtr->tail->next = newPassenger;
	qPtr->tail = newPassenger;

	return SUCCESS;
}

int addPriorityPassenger(BoardingQueue *qPtr, char name[], double passportNumber, int seatNumber)
{
	//checking to see if pointer is pointing to valid queue
	if (qPtr == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}

	//creates a passenger to add to queue
	Passenger *newPriority = (Passenger*)myMalloc(sizeof(Passenger));

	//check to see wether memory has been succesfully allocated
	if (newPriority == NULL)
	{
		return MEMORY_ALLOCATION_ERROR;
	}

	//initialise fields
	strcpy(newPriority->name, name);
	newPriority->passportNumber = passportNumber;
	newPriority->seatNumber = seatNumber;
	//set priorities next to head of queue
	newPriority->next = qPtr->head;

	//check to see if queue is empty
	if (qPtr->head == NULL && qPtr->tail == NULL)
	{
		qPtr->head = newPriority;
		qPtr->tail = newPriority;
	}

	qPtr->head = newPriority;

	return SUCCESS;
}

//FOR TESTING PURPOSES
/* A function (and global) that can trigger malloc fails on demand. */
int mallocFail = 0;
void* myMalloc(size_t size) {
	if (mallocFail) { return NULL; }
	else { return malloc(size); }
}
