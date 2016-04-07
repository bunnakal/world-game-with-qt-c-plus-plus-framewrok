#include "worldscene.h"

/**
 * @brief WorldScene::WorldScene
 * @param worldmodel WorldModel object use to create some needed
 * visual tiles world, enemies, and healthpacks.
 * @param parent QGraphicsScene base class object
 */
WorldScene::WorldScene(WorldModel *worldmodel,QGraphicsScene *parent) :
    QGraphicsScene(parent)
{
    model=worldmodel;
    addVisualWorld(model->createVisualWorld());
    addEnemy(model->createEnemy());
    addHealthPack(model->createHealthPack());

}

/**
 * @brief WorldScene::addVisualWorld
 * @param tiles vector of visual world tile position and value to be put into
 * QGraphicsRectItem onto the QGraphicsScene
 *
 */
void WorldScene::addVisualWorld(std::vector<std::shared_ptr<Tile> > tiles)
{
    for(unsigned int i=0;i<tiles.size();i++){
        QGraphicsRectItem * item=new QGraphicsRectItem(tiles.at(i)->getXPos()*itemSize,tiles.at(i)->getYPos()*itemSize,itemSize,itemSize);
        item->setBrush(QColor::fromRgbF(0.2,0.3,0.5,tiles.at(i)->getValue()));
        item->setPen(Qt::NoPen);
        addItem(item);
    }
}

/**
 * @brief WorldScene::addEnemy
 * @param enemies vector of enemy which created by world model class
 * to be put into QGraphicsPixmapItem onto the QGraphicsScene
 *
 */
void WorldScene::addEnemy(std::vector<std::shared_ptr<Enemy> > enemies)
{
    for(unsigned int i=0;i<enemies.size();i++){
        QGraphicsPixmapItem * item=new QGraphicsPixmapItem();
        item->setX((enemies.at(i)->getXPos()+0.2f)*itemSize);
        item->setY((enemies.at(i)->getYPos()+0.4f)*itemSize);
        item->setPixmap(QPixmap(":/images/enemy25x25.png"));
        QString t;
        t.setNum(enemies.at(i)->getValue());

        QGraphicsTextItem * text=new QGraphicsTextItem(t);
        text->setFont(QFont( "lucida", 10, QFont::Bold));
        text->setDefaultTextColor(Qt::red);
        text->setX((enemies.at(i)->getXPos()+0.2f)*itemSize);
        text->setY((enemies.at(i)->getYPos()-0.15f)*itemSize);
        addItem(text);
        addItem(item);

        sceneEnemyTexts.push_back(text);
        sceneEnemies.push_back(item);

        std::cout<<"Enemy Pos (" << enemies.at(i)->getXPos() << "," << enemies.at(i)->getYPos() << ")" << std::endl;
        std::cout << "---------------------------------------------" << std::endl;
    }
}

/**
 * @brief WorldScene::addHealthPack
 * @param healthPacks vector of healthpacks which was created by world model object.
 * use to create QGraphicsPixmapItem corresponding to healthpack created by world model
 * it was create and put into QGraphicsScene
 */
void WorldScene::addHealthPack(std::vector<std::shared_ptr<Tile> > healthPacks)
{
    for(unsigned int i=0;i<healthPacks.size();i++){
        QGraphicsPixmapItem * item=new QGraphicsPixmapItem();
        item->setX((healthPacks.at(i)->getXPos()+0.2f)*itemSize);
        item->setY((healthPacks.at(i)->getYPos()+0.4f)*itemSize);
        item->setPixmap(QPixmap(":/images/health25x25.png"));
        QString t;
        t.setNum(healthPacks.at(i)->getValue());

        QGraphicsTextItem * text=new QGraphicsTextItem(t);
        text->setFont(QFont( "lucida", 10, QFont::Bold));
        text->setDefaultTextColor(Qt::yellow);
        text->setX((healthPacks.at(i)->getXPos()+0.2f)*itemSize);
        text->setY((healthPacks.at(i)->getYPos()-0.15f)*itemSize);
        addItem(text);
        addItem(item);

        sceneHealthPackTexts.push_back(text);
        sceneHealthpacks.push_back(item);

        std::cout<<"healthPacks Pos (" << healthPacks.at(i)->getXPos() << "," << healthPacks.at(i)->getYPos() << ")" << std::endl;
        std::cout << "---------------------------------------------" << std::endl;
    }
}

