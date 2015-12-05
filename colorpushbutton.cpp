#include "colorpushbutton.h"

ColorPushButton::ColorPushButton(GameBoard *parent) : QPushButton(parent), my_parent(parent)
{

}

/*!
 * if a button is clicked, this slot gets called
 * updates score and updates the life
 * if the background color on click is red, sets it back to blue
 */
void ColorPushButton::clicked_mole( ){
    if (this->styleSheet() == "background-color: red"){
        this->setStyleSheet("background-color: blue");
        my_parent->update_score();
    }
    else{
        my_parent->update_life();
    }
}

