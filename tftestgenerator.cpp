#include <iostream>
#include "tftestgenerator.h"
using namespace std;

TFTestGenerator::TFTestGenerator()
{
    ignoreMetaSymbols = false;
}

TFTestGenerator::~TFTestGenerator()
{
    while(data.size())
    {
        delete data.first();
        data.remove(0);
    }
}

QVector<State*> TFTestGenerator::getOutput(int connectivity)
{
    return getOutputOfLength(25,connectivity);
}

QVector<State*> TFTestGenerator::getOutputOfLength(int length, int connectivity)
{
    if(!ignoreMetaSymbols)
        length += 2; //for start/end symbols.
    if(connectivity < 1)
        return QVector<State*>();

    //Initialize.
    QVector<TFState*> ret;
    if(ignoreMetaSymbols) {
        TFState* init = ((RAND_DOUBLE < 0.5) ? new TFState(TFState::True) : new TFState(TFState::False));
        ret << init;
    } else
        ret << new TFState(TFState::StartSymbol);
    for(int i = 1; i < connectivity; i++) {
        ret << getNextState(ret);
    }

    //Start generating.
    do
    {
        QVector<TFState*> previous = ret.mid(ret.size()-connectivity);
        addNextState(ret,previous);

        if(ret.size() == length && ignoreMetaSymbols) //In this case, we're done.
            break;
        else if(ret.last()->get() == TFState::EndSymbol) { //This is the end case when we're not ignoring meta symbols
            if(ret.size() >= length)
                break;
            else
                ret.remove(ret.size()-1); //Make sure we end above the /length/ variable. Length specifies a minium when we consider those symbols.
        }

        if(ret.last()->get() == TFState::None) { //Crap. Try again.
            cout << "Crap." << endl;
            while(ret.size()) {
                delete ret.first();
                ret.remove(0,1);
            }
            TFState* init = 0;
            if(ignoreMetaSymbols)
                init = ((RAND_DOUBLE < 0.5) ? new TFState(TFState::True) : new TFState(TFState::False));
            else
                init = new TFState(TFState::StartSymbol);
            ret << init;

            for(int i = 1; i < connectivity; i++) {
                addNextState(ret,previous);
            }
        }
    } while(true);
    QVector<State*> real_ret;
    foreach(TFState* t, ret)
        real_ret << t;
    return real_ret;
}

void TFTestGenerator::addNextState(QVector<TFState *> &terms, QVector<TFState *> &previous)
{
    TFState* nextState = 0;
    do {
        nextState = getNextState(previous);
        if(ignoreMetaSymbols) {
            if(nextState->get() == TFState::StartSymbol || nextState->get() == TFState::EndSymbol)
                continue;
        }
    } while(nextState->get() == TFState::None);
    terms << nextState;
}

void TFTestGenerator::addState(State *state)
{
    if(state->type() == State::TrueFalse)
    {
        data.append(static_cast<TFState*>(state));
    }
}

TFState* TFTestGenerator::getNextState(QVector<TFState *> previous)
{
//    int prob_a, prob_b, prob_s, prob_e;
    int counts[] = {0,0,0,0};
//    prob_a = prob_b = prob_s = prob_e = 0;
    int lastIndex = 0;
    while((lastIndex = indexInData(previous,lastIndex)) != -1)
    {
        if(lastIndex+previous.size() < data.size()) {
            TFState* next = data.at(lastIndex+previous.size());
            counts[next->get()]++;
//            switch(next->get())
//            {
//            case TFState::StartSymbol:
//                prob_s++;
//                break;
//            case TFState::EndSymbol:
//                prob_e++;
//                break;
//            case TFState::True:
//                prob_a++;
//                break;
//            case TFState::False:
//                prob_b++;
//                break;
//            default:
//                break;
//            }
        } else {
            break;
        }
        lastIndex++;
    }
    //This is a terrible unrolled loop. :
//    double pa,pb,pe,ps;
//    pa = (double)prob_a/double(prob_a+prob_b+prob_e+prob_s);
//    pb = (double)prob_b/double(prob_a+prob_b+prob_e+prob_s);
//    pe = (double)prob_e/double(prob_a+prob_b+prob_e+prob_s);
//    ps = (double)prob_s/double(prob_a+prob_b+prob_e+prob_s);
//    double r = RAND_DOUBLE;
//    if(r < pa)
//        return new TFState(TFState::True);
//    else if(r < pb+pa)
//        return new TFState(TFState::False);
//    else if(r < pe+pb+pa)
//        return new TFState(TFState::EndSymbol);
//    else if(r < ps+pb+pa+pe)
//        return new TFState(TFState::StartSymbol);
    return new TFState(TFState::None);
}

int TFTestGenerator::indexInData(QVector<TFState *> term, int start)
{
    QVector<TFState *> workingSet = data.mid(start);
    if(term.size() > workingSet.size())
        return -1;
    for(int i = 0; i < workingSet.size(); i++) {
        if(workingSet.at(i)->toString() == term.first()->toString()) {
            QVector<TFState *> tmp = workingSet.mid(i,term.size());
            if(statesToString(tmp) == statesToString(term)) {
                return i+start;
            }
        }
    }
    return -1;
}

QString TFTestGenerator::statesToString(QVector<TFState *> terms)
{
    QString termAsString = "";
    foreach(TFState* s, terms) {
        termAsString += s->toString();
    }
    return termAsString;
}
