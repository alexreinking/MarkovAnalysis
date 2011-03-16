#ifndef TFREADER_H
#define TFREADER_H

#include <QStringList>
#include "StateReader.h"

class TFReader : public StateReader
{
public:
    TFReader();
    ~TFReader();
    bool open(QIODevice *input);
    void writeTo(MarkovGenerator *target);
    QStringList getKeys() const { return keys; }

private:
    QIODevice* input;
    QStringList keys;
};

#endif // TFREADER_H
