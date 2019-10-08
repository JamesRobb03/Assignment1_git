#include <stddef.h> // header required for myMalloc function

/* error codes / success codes */
#define SUCCESS                  100   // Value to be returned if a function is completed successfully
#define INVALID_INPUT_PARAMETER  101   // Value to be returned if you detect that one of the input parameters 
                                       // into your function is invalid, e.g. it is NULL or an unexpected value
#define MEMORY_ALLOCATION_ERROR  102   // Value to be returned if a memory allocation error occurs during your function
#define INVALID_QUEUE_OPERATION  103   // Value to be returned if your function detects an operation that is being
                                       // attempted on your queue data structure that isn't valid or your queue
                                       // isn't in a ready state to receive. For example, an attempt is made to remove
                                       // an item from an empty queue
#define NOT_IMPLEMENTED          104   // Value to be returned if you haven't implemented this function yet



/* typedef for passengers that may join a boarding queue. */
typedef struct passenger {
	char name[30];			// the passenger's name
	double passportNumber;	// their passport number
	int seatNumber;			// their seat number on the plane
	struct passenger* next;	// a pointer to the next passenger in the queue after this one
} Passenger;


/* typedef for a boarding queue, i.e. a queue of passengers waiting to board a plane. */
typedef struct boardingQueue {
	Passenger* head; // points to the Passenger at the front/head of the queue
	Passenger* tail; // points to the Passenger at the end/tail of the queue
} BoardingQueue;


/* Create a new, empty boarding queue, storing a pointer to it in the variable 
   provided (e.g. qPtr) */
int createBoardingQueue(BoardingQueue **qPtr);


/* Add a new Passenger to the END / tail of the boarding queue using the values provided */
int addPassenger(BoardingQueue *qPtr, char name[], double passportNumber, int seatNumber);


/* Add a new Passenger to the HEAD / front of the boarding queue - they are being added
   to the front of the queue because they are a priority passenger */
int addPriorityPassenger(BoardingQueue *qPtr, char name[], double passportNumber, int seatNumber);


/* Remove the next passenger from the front of the queue - because they have been processed and can now
   board the plane. This function is equivalent to the 'pop' function that a queue usually
   has, i.e. to remove the item which is currently at the head of the queue. The data for
   the passenger that is being removed should be stored in the variable provided (e.g. 'p') */
int removePassenger(BoardingQueue *qPtr, Passenger *p);


/* Peek at the head of the queue to get the data for the passenger that is next
   to board the plane. The passenger data should be stored in the variable provided (e.g. 'p')  */
int peekAtHeadPassenger(BoardingQueue *qPtr, Passenger *p);


/* Peek at the tail of the queue to get the data for the passenger that is currently last in
   line to board the plane. The passenger data should be stored in the variable provided (e.g. 'p')  */
int peekAtTailPassenger(BoardingQueue *qPtr, Passenger *p);


/* Empty the boarding queue, freeing up any memory that it is currently using */
int clearBoardingQueue(BoardingQueue *qPtr);

/* ADVANCED - EXTRA MARKS!
   Sort the boarding queue so that passengers are arranged based on their seat number, from lowest
   to highest. This is to allow the plane to be boarded based on seat numbers. */
int sortBoardingQueue(BoardingQueue *qPtr);

/* A function to allocate memory - the same as 'malloc()'.
   You will use myMalloc() to allocate memory in your own code. 
   We implement the code for this function for you. You will
   find the code in the tester file 'boarding_tester.c'. */
void* myMalloc(size_t size);