#include "worldmodel.h"

WorldModel::WorldModel(QString imagepath)
{
    image=imagepath;
    createProtogonist();

}

WorldModel::~WorldModel()
{
    std::cout<<"Destructor of WorldModel is called...!"<<std::endl;
}

/**
 * @brief WorldModel::createVisualWorld
 * @return vector of visual Tile object
 * give a visual world tiles within the given image
 *
 */
std::vector<std::shared_ptr<Tile> > WorldModel::createVisualWorld()
{
    tiles=game.createWorld(image);
    return tiles;
}

/**
 * @brief WorldModel::createEnemy
 * @return  vector of Enemy object wthin a given nOfEnemies
 * given the Enemy
 */
std::vector<std::shared_ptr<Enemy> > WorldModel::createEnemy()
{
    enemies=game.getEnemies(nOfEnemies);
    return enemies;
}

/**
 * @brief WorldModel::createProtogonist
 * @return Protagonist object and put it on the given xPos
 * and yPos
 *
 */
std::shared_ptr<Protagonist> WorldModel::createProtogonist()
{
    //add a Protagonist to scence
    protogonist=game.getProtagonist();
    protogonist->setXPos(xPos);
    protogonist->setYPos(yPos);
    return protogonist;
}

/**
 * @brief WorldModel::createHealthPack
 * @return vector of healthpacks that not the same location with Enemy
 *
 */
std::vector<std::shared_ptr<Tile> > WorldModel::createHealthPack()
{
    while(healthPacks.size() < nOfHealthPacks)
    {
        int xPos = qrand() % game.getCols();
        int yPos = qrand() % game.getRows();
        auto eptr = std::make_shared<Tile>(xPos, yPos, qrand()%100);
        if (xPos != 0 || yPos != 0)
        {
            if (std::find_if(enemies.begin(), enemies.end(), [eptr](std::shared_ptr<const Enemy> p)-> bool
            {return *p == *eptr;}) == enemies.end())
                if(healthPacks.size()==0){
                    healthPacks.push_back(eptr);
                }else{
                    for(int i=0;i<healthPacks.size();i++){
                        while(xPos==healthPacks.at(i)->getXPos()&&yPos==healthPacks.at(i)->getYPos()){
                            xPos = qrand() % game.getCols();
                            yPos = qrand() % game.getRows();
                        }
                    }
                    eptr = std::make_shared<Tile>(xPos, yPos, qrand()%100);
                    if(xPos != 0 || yPos != 0){
                        if (std::find_if(enemies.begin(), enemies.end(), [eptr](std::shared_ptr<const Enemy> p)-> bool
                        {return *p == *eptr;}) == enemies.end())
                            healthPacks.push_back(eptr);
                    }
                }
        }
    }
    return healthPacks;
}

/**
 * @brief WorldModel::getVisualWorld
 * @return vector of visual world Tile with was created by WorldModel
 *
 */
std::vector<std::shared_ptr<Tile> > WorldModel::getTile() const
{
    return tiles;
}

/**
 * @brief WorldModel::getProtagonist
 * @return Protagonist object which created by WorldModel
 *
 */
std::shared_ptr<Protagonist> WorldModel::getProtagonist() const
{
    return protogonist;
}

/**
 * @brief WorldModel::getEnemy
 * @return vector enemies of Enemy which was created by WorldModel
 *
 */
std::vector<std::shared_ptr<Enemy> > WorldModel::getEnemy() const
{
    return enemies;
}

/**
 * @brief WorldModel::getHealthPack
 * @return vector of healthPacks which was created by WorldModel
 *
 */
std::vector<std::shared_ptr<Tile> > WorldModel::getHealthPack() const
{
    return healthPacks;
}



/**
 * @brief WorldModel::getDefeatableEnemy
 * @return vector of all defeatableEnemies which use make a vector
 * distances from the current Protagonist position to all enemies
 */
std::vector<std::shared_ptr<Enemy> > WorldModel::getDefeatableEnemy() const
{
    return defeatableEnemies;
}

std::vector<std::shared_ptr<Tile> > WorldModel::getAvailableHealthPack() const
{
    return availableHealthPack;
}

