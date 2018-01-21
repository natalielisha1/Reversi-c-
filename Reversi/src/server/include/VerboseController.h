/*
 * VerboseController.h
 *
 *  Created on: Jan 20, 2018
 *      Author: ofek286
 */

#ifndef VERBOSECONTROLLER_H_
#define VERBOSECONTROLLER_H_

#include <pthread.h>

class VerboseController {
public:
	static void initialize();

	static VerboseController *getInstance(bool verbose);
	static VerboseController *getInstance();

	static void deleteInstance();

	bool getVerbose() const;

	void lockCout();
	void unlockCout();

private:
	static VerboseController *theInstance;
	static pthread_mutex_t lock;

	VerboseController(bool verbose);
	~VerboseController();
	bool verbose;

	pthread_mutex_t coutMutex;
};

#endif /* VERBOSECONTROLLER_H_ */
