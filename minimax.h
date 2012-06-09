/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/


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

signals:
    /*! Available on the client side */
    void computerPlayed(int pos);
    //void updateProgress(int completed, int total);
    //! [ public interface ]

private slots:

private:
    int miniMax(char _board[AMOUNT_POSITIONS], player _player);
    int minMove(char _board[AMOUNT_POSITIONS], player _player);
    int maxMove(char _board[AMOUNT_POSITIONS], player _player);
    void resetBoard();
    void initNeighbors();
    void changeState(GAME_STATE newState);
    void storePlayerMove(int move, int player);
    int evaluate(char _board[AMOUNT_POSITIONS], bool isComputerTurn);
    char** germov(char _board[AMOUNT_POSITIONS], bool isComputerTurn); // Method that returns the valid moves of a move


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
