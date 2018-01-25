/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex7
 **************************************/

#ifndef EXITCONTROLLER_H_
#define EXITCONTROLLER_H_

#include <pthread.h>

class ExitController {
public:
	static void initialize();

	static ExitController *getInstance();

	static void deleteInstance();

	bool getExit() const;

	void setExit();
private:
	static ExitController *theInstance;
	static pthread_mutex_t lock;

	ExitController();

	bool exit;
};

#endif /* EXITCONTROLLER_H_ */
