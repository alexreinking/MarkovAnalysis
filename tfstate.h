#ifndef TFSTATE_H
#define TFSTATE_H

#include "State.h"

class TFState : public State
{
public:
    enum AnswerType {
        StartSymbol,
        EndSymbol,
        True,
        False,
        None
    };
    TFState(AnswerType t);
    bool operator==(const TFState &rhs);
    TFState& operator=(const TFState &rhs);
    AnswerType get() const;
    void set(AnswerType t);
    StateType type() { return State::TrueFalse; }

    void fromString(const QString &string);
    QString toString() const;

private:
    AnswerType me;
};

#endif // TFSTATE_H
