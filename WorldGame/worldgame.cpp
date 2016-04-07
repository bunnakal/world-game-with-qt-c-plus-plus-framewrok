#include "worldgame.h"
#include "ui_worldgame.h"

WorldGame::WorldGame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WorldGame)
{
    ui->setupUi(this);

    createUI();

}

/**
 * @brief WorldGame::createUI
 * create the main user graphical user interface
 * for the world game.
 */
void WorldGame::createUI()
{
    std::cout<<"CreateUI()"<<std::endl;

    // create world model object
    model= new WorldModel(":/images/world.png");
    // set number of enemy in the world game
    model->setnrOfEnemy(200);
    // set number of HealthPacks in the world game
    model->setnrOfHealthPack(24);
    // the (x, y) start index of protagonist
    model->setXPosProtagonist(0);
    model->setYPosProtagonist(0);
    // set the start health and energy value
    model->setHealth(100);
    model->setEnergy(100);

    // create world view and scene
    view = new WorldView();
    // create the world scene object which add all enemies and healthpack
    // within the given model
    scene= new WorldScene(model);
    // put the scene into world view
    view->setScene(scene);

    // get the protagonist object from world model
    protagonist=model->getProtagonist();
    // create default WorldProtagonist object to add protagonist
    // on the position (0,0) regaurding to protagonist of world model
    worldprotagnist=new WorldProtagonist();
    // add worldprotagonist to scene
    scene->addItem(worldprotagnist);

    // create instance of timer
    timer= new QTimer(this);

    // create the main window layout with gridlayout
    layout=new QGridLayout();
    // create health label object
    healthLabel=new QLabel("Health: ");
    // create WorldProgressbar object within a given model
    // this object use for health progressbar
    healthProgressBar= new WorldProgressBar(model);
    healthProgressBar->setMinimum(0);
    healthProgressBar->setMaximum(100);
    healthProgressBar->setValue(protagonist->getHealth());
    // create energy label object
    energyLabel=new QLabel("Energy: ");
    // create WorldProgressbar object within a given model
    // this object use for energy progressbar
    energyProgressBar=new WorldProgressBar(model);
    energyProgressBar->setValue(protagonist->getEnergy());

    // create QPushButton object to handle with START STRATEGY button CLICK() event
    startButton=new QPushButton("START STRATEGY");
    // connect the signal click of startButton to the slot when the use
    // clicked on the startButton
    connect(startButton, SIGNAL(clicked()), this, SLOT(start()));
    // create QPushButton object to handle with RESET GAME button CLICK() event
    resetButton=new QPushButton("RESET GAME");
    connect(resetButton, SIGNAL(clicked()), this, SLOT(reset()));
    // create distance weight label object
    weightLabel = new QLabel("Distance Weight: ");
    // create
    weightSlider= new QSlider(Qt::Horizontal);
    weightSlider->setValue(5.0f);
    weightSlider->setSingleStep(10);
    weightSlider->setMinimum(0);
    weightSlider->setMaximum(60);
    connect(weightSlider, SIGNAL(sliderMoved(int)),this, SLOT(setWeight(int)));



    speedLabel = new QLabel("Animation Speed: ");
    // create WorldSlider object to handle on movement of speed slider
    speedSlider= new QSlider(Qt::Horizontal);
    speedSlider->setValue(500);
    speedSlider->setSingleStep(10);
    speedSlider->setMinimum(500);
    speedSlider->setMaximum(1100);
    // connect the sinal valueChanged to the slot setSpeed when the user
    // slide the slider bar
    connect(speedSlider, SIGNAL(sliderMoved(int)),this, SLOT(setSpeed(int)));

    status=new QStatusBar();
    status->showMessage("Ready...");

    // add all the widget to the main gridlayout
    // at the specific location
    layout->addWidget(healthLabel,0,0);
    layout->addWidget(healthProgressBar,0,1);
    layout->addWidget(weightLabel,0,2);
    layout->addWidget(weightSlider,0,3);

    layout->addWidget(energyLabel,1,0);
    layout->addWidget(energyProgressBar,1,1);
    layout->addWidget(speedLabel,1,2);
    layout->addWidget(speedSlider,1,3);

    layout->addWidget(startButton,2,0,1,2);
    layout->addWidget(resetButton,2,2,1,3);
    layout->addWidget(view,4,0,4,4);
    //layout->addWidget(status,5,0);

    // add the main layout to the main window form
    this->setLayout(layout);
}

