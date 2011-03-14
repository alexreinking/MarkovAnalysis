#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

class RandomGenerator
{
public:
    static RandomGenerator* instance();
    ~RandomGenerator();
    int getRandomInt(int lower = 0, int upper = RAND_MAX);
    double getNormalizedDouble();
    void reseed();

private:
    RandomGenerator();
    static RandomGenerator* m_instance;
};

#endif // RANDOMGENERATOR_H
