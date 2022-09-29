#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(0,0,640, 300, this);
    ui->graphicsView->setScene(scene);
    scene->addRect(scene->sceneRect());

    animationTime = new QTimer(this);
    connect(animationTime, SIGNAL(timeout()),scene, SLOT(advance()));
    animationTime->start(1000/60);
    for(int i = 0;i<10;i++){
        fc.append(new FallingCircle(scene->sceneRect().width(),scene->sceneRect().height()));
        rep.append(new RePainter);
    }
    for(int i = 0;i<fc.size();i++){
        scene->addItem(fc[i]);
    }
    for(int i = 0;i<fc.size();i++){
        rep[i]->circle = fc[i];
        rep[i]->proc = true;
        rep[i]->start();
    }
    for(int i = 0;i<fc.size();i++){
        connect(rep[i], SIGNAL(finished()), rep[i], SLOT(quit()));
        connect(rep[i], SIGNAL(finished()), this, SLOT(check()));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

FallingCircle::FallingCircle(int xspread, int yspread):QGraphicsEllipseItem(0)
{
    QColor color = QColor(rand()%255,rand()%255,rand()%255);
    setBrush(color);
    setRect(0, 0, 25, 25);
    setPos(25+rand()%(xspread-100), 25+rand()%(yspread-100));
}

void FallingCircle::advance(int phase)
{
    if(phase&&!stop){
        move();
    }
}

void FallingCircle::move()
{
    if(fabs(xspeed)>=0.01&&fabs(yspeed)>= 0.01){
        if(this->x()>615||this->x()<0){
            xspeed*=(-1);
            if(this->x()>615){
                this->setPos(615, this->y());
            } else {
                this->setPos(0, this->y());
            }
        }
        if(this->y()>275||this->y()<0){
            yspeed*=(-1);
            if(this->y()>275){
                this->setPos(this->x(), 275);
            } else {
                this->setPos(this->x(), 0);
            }
        }
        moveBy(xspeed, yspeed);
    }
}


void MainWindow::on_pushButton_clicked()
{
    for(int i = 0;i<fc.size();i++){
        ui->label->setText(" ");
        fc[i]->xspeed =0.5*(-20 + rand()%41);
        fc[i]->yspeed =0.5*(-20 + rand()%41);
        rep[i]->proc = true;
        fc[i]->stop = false;
        rep[i]->start();
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    for(int i = 0;i<fc.size();i++){
        fc[i]->stop = true;
    }
}


void RePainter::run()
{
    while(true){
        msleep(rand()%400);
        if(!circle->stop){
            circle->xspeed-= 0.05*circle->xspeed;
            circle->yspeed-= 0.05*circle->yspeed;
        }
        //qDebug()<<circle->xspeed<<"  "<<circle->yspeed;
        if(fabs(circle->xspeed)<=0.005&&fabs(circle->xspeed)<=0.005){
            circle->xspeed = 0;
            circle->yspeed = 0;
            proc = false;
            break;
        }
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    for(int i = 0;i<fc.size();i++){
        fc[i]->stop = false;
    }
}

void MainWindow::check()
{
    bool cont = false;
    for(int i = 0;i<rep.size();i++){
        if(rep[i]->proc){
            cont = true;
        }
    }
    if(!cont){
        ui->label->setText("All threads are finished!");
    }
}

