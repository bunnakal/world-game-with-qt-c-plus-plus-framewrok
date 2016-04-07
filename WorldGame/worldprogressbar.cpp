#include "worldprogressbar.h"

WorldProgressBar::WorldProgressBar(WorldModel *worldmodel, QProgressBar *parent) :
    QProgressBar(parent)
{
    energy=worldmodel->getEnergy();
    health=worldmodel->getHealth();
}

void WorldProgressBar::decreaseEnergyBy(int decrease)
{
    energy-=decrease;
}

void WorldProgressBar::decreaseHealthBy(int decrease)
{
    health-=decrease;
}

void WorldProgressBar::increaseHealthBy(int increase)
{
    health+=increase;
}

float WorldProgressBar::getEnergy() const
{
    return energy;
}

float WorldProgressBar::getHealth() const
{
    return health;
}

void WorldProgressBar::setEnergy(int value)
{
    energy=value;
}
void WorldProgressBar::setHealth(int value){
    health=value;
}
