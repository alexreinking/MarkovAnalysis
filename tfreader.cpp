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

    keys.clear();

    QTextStream stream(input);
    QString line;
    QString keyLine = "";
    TFState* tmp = 0;
    do {
        line = stream.readLine();
        line = line.simplified();
        if(line.length()) {
            target->addState(tmp = new TFState(TFState::StartSymbol));
            keyLine += tmp->toString();
            for(int i = 0; i < line.length(); i++)
            {
                if(line[i].toLower() == 't') {
                    target->addState(tmp = new TFState(TFState::True));
                    keyLine += tmp->toString();
                } else if(line[i].toLower() == 'f') {
                    target->addState(tmp = new TFState(TFState::False));
                    keyLine += tmp->toString();
                } else {
                    qDebug("Character \'%c\' invalid for a T/F test.",line[i].toAscii());
                }
            }
            target->addState(tmp = new TFState(TFState::EndSymbol));
            keyLine += tmp->toString();
            keys << keyLine;
            keyLine = "";
        }
    } while (!line.isNull());
}
