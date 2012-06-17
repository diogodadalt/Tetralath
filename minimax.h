#ifndef MINIMAX_H
#define MINIMAX_H

#include <QtGui>


#define AMOUNT_POSITIONS 61

// declare the possible states for the game session
enum GAME_STATE {START, HUMAN_TURN, COMPUTER_TURN, QUIT, OWIN, XWIN, DRAW};

// this stucture simply defines the characteristic of each player
typedef struct {
    QString name;
    char symbol;
    int move;
    int game_win;
    int draw_num;
    bool selected;
    bool win;
} player;

struct MinimaxResult {
    int value;
    char* board;
};

//! [ public interface ]
class MiniMax : public QObject
{
    Q_OBJECT
public:
    MiniMax(QObject * parent=0);

    /*
      Available on the client side
    float lastRed();
    float lastGreen();
    float lastBlue();
    bool isBusy();
    Q_PROPERTY(bool busy READ isBusy);
    Q_PROPERTY(float red READ lastRed);
    Q_PROPERTY(float green READ lastGreen);
    Q_PROPERTY(float blue READ lastBlue);
    */
    ~MiniMax();

public slots:
    /*! Available on the client side */
    void gameStarted(bool computerBegins);
    void humanPlayed(int pos);
    void onSomebodyWon();

signals:
    /*! Available on the client side */
    void computerPlayed(int pos);
    void somebodyWon(bool isComputer);
    //void updateProgress(int completed, int total);
    //! [ public interface ]

private slots:

private:
    int miniMax(char _board[AMOUNT_POSITIONS], bool isComputerTurn);
    int minMove(char _board[AMOUNT_POSITIONS], player _player);
    int maxMove(char _board[AMOUNT_POSITIONS], player _player);
    void resetBoard();
    void resetBoard(char _board[]);
    void initNeighbors();
    void changeState(GAME_STATE newState);
    void storePlayerMove(int move, int player);
    char* copyBoardState(char _board[AMOUNT_POSITIONS]);
    int evaluate(char _board[], bool isComputerTurn);
    char** germov(char _board[], bool isComputerTurn); // Method that returns the valid moves of a move
    int amountOfPossibleMoves(char _board[]);
    bool deepEnough(char _board[], int depth);
    int getBoardPositionOfMove(char previousBoard[], char currentBoard[]);
    MinimaxResult& miniMaxShortVersion(char _board[], int depth, bool isComputerTurn);
    void checkForGameState(char _board[]);
    void debugBoard(char _board[]);
    int temporary(char _board[], int depth, bool isComputerTurn);


    //! [ private members ]
private:
    GAME_STATE gameState;
    player humanPlayer, computerPlayer, currentPlayer;
    char board[AMOUNT_POSITIONS];
    QList<QList<QList<int> > > neighbors;
    bool computerStarted;
    //! [ private members ]
};

#endif
