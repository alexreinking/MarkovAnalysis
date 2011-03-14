#include "tfstate.h"

TFState::TFState(AnswerType t)
{
    this->me = t;
}

bool TFState::operator==(const TFState &rhs)
{
    return (this->me == rhs.get());
}

TFState& TFState::operator=(const TFState &rhs)
{
    if(this == &rhs)
        return *this;
    this->me = rhs.get();
    return *this;
}

TFState::AnswerType TFState::get() const
{
    return this->me;
}

void TFState::set(AnswerType t)
{
    this->me = t;
}

void TFState::fromString(const QString &string)
{
    if(string.toLower() == "t")
        this->me = True;
    else if(string.toLower() == "<start>")
        this->me = StartSymbol;
    else if(string.toLower() == "<end>\n")
        this->me = EndSymbol;
    else
        this->me = False;
}

QString TFState::toString() const
{
    switch(this->me)
    {
    case True:
        return "T";
        break;
    case False:
        return "F";
        break;
    case StartSymbol:
        return "<start>";
        break;
    case EndSymbol:
        return "<end>\n";
        break;
    default:
        break;
    }
    return "<invalid>\n";
}
