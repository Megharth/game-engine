#ifndef LIVES_HPP
#define LIVES_HPP
//! \brief This class is responsible for storing the number of lives and manipulating them
class Lives {
private:
    int lives{3};

public:
    Lives();
    virtual ~Lives();

    inline int getLives() { return lives; };

    inline void decrementLife() { lives--; };

    inline void setLife(int l) { lives = l; }

};

#endif
