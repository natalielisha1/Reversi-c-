/*
 * Tools.cpp
 *
 *  Created on: 22 בדצמ 2017
 *      Author: ofek286
 */

#ifndef TOOLS_H_
#define TOOLS_H_

#include <vector>

template <class T>
bool removeFromVector(std::vector<T> *theVector, T object) {
	for (typename std::vector<T>::iterator it = theVector->begin(); it != theVector->end(); ++it) {
		if (*it == object) {
			theVector->erase(it);
			return true;
		}
	}
	return false;
}

#endif /* TOOLS_H_ */
