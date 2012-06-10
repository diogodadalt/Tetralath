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

#include "minimax.h"

//! [ ImageAnalyzer - Constructor ]
MiniMax::MiniMax(QObject *parent)
    : QObject(parent)
{
    initNeighbors();
    resetBoard();
    changeState(START);

    // Test
    char bd[AMOUNT_POSITIONS];
    for(int i = 0; i < AMOUNT_POSITIONS; i++) {
        bd[i] = 0;
    }
    int amountPossibleMoves = 47;
    bd[0] = 'h';
    bd[2] = 'h';
    bd[3] = 'h';
    bd[7] = 'h';
    bd[8] = 'h';
    bd[23] = 'h';
    bd[20] = 'h';
    bd[1] = 'c';
    bd[4] = 'c';
    bd[5] = 'c';
    bd[9] = 'c';
    bd[10] = 'c';
    bd[24] = 'c';
    bd[21] = 'c';
    computerStarted = false;
    int res = evaluate(bd, false);
    char** mvslist = germov(bd, false);
    qDebug() << "asdasd";
    qDebug() << res;
    for (int i = 0; i < amountPossibleMoves; i++) {
        for (int j = 0; j < AMOUNT_POSITIONS; j++) {
            qDebug() << i << ", " << j << " ";
            qDebug() << (mvslist[i][j] == 0);
            qDebug() << mvslist[i][j];
        }
    }
}
//! [ ImageAnalyzer - Constructor ]

MiniMax::~MiniMax() {}

void MiniMax::gameStarted(bool computerBegins) {
    if (computerBegins)
        changeState(COMPUTER_TURN);
    else
        changeState(HUMAN_TURN);

    computerStarted = computerBegins;
}

void MiniMax::humanPlayed(int pos) {
    storePlayerMove(pos, 1);
    changeState(COMPUTER_TURN);
}

void MiniMax::changeState(GAME_STATE newState) {
    int position = -1;
    switch(newState) {
    case COMPUTER_TURN:
        currentPlayer = computerPlayer;
        //position = miniMax(board, computerPlayer);
        position = miniMaxShortVersion(board, 5, true);
        storePlayerMove(position, 2);
        emit computerPlayed(position);
        changeState(HUMAN_TURN);
        break;
    case HUMAN_TURN:
        currentPlayer = humanPlayer;
        break;
    }

    gameState = newState;
}

void MiniMax::storePlayerMove(int move, int player) {
    board[move] = (player == 1) ? 'h' : 'c';
}

void MiniMax::resetBoard() {
    for(int i = 0; i < AMOUNT_POSITIONS; i++) {
        board[i] = 0;
    }
}

void MiniMax::resetBoard(char _board[AMOUNT_POSITIONS]) {
    for(int i = 0; i < AMOUNT_POSITIONS; i++) {
        _board[i] = 0;
    }
}

char* MiniMax::copyBoardState(char _board[AMOUNT_POSITIONS]) {
    char* b;
    b = new char[AMOUNT_POSITIONS];
    for (int i = 0; i < AMOUNT_POSITIONS; i++)
        b[i] = _board[i];

    return b;
}

