#include <QtCore>
#include <iostream>
#include "tfreader.h"
#include "tfstate.h"
#include "tftestgenerator.h"
using namespace std;

QString statesToString(QVector<State *> terms);
int hammingDistance(QString a, QString b);
QString percentToGrade(double p);

int main(int argc, char *argv[])
{
    if(argc < 2) {
        cerr << "Usage: ./" << argv[0] << " <filename>" << endl;
        return 1;
    }
    TFTestGenerator *tfGen = new TFTestGenerator;
    TFReader *tfReader = new TFReader;
//    tfGen->setIgnoreMetaSymbols(true);
    QFile file(argv[1]);
    if(!tfReader->open(&file)) {
        cerr << "Unable to open file: " << argv[1] << ". :(" << endl;
        return 2;
    }
    tfReader->writeTo(tfGen);

    QVector<State*> states;
    QString generatedString;
    QVector<double> grades;
    foreach(QString line, tfReader->getKeys()) {
        int totalHam = 0;
        int i;
        line = line.simplified();
        cout << "Generated test:" << endl;
        cout << "Hamming distances:" << endl;
        for(i = 0; i<100; i++) {
            while(generatedString.length() != line.length()) {
                generatedString = statesToString(tfGen->getOutputOfLength(line.length()-12,2)); //12 is the length of "<start><end>" to account for the meta symbols.
                generatedString = generatedString.simplified();
            }
            int h;
            totalHam += (h = hammingDistance(generatedString,line));
            generatedString = "";
            cout << h << " ";
        }
        cout << endl;
        cout << "Original test: " << qPrintable(line) << endl;
        double avgDist = double((double)totalHam/(double)i);
        double grade = (line.length()-avgDist)/line.length();
        cout << "Average hamming distance: " << avgDist << endl;
        cout << "Projected grade: " << qPrintable(percentToGrade(grade)) << "(" << grade*100 << ")" << endl;
        grades << grade;
    }
    double sum = 0;
    foreach(double g, grades)
        sum += g;
    sum /= grades.size();
    cout << "Average projected grade: " << qPrintable(percentToGrade(sum)) << "(" << sum*100 << ")" << endl;
    return 0;
}

QString statesToString(QVector<State *> terms)
{
    QString termAsString = "";
    foreach(State* s, terms) {
        termAsString += s->toString();
    }
    return termAsString;
}

int hammingDistance(QString a, QString b)
{
    int dh = 0;
    if(a.length() != b.length()) {
        return -1;
    }
    for(int i = 0; i < a.length(); i++) {
        if(a.at(i) != b.at(i))
            dh++;
    }
    return dh;
}

QString percentToGrade(double p)
{
    if(p < 0.0) {
        return "F-";
    } else if(p < 0.6) {
        return "F";
    } else if(p < 0.62) {
        return "D-";
    } else if(p < 0.68) {
        return "D";
    } else if(p < 0.70) {
        return "D+";
    } else if(p < 0.72) {
        return "C-";
    } else if(p < 0.78) {
        return "C";
    } else if(p < 0.80) {
        return "C+";
    } else if(p < 0.82) {
        return "B-";
    } else if(p < 0.88) {
        return "B";
    } else if(p < 0.90) {
        return "B+";
    } else if(p < 0.92) {
        return "A-";
    } else if(p < 1.00) {
        return "A";
    } else {
        return "A+";
    }
}
