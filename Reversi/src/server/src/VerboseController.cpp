/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex7
 **************************************/

#include "VerboseController.h"

VerboseController *VerboseController::theInstance = NULL;
pthread_mutex_t VerboseController::lock = PTHREAD_MUTEX_INITIALIZER;

/***************************************
 * Function Name: initialize
 * The Input: no input
 * The Output: no output
 * The Function Operation: initializing the
 * VerboseController thread
 **************************************/
void VerboseController::initialize() {
	pthread_mutex_init(&lock, NULL);
}

/***************************************
 * Function Name: getInstance
 * The Input: verbose -  boolean value (true/false)
 * The Output: a pointer to a VerboseController instance
 * The Function Operation: returning a
 * pointer to a VerboseController instance
 * that is initialized with the given boolean value
 **************************************/
VerboseController *VerboseController::getInstance(bool verbose) {
	if (theInstance == NULL) {
		pthread_mutex_lock(&lock);
		if (theInstance == NULL) {
			theInstance = new VerboseController(verbose);
		}
		pthread_mutex_unlock(&lock);
	}
	theInstance->verbose = verbose;
	return theInstance;
}

/***************************************
 * Function Name: getInstance
 * The Input: no input
 * The Output: a pointer to a VerboseController instance
 * The Function Operation: returning a
 * pointer to a VerboseController instance
 **************************************/
VerboseController *VerboseController::getInstance() {
	if (theInstance == NULL) {
		pthread_mutex_lock(&lock);
		if (theInstance == NULL) {
			theInstance = new VerboseController(false);
		}
		pthread_mutex_unlock(&lock);
	}
	return theInstance;
}

/***************************************
 * Function Name: deleteInstance
 * The Input: no input
 * The Output: no ouput
 * The Function Operation: deleting the excisting
 * VerboseController instance if exists
 **************************************/
void VerboseController::deleteInstance() {
	if (theInstance != NULL) {
		pthread_mutex_lock(&lock);
		if (theInstance != NULL) {
			delete theInstance;
			theInstance = NULL;
		}
		pthread_mutex_unlock(&lock);
	}
}

/***************************************
 * Function Name: getVerbose
 * The Input: no input
 * The Output: boolean value (true/false)
 * The Function Operation: returning the value
 * of the verbose member, true or false
 **************************************/
bool VerboseController::getVerbose() const {
	return verbose;
}

/***************************************
 * Function Name: lockCout
 * The Input: no input
 * The Output: no output
 * The Function Operation: locking the
 * VerboseController thread
 **************************************/
void VerboseController::lockCout() {
	pthread_mutex_lock(&coutMutex);
}

/***************************************
 * Function Name: unlockCout
 * The Input: no input
 * The Output: no output
 * The Function Operation: unlocking the
 * VerboseController thread
 **************************************/
void VerboseController::unlockCout() {
	pthread_mutex_unlock(&coutMutex);
}

/***************************************
 * Function Name: VerboseController
 * The Input: verbose - a boolean value, true\false
 * The Output: a VerboseController instance
 * The Function Operation: constructor of VerboseController
 * instances using a given boolean value, also initializing
 * the VerboseConstructor thread
 **************************************/
VerboseController::VerboseController(bool verbose):verbose(verbose) {
	pthread_mutex_init(&coutMutex, NULL);
}

/***************************************
 * Function Name: ~VerboseController
 * The Input: no input
 * The Output: no output
 * The Function Operation: destructor of
 * VerboseController instances
 **************************************/
VerboseController::~VerboseController() {
	pthread_mutex_destroy(&coutMutex);
}
