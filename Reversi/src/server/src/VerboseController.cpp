/*
 * VerboseController.cpp
 *
 *  Created on: Jan 20, 2018
 *      Author: ofek286
 */

#include "VerboseController.h"

VerboseController *VerboseController::theInstance = NULL;
pthread_mutex_t VerboseController::lock = PTHREAD_MUTEX_INITIALIZER;

void VerboseController::initialize() {
	pthread_mutex_init(&lock, NULL);
}

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

bool VerboseController::getVerbose() const {
	return verbose;
}

void VerboseController::lockCout() {
	pthread_mutex_lock(&coutMutex);
}

void VerboseController::unlockCout() {
	pthread_mutex_unlock(&coutMutex);
}

VerboseController::VerboseController(bool verbose):verbose(verbose) {
	pthread_mutex_init(&coutMutex, NULL);
}

VerboseController::~VerboseController() {
	pthread_mutex_destroy(&coutMutex);
}
