#ifndef TFREADER_H
#define TFREADER_H

#include "StateReader.h"

class TFReader : public StateReader
{
public:
    TFReader();
    ~TFReader();
    bool open(QIODevice *input);
    void writeTo(MarkovGenerator *target);

private:
    QIODevice* input;
};

#endif // TFREADER_H
