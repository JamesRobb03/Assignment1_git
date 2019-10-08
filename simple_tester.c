#include <stdio.h>
#include <stdlib.h>
#include "boarding.h"
#include <string.h>

/* A function (and global) that can trigger malloc fails on demand. */
int mallocFail = 0;
void* myMalloc(size_t size) {
	if (mallocFail) { return NULL; }
	else { return malloc(size); }
}

int main()
{
	// store result of calling functions
	int result;

	// a variable to store data (i.e. a passenger) popped from the queue
	Passenger p;

	// a pointer to a double-ended queue
	BoardingQueue *qPtr = NULL;

	// initialise the queue - passing the address of our
	// queue pointer as an input so it can be modified 
	// to point to the memory allocated for the queue
	result = createBoardingQueue(&qPtr);
	if (result != SUCCESS)
	{
		printf("An error occurred when attempting to initialise the queue\n");
	}
	else
	{
		printf("Queue initialised successfully\n");
	}

	// try popping / remvoving the passenger at the head of the queue.
	// this should fail since the queue is currently empty
	result = removePassenger(qPtr, &p);
	if (result != INVALID_QUEUE_OPERATION)
	{
		printf("Error: should have detected attempt to remove passenger from an empty queue\n");
	}
	else
	{
		printf("Correctly identified attempt to remove passenger from an empty queue\n");
	}

	// try peeking at the head of the queue - this should fail since the
	// queue is empty
	result = peekAtHeadPassenger(qPtr, &p);
	if (result != INVALID_QUEUE_OPERATION)
	{
		printf("Error: should have detected attempt to peek at the head of an empty queue\n");
	}
	else
	{
		printf("Correctly identified attempt to peek at the head of an empty queue\n");
	}

	// try peeking at the tail of the queue - this should fail since the
	// queue is empty
	result = peekAtTailPassenger(qPtr, &p);
	if (result != INVALID_QUEUE_OPERATION)
	{
		printf("Error: should have detected attempt to peek at the tail of an empty queue\n");
	}
	else
	{
		printf("Correctly identified attempt to peek at the tail of an empty queue\n");
	}

	// add a passenger to the end / tail of the queue
	char passengerName[] = "C. Jones";
	double passportNumber = 12;
	int seatNumber = 35;
	result = addPassenger(qPtr, passengerName, passportNumber, seatNumber); 
	if (result != SUCCESS)
	{
		printf("Error: failed to add passenger to end / tail of queue\n");
	}
	else
	{
		printf("addPassenger() successful\n");
	}

	// add a passenger to the head / front of the queue	
	char passengerName2[] = "C. Smith";
	double passportNumber2 = 87;
	int seatNumber2 = 2;
	result = addPriorityPassenger(qPtr, passengerName2, passportNumber2, seatNumber2); 
	if (result != SUCCESS)
	{
		printf("Error: failed to add passenger to front / head of queue\n");
	}
	else
	{
		printf("addPriorityPassenger() successful\n");
	}

	// try peeking at the head of the queue - expect to find the passenger "C. Smith"
	result = peekAtHeadPassenger(qPtr, &p);
	if (result != SUCCESS)
	{
		printf("Error: attempt to peek at head of queue failed\n");
	}
	else
	{
		// check passenger name
		if (strncmp(p.name, "C. Smith", 29) != 0)
		{
			printf("Error: data at head passenger isn't as expected\n");
		}
		else
		{
			printf("peekAtHeadPassenger() successful\n");
		}
	}

	// try peeking at the tail of the queue - expect to find the passenger "C. Jones"
	result = peekAtTailPassenger(qPtr, &p);
	if (result != SUCCESS)
	{
		printf("Error: attempt to peek at tail of queue failed\n");
	}
	else
	{
		// check passenger name
		if (strncmp(p.name, "C. Jones", 29) != 0)
		{
			printf("Error: data at tail passenger isn't as expected\n");
		}
		else
		{
			printf("peekAtTailPassenger() successful\n");
		}
	}

	// try removing the next passenger from the head of the queue
	result = removePassenger(qPtr, &p);
	if (result != SUCCESS)
	{
		printf("Error: failed to remove passenger from head of the queue\n");
	}
	else
	{
		printf("Successfully removed passenger %s from the head of the queue\n", p.name);
	}

	// try emptying the queue
	result = clearBoardingQueue(qPtr);
	if (result != SUCCESS)
	{
		printf("Error: failed to clear the boarding queue\n");
	}
	else
	{
		printf("Successfully cleared the boarding queue\n");
	}

	return 0;
}