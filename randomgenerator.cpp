#include <QtCore>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <sys/stat.h>
#include <fcntl.h>
#include "randomgenerator.h"

RandomGenerator* RandomGenerator::m_instance = NULL;

RandomGenerator::RandomGenerator()
{
    reseed();
}

RandomGenerator* RandomGenerator::instance()
{
    if(m_instance == NULL)
        m_instance = new RandomGenerator;
    return m_instance;
}

RandomGenerator::~RandomGenerator()
{
    delete m_instance;
    m_instance = NULL;
}

int RandomGenerator::getRandomInt(int lower, int upper)
{
    int range = abs(upper-lower);
    double offset = getNormalizedDouble()*(double)range;
    return lower+(int)offset;
}

double RandomGenerator::getNormalizedDouble()
{
    return ((double)rand()/double(RAND_MAX+1ul));
}

void RandomGenerator::reseed()
{
    unsigned int seed = time(NULL);
#ifdef Q_OS_LINUX
//    int randomData = open("/dev/random", O_RDONLY);
//    read(randomData, &seed, sizeof(seed));
//    close(randomData);
    srand(seed);
#else
    srand(seed);
#endif
}
