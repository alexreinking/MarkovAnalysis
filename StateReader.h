#ifndef STATEREADER_H
#define STATEREADER_H

#include <QIODevice>
class MarkovGenerator;

/*! \brief This is the header file for the StateReader interface.
  * This class provides the basic set of functions needed by a class
  * that reads in an ordered list of states from a file (or stdin).
  */
class StateReader
{
public:
    //! A virtual destructor for the StateReader interface.
    virtual ~StateReader() {}
    //! A pure virtual method that is used to open the input source. This function should have no side effects.
    /*! \param A pointer to the input device to use. This can be binary data or stdin. The StateReader class does NOT take ownership of this pointer.
      * \returns True upon a successful open, false if there was an error.
      */
    virtual bool open(QIODevice* input) = 0;
    //! A pure virtual method that is used to write data to a MarkovGenerator. This function does nothing if open(QIODevice*) has not been called. This function is blocking.
    /*! \param A pointer to a MarkovGenerator object to which data will be appended.
      * \sa open(QIODevice* input)
      */
    virtual void writeTo(MarkovGenerator* target) = 0;
};

#endif // STATEREADER_H