/**
 * @brief WorldScene::getSceneEnemy
 * @return vector of QGraphicsPixmapItem of Enemies which was added to QGraphicsScene
 *
 */
std::vector<QGraphicsPixmapItem *> WorldScene::getSceneEnemy() const
{
    return sceneEnemies;
}

/**
 * @brief WorldScene::getSceneHealthPack
 * @return vector of QGraphicsPathItem of HealthPacks which was added to QGraphicsScene
 *
 */
std::vector<QGraphicsPixmapItem *> WorldScene::getSceneHealthPack() const
{
    return sceneHealthpacks;
}

/**
 * @brief WorldScene::getSceneEnemyText
 * @return vector of QGraphicsTextItem of Enemy text which was added to QGraphicsScene
 *
 */
std::vector<QGraphicsTextItem *> WorldScene::getSceneEnemyText() const
{
    return sceneEnemyTexts;
}

/**
 * @brief WorldScene::getSceneHealthPackText
 * @return vector of QGraphicsTextItem of HealthPacks which was added to QGraphicsScene
 *
 */
std::vector<QGraphicsTextItem *> WorldScene::getSceneHealthPackText() const
{
    return sceneHealthPackTexts;
}

/**
 * @brief WorldScene::deleteEnemyAt
 * @param x position of enemy pix map item and text to be deleted
 * @param y position of enemy pix map item and text to be deleted
 */
void WorldScene::deleteEnemyAt(int x, int y)
{   if(sceneEnemies.size()>0){
        for(unsigned int i=0;i<sceneEnemies.size();i++){
            if((int)sceneEnemies.at(i)->x()/itemSize==x && (int)sceneEnemies.at(i)->y()/itemSize==y){

                delete sceneEnemies.at(i);
                delete sceneEnemyTexts.at(i);

                sceneEnemies.erase(sceneEnemies.begin()+i);
                sceneEnemyTexts.erase(sceneEnemyTexts.begin()+i);
                return ;
            }
        }
    }
}

/**
 * @brief WorldScene::addDefeatedEnemyAt
 * @param x position of defeated enemy to be added to the scene
 * @param y position of defeated enemy to be added to the scene
 */
void WorldScene::addDefeatedEnemyAt(int x, int y)
{
    std::cout<<"\t\tAdd Defeated is called...!"<<std::endl;
    QGraphicsPixmapItem * item=new QGraphicsPixmapItem();
    item->setPixmap(QPixmap(":/images/defeatedenemy25x25.png"));
    item->setX((x+0.2f)*itemSize);
    item->setY((y+0.4f)*itemSize);

    QString t;
    t.setNum(0.0f);
    QGraphicsTextItem * text=new QGraphicsTextItem(t);
    text->setFont(QFont( "lucida", 10, QFont::Bold));
    text->setDefaultTextColor(Qt::white);
    text->setX((x+0.3f)*itemSize);
    text->setY((y-0.15f)*itemSize);

    addItem(item);
    addItem(text);
}

/**
 * @brief WorldScene::deleteEnemyAt
 * @param x x position of healthpack pix map item and text to be deleted
 * @param y y position of healthpack pix map item and text to be deleted
 */
void WorldScene::deleteHealthPackAt(int x, int y)
{
    for(unsigned int i=0;i<sceneHealthpacks.size();i++){
        if((int)sceneHealthpacks.at(i)->x()/itemSize==x && (int)sceneHealthpacks.at(i)->y()/itemSize==y){

            delete sceneHealthpacks.at(i);
            delete sceneHealthPackTexts.at(i);

            sceneHealthpacks.erase(sceneHealthpacks.begin()+i);
            sceneHealthPackTexts.erase(sceneHealthPackTexts.begin()+i);

            return ;
        }
    }
}
