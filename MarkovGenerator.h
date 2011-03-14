#ifndef MARKOVGENERATOR_H
#define MARKOVGENERATOR_H

#include <QVector>
class State;

/*! \brief This is the header file for the MarkovGenerator interface.
 *
 * This class defines a basic subset of functions that a class that
 * generates data based off of Markov Chains needs.
 */
class MarkovGenerator
{
public:
    //! A virtual destructor for the MarkovGenerator class.
    virtual ~MarkovGenerator() {}
    //! A pure virtual method that gets the output of a Markov Chain walk.
    /*! \param An integer argument specifying how many previous states to consider.
      * \returns An ordered vector of the generated states. These can be traversed with a loop and printed to stdout by using State's toString() function.
      * \sa State::toString()
      */
    virtual QVector<State*> getOutput(int connectivity) = 0;
    //! A pure virtual function to append a state to the end of the data.
    /*! \param A pointer to the State object in question. Note that MarkovGenerator takes ownership of the pointer.
      */
    virtual void addState(State *state) = 0;
};

#endif // MARKOVGENERATOR_H
