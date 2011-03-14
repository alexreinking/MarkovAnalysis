#ifndef STATE_H
#define STATE_H

#include <QString>

/*! \brief This is the header file for the State interface.
 *
 * This class defines a basic subset of functions that a class that
 * stores the (meta)data in a state of a Markov Chain needs to do its job.
 */
class State
{
public:
    //! This enum represents the type of the instantiated State subclass.
    /*! Those using the library should start their own enumerated types at UserType.
      * The Invalid state means that the function was (somehow) called on State.
      * This enum is used mostly to ease casting between the subclass types.
      */
    enum StateType {
        Invalid, /*!< Enum value for an invalid state. */
        TrueFalse, /*!< Enum value for a True or False answer in a multiple choice test. */
        Word, /*!< Enum value for a word from a corpus. */
        Note, /*!< Enum value for a musical note. */
        UserType /*!< Enum value for use by third parties. */
    };
    //! A virtual destructor for the State class.
    virtual ~State() {}
    //! A pure virtual member that populates the data structure from a string.
    /*! \param The format of this string is specific to the subclass. However, the format that this function takes is the same as the format that toString() produces.
      * \sa toString()
      */
    virtual void fromString(const QString &string) = 0;
    //! A pure virtual member that converts the internal representation of the data structure into a serializable string.
    /*! \returns A string representing the data structure.
      * \sa fromString(const QString &)
      */
    virtual QString toString() const = 0;
    //! A virtual member that reports the type of the member. This is done to ease casting.
    /*! \returns The enumerated type of the State. If the function is called on State itself, the result will be State::Invalid.
      */
    virtual StateType type() { return Invalid; }
};


#endif // STATE_H