void WorldModel::resetDefeatableEnemy()
{
    if(defeatableEnemies.size()>0){
        defeatableEnemies.erase(defeatableEnemies.begin(),defeatableEnemies.end());
    }
}

void WorldModel::resetAvailablelHealthPack()
{
    if(availableHealthPack.size()>0){
        availableHealthPack.erase(availableHealthPack.begin(),availableHealthPack.end());
    }
}

/**
 * @brief WorldModel::setnOfEnemies
 * @param nrOfEnemies the number of enemy giving to world game
 * giving the numebr of enemy to world game
 *
 */
void WorldModel::setnrOfEnemy(int nrOfEnemies)
{
    nOfEnemies=nrOfEnemies;
}

/**
 * @brief WorldModel::setnOfHealthPacks
 * @param nrOfHealthPacks the number of healthPack giving to world game
 *
 */
void WorldModel::setnrOfHealthPack(int nrOfHealthPacks)
{
    nOfHealthPacks=nrOfHealthPacks;
}

/**
 * @brief WorldModel::setXPosProtagonist
 * @param xPos the position of x axis of Protagonist in the world game
 *
 */
void WorldModel::setXPosProtagonist(int xPos)
{
    protogonist->setXPos(xPos);
}

/**
 * @brief WorldModel::setYPosProtagonist
 * @param yPos the position of y axis of Protagonist in the world game
 *
 */
void WorldModel::setYPosProtagonist(int yPos)
{
    protogonist->setYPos(yPos);
}

/**
 * @brief WorldModel::setEnergy
 * @param energy the energy value set to energy progressbar of world game
 *
 */
void WorldModel::setEnergy(float energy)
{
    protogonist->setEnergy(energy);
}

/**
 * @brief WorldModel::setHealth
 * @param health the health value set to health progressbar of world game
 */
void WorldModel::setHealth(float health)
{
    protogonist->setHealth(health);
}

void WorldModel::setGameOver(bool isOver)
{
    isGameOver=isOver;
}

void WorldModel::setEnemyAsTarget(bool target)
{
    isDefeatEnemy=target;
}


/**
 * @brief WorldModel::getnOfTile
 * @return size of visual tile in the world game
 *
 */
int WorldModel::getnOfTile() const
{
    return tiles.size();
}

/**
 * @brief WorldModel::getnOfEnemy
 * @return size of enemy in the world game
 *
 */
int WorldModel::getnOfEnemy() const
{
    return enemies.size();
}

/**
 * @brief WorldModel::getnOfHealthPack
 * @return size of healthpack in the world game
 *
 */
int WorldModel::getnOfHealthPack() const
{
    return healthPacks.size();
}

/**
 * @brief WorldModel::getXPosProtagonist
 * @return x position of Protagonist at current world model object
 *
 */
int WorldModel::getXPosProtagonist() const
{
    return xPos;
}

/**
 * @brief WorldModel::getYPosProtagonist
 * @return y position of Protagonist at current world model object
 */
int WorldModel::getYPosProtagonist() const
{
    return yPos;
}

float WorldModel::getHealth() const
{
    return protogonist->getHealth();
}

float WorldModel::getEnergy() const
{
    return protogonist->getEnergy();
}

bool WorldModel::gameOver() const
{
    return isGameOver;
}

int WorldModel::getXStart() const
{
    return xStart;
}

int WorldModel::getYStart() const
{
    return yStart;
}

int WorldModel::getXEnd() const
{
    return xEnd;
}

int WorldModel::getYEnd() const
{
    return yEnd;
}

int WorldModel::getIndex() const
{
    return index;
}

bool WorldModel::isEnemyTarget() const
{
    return isDefeatEnemy;
}

