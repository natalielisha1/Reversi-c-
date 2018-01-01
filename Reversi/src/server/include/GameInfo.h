/***************************************
 * Student Name: Ofek Segal and Natalie Elisha
 * Student ID: 315638288, 209475458
 * Exercise Name: Ex5
 **************************************/

#ifndef GAMEINFO_H_
#define GAMEINFO_H_

#include <string>
#include <pthread.h>

class GameInfo {
public:
	enum MatchStatus {ReadyForMatch, XWaiting, Playing, Ending};

	GameInfo();
	~GameInfo();

	int getClientA();
	void setClientA(int newClient);

	int getClientB();
	void setClientB(int newClient);

	const std::string& getGameName();
	void setGameName(const std::string& name);

	GameInfo::MatchStatus getStatus();
	void setStatus(GameInfo::MatchStatus newStatus);

	bool clientInMatch(int client);

	int getOtherClient(int firstClient);

	bool getInterrupt();
	void setInterrupt(bool interrupt);

private:
	std::string gameName;

	int clientA;
	int clientB;

	GameInfo::MatchStatus status;

	bool interrupt;

	pthread_mutex_t statusMutex;
	pthread_mutex_t interruptMutex;
	pthread_mutex_t nameMutex;
	pthread_mutex_t clientAMutex;
	pthread_mutex_t clientBMutex;
};

#endif /* GAMEINFO_H_ */
