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
    resetBoard();
    changeState(START);
}
//! [ ImageAnalyzer - Constructor ]
MiniMax::~MiniMax()
{
}

void MiniMax::gameStarted(bool computerBegins) {
    if (computerBegins)
        changeState(COMPUTER_TURN);
    else
        changeState(HUMAN_TURN);
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
        position = miniMax(board, computerPlayer);
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

// returns best move for the current computer player
int MiniMax::miniMax(char _board[AMOUNT_POSITIONS], player _player) {
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
