#ifndef WORLDVIEW_H
#define WORLDVIEW_H
#include <QWheelEvent>

#include <QGraphicsView>

class WorldView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit WorldView(QGraphicsView *parent = 0);
protected:
    virtual void wheelEvent(QWheelEvent *event);
signals:

public slots:

};

#endif // WORLDVIEW_H