/**
 * @brief WorldGame::startStrategy
 * this SLOT is handle for the START STRATEGY
 * button click
 */

void WorldGame::start()
{
    model->startStrategy();
    resetPath();
    worldPath=model->getPath();
    pathSize=worldPath.size()-1;

    connect(timer, SIGNAL(timeout()),this, SLOT(move()));
    timer->setInterval(500);
    timer->start();
}

/**
 * @brief WorldGame::move
 * this SLOT will invoke every timer object is time out (the time
 * interval was finished or equal 0).
 */
void WorldGame::move()
{
    try{
        if(worldPath.size()==0){
            QMessageBox::information(this,tr("Info"),tr("No Path Found!!!"));
            timer->stop();
            return;
        }
        // if have path to move through it will move
        // until reach the destination (pathSize=0)
        if(pathSize!=-1)
        {
            connect(protagonist.get(),SIGNAL(posChanged(int,int)), worldprotagnist,SLOT(setPosChange(int,int)));
            protagonist->setXPos(worldPath.at(pathSize)->getXPos());
            protagonist->setYPos(worldPath.at(pathSize)->getYPos());
            std::cout<<"Protagonist Pos "<<pathSize<<"(" << protagonist->getXPos()<<", " << protagonist->getYPos()<<")"<<std::endl;
            worldprotagnist->setX(worldprotagnist->getXPos()*itemSize);
            worldprotagnist->setY(worldprotagnist->getYPos()*itemSize);
            if(pathSize>0){
                int nextLoc=pathSize-1;
                int indexCurrent=(worldPath.at(pathSize)->getXPos())*(15)+(worldPath.at(pathSize)->getYPos());
                int indexNext=(worldPath.at(nextLoc)->getXPos())*(15)+(worldPath.at(nextLoc)->getYPos());
                float current=model->getTile().at(indexCurrent)->getValue();
                float next=model->getTile().at(indexNext)->getValue();

                std::cout<<"wieght value in move:"<<distWeight<<std::endl;
                cost=distWeight*fabs(next-current);
                std::cout<<"cost"<<cost<<std::endl;
            }
            // update world progress bar
            synWorldProgressBar();

            pathSize--;
        }
        // if pathSize=0 then the target is reach
        // then startStrategy again to find another suitable path
        else {
            // stop timer to find another suitable path with startStrategy()
            timer->stop();

            model->startStrategy();

            resetPath();
            worldPath=model->getPath();
            pathSize=worldPath.size()-1;

            // start timer again to make protagonist move along the new path
            if(pathSize==0) timer->stop();
            timer->start();

        }
    }
    catch(std::exception &e){

        std::cout<<"Error handdler in move():"<<e.what()<<std::endl;
    }
}

/**
 * @brief WorldGame::synWorldProgressBar
 * this method use to update or synchronize the health and energy progress bar
 * every move is called.
 */
