#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gameboard.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*!
 * slot that returns you to the main menu so that when you click "main menu"
 * you go back to the first screen
 */
void MainWindow::main_menu(){
    MainWindow *w = new MainWindow();
    this->setCentralWidget(w);
}

/*!
 * begins a game and creates a 4x4 board where the moles change every 1 second
 */
void MainWindow::easy_game_begin(){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    board = new GameBoard(this, 4, 4, seed, 1000);
    this->setCentralWidget(board);
}

/*!
 * begins a game and creates a 6x6 board where the moles change every 850 miliseconds
 */
void MainWindow::medium_game_begin(){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    board = new GameBoard(this, 6,6, seed, 850);
    this->setCentralWidget(board);
}

/*!
 * begins a game and creates a 8x8 board where the moles change every 700 miliseconds
 */
void MainWindow::hard_game_begin(){
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    board = new GameBoard(this, 8,8, seed, 700);
    this->setCentralWidget(board);
}

/*!
 * leads you to a separate screen that displays the instructiosn about game mechanics
 * also creates a QPushButton that returns you to the main menu
 */
void MainWindow::show_instructions(){
    instr = new QLabel;
    instr->setText("You have three lives, as depicted by the green boxes at the top of the screen. Your goal is to click"
                   "on the red boxes to make them turn back to blue. If you're too slow and misclick, you will lose a life. "
                   "Every ten points you will advance to the next level. Once you lose all three of your lives, "
                   "the game is over. The level of difficulty will change the size of the board and the speed "
                   "that the red boxes move.");
    instr->setFixedWidth(300);
    //instr->setFixedHeight(400);
    instr->setWordWrap(true);
    instr->show();

    QPushButton* back = new QPushButton;
    back->setText("Main Menu");
    back->show();
    QObject::connect(back, SIGNAL(clicked()), this, SLOT(main_menu()));

    QWidget* vert = new QWidget;
    QVBoxLayout* vertLayout = new QVBoxLayout(vert);
    vertLayout->addWidget(back);
    vertLayout->addWidget(instr);

    this->setCentralWidget(vert);
}
