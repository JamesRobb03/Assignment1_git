/*
 Name: James Robb
 Matric number: 180010640
 Module code: AC21008
*/

#include "boarding.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//TODO - Add more robust input checks. Add more commenting. Add the sort function.

//Function to display queue. Used in testing when i wanted to see all passengers currently in the queue
//Altered from the lab 3 answers.
int displayQ(BoardingQueue *pQ)
{
	// if there is no stack to traverse
	if (pQ == NULL)
		return INVALID_INPUT_PARAMETER;

	// if the stack is empty
	if (pQ->head == NULL)
		return INVALID_QUEUE_OPERATION;

	// traverse the entire Stack, from top to bottom
	Passenger *nextNodeToDisplay = pQ->head;
	while (nextNodeToDisplay != NULL)
	{
		// display node
		printf("Next passenger in Queue: %s\n", nextNodeToDisplay->name);

		// move to next node down the stack
		nextNodeToDisplay = nextNodeToDisplay->next;
	}

	// done
	return SUCCESS;
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
	//check to see if name is not greater than 30 characters long
	if (name!=NULL)
	{
		int len;
		len = strlen(name);
		if (len>30)
		{
			return INVALID_INPUT_PARAMETER;
		}
	}
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
	if (name == NULL || passportNumber < 1 || passportNumber > 88000 ||seatNumber < 1 || seatNumber > 150)
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
	}else
	{
		qPtr->tail->next = newPassenger;
		qPtr->tail = newPassenger;
	}

	return SUCCESS;
}

int addPriorityPassenger(BoardingQueue *qPtr, char name[], double passportNumber, int seatNumber)
{
	//check to see if name is not greater than 30 characters long
	if (name!=NULL)
	{
		int len;
		len = strlen(name);
		if (len>30)
		{
			return INVALID_INPUT_PARAMETER;
		}
	}

	//checking to see if pointer is pointing to valid queue
	if (qPtr == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}

	if (name == NULL || passportNumber < 1 || passportNumber > 88000 ||seatNumber < 1 || seatNumber > 150)
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

	//copying the passenger at the head of the queue into the passenger p
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

	//copying the passenger at the tail of the queue into the passenger p
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

		//move head to next passenger down
		qPtr->head = qPtr->head->next;

		//free the current head
		currentHead->next = NULL;
		currentHead->seatNumber=0;
		currentHead->passportNumber=0;
		strcpy(currentHead->name, "");

		//Free's the passenger at the head of the queue
		free(currentHead);
	}

	//free empty stack
	free(qPtr);

	return SUCCESS;
}

/*Function that sorts the boarding queue based on the seat number of the passenger*/
int sortBoardingQueue(BoardingQueue *qPtr)
{
	//initialising variables
	int isSwapped; 
	int i;
	Passenger *tempPass;
	Passenger *lastPassenger = NULL;

	//check to see if queue is empty
	if (qPtr == NULL)
	{
		return INVALID_INPUT_PARAMETER;
	}

	//do while loop which swaps the data from one passenger to another passenger if the seat number is 
	//larger nearer the head of the queue.
	do
	{
		//sets up variables 
		isSwapped = 0;
		tempPass = qPtr->head;

		//while loops which loops through the queue 
		while(tempPass->next != lastPassenger)
		{
			//if statement which checks if the currents passengers seat number is larger than the next passengers seat number
			if (tempPass->seatNumber > tempPass->next->seatNumber)
			{
				//swaps values of one passenger to the other 
				int temp = tempPass->seatNumber;
				tempPass->seatNumber = tempPass->next->seatNumber;
				tempPass->next->seatNumber = temp;

				double temp2 = tempPass->passportNumber;
				tempPass->passportNumber = tempPass->next->passportNumber;
				tempPass->next->passportNumber = temp;

				char temp3[30];
				strcpy(temp3, tempPass->name);
				strcpy(tempPass->name, tempPass->next->name);
				strcpy(tempPass->next->name, temp3);

				//sets the isSwapped value to break the loop
				isSwapped = 1;
			}
			//sets tempPass to the next Passenger along
			tempPass = tempPass->next;
		}
		//sets lastPassenger to tempPass
		lastPassenger = tempPass;	
	}while(isSwapped);

	return SUCCESS;
}

