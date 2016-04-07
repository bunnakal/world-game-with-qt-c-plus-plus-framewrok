#ifndef WORLDSCENE_H
#define WORLDSCENE_H
#include <memory>
#include <iostream>
#include <QtGui>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include "worldmodel.h"

#include <QObject>

class WorldScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit WorldScene(WorldModel * worldmodel, QGraphicsScene *parent = 0);
    void addVisualWorld(std::vector<std::shared_ptr<Tile>>tiles);
    void addEnemy(std::vector<std::shared_ptr<Enemy> > enemies);
    void addHealthPack(std::vector<std::shared_ptr<Tile>> healthPacks);
    std::vector<QGraphicsPixmapItem*> getSceneEnemy()const;
    std::vector<QGraphicsPixmapItem*> getSceneHealthPack()const;
    std::vector<QGraphicsTextItem*> getSceneEnemyText()const;
    std::vector<QGraphicsTextItem*> getSceneHealthPackText()const;
    void deleteEnemyAt(int x,int y);
    void addDefeatedEnemyAt(int x,int y);
    void deleteHealthPackAt(int x, int y);


signals:

public slots:

private:
    WorldModel* model;
    const int itemSize=40;
    std::vector<QGraphicsPixmapItem*> sceneEnemies;
    std::vector<QGraphicsPixmapItem*> sceneHealthpacks;
    std::vector<QGraphicsTextItem*> sceneEnemyTexts;
    std::vector<QGraphicsTextItem*> sceneHealthPackTexts;

};

#endif // WORLDSCENE_H
