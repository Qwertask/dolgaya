#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <QGraphicsEllipseItem>
#include <QGraphicsLineItem>
#include <QGraphicsPixmapItem>
#include <QThread>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class FallingCircle:public QGraphicsEllipseItem{
public:
    FallingCircle(int xspread, int yspread);

    // QGraphicsItem interface
public:
    virtual void advance(int phase);
    QVector <int> threadStatus;
    void move();

public:
    bool stop = false;
    double yspeed = 0.2*(-20 + rand()%41);
    double xspeed = 0.2*(-20 + rand()%41);
};

class RePainter:public QThread{
    Q_OBJECT
public:
    void run();
    QGraphicsScene* scene;
    FallingCircle* circle;
    bool stop;
    bool proc;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void check();

private:
    Ui::MainWindow *ui;
    QGraphicsScene* scene;
    QTimer* animationTime;
    QVector <FallingCircle*> fc;
    QVector <RePainter* > rep;
    QVector <int> threadStatus;
    RePainter* r;
    bool stop = false;
};


#endif // MAINWINDOW_H
