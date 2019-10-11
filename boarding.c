#include "boarding.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//TODO - ADD INPUT VALIDATION FOR FIELDS.


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

	//checks to see if inputs are valid
	if (name == NULL || passportNumber <1 || seatNumber <1)
	{
		return INVALID_INPUT_PARAMETER;
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

	if (name == NULL || passportNumber <1 || seatNumber <1)
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

/*function to remove passenger from queue*/
int removePassenger(BoardingQueue *qPtr, Passenger *p)
{
	//check if queue is valid
	if (qPtr == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}

	//checking to see if memory address of p is valid
	if (p == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}

	//checking to see if queue is empty
	if (qPtr->head == NULL)
	{
		return INVALID_QUEUE_OPERATION;
	}

	//store passenger thats at the head of the queue
	strcpy(p->name, qPtr->head->name);
	p->passportNumber = qPtr->head->passportNumber;
	p->seatNumber = qPtr->head->seatNumber;
	p->next = qPtr->head->next;

	//create temp pointer to person at head of stack
	Passenger *pToRemove = qPtr->head;

	//change head of queue to be next person in queue
	qPtr->head = qPtr->head->next;

	//remove / free existing top
	pToRemove->next = NULL;
	pToRemove->seatNumber=0;
	pToRemove->passportNumber=0;
	strcpy(pToRemove->name, "");
	free(pToRemove);

	return SUCCESS;
}

//function to look at the Passenger at the head of the queue
int peekAtHeadPassenger(BoardingQueue *qPtr, Passenger *p)
{
	//check to see if qPtr is pointing to a valid queue
	if (qPtr == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}

	//checking to see that the pointer storing the Person isnt null
	if (p == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}

	//checking that queue isnt empty
	if (qPtr->head == NULL)
	{
		return INVALID_QUEUE_OPERATION;
	}

	strcpy(p->name, qPtr->head->name);
	p->passportNumber = qPtr->head->passportNumber;
	p->seatNumber = qPtr->head->seatNumber;
	p->next = qPtr->head->next;

	return SUCCESS;
}

//function to look at the passenger at the tail of the queue
int peekAtTailPassenger(BoardingQueue *qPtr, Passenger *p)
{
	//check to see if qPtr is pointing to a valid queue
	if (qPtr == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}

	//checking to see that the pointer storing the Person isnt null
	if (p == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}

	//checking that queue isnt empty
	if (qPtr->tail == NULL)
	{
		return INVALID_QUEUE_OPERATION;
	}

	strcpy(p->name, qPtr->tail->name);
	p->passportNumber = qPtr->tail->passportNumber;
	p->seatNumber = qPtr->tail->seatNumber;
	p->next = qPtr->tail->next;

	return SUCCESS;	
}

/* Empty the boarding queue, freeing up any memory that it is currently using */
int clearBoardingQueue(BoardingQueue *qPtr)
{
	//checking to see if pointer is pointing to valid queue
	if (qPtr == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}

	//loops to see if there is still passengers in the queue to free
	while(qPtr->head != NULL)
	{
		//get pointer to current head of queue
		Passenger *currentHead = qPtr->head;

		//printf("%d\n", currentHead->seatNumber);
		//move head to next passenger down
		qPtr->head = qPtr->head->next;

		//free the current head
		currentHead->next = NULL;
		currentHead->seatNumber=0;
		currentHead->passportNumber=0;
		strcpy(currentHead->name, "");

		//free(currentHead);
	}

	qPtr->tail = NULL;

	free(qPtr);

	return SUCCESS;
}