void MiniMax::initNeighbors() {
    QList<QList<int> > directNeighbors;
    for(int i = 0; i < AMOUNT_POSITIONS; i++) {
        directNeighbors.clear();
        for(int j = 0; j < 6; j++) {
            directNeighbors.append(QList<int>());
        }
        neighbors.append(directNeighbors);
    }
    neighbors[0][0] << 1 << 2 << 3;
    neighbors[0][1] << 5 << 11 << 18;
    neighbors[0][2] << 6 << 13 << 21;
    neighbors[1][0] << 0;
    neighbors[1][1] << 2 << 3 << 4;
    neighbors[1][2] << 6 << 12 << 19;
    neighbors[1][3] << 7 << 14 << 22;
    neighbors[2][0] << 1 << 0;
    neighbors[2][1] << 3 << 4;
    neighbors[2][2] << 7 << 13 << 20;
    neighbors[2][3] << 8 << 15 << 23;
    neighbors[3][0] << 2 << 1 << 0;
    neighbors[3][1] << 4;
    neighbors[3][2] << 8 << 14 << 21;
    neighbors[3][3] << 9 << 16 << 24;
    neighbors[4][0] << 3 << 2 << 1;
    neighbors[4][1] << 9 << 15 << 22;
    neighbors[4][2] << 10 << 17 << 25;
    neighbors[5][0] << 0;
    neighbors[5][1] << 6 << 7 << 8;
    neighbors[5][2] << 11 << 18 << 26;
    neighbors[5][3] << 12 << 20 << 29;
    neighbors[6][0] << 0;
    neighbors[6][1] << 1;
    neighbors[6][2] << 5;
    neighbors[6][3] << 7 << 8 << 9;
    neighbors[6][4] << 12 << 19 << 27;
    neighbors[6][5] << 13 << 21 << 30;
    neighbors[7][0] << 1;
    neighbors[7][1] << 2;
    neighbors[7][2] << 6 << 5;
    neighbors[7][3] << 8 << 9 << 10;
    neighbors[7][4] << 13 << 20 << 28;
    neighbors[7][5] << 14 << 22 << 31;
    neighbors[8][0] << 2;
    neighbors[8][1] << 3;
    neighbors[8][2] << 7 << 6 << 5;
    neighbors[8][3] << 9 << 10;
    neighbors[8][4] << 14 << 21 << 29;
    neighbors[8][5] << 15 << 23 << 32;
    neighbors[9][0] << 3;
    neighbors[9][1] << 4;
    neighbors[9][2] << 8 << 7 << 6;
    neighbors[9][3] << 10;
    neighbors[9][4] << 15 << 22 << 30;
    neighbors[9][5] << 16 << 24 << 33;
    neighbors[10][0] << 4;
    neighbors[10][1] << 9 << 8 << 7;
    neighbors[10][2] << 16 << 23 << 31;
    neighbors[10][3] << 17 << 25 << 34;
    neighbors[11][0] << 5;
    neighbors[11][1] << 12 << 13 << 14;
    neighbors[11][2] << 18 << 26;
    neighbors[11][3] << 19 << 28 << 37;
    neighbors[12][0] << 5;
    neighbors[12][1] << 6 << 1;
    neighbors[12][2] << 11;
    neighbors[12][3] << 13 << 14 << 15;
    neighbors[12][4] << 19 << 27 << 35;
    neighbors[12][5] << 20 << 29 << 38;
    neighbors[13][0] << 6 << 0;
    neighbors[13][1] << 7 << 2;
    neighbors[13][2] << 12 << 11;
    neighbors[13][3] << 14 << 15 << 16;
    neighbors[13][4] << 20 << 28 << 36;
    neighbors[13][5] << 21 << 30 << 39;
    neighbors[14][0] << 7 << 1;
    neighbors[14][1] << 8 << 3;
    neighbors[14][2] << 13 << 12 << 11;
    neighbors[14][3] << 15 << 16 << 17;
    neighbors[14][4] << 21 << 29 << 37;
    neighbors[14][5] << 22 << 31 << 40;
    neighbors[15][0] << 8 << 2;
    neighbors[15][1] << 9 << 4;
    neighbors[15][2] << 14 << 13 << 12;
    neighbors[15][3] << 16 << 17;
    neighbors[15][4] << 22 << 30 << 38;
    neighbors[15][5] << 23 << 32 << 41;
    neighbors[16][0] << 9 << 3;
    neighbors[16][1] << 10;
    neighbors[16][2] << 15 << 14 << 13;
    neighbors[16][3] << 7;
    neighbors[16][4] << 23 << 31 << 39;
    neighbors[16][5] << 24 << 33 << 42;
    neighbors[17][0] << 10;
    neighbors[17][1] << 16 << 15 << 14;
    neighbors[17][2] << 24 << 32 << 40;
    neighbors[17][3] << 25 << 34;
    neighbors[18][0] << 11 << 5 << 0;
    neighbors[18][1] << 19 << 20 << 21;
    neighbors[18][2] << 6;
    neighbors[18][3] << 27 << 36 << 44;
    neighbors[19][0] << 11;
    neighbors[19][1] << 12 << 6 << 1;
    neighbors[19][2] << 18;
    neighbors[19][3] << 20 << 21 << 22;
    neighbors[19][4] << 27 << 35;
    neighbors[19][5] << 28 << 37 << 45;
    neighbors[20][0] << 12 << 5;
    neighbors[20][1] << 13 << 7 << 2;
    neighbors[20][2] << 19 << 18;
    neighbors[20][3] << 21 << 22 << 23;
    neighbors[20][4] << 28 << 36 << 43;
    neighbors[20][5] << 29 << 38 << 46;
    neighbors[21][0] << 13 << 6 << 0;
    neighbors[21][1] << 14 << 8 << 3;
    neighbors[21][2] << 20 << 19 << 18;
    neighbors[21][3] << 22 << 23 << 24;
    neighbors[21][4] << 29 << 37 << 44;
    neighbors[21][5] << 30 << 39 << 47;
    neighbors[22][0] << 14 << 7 << 1;
    neighbors[22][1] << 15 << 9 << 4;
    neighbors[22][2] << 21 << 20 << 19;
    neighbors[22][3] << 23 << 24 << 25;
    neighbors[22][4] << 30 << 38 << 45;
    neighbors[22][5] << 31 << 40 << 48;
    neighbors[23][0] << 15 << 8 << 2;
    neighbors[23][1] << 16 << 10;
    neighbors[23][2] << 22 << 21 << 20;
    neighbors[23][3] << 24 << 25;
    neighbors[23][4] << 31 << 39 << 46;
    neighbors[23][5] << 32 << 41 << 49;
    neighbors[24][0] << 16 << 9 << 3;
    neighbors[24][1] << 17;
    neighbors[24][2] << 23 << 22 << 21;
    neighbors[24][3] << 25;
    neighbors[24][4] << 32 << 40 << 47;
    neighbors[24][5] << 33 << 42;
    neighbors[25][0] << 17 << 10 << 4;
    neighbors[25][1] << 24 << 23 << 22;
    neighbors[25][2] << 33 << 41 << 48;
    neighbors[25][3] << 34;
    neighbors[26][0] << 18 << 11 << 5;
    neighbors[26][1] << 27 << 28 << 29;
    neighbors[26][2] << 35 << 43 << 50;
    neighbors[27][0] << 18;
    neighbors[27][1] << 19 << 12 << 6;
    neighbors[27][2] << 26;
    neighbors[27][3] << 28 << 29 << 30;
    neighbors[27][4] << 35;
    neighbors[27][5] << 36 << 44 << 51;
    neighbors[28][0] << 19 << 11;
    neighbors[28][1] << 20 << 13 << 7;
    neighbors[28][2] << 27 << 26;
    neighbors[28][3] << 29 << 30 << 31;
    neighbors[28][4] << 36 << 43;
    neighbors[28][5] << 37 << 45 << 52;
    neighbors[29][0] << 20 << 12 << 5;
    neighbors[29][1] << 21 << 14 << 8;
    neighbors[29][2] << 28 << 27 << 26;
    neighbors[29][3] << 30 << 31 << 32;
    neighbors[29][4] << 37 << 44 << 50;
    neighbors[29][5] << 38 << 46 << 53;
    neighbors[30][0] << 21 << 13 << 6;
    neighbors[30][1] << 22 << 15 << 9;
    neighbors[30][2] << 29 << 28 << 27;
    neighbors[30][3] << 31 << 32 << 33;
    neighbors[30][4] << 38 << 45 << 51;
    neighbors[30][5] << 39 << 47 << 54;
    neighbors[31][0] << 22 << 14 << 7;
    neighbors[31][1] << 23 << 16 << 10;
    neighbors[31][2] << 30 << 29 << 28;
    neighbors[31][3] << 32 << 33 << 34;
    neighbors[31][4] << 39 << 46 << 52;
    neighbors[31][5] << 40 << 48 << 55;
    neighbors[32][0] << 23 << 15 << 8;
    neighbors[32][1] << 24 << 17;
    neighbors[32][2] << 31 << 30 << 29;
    neighbors[32][3] << 33 << 34;
    neighbors[32][4] << 40 << 47 << 53;
    neighbors[32][5] << 41 << 49;
    neighbors[33][0] << 24 << 16 << 9;
    neighbors[33][1] << 25;
    neighbors[33][2] << 32 << 31 << 30;
    neighbors[33][3] << 34;
    neighbors[33][4] << 41 << 48 << 54;
    neighbors[33][5] << 42;
    neighbors[34][0] << 25 << 17 << 10;
    neighbors[34][1] << 33 << 32 << 31;
    neighbors[34][2] << 42 << 49 << 55;
    neighbors[35][0] << 26;
    neighbors[35][1] << 27 << 19 << 12;
    neighbors[35][2] << 36 << 37 << 38;
    neighbors[35][3] << 43 << 50 << 56;
    neighbors[36][0] << 27 << 28;
    neighbors[36][1] << 28 << 20 << 13;
    neighbors[36][2] << 35;
    neighbors[36][3] << 37 << 38 << 39;
    neighbors[36][4] << 43;
    neighbors[36][5] << 44 << 51 << 57;
    neighbors[37][0] << 28 << 19 << 11;
    neighbors[37][1] << 29 << 21 << 14;
    neighbors[37][2] << 36 << 35;
    neighbors[37][3] << 38 << 39 << 40;
    neighbors[37][4] << 44 << 50;
    neighbors[37][5] << 45 << 52 << 58;
    neighbors[38][0] << 29 << 20 << 12;
    neighbors[38][1] << 30 << 22 << 15;
    neighbors[38][2] << 37 << 36 << 35;
    neighbors[38][3] << 39 << 40 << 41;
    neighbors[38][4] << 45 << 51 << 56;
    neighbors[38][5] << 46 << 53 << 59;
    neighbors[39][0] << 30 << 21 << 13;
    neighbors[39][1] << 31 << 23 << 16;
    neighbors[39][2] << 38 << 37 << 36;
    neighbors[39][3] << 40 << 41 << 42;
    neighbors[39][4] << 46 << 52 << 57;
    neighbors[39][5] << 47 << 54 << 60;
    neighbors[40][0] << 31 << 22 << 14;
    neighbors[40][1] << 32 << 24 << 17;
    neighbors[40][2] << 39 << 38 << 37;
    neighbors[40][3] << 41 << 42;
    neighbors[40][4] << 47 << 53 << 58;
    neighbors[40][5] << 48 << 55;
    neighbors[41][0] << 32 << 23 << 15;
    neighbors[41][1] << 33 << 25;
    neighbors[41][2] << 40 << 39 << 38;
    neighbors[41][3] << 42;
    neighbors[41][4] << 48 << 54 << 59;
    neighbors[41][5] << 49;
    neighbors[42][0] << 33 << 24 << 16;
    neighbors[42][1] << 34;
    neighbors[42][2] << 41 << 40 << 39;
    neighbors[42][3] << 49 << 55 << 60;
    neighbors[43][0] << 35 << 26;
    neighbors[43][1] << 36 << 28 << 20;
    neighbors[43][2] << 44 << 45 << 46;
    neighbors[43][3] << 50 << 56;
    neighbors[44][0] << 36 << 27 << 18;
    neighbors[44][1] << 37 << 29 << 21;
    neighbors[44][2] << 43;
    neighbors[44][3] << 45 << 46 << 47;
    neighbors[44][4] << 50;
    neighbors[44][5] << 51 << 57;
    neighbors[45][0] << 37 << 28 << 19;
    neighbors[45][1] << 38 << 30 << 22;
    neighbors[45][2] << 44 << 43;
    neighbors[45][3] << 46 << 47 << 48;
    neighbors[45][4] << 51 << 56;
    neighbors[45][5] << 52 << 58;
    neighbors[46][0] << 38 << 29 << 20;
    neighbors[46][1] << 39 << 31 << 23;
    neighbors[46][2] << 45 << 44 << 43;
    neighbors[46][3] << 47 << 48 << 49;
    neighbors[46][4] << 52 << 57;
    neighbors[46][5] << 53 << 59;
    neighbors[47][0] << 39 << 30 << 21;
    neighbors[47][1] << 40 << 32 << 24;
    neighbors[47][2] << 46 << 45 << 44;
    neighbors[47][3] << 48 << 49;
    neighbors[47][4] << 53 << 58;
    neighbors[47][5] << 54 << 60;
    neighbors[48][0] << 40 << 31 << 22;
    neighbors[48][1] << 41 << 33 << 25;
    neighbors[48][2] << 47 << 46 << 45;
    neighbors[48][3] << 49;
    neighbors[48][4] << 54 << 59;
    neighbors[48][5] << 55;
    neighbors[49][0] << 41 << 32 << 23;
    neighbors[49][1] << 42 << 34;
    neighbors[49][2] << 48 << 47 << 46;
    neighbors[49][3] << 55 << 60;
    neighbors[50][0] << 43 << 35 << 26;
    neighbors[50][1] << 44 << 37 << 29;
    neighbors[50][2] << 51 << 52 << 53;
    neighbors[50][3] << 56;
    neighbors[51][0] << 44 << 36 << 27;
    neighbors[51][1] << 45 << 38 << 30;
    neighbors[51][2] << 50;
    neighbors[51][3] << 52 << 53 << 54;
    neighbors[51][4] << 56;
    neighbors[51][5] << 57;
    neighbors[52][0] << 45 << 37 << 28;
    neighbors[52][1] << 46 << 39 << 31;
    neighbors[52][2] << 51 << 50;
    neighbors[52][3] << 53 << 54 << 55;
    neighbors[52][4] << 57;
    neighbors[52][5] << 58;
    neighbors[53][0] << 46 << 38 << 29;
    neighbors[53][1] << 47 << 40 << 32;
    neighbors[53][2] << 52 << 51 << 50;
    neighbors[53][3] << 54 << 55;
    neighbors[53][4] << 58;
    neighbors[53][5] << 59;
    neighbors[54][0] << 47 << 39 << 30;
    neighbors[54][1] << 48 << 41 << 33;
    neighbors[54][2] << 53 << 52 << 51;
    neighbors[54][3] << 55;
    neighbors[54][4] << 59;
    neighbors[54][5] << 60;
    neighbors[55][0] << 48 << 40 << 31;
    neighbors[55][1] << 49 << 42 << 34;
    neighbors[55][2] << 54 << 53 << 52;
    neighbors[55][3] << 60;
    neighbors[56][0] << 50 << 43 << 35;
    neighbors[56][1] << 51 << 45 << 38;
    neighbors[56][2] << 57 << 58 << 59;
    neighbors[57][0] << 51 << 44 << 36;
    neighbors[57][1] << 52 << 46 << 39;
    neighbors[57][2] << 6;
    neighbors[57][3] << 58 << 59 << 60;
    neighbors[58][0] << 52 << 45 << 37;
    neighbors[58][1] << 53 << 47 << 40;
    neighbors[58][2] << 57 << 56;
    neighbors[58][3] << 59 << 60;
    neighbors[59][0] << 53 << 46 << 38;
    neighbors[59][1] << 54 << 48 << 41;
    neighbors[59][2] << 58 << 57 << 56;
    neighbors[59][3] << 60;
    neighbors[60][0] << 54 << 47 << 39;
    neighbors[60][1] << 55 << 49 << 42;
    neighbors[60][2] << 59 << 58 << 57;
}

