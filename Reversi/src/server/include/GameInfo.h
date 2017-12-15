/*
 * GameInfo.h
 *
 *  Created on: Dec 13, 2017
 *      Author: ofek286
 */

#ifndef GAMEINFO_H_
#define GAMEINFO_H_

#include <string>
#include <pthread.h>

class GameInfo {
public:
	enum MatchStatus {ReadyForMatch, XWaiting, Playing, Ending};

	GameInfo();
	~GameInfo();

	int getClientA() const;
	void setClientA(int clientA);

	int getClientB() const;
	void setClientB(int clientB);

	const std::string& getGameName() const;
	void setGameName(const std::string& gameName);

	GameInfo::MatchStatus getStatus();
	void setStatus(GameInfo::MatchStatus status);

	bool clientInMatch(int client) const;

	int getOtherClient(int firstClient) const;

	pthread_mutex_t getStatusMutex() const;

	void setInterrupt(bool interrupt);

private:
	std::string gameName;

	int clientA;
	int clientB;

	GameInfo::MatchStatus status;

	bool interrupt;

	pthread_mutex_t statusMutex;
	pthread_mutex_t interruptMutex;
};

#endif /* GAMEINFO_H_ */
