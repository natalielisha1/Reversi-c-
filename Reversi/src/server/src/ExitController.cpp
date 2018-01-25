/*
 * ExitController.cpp
 *
 *  Created on: Jan 24, 2018
 *      Author: ofek286
 */

#include "ExitController.h"

ExitController *ExitController::theInstance = NULL;
pthread_mutex_t ExitController::lock = PTHREAD_MUTEX_INITIALIZER;

/***************************************
 * Function Name: initialize
 * The Input: no input
 * The Output: no output
 * The Function Operation: initializing
 * ExitController's thread
 **************************************/
void ExitController::initialize() {
	pthread_mutex_init(&lock, NULL);
}

/***************************************
 * Function Name: getInstance
 * The Input: no input
 * The Output: a pointer to an ExitController instance
 * The Function Operation: returning a
 * pointer to an ExitController instance
 **************************************/
ExitController* ExitController::getInstance() {
	if (theInstance == NULL) {
		pthread_mutex_lock(&lock);
		if (theInstance == NULL) {
			theInstance = new ExitController();
		}
		pthread_mutex_unlock(&lock);
	}
	return theInstance;
}

/***************************************
 * Function Name: deleteInstance
 * The Input: no input
 * The Output: no output
 * The Function Operation: deleting the
 * excisting ExitController instance
 **************************************/
void ExitController::deleteInstance() {
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
 * Function Name: getExit
 * The Input: no input
 * The Output: true or false
 * The Function Operation: returning the
 * boolean value of the exit member,
 * true if should exit, otherwise false.
 **************************************/
bool ExitController::getExit() const {
	return exit;
}

/***************************************
 * Function Name: setExit
 * The Input: no input
 * The Output: no output
 * The Function Operation: setting the value
 * of the exit boolean member to true
 **************************************/
void ExitController::setExit() {
	exit = true;
}

/***************************************
 * Function Name: ExitController
 * The Input: no input
 * The Output: an ExitController instance
 * The Function Operation: constructor for
 * ExitController instances, initialize exit
 * boolean member to false.
 **************************************/
ExitController::ExitController(): exit(false) {
	//Nothing right now
}
