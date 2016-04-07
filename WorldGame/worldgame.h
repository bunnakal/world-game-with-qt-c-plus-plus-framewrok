#ifndef WORLDGAME_H
#define WORLDGAME_H
#include <memory>
#include <exception>
#include <QDialog>
#include <QtGui>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QLabel>
#include <QProgressBar>
#include <QGridLayout>
#include <QPushButton>
#include <QSlider>
#include <QStatusBar>
#include <QMessageBox>
#include <iostream>
#include "worldmodel.h"
#include "worldscene.h"
#include "worldview.h"
#include "worldprotagonist.h"
#include "worldprogressbar.h"

namespace Ui {
class WorldGame;
}

class WorldGame : public QDialog
{
    Q_OBJECT

public:
    explicit WorldGame(QWidget *parent = 0);
    ~WorldGame();
    void createUI();
    void resetAll();
    bool isWin();
    bool isLost();

    void resetPath();
signals:

public slots:
    void start();
    void reset();
    void setSpeed(int value);
    void setWeight(int value);
    void synWorldProgressBar();
    void move();

private:
    // the main window
    Ui::WorldGame *ui;
    // the WorldModel  object to keep track all visualization
    WorldModel * model;
    // the WorldView  object to display scene on the main window object
    WorldView * view;
    // the WorldScene  object to display all object such visualize world with tiles,
    // enemies,and healthpacks
    WorldScene * scene;
    // the WorldPortagonist object use to place and the movement of Protagonist
    // as QGraphicsPixmapItem
    WorldProtagonist * worldprotagnist;

    // create all label object use in UI of worldgame
    QLabel * healthLabel;
    QLabel * energyLabel;
    QLabel * weightLabel;
    QLabel * speedLabel;

    // the start and reset button use in WorldGame
    QPushButton * startButton;
    QPushButton * resetButton;

    // the WorldProgressBar object use to create Health and Energy ProgressBar
    // and keep track all real time update level of progress bar every time protagonist moves.
    WorldProgressBar * healthProgressBar;
    WorldProgressBar * energyProgressBar;

    //
    QSlider * weightSlider;
    QSlider * speedSlider;
    QStatusBar * status;

    QGridLayout * layout;

    // the WorldTimer object use to create real time tick of protagonist
    // and can manage the speed of protagonist as well
    QTimer *timer;

    // the default speed of protagonist
    float speed;
    // the shortest path lenght to the destination
    int pathSize;

    // the energy and health variable use to store and update prograss bar on real time
    float energy;
    float health;
    // the cost between two tiles
    float cost=0;
    float distWeight;
    int const itemSize=40;

    // the protagonist object use to move on the world
    std::shared_ptr<Protagonist>protagonist;

    // the vector of shortest path to move along to reach target point
    std::vector<std::shared_ptr<Tile>> worldPath;

};

#endif // WORLDGAME_H
