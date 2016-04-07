#ifndef WORLDPROTAGONIST_H
#define WORLDPROTAGONIST_H
#include "world.h"
#include <memory>
#include <iostream>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QObject>
#include "worldmodel.h"
#include "worldprogressbar.h"

class WorldProtagonist : public QObject,public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    WorldProtagonist(QGraphicsPixmapItem *parent = 0);
    void paint(QPainter * painter,const QStyleOptionGraphicsItem * option,QWidget * widget);
    QRectF boundingRect() const;
    int getXPos()const;
    int getYPos()const;

signals:

public slots:
    void setPosChange(int x, int y);

private:
    int xPos;
    int yPos;
};

#endif // WORLDPROTAGONIST_H