int MiniMax::evaluate(char _board[AMOUNT_POSITIONS], bool isComputerTurn) {
    int valUnitsH = 0, valUnisC = 0,
        valPairsH = 0, valPairsC = 0,
        valTripletH = 0, valTripletC = 0,
        valHuman = 0, valComputer = 0, val = 0;
    int numPiecesHuman = 0, numPiecesComputer = 0,
        numPieces = 0, count = 0;
    char currentP = 0;
    char somebodyWon = 0;


    for(int i = 0; i < AMOUNT_POSITIONS; i++) {
        currentP = _board[i];
        if (currentP == 'h' || currentP == 'c') {

            if (currentP == 'h') {
                //numPiecesHuman = 1;
                valUnitsH++;
            }
            else if (currentP == 'c') {
                //numPiecesComputer = 1;
                valUnisC++;
            }

            for(int j = 0; j < 6 ; j++) {
                if (neighbors[i][j].length() > 0) {
                    numPieces = 1;
                    count = 1;
                    foreach(int n, neighbors[i][j]) {
                        if (currentP == _board[n]) {

                            if (numPieces == count && numPieces == 1) {
                                if (currentP == 'h')
                                    valPairsH++;
                                else if (currentP == 'c')
                                    valPairsC++;
                            } else if (numPieces == count && numPieces == 2) {
                                // somebody lost the game
                                somebodyWon = (currentP == 'h') ? 'c' : 'h';
                                break;
                            } else if (numPieces == count && numPieces == 3) {
                                // somebody won the game
                                somebodyWon = currentP;
                                break;
                            } else if (numPieces == count-1 && numPieces == 2) {
                                if (currentP == 'h')
                                    valTripletH++;
                                else if (currentP == 'c')
                                    valTripletC++;
                            }

                            numPieces++;
                        } else if (numPieces == count && numPieces == 1)
                            break;

                        count++;
                    }
                }

                if (somebodyWon != 0)
                    break;
            }
        }

        if (somebodyWon != 0)
            break;
    }

    if (somebodyWon == 0) {
        valComputer += valUnisC;
        valComputer += valPairsC; // Não estou eliminando os repetidos exatamente para dar maior peso aos pares.
        valComputer += valTripletC * 6;
        valHuman += valUnitsH;
        valHuman += valPairsH; // Não estou eliminando os repetidos exatamente para dar maior peso aos pares.
        valHuman += valTripletH * 6;
        if (isComputerTurn)
            val = valComputer - valHuman;
        else
            val = valHuman - valComputer;
    } else if (somebodyWon == 'c') {
        if (isComputerTurn)
            val = 1000;
        else
            val = -1000;
    } else if (somebodyWon == 'h') {
        if (!isComputerTurn)
            val = 1000;
        else
            val = -1000;
    }

    return val;
}