void WorldModel::startStrategy()
{
    xStart=yStart=xEnd=yEnd=0;

    std::cout<<"Start Strategy is Started...!"<<std::endl;

    getAllDefeatableEnemy();

    std::cout<<"Defeatable: "<<defeatableEnemies.size()<<std::endl;

    if(defeatableEnemies.size()>0)
    {
        std::cout<<"Target is Enemy...!"<<std::endl;
        setEnemyAsTarget(true);
        makeExistEnemyPassable();
        std::vector<double>vecEnemy;
        vecEnemy=calculateAllDistanceToEnemy();
        std::cout<<"Vec Enemy:"<<vecEnemy.size()<<std::endl;

        index=getShortestPos(vecEnemy);
        std::cout<<"The Index Enemy: "<<index<<std::endl;

        // starting positions
        xStart= protogonist->getXPos();
        yStart= protogonist->getYPos();

        // ending position
        xEnd= defeatableEnemies.at(index)->getXPos();
        yEnd= defeatableEnemies.at(index)->getYPos();
    }
    else {

        std::cout<<"Target is HealthPack...!"<<std::endl;

        setEnemyAsTarget(false);

        getAllAvailableHealthPack();
        std::cout<<"Available HealthPacks: "<<availableHealthPack.size()<<std::endl;

        markAllProtagonistPassable(true);

        std::vector<double>vecHealth;
        vecHealth=calculateAllDistanceToAvailableHealthPack();

        std::cout<<"Vec Health :"<<vecHealth.size()<<std::endl;
        index=getShortestPos(vecHealth);
        std::cout<<"The Index Health: "<<index<<std::endl;

        // starting positions
        xStart= protogonist->getXPos();
        yStart= protogonist->getYPos();

        // ending position
        xEnd = availableHealthPack.at(index)->getXPos();
        yEnd = availableHealthPack.at(index)->getYPos();

    }

    std::cout<<"Strategy Start("<<xStart<<","<<yStart<<")"<<std::endl;
    std::cout<<"Strategy End("<<xEnd<<","<<yEnd<<")"<<std::endl;


    resetWorldPath();

    //start timer to measure pathFind A* algorithms
    // start and end time to measure pathFinding of A* algorithms
    clock_t  Start = clock();
    // get the path
    std::string path = pathFind(Point(getXStart(), getYStart()), Point(getXEnd(), getYEnd()));
    clock_t End = clock();

    std::cout<<"Path Size: " << worldPath.size()<<std::endl;
    std::cout<<"Path "<<path<<std::endl;

    //calculate time to find
    double time = double(End - Start);
    std::cout << "Time (ms): "<< time << std::endl;

    std::cout<<"Start Strategy is Ended...!"<<std::endl;
}

/**
 * @brief WorldModel::getPath
 * @return vector of Tile which indicate the point to go through
 * from start to end
 */
std::vector<std::shared_ptr<Tile> > WorldModel::getPath() const
{
    return worldPath;
}

/**
 * @brief WorldModel::getAllDefeatableEnemy
 * @return all enemy that can defeatable within it value and health of world game
 *
 */
std::vector<std::shared_ptr<Enemy> > WorldModel::getAllDefeatableEnemy()
{
    // reset all defeable to null
    resetDefeatableEnemy();
    if(enemies.size()>0){
        std::cout<<"Current Enemy :"<<enemies.size()<<std::endl;
        for(unsigned int i=0;i<enemies.size();i++){
            if(protogonist->getHealth()>enemies.at(i)->getValue()){
                defeatableEnemies.push_back(enemies.at(i));
            }
            else{
                squares[enemies.at(i)->getXPos()][enemies.at(i)->getYPos()]=1;
            }
        }
        markAllProtagonistPassable(false);
        return defeatableEnemies;
    }
}

std::vector<std::shared_ptr<Tile> > WorldModel::getAllAvailableHealthPack()
{
    // reset all healthpack to null
    resetAvailablelHealthPack();
    std::cout<<"Current HealthPack "<<healthPacks.size()<<std::endl;
    if(healthPacks.size()>0){
        for(unsigned int i=0;i<healthPacks.size();i++){
            availableHealthPack.push_back(healthPacks.at(i));
        }
    }
    return availableHealthPack;
}

/**
 * @brief WorldModel::calculateAllDistanceToAvailableHealthPack
 * @return vector of double of all the available healthpack to get the shortest target one
 * from the current protagonist to health packs
 *
 */
std::vector<double> WorldModel::calculateAllDistanceToAvailableHealthPack()
{
    std::vector<double>vec;
    if(availableHealthPack.size()>0){
        for(unsigned int i=0;i<availableHealthPack.size();i++){
            double dis=sqrt((availableHealthPack.at(i)->getXPos() - protogonist->getXPos())*(availableHealthPack.at(i)->getXPos() - protogonist->getXPos()) +
                            (availableHealthPack.at(i)->getYPos() - protogonist->getYPos())*(availableHealthPack.at(i)->getYPos() - protogonist->getYPos()));
            vec.push_back(dis);
        }
        return vec;
    }
}

