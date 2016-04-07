#ifndef WORLDPROGRESSBAR_H
#define WORLDPROGRESSBAR_H
#include "worldmodel.h"
#include <QProgressBar>

class WorldProgressBar : public QProgressBar
{
    Q_OBJECT
public:
    explicit WorldProgressBar(WorldModel * worldmodel,QProgressBar *parent = 0);

    void decreaseEnergyBy(int decrease);
    void decreaseHealthBy(int decrease);
    void increaseHealthBy(int increase);
    float getEnergy()const;
    float getHealth()const;

    void setEnergy(int value);
    void setHealth(int value);

private:
    float energy;
    float health;

};

#endif // WORLDPROGRESSBAR_H