char** MiniMax::germov(char _board[AMOUNT_POSITIONS], bool isComputerTurn) {
    char** movesList;
    movesList = new  char*[amountOfPossibleMoves(_board)];
    int countMoves = 0;
    if (isComputerTurn) {
        for(int i = 0; i < AMOUNT_POSITIONS; i++) {
            if (_board[i] == 0) {
                movesList[countMoves] = new char[AMOUNT_POSITIONS];
                movesList[countMoves] = copyBoardState(_board);
                movesList[countMoves][i] = 'c';
                countMoves++;
            }
        }
    } else {
        for(int i = 0; i < AMOUNT_POSITIONS; i++) {
            if (_board[i] == 0) {
                movesList[countMoves] = new char[AMOUNT_POSITIONS];
                movesList[countMoves] = copyBoardState(_board);
                movesList[countMoves][i] = 'h';
                countMoves++;
            }
        }
    }
    return movesList;
}

int MiniMax::amountOfPossibleMoves(char _board[AMOUNT_POSITIONS]) {
    int possibleMoves = 0;
    for (int i = 0; i < AMOUNT_POSITIONS; i++) {
        if (_board[i] == 0)
            possibleMoves++;
    }
    return possibleMoves;
}

bool MiniMax::deepEnough(char _board[AMOUNT_POSITIONS], int depth) {
    int amountOfEmptyPlaceHolders = 0;
    int amountOfDifferentValues = 0;
    for (int i = 0; i < AMOUNT_POSITIONS; i++) {
        if (_board[i] == 0)
            amountOfEmptyPlaceHolders++;
        else if (_board[i] != board[i])
            amountOfDifferentValues++;
    }

    if (amountOfEmptyPlaceHolders || amountOfDifferentValues == depth)
        return true;
    else
        return false;
}

