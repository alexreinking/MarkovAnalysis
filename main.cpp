#include <QtCore>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "tfreader.h"
#include "tfstate.h"
#include "tftestgenerator.h"
using namespace std;

int main(int argc, char *argv[])
{
    srand(time(NULL));
    if(argc < 2) {
        cerr << "Usage: ./" << argv[0] << " <filename> [length of output = 25]" << endl;
        return 1;
    }
    int len = 25;
    if(argc == 3)
        len = atoi(argv[2]);
    TFTestGenerator *tfGen = new TFTestGenerator;
    TFReader *tfReader = new TFReader;
//    tfGen->setIgnoreMetaSymbols(true);
    QFile file(argv[1]);
    if(!tfReader->open(&file))
    {
        cerr << "Unable to open file: " << argv[1] << ". :(" << endl;
        return 2;
    }
    tfReader->writeTo(tfGen);
    QVector<State*> states = tfGen->getOutputOfLength(len);
    cout << "Test of length " << states.size()-2 << " generated." << endl;
    foreach(State* state, states)
    {
        cout << qPrintable(static_cast<TFState*>(state)->toString());
    }
    cout << endl;
    return 0;
}
