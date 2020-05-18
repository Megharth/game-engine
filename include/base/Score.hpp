
#ifndef SRC_SCORE_HPP
#define SRC_SCORE_HPP
//! The storing and manipulation of score is done in this class
class Score {
private:
	int score{0};
public:
	Score();
	virtual ~Score();
	   /**
	     * intialize score variable to 0. This will be called at the start of the game
	     */
	    void init();

	    /**
	     * increments score
	     */
	    void incrementScore(int);

	    /**
	     * gets current score
	     */
	    int getScore();

};

#endif