int MiniMax::getBoardPositionOfMove(char previousBoard[AMOUNT_POSITIONS], char currentBoard[AMOUNT_POSITIONS]) {
    int pos = -1;
    for (int i = 0; i < AMOUNT_POSITIONS; i++) {
        if (previousBoard[i] != currentBoard[i]) {
            pos = i;
            break;
        }
    }
    return pos;
}

int MiniMax::miniMaxShortVersion(char _board[AMOUNT_POSITIONS], int depth, bool isComputerTurn) {
    if (deepEnough(_board, depth)) {

    }
    // TODO
    return 0;
}

// returns best move for the current computer player
int MiniMax::miniMax(char _board[AMOUNT_POSITIONS], bool isComputerTurn) {
    /*
    int best_val = -INFINITY, index = 0;
    std::list<int> move_list;
    char best_moves[9] = {0};
    generate_moves(_board, move_list);
    while(!move_list.empty()) {
        _board[move_list.front()] = _player.symbol;
        cSymbol = _player.symbol;
        int val = MinMove(_board, _player);
        if(val > best_val) {
            best_val = val;
            index = 0;
            best_moves[index] = move_list.front() + 1;
        } else if(val == best_val) {
            best_moves[++index] = move_list.front() + 1;
        }
        _board[move_list.front()] = 0;
        move_list.pop_front();
    }
    if(index > 0) {
        index = rand() % index;
    }
    return best_moves[index];
    */
    /*
    int pos = -1;
    bool emptyPlaceHolder = false;

    while(!emptyPlaceHolder) {
        pos = rand() % AMOUNT_POSITIONS;
        if (board[pos] == 0)
            emptyPlaceHolder = true;
        else
            emptyPlaceHolder = false;
    }
    return pos;

    valorMelhorJogada = tabuleiroTetralath::PERDA;
    while(!(*deve_parar_param) and jogadaAtual < tabuleiroTetralath::NUMERO_CASAS){
        if(tabuleiro.jogar(jogadaAtual)){
            valorJogada = minimax(deve_parar_param, tipoJogadaFilho, nivel_maximo_param, nivel_atual_param+1, cor_pecas_avaliacao_param);
            tabuleiro.desfazerUltimaJogada();
            if(valorMelhorJogada <= valorJogada){
                casaMelhorJogada = jogadaAtual;
                valorMelhorJogada = valorJogada;
            }
        }
        jogadaAtual++;
    }
    */
    return 0;
}

