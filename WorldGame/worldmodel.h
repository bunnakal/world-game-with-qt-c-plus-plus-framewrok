#ifndef GAMEMODEL_H
#define GAMEMODEL_H
#include <memory>
#include <vector>
#include <iomanip>
#include <math.h>
#include <ctime>
#include <string>
#include <queue>
#include <iostream>
#include "world.h"

const int ROW = 15; // horizontal size of the squares (15x15Pixel image)
const int COL = 15; // vertical size size of the squares (15x15Pixel image)
const int NDIR = 8; // number of possible directions to go at any position

// if NDIR = 4
//const int iDir[NDIR] = {1, 0, -1, 0};
//const int jDir[NDIR] = {0, 1, 0, -1};
// if NDIR = 8
const int iDir[NDIR] = {1, 1, 0, -1, -1, -1, 0, 1};
const int jDir[NDIR] = {0, 1, 1, 1, 0, -1, -1, -1};

struct Point
{
    int row, col;

    Point()
    {
        row = col = 0;
    }

    Point(int r, int c)
    {
        row = r;
        col = c;
    }
};

class WorldNode: public Tile
{

public:
    WorldNode(const Point &loc, int g, int f):Tile(loc.row,loc.col,qrand()%100){
        GValue = g;
        FValue = f;
    }

    Point getLocation() const {return Point(xPos,yPos);}
    int getGValue() const {return GValue;}
    int getFValue() const {return FValue;}

    void calculateFValue(const Point& locDest)
    {
        FValue = GValue + getHValue(locDest) * 10;
    }

    void updateGValue(const int & i) // i: direction
    {
        GValue += (NDIR == 8 ? (i % 2 == 0 ? 10 : 14) : 10);
    }

    // Estimation function for the remaining distance to the goal.
    const int & getHValue(const Point& locDest) const
    {
        static int rd, cd, d;
        rd = locDest.row - xPos;
        cd = locDest.col - yPos;

        // Manhattan distance
        d = abs(rd) + abs(cd);

        return(d);
    }

    // Determine FValue (in the priority queue)
    friend bool operator<(const WorldNode & a, const WorldNode & b)
    {
        return a.getFValue() > b.getFValue();
    }

private:
    // total distance already travelled to reach the node
    int GValue;
    // FValue = GValue + remaining distance estimate
    int FValue;  // smaller FValue gets priority
};

class WorldModel
{

public:

    WorldModel(QString imagepath);
    ~WorldModel();
    std::vector<std::shared_ptr<Tile>> createVisualWorld();
    std::vector<std::shared_ptr<Enemy>> createEnemy();
    std::shared_ptr<Protagonist> createProtogonist();
     std::vector<std::shared_ptr<Tile>> createHealthPack();

    std::vector<std::shared_ptr<Tile>> getTile()const;
    std::shared_ptr<Protagonist> getProtagonist()const;
    std::vector<std::shared_ptr<Enemy>> getEnemy() const;
    std::vector<std::shared_ptr<Tile>> getHealthPack()const;



    std::string pathFind( const Point &locStart ,
                          const Point &locFinish );
    std::vector<std::shared_ptr<Tile>> getPath()const;
    void startStrategy();
    std::vector<std::shared_ptr<Enemy>> getAllDefeatableEnemy();
    std::vector<std::shared_ptr<Tile>> getAllAvailableHealthPack();
    std::vector<double> calculateAllDistanceToAvailableHealthPack();
    std::vector<double> calculateAllDistanceToEnemy()const;
    std::vector<std::shared_ptr<Enemy>> getDefeatableEnemy()const;
    std::vector<std::shared_ptr<Tile>> getAvailableHealthPack()const;
    void resetDefeatableEnemy();
    void resetAvailablelHealthPack();
    int getShortestPos(std::vector<double>vec)const;
    void markAllProtagonistPassable(bool movable);
    void makePassableAt(int x, int y,bool passable);
    void markPassableProtagonistAt(int x, int y);
    void makeExistEnemyPassable();
    void deleteEnemyAt(int x,int y);
    void deleteHealthPackAt(int x,int y);
    void resetWorldPath();

    void setnrOfEnemy( int nrOfEnemies);
    void setnrOfHealthPack( int nrOfHealthPacks);
    void setXPosProtagonist(int xPos);
    void setYPosProtagonist(int yPos);
    void setEnergy(float energy);
    void setHealth(float health);
    void setGameOver(bool isOver);
    void setEnemyAsTarget(bool target);

    int getnOfTile()const;
    int getnOfEnemy()const;
    int getnOfHealthPack()const;
    int getXPosProtagonist()const;
    int getYPosProtagonist()const;
    float getHealth()const;
    float getEnergy()const;
    bool gameOver()const;
    int getXStart()const;
    int getYStart()const;
    int getXEnd()const;
    int getYEnd()const;
    int getIndex()const;
    bool isEnemyTarget()const;


private:

    //data members use for create world model
    World game;
    QString image;
    std::vector<std::shared_ptr<Tile>>tiles;
    std::shared_ptr<Protagonist> protogonist;
    std::vector<std::shared_ptr<Enemy>>enemies;
    std::vector<std::shared_ptr<Tile>>healthPacks;
    std::vector<std::shared_ptr<Tile>>worldPath;
    std::vector<std::shared_ptr<Enemy>>defeatableEnemies;
    std::vector<std::shared_ptr<Tile>> availableHealthPack;

    int nOfEnemies;
    int nOfHealthPacks;
    int xPos;
    int yPos;
    bool isGameOver=false;
    int xStart,yStart,xEnd,yEnd,index=0;
    bool isDefeatEnemy=false;
    int pathSize;

    //data members use for A* algorithms
    int squares[ROW][COL];
    // list of closed (check-out) nodes
    int closedNodes[ROW][COL];
    // list of open (not-yet-checked-out) nodes
    int openNodes[ROW][COL];
    // map of directions (0: East, 1: North, 2: West, 3: South)
    int dirMap[ROW][COL];
};

#endif // GAMEMODEL_H
