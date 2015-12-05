#include "gameboard.h"
#include <QPushButton>
#include <QGridLayout>
#include <time.h>
#include <stdlib.h>
#include <chrono>
#include <random>


/*!
 * GameBoard constructor, intitializes all private member variables, creates the board using a grid layout.
 * Adds the grid layout to a vertical layout so that the board include a count of lives, level, and score.
 * Sets a QTimer so that the mole will move ever xxx miliseconds.
 */
GameBoard::GameBoard(MainWindow* parent_input, int rows0, int cols0, unsigned int seed, int timeInt, int live) :
    moles(3), mole_x1(0), mole_y1(0), mole_x2(2), mole_y2(2), mole_x3(1), mole_y3(3),
    rows(rows0), cols(cols0), generator(seed), lives(live), parent(parent_input), timeInterval(timeInt)
{

    std::cout << "number of lives" << lives << std::endl;

    // This code Creates the Board
    board = new QWidget;
    gridLayout = new QGridLayout(board);
    gridLayout->setSpacing(0);
    buttonContainer = std::vector<ColorPushButton*>(rows*cols);

    for (int i = 0; i<rows*cols; i++){
        for (int x = 0; x < cols; x++){
            for (int y = 0; y < rows; y++){
                buttonContainer[i] = new ColorPushButton(this);
                buttonContainer[i]->setStyleSheet("background-color: blue");
                buttonContainer[i]->setFixedSize(40,40);

                QObject::connect(buttonContainer[i], SIGNAL(clicked()), buttonContainer[i], SLOT(clicked_mole( )));
                //QObject::connect(buttonContainer[i], SIGNAL(clicked()), this , SLOT(update_life() )) ;

            }
        }
    }

    QWidget* lifeBarWidget = new QWidget;
    QHBoxLayout *lifeBar = new QHBoxLayout(lifeBarWidget);

    life1 = new QLabel;
    life2 = new QLabel;
    life3 = new QLabel;

    score_num = new QLabel;
    level_num = new QLabel;

    score_str = new QLabel;
    level_str = new QLabel;

    score_num->setText(QString::number(score_int));
    level_num->setText(QString::number(level_int));


    score_str->setText("Score: ");
    level_str->setText("Level: ");

    life1->setFixedSize(40,40);
    life2->setFixedSize(40,40);
    life3->setFixedSize(40,40);

    life1->setStyleSheet("background-color: green");
    life2->setStyleSheet("background-color: green");
    life3->setStyleSheet("background-color: green");

    quit = new QPushButton;
    quit->setText("Quit");
    QObject::connect(quit, SIGNAL(clicked()), this, SLOT(quit_game( )));


    lifeBar->addWidget(life1);
    lifeBar->addWidget(life2);
    lifeBar->addWidget(life3);
    lifeBar->addWidget(level_str);
    lifeBar->addWidget(level_num);
    lifeBar->addWidget(score_str);
    lifeBar->addWidget(score_num);
    lifeBar->addWidget(quit);

    QWidget* entireBoardWidget = new QWidget;
    QVBoxLayout *entireBoard = new QVBoxLayout(entireBoardWidget);

    entireBoard->addWidget(lifeBarWidget);
    entireBoard->addWidget(board);




    auto it = std::begin(buttonContainer);
    for (int x = 0; x < cols; x++){
        for (int y = 0; y < rows; y++){
             gridLayout->addWidget(*it++, x, y);
        }
    }


    gridLayout->setGeometry(QRect());
    //gridLayout->setSpacing(0);

    this->setLayout(entireBoard);

    timer = new QTimer;
    timer->setInterval(timeInt);
    timer->start();

    QObject::connect(timer,SIGNAL(timeout()), this, SLOT(update_mole()));


    std::cout << "number of lives" << lives << std::endl;

}

/*!
 * A slot that quits the game when you click the QPushButton "quit, which is initialized in the constructor.
 * Sets lives to 0, and then calls update_life() slot which will decrement lives and then bring you to the Game Over screen.
 */
void GameBoard::quit_game(){
    lives = 0;
    update_life();

}

/*!
 * updates the score -- every time you correctly click on a red square, your score increases by 1
 * gets called in the clicked_mole slot of the colorpushbutton class
 * also prints score to the console just to make sure i'm not screwing up\
 * calls update_level whenever the score gets to be a multiple of 10
 */
void GameBoard::update_score(){
    ++score_int;
    score_num->setText(QString::number(score_int));

    if (score_int % 10 == 0){
        update_level();
    }

    std::cout << "score: " << score_int << std::endl;
}

/*!
 * does the same as above except with levels instead of score
 */
void GameBoard::update_level(){
    ++level_int;
    level_num->setText(QString::number(level_int));
    std::cout << "level: " << level_int << std::endl;
}

/*!
 * updates a QLabel's color every time you misclick,
 * you get three misclicks before the game leads you to the "game over" screen
 * also updates a integer "lives"
 */