/**
 * @brief WorldModel::calculateAllDistanceToEnemy
 * @return vector of double of all the available enemy to get the shortest target one
 * from the current protagonist to enemies
 */
std::vector<double> WorldModel::calculateAllDistanceToEnemy() const
{
    std::vector<double>vec;
    if(defeatableEnemies.size()>0){
        for(unsigned int i=0;i<defeatableEnemies.size();i++){
            double dis=sqrt((defeatableEnemies.at(i)->getXPos() - protogonist->getXPos())*(defeatableEnemies.at(i)->getXPos() - protogonist->getXPos()) +
                            (defeatableEnemies.at(i)->getYPos() - protogonist->getYPos())*(defeatableEnemies.at(i)->getYPos() - protogonist->getYPos()));
            vec.push_back(dis);
        }
    }
    return vec;
}

/**
 * @brief WorldModel::getShortestPos
 * @param vec the vector of all distance to all target (Healthpacks and Enemies)
 * @return the position of the shortest vector of distance one
 */
int WorldModel::getShortestPos(std::vector<double> vec) const
{
    int lo=0;
    for (unsigned int i = 1;i < vec.size();i++) {
        if(vec[i] < vec[lo]) {
            lo = i;
        }
    }
    return lo;
}

/**
 * @brief WorldModel::markAllProtagonistPassable
 * @param movable has posible value ture to make position is passale
 * and false to make position is unpassable
 *
 */
void WorldModel::markAllProtagonistPassable(bool movable)
{
    int wall=0;
    if(!movable){
        wall=1;
    }
    for(unsigned int i=0;i<healthPacks.size();i++){
        squares[healthPacks.at(i)->getXPos()][healthPacks.at(i)->getYPos()]=wall;
    }
}

/**
 * @brief WorldModel::markPassableEnemyAt
 * @param x axis x of worldgame that would be set to passable or unpassable
 * @param y axis y of worldgame that would be set to passable or unpassable
 */
void WorldModel::makePassableAt(int x, int y, bool passable)
{
    int wall=0;
    if(!passable){
        wall=1;
    }
    squares[x][y]=wall;
}

void WorldModel::makeExistEnemyPassable()
{
    for(unsigned int i=0;i<defeatableEnemies.size();i++){
        squares[defeatableEnemies.at(i)->getXPos()][defeatableEnemies.at(i)->getYPos()]=0;
    }
}

/**
 * @brief WorldModel::deleteEnemyAt
 * @param x axis x of enemy on the worldmodel
 * @param y axis y of enemy on the worldmodel
 */
void WorldModel::deleteEnemyAt(int x, int y)
{
    if(enemies.size()>0){
        for(unsigned int i=0;i<enemies.size();i++){
            if(enemies.at(i)->getXPos()==x && enemies.at(i)->getYPos()==y){
                enemies.erase(enemies.begin()+i);
                std::cout<<"\t\tdelete enemy model..Now Enemy is only:"<<enemies.size()<<std::endl;
                return ;
            }
        }
    }
}

/**
 * @brief WorldModel::deleteHealthPackAt
 * @param x axis x of healthpack on the worldmodel
 * @param y axis y of healthpack on the worldmodel
 */
void WorldModel::deleteHealthPackAt(int x, int y)
{
    if(healthPacks.size()>0){
        for(unsigned int i=0;i<healthPacks.size();i++){
            if(healthPacks.at(i)->getXPos()==x && healthPacks.at(i)->getYPos()==y){
                healthPacks.erase(healthPacks.begin()+i);
                return ;
            }
        }
    }

}

/**
 * @brief WorldModel::resetWorldPath
 * reset all elements of worldPath vector to provent from
 * it contains the old value one.
 */
void WorldModel::resetWorldPath()
{
    if(worldPath.size()>0){
        worldPath.erase(worldPath.begin(),worldPath.end());
    }

}