// finds best move for 'min player'
int MiniMax::minMove(char _board[AMOUNT_POSITIONS], player _player) {
    /*
    int pos_value = evaluate_position(_board, _player);
    if(pos_value != -1) {
        return pos_value;
    }
    int best_val = +INFINITY;
    std::list<int> move_list;
    generate_moves(_board, move_list);
    while(!move_list.empty()) {
        _player.symbol == 'X' ? cSymbol = 'O' : cSymbol = 'X';
        _board[move_list.front()] = cSymbol;
        int val = MaxMove(_board, _player);
        if(val < best_val) {
            best_val = val;
        }
        _board[move_list.front()] = 0;
        move_list.pop_front();
    }
    return best_val;
    */
    return 0;
}

// finds best move for 'max player'
int MiniMax::maxMove(char _board[AMOUNT_POSITIONS], player _player) {
    /*
    int pos_value = evaluate_position(_board, _player);
    if(pos_value != -1) {
        return pos_value;
    }
    int best_val = -INFINITY;
    std::list<int> move_list;
    generate_moves(_board, move_list);
    while(!move_list.empty()) {
        _player.symbol == 'X' ? cSymbol = 'X' : cSymbol = 'O';
        _board[move_list.front()] = cSymbol;
        int val = MinMove(_board, _player);
        if(val > best_val) {
            best_val = val;
        }
        _board[move_list.front()] = 0;
        move_list.pop_front();
    }
    return best_val;
    */
    return 0;
}
