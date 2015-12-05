#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QLabel>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTimer>
#include <QPushButton>
#include <random>
#include "colorpushbutton.h"
#include <iostream>

#include "mainwindow.h"

class MainWindow;
class ColorPushButton;

namespace Ui {
class GameBoard;
}

class GameBoard : public QWidget
{
    Q_OBJECT

    friend class ColorPushButton;

public:
    GameBoard(MainWindow* parent, int rows, int cols, unsigned int seed=0, int timeInt = 1000, int live = 3);

//signals:

public slots:
    void update_mole();
//    void clicked_mole(QPushButton *button);

    void update_life ();
    void update_score();
    void update_level();

    void quit_game();

private:
    // Board Variables
    QWidget *board;
    std::vector< ColorPushButton*> buttonContainer;
    int moles;
    int easyMoles;
    int mediumMoles;
    int hardMoles;
    int lives;

    int timeInterval;

    QGridLayout *gridLayout;

    QLabel *life1;
    QLabel *life2;
    QLabel *life3;

    QLabel *score_num;
    QLabel *level_num;

    QLabel *score_str;
    QLabel *level_str;

    int score_int = 0;
    int level_int = 1;

    QPushButton *quit;

    size_t mole_x1;
    size_t mole_y1;

    size_t mole_x2;
    size_t mole_y2;

    size_t mole_x3;
    size_t mole_y3;



    size_t rows;
    size_t cols;

    QTimer* timer;

    std::default_random_engine generator;

    MainWindow* parent;

};

#endif // GAMEBOARD_H