/**
 * @brief WorldModel::pathFind
 * @param locStart the start point
 * @param locFinish the end point(target point)
 * @return
 */
std::string WorldModel::pathFind(const Point &locStart, const Point &locFinish)
{
    // list of open (not-yet-checked-out) nodes
    static std::priority_queue<WorldNode> q[2];

    // q index
    static int qi;

    static WorldNode* pNode1;
    static WorldNode* pNode2;
    static int i, j, row, col, iNext, jNext;
    static char c;
    qi = 0;

    // reset the Node lists (0 = ".")
    for(j = 0; j < COL; j++) {
        for(i = 0; i < ROW; i++) {
            closedNodes[i][j] = 0;
            openNodes[i][j] = 0;
        }
    }

    // create the start node and push into list of open nodes
    pNode1 = new WorldNode(locStart, 0, 0);
    pNode1->calculateFValue(locFinish);
    q[qi].push(*pNode1);

    // A* search
    while(!q[qi].empty()) {
        // get the current node w/ the lowest FValue
        // from the list of open nodes
        pNode1 = new WorldNode( q[qi].top().getLocation(), q[qi].top().getGValue(), q[qi].top().getFValue());
        row = (pNode1->getLocation()).row;
        col = pNode1->getLocation().col;

        // remove the node from the open list
        q[qi].pop();
        openNodes[row][col] = 0;

        // mark it on the closed nodes list
        closedNodes[row][col] = 1;

        // stop searching when the goal state is reached
        if(row == locFinish.row && col == locFinish.col) {

            // generate the path from finish to start from dirMap
            std::string path = "";
            while(!(row == locStart.row && col == locStart.col)) {
                j = dirMap[row][col];
                c = '0' + (j + NDIR/2) % NDIR;
                path = c + path;
                auto p = std::make_shared<Tile>(row,col,qrand()%100);
                worldPath.push_back(p);

                row += iDir[j];
                col += jDir[j];
            }

            // garbage collection
            delete pNode1;

            // empty the leftover nodes
            while(!q[qi].empty()) q[qi].pop();
            return path;
        }

        // generate moves in all possible directions
        for(i = 0; i < NDIR; i++) {
            iNext = row + iDir[i];
            jNext = col + jDir[i];

            // if not wall (obstacle) nor in the closed list
            if(!(iNext < 0 || iNext > ROW - 1 || jNext < 0 || jNext > COL - 1 ||
                 squares[iNext][jNext] == 1 || closedNodes[iNext][jNext] == 1)) {

                // generate a child node
                pNode2 = new WorldNode( Point(iNext, jNext), pNode1->getGValue(), pNode1->getFValue());
                pNode2->updateGValue(i);
                pNode2->calculateFValue(locFinish);

                // if it is not in the open list then add into that
                if(openNodes[iNext][jNext] == 0) {
                    openNodes[iNext][jNext] = pNode2->getFValue();
                    q[qi].push(*pNode2);
                    // mark its parent node direction
                    dirMap[iNext][jNext] = (i + NDIR/2) % NDIR;
                }

                // already in the open list
                else if(openNodes[iNext][jNext] > pNode2->getFValue()) {
                    // update the FValue info
                    openNodes[iNext][jNext] = pNode2->getFValue();

                    // update the parent direction info,  mark its parent node direction
                    dirMap[iNext][jNext] = (i + NDIR/2) % NDIR;
/*
                    // replace the node by emptying one q to the other one
                    // except the node to be replaced will be ignored
                    // and the new node will be pushed in instead
                    while(!(q[qi].top().getLocation().row == iNext &&
                            q[qi].top().getLocation().col == jNext)) {
                        q[1 - qi].push(q[qi].top());
                        q[qi].pop();
                    }

                    // remove the wanted node
                    q[qi].pop();

                    // empty the larger size q to the smaller one
                    if(q[qi].size() > q[1 - qi].size()) qi = 1 - qi;
                    while(!q[qi].empty()) {
                        q[1 - qi].push(q[qi].top());
                        q[qi].pop();
                    }
                    qi = 1 - qi;
*/
                    // add the better node instead
                    q[qi].push(*pNode2);
                }
                else delete pNode2;
            }
        }
        delete pNode1;
    }
    // no path found
    return "No Path Found";
}


