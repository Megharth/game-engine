/*
 * Score.cpp
 *
 *  Created on: Mar 12, 2020
 *      Author: saite
 */

#include "base/Score.hpp"

Score::Score() {
	// TODO Auto-generated constructor stub

}

Score::~Score() {
	score = 0;
}

void Score::init() {
    score = 0;
}

void Score::incrementScore(int increment) {
    score += increment;
}

int Score::getScore() {
    return score;
}

