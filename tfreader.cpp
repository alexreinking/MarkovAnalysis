#include <QtCore>
#include "tftestgenerator.h"
#include "tfreader.h"
#include "tfstate.h"

TFReader::TFReader()
{
    input = 0;
}

TFReader::~TFReader()
{
    if(input)
        if(input->isOpen())
            input->close();
}

bool TFReader::open(QIODevice *input)
{
    if(input->open(QIODevice::ReadOnly)) {
        this->input = input;
        return true;
    }
    this->input = 0;
    return false;
}

void TFReader::writeTo(MarkovGenerator *target)
{
    if(!input)
        return;
    TFTestGenerator *tf = 0;
    if(!(tf = static_cast<TFTestGenerator*>(target))) //TODO: Start using enums here.
        return;

    QTextStream stream(input);
    QString line;
    do {
        line = stream.readLine();
        line = line.simplified();
        target->addState(new TFState(TFState::StartSymbol));
        for(int i = 0; i < line.length(); i++)
        {
            if(line[i].toLower() == 't') {
                target->addState(new TFState(TFState::True));
            } else if(line[i].toLower() == 'f') {
                target->addState(new TFState(TFState::False));
            } else {
                qDebug("Character \'%c\' invalid for a T/F test.",line[i].toAscii());
            }
        }
        target->addState(new TFState(TFState::EndSymbol));
    } while (!line.isNull());
}
