/**
 * Created by JetBrains PhpStorm.
 * User: Diogo
 * Date: 29/04/12
 * Time: 20:52
 * To change this template use File | Settings | File Templates.
 */

var GameOptions = new function() {

    var self;

    function getInfo() {
        var name = ($("#txt-name").val() != "") ? $("#txt-name").val() : "Jogador 1";
        var color = ($("#slc-color").val() == "1") ? "#fff" : "#000";
        var startingPlayer = $("input:radio[name=player]:checked").val();

        return {
            name : name,
            color: color,
            startingPlayer : startingPlayer
        }
    }

    function startGame() {
        $(self).trigger("startgame", getInfo());
    }

    return self = {
        init : function() {
            $("#btn-start-game").click(startGame);
        }
    }
}