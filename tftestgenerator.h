#ifndef TFTESTGENERATOR_H
#define TFTESTGENERATOR_H

#include <QVector>
#include "MarkovGenerator.h"
#include "tfstate.h"

#define RAND_DOUBLE ((double)rand()/double(RAND_MAX+1ul))

class TFTestGenerator : public MarkovGenerator
{
public:
    TFTestGenerator();
    ~TFTestGenerator();
    QVector<State*> getOutput(int connectivity);
    QVector<State*> getOutputOfLength(int length, int connectivity = 2);
    void addState(State *state);
    QVector<TFState*> getData() const { return data; }

    void setIgnoreMetaSymbols(bool t) { ignoreMetaSymbols = t; }
    bool getIgnoreMetaSymbols() const { return ignoreMetaSymbols; }

private:
    bool ignoreMetaSymbols;
    QVector<TFState*> data;
    TFState* getNextState(QVector<TFState*> previous);
    int indexInData(QVector<TFState*> term, int start = 0);
    QString statesToString(QVector<TFState *> terms);

    inline void addNextState(QVector<TFState *> &terms, QVector<TFState *> &previous);
};

#endif // TFTESTGENERATOR_H