void GameBoard::update_life(){
    --lives;
    if (lives == 2){
        life3->setStyleSheet("background-color: red");
    }
    else if (lives == 1){
        life2->setStyleSheet("background-color: red");
    }
    else if (lives == 0){
        life1->setStyleSheet("background-color: red");
    }
    else if(lives < 0) {
        QWidget* center = new QWidget;
        QVBoxLayout* center_GO = new QVBoxLayout(center);
        QWidget* final_level = new QWidget;
        QHBoxLayout* final_level_update = new QHBoxLayout (final_level);
        QWidget* final_score = new QWidget;
        QHBoxLayout* final_score_update = new QHBoxLayout (final_score);

        QLabel* label = new QLabel("GAME OVER");
        label->setAlignment(Qt::AlignCenter);

        final_level_update->addWidget(level_str);
        final_level_update->addWidget(level_num);

        final_score_update->addWidget(score_str);
        final_score_update->addWidget(score_num);

        center_GO->addWidget(label);
        center_GO->addWidget(final_level);
        center_GO->addWidget(final_score);

        center->show();
        parent->setCentralWidget(center);
        this->setParent(nullptr);
    }
    std::cout << "Number of lives: " << lives << std::endl;

}

/*!
 * i don't want to comment this function, but here we go
 * creates three random number generators, and three different "moles", red squares that just move around the screen
 * uses a switch statement to make sure the mole doesn't go off the grid and just increments or decrements mole_xn or mole_xy
 * so that the position changes.
 */
void GameBoard::update_mole() {


    auto random = generator()%4;
    auto random2 = (generator()*random)%4;
    auto random3 = (generator()*random2)%4;

    gridLayout->itemAtPosition(mole_x1,mole_y1)->widget()->setStyleSheet("background-color: blue");
    gridLayout->itemAtPosition(mole_x2,mole_y2)->widget()->setStyleSheet("background-color: blue");
    gridLayout->itemAtPosition(mole_x3,mole_y3)->widget()->setStyleSheet("background-color: blue");

    //gridLayout->itemAtPosition(mole_x,mole_y)->widget()->styleSheet();

    std::cout << random << std::endl;

    switch(random) {
    case 0:
        if (mole_x1 < rows-1 && (mole_x1 != mole_x2, mole_x3 && mole_y1 != mole_y2, mole_y3))
            ++mole_x1;
        else
            break;
        break;
    case 1:
        if(mole_y1 < cols-1 && (mole_x1 != mole_x2, mole_x3 && mole_y1 != mole_y2, mole_y3))
            ++mole_y1;
        else
            break;
        break;
    case 2:
        if (mole_x1 > 0 && (mole_x1 != mole_x2, mole_x3 && mole_y1 != mole_y2, mole_y3))
            --mole_x1;
        else
            break;
        break;
    case 3:
        if (mole_y1>0 && (mole_x1 != mole_x2, mole_x3 && mole_y1 != mole_y2, mole_y3))
            --mole_y1;
        else
            break;
        break;
    }

    switch(random2) {
    case 0:
        if (mole_x2 < rows-1 && (mole_x2 != mole_x1, mole_x3 && mole_y2 != mole_y1, mole_y3))
            ++mole_x2;
        else
            break;
        break;
    case 1:
        if(mole_y2 < cols-1 && (mole_x2 != mole_x1, mole_x3 && mole_y2 != mole_y1, mole_y3))
            ++mole_y2;
        else
            break;
        break;
    case 2:
        if (mole_x2 > 0 && (mole_x2 != mole_x1, mole_x3 && mole_y2 != mole_y1, mole_y3))
            --mole_x2;
        else
            break;
        break;
    case 3:
        if (mole_y2>0  && (mole_x2 != mole_x1, mole_x3 && mole_y2 != mole_y1, mole_y3))
            --mole_y2;
        else
            break;
        break;
    }

    switch(random3) {
    case 0:
        if (mole_x3 < rows-1 && (mole_x3 != mole_x1, mole_x2 && mole_y3 != mole_y1, mole_y2))
            ++mole_x3;
        else
            break;
        break;
    case 1:
        if(mole_y3 < cols-1 && (mole_x3 != mole_x1, mole_x2 && mole_y3 != mole_y1, mole_y2))
            ++mole_y3;
        else
            break;
        break;
    case 2:
        if (mole_x3 > 0 && (mole_x3 != mole_x1, mole_x2 && mole_y3 != mole_y1, mole_y2))
            --mole_x3;
        else
            break;
        break;
    case 3:
        if (mole_y3>0  && (mole_x3 != mole_x1, mole_x2 && mole_y3 != mole_y1, mole_y2))
            --mole_y3;
        else
            break;
        break;
    }

    gridLayout->itemAtPosition(mole_x1,mole_y1)->widget()->setStyleSheet("background-color: red");
    gridLayout->itemAtPosition(mole_x2,mole_y2)->widget()->setStyleSheet("background-color: red");
    gridLayout->itemAtPosition(mole_x3,mole_y3)->widget()->setStyleSheet("background-color: red");


}





