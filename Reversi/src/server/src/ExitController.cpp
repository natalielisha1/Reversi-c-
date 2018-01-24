/*
 * ExitController.cpp
 *
 *  Created on: Jan 24, 2018
 *      Author: ofek286
 */

#include "ExitController.h"

ExitController *ExitController::theInstance = NULL;
pthread_mutex_t ExitController::lock = PTHREAD_MUTEX_INITIALIZER;

void ExitController::initialize() {
	pthread_mutex_init(&lock, NULL);
}

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

bool ExitController::getExit() const {
	return exit;
}

void ExitController::setExit() {
	exit = true;
}

ExitController::ExitController(): exit(false) {
	//Nothing right now
}
