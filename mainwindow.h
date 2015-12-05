#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "gameboard.h"

class GameBoard;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void easy_game_begin();
    void medium_game_begin();
    void hard_game_begin();

    void show_instructions();
    void main_menu();

private:
    Ui::MainWindow *ui;
    GameBoard* board;
    QLabel* instr;
};

#endif // MAINWINDOW_H
