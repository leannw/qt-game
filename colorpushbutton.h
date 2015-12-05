#ifndef COLORPUSHBUTTON_H
#define COLORPUSHBUTTON_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <iostream>
#include "gameboard.h"

class GameBoard;

class ColorPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit ColorPushButton(GameBoard *parent = 0);

private:
    GameBoard* my_parent;
signals:

public slots:
    void clicked_mole( );
};

#endif // COLORPUSHBUTTON_H