void WorldGame::synWorldProgressBar()
{
    energyProgressBar->decreaseEnergyBy(cost);
    energy=energyProgressBar->getEnergy();
    energyProgressBar->setValue(energy);
    protagonist->setEnergy(energy);
    std::cout<<"Current Energy: "<<protagonist->getEnergy()<<std::endl;
    std::cout<<"Current Path Size: "<<pathSize<<std::endl;

    // if the level of energy bellow the cost to go throw
    // then the game will be over as no more energy to go on
    if(energy<cost)
    {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::question(this,"GameOver", "YOU ARE RUN OUT OF!!!\n\nENERGY?", QMessageBox::Yes|QMessageBox::No);
        if (reply == QMessageBox::Yes) {
            std::cout<< "Yes was clicked"<<std::endl;
            reset();
        } else {
            std::cout << "Yes was *not* clicked"<<std::endl;
        }
        model->setGameOver(true);
        timer->stop();
    }

    // if the still have energy and no more path to go throw
    // then reset the energy bar to maximize.
    else if(energy>0 && pathSize==0)
    {
        std::cout<<"Reset Eenergy to maximize...!"<<std::endl;
        energyProgressBar->setValue(100);
        energyProgressBar->setEnergy(100);
        protagonist->setEnergy(100);

        float value;
        int x,y;
        // if the target is enemy then it will be decreased
        // the health bar with the value of defeated enemy.
        if(model->isEnemyTarget())
        {
            try{

                value=model->getDefeatableEnemy().at(model->getIndex())->getValue();

                std::cout<<"Health decreased by: "<<value<<std::endl;
                healthProgressBar->decreaseHealthBy(value);
                health=healthProgressBar->getHealth();
                healthProgressBar->setValue(health);
                model->setHealth(health);
                std::cout<<"Health after decreased: "<<model->getHealth()<<std::endl;

                x=model->getDefeatableEnemy().at(model->getIndex())->getXPos();
                y=model->getDefeatableEnemy().at(model->getIndex())->getYPos();

                model->deleteEnemyAt(x,y);
                scene->deleteEnemyAt(x,y);
                model->makePassableAt(x,y,false);
                scene->addDefeatedEnemyAt(x,y);
            }
            catch(std::exception& e){
                std::cout<<"Error handdler in synWorldProgressBar() Occur on Target is Enemy"<<e.what()<<std::endl;
            }
        }
        // otherwise the target will be healthpacks
        // then after reach the healthPack the health bar will be increased with the value of healthpack
        // which has been attached.
        else
        {
            try{

                value=model->getAvailableHealthPack().at(model->getIndex())->getValue();

                x=model->getAvailableHealthPack().at(model->getIndex())->getXPos();
                y=model->getAvailableHealthPack().at(model->getIndex())->getYPos();

                std::cout<<"Health Increased by: "<<value<<std::endl;
                healthProgressBar->increaseHealthBy(value);
                health=healthProgressBar->getHealth();
                healthProgressBar->setValue(health);
                model->setHealth(health);
                std::cout<<"Health after increased: "<<model->getHealth()<<std::endl;

                model->deleteHealthPackAt(x,y);
                scene->deleteHealthPackAt(x,y);
                model->makePassableAt(x,y,true);
            }
            catch(std::exception& e){
                std::cout<<"Error handdler in synWorldProgressBar() Occur on Target is HealthPack"<<e.what()<<std::endl;
            }
        }
        // check to see wheather the game is win
        if(isWin()){
            timer->stop();
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this,"WIN", "YOU ARE WIN!!!\n\nPLAY AGAIN?", QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                std::cout<< "Yes was clicked"<<std::endl;
                reset();
            } else {
                std::cout << "Yes was *not* clicked"<<std::endl;
            }

        }
        // otherwise check to see weather the game is lost
        else if(isLost()){
            timer->stop();
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this,"LOST", "YOU ARE LOST!!!\n\nPLAY AGAIN?", QMessageBox::Yes|QMessageBox::No);
            if (reply == QMessageBox::Yes) {
                std::cout<< "Yes was clicked"<<std::endl;
                reset();
                //QApplication::quit();
            } else {
                std::cout << "Yes was *not* clicked"<<std::endl;
            }
            model->setGameOver(true);
        }
    }
}
/**
 * @brief WorldGame::reset
 * this SLOT was call when user click on the reset game button
 */
void WorldGame::reset()
{
    resetAll();
    createUI();
}

/**
 * @brief WorldGame::resetAll
 * delete all object which was created
 */
void WorldGame::resetAll()
{
    delete model;
    delete scene;
    delete timer;
    protagonist.reset();
    worldPath.erase(worldPath.begin(),worldPath.end());
    delete healthLabel;
    delete healthProgressBar;
    delete energyLabel;
    delete energyProgressBar;
    delete weightLabel;
    delete weightSlider;
    delete speedLabel;
    delete speedSlider;
    delete startButton;
    delete resetButton;
    delete layout;
}
/**
 * @brief WorldGame::isWin
 * @return true if the game is win
 * otherwise return false.
 */
bool WorldGame::isWin()
{
    if(model->getEnemy().size()==0 && model->getHealth()>0) return true;
    return false;
}

/**
 * @brief WorldGame::isLost
 * @return true if the game is lost
 * otherwise return false.
 */
bool WorldGame::isLost()
{
    if(model->getEnemy().size()>0 && model->getHealthPack().size()==0) return true;
    return false;
}

/**
 * @brief WorldGame::setSpeed
 * @param value use to decrease the current speed with this value
 * make the world game Protagonist speed changed
 */
void WorldGame::setSpeed(int value)
{
    speed=1000-(float)value;
    timer->setInterval(speed);
    //setProtagonistSpeed(speed);
    std::cout<<"Slider Value Changed to: "<<speed<<std::endl;

}

void WorldGame::setWeight(int value)
{
    distWeight=value;
    std::cout<<"slider weight value:"<<distWeight<<std::endl;
}

WorldGame::~WorldGame()
{
    delete ui;
}

void WorldGame::resetPath()
{
    worldPath.erase(worldPath.begin(),worldPath.end());
}

