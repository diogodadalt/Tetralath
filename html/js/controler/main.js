/**
 * Created by JetBrains PhpStorm.
 * User: Diogo
 * Date: 29/04/12
 * Time: 01:33
 * To change this template use File | Settings | File Templates.
 */

$(function () {

    $.fancybox.open({
        autoSize: true,
        modal: true,
        minHeight: 260,
        minWidth: 400,
        scrolling: 'no',
        href : 'gameoptions.html',
        type : 'ajax',
        padding : 5,
        afterShow: function() {
            GameOptions.init();
        }
    });

    Tetralath.init();
});


var Tetralath = new function() {

    var self,
        gameOptions = null,
        humanPlayer = null,
        computerPlayer = null,
        computerTurn = false,
        humanName = "";

    function startGame(e, data) {
        gameOptions = data;
        humanName = gameOptions.name;
        humanPlayer = {
            color: gameOptions.color,
            willStart: (gameOptions.startingPlayer == 1) ? true : false
        };
        computerPlayer = {
            color: (gameOptions.color == "#fff") ? "#000" : "#fff",
            willStart: (gameOptions.startingPlayer == 2) ? true : false
        }
        $.fancybox.close();
        Minimax.gameStarted(computerPlayer.willStart);
    }

    function placeHolderSelected(e, data) {
        if (!computerTurn) {
            var piece = Player.draw(data.paper, gameOptions.color);
            piece.translate(data.pos.x+9, data.pos.y+16);
            computerTurn = true;
            console.log(data);
            Minimax.humanPlayed(parseInt(data.number));
        }
    }

    function somebodyWon(isComputer) {
        var winner;
        if (isComputer)
            winner = "computerwon.html";
        else
            winner = "humanwon.html";

        $.fancybox.open({
            autoSize: true,
            modal: true,
            minHeight: 260,
            minWidth: 400,
            scrolling: 'no',
            href : winner,
            type : 'ajax',
            padding : 5,
            afterShow: function() {
                if (!isComputer)
                    $(".winner-message").html(humanName + " ganhou!");;
            }
        });
    }

    return self = {
        init: function() {
            Board.draw();
            $(Board).bind("placeholderselected", placeHolderSelected);
            $(GameOptions).bind("startgame", startGame);
            Minimax.computerPlayed.connect(self, self.cpuMove);
            Minimax.somebodyWon.connect(self, somebodyWon);
        },
        cpuMove: function(pos) {
            Board.drawCpuPiece(pos, computerPlayer.color);
            computerTurn = false;
        }
    }
}