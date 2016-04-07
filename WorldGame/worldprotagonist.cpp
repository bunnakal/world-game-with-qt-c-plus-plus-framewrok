#include "worldprotagonist.h"

/**
 * @brief WorldProtagonist::WorldProtagonist
 * @param parent
 */
WorldProtagonist::WorldProtagonist(QGraphicsPixmapItem *parent):
    QGraphicsPixmapItem(parent)
{
    setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    setFlag(QGraphicsPixmapItem::ItemIsMovable);
    setFlag(QGraphicsPixmapItem::ItemSendsScenePositionChanges);
}

/**
 * @brief WorldProtagonist::paint
 * @param painter
 * @param option
 * @param widget
 */
void WorldProtagonist::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QPixmap image(":/images/mario.png");
    painter->drawPixmap(0,0,image);
}

/**
 * @brief WorldProtagonist::boundingRect
 * @return
 */
QRectF WorldProtagonist::boundingRect() const
{
    return QRectF(0,0,40,40);
}

/**
 * @brief WorldProtagonist::getXPos
 * @return
 */
int WorldProtagonist::getXPos() const
{
    return xPos;
}

/**
 * @brief WorldProtagonist::getYPos
 * @return
 */
int WorldProtagonist::getYPos() const
{
    return yPos;
}

/**
 * @brief WorldProtagonist::setPosChange
 * @param x
 * @param y
 */
void WorldProtagonist::setPosChange(int x, int y)
{
    xPos=x;
    yPos=y;
}

