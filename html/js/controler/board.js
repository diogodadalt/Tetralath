/**
 * Created by JetBrains PhpStorm.
 * User: Diogo
 * Date: 29/04/12
 * Time: 04:41
 * To change this template use File | Settings | File Templates.
 */

var Board = new function () {

    var self,
        paper = null,
        hexagonMeasures = {
            width: 70,
            height: 85
        },
        placeholder = 0,
        previousPlaceholder = null;

    function hexagonMouseOver() {
        //this.attr("stroke", "#EEDA40");
        this.attr("stroke", "#000000");
    }

    function hexagonMouseOut() {
        if (previousPlaceholder !== this)
            this.attr("stroke", "#FFEC40");
    }

    function hexagonClick() {
        var elem = this,
            bbox = elem.getBBox();
        console.log(elem);
        $(self).trigger("placeholderselected", [{ number : $(elem).data("placeholder"), pos: bbox, paper: paper }]);
        markPlaceholder(elem);
    }

    function storePlaceholderNumer(elem) {
        $(elem).data("placeholder", placeholder);
        elem.id = "id_" + placeholder;
        placeholder++;
    }

    function markPlaceholder(current) {
        if (previousPlaceholder !== null)
            previousPlaceholder.attr("stroke", "#FFEC40");

        previousPlaceholder = current;
        current.attr("stroke", "#000000");
    }

    function drawHexagon(position) {
        var hexagon = paper.path(Raphael.format("M{0} {1}L{2} {3}L{4} {5}L{6} {7}L{8} {9}L{10} {11}L{12} {13}",
            hexagonMeasures.width / 2, 0, hexagonMeasures.width, hexagonMeasures.height / 4,
            hexagonMeasures.width, hexagonMeasures.height * 3 / 4, hexagonMeasures.width / 2,
            hexagonMeasures.height, 0, hexagonMeasures.height * 3 / 4, 0, hexagonMeasures.height / 4,
            hexagonMeasures.width / 2, 0));

        hexagon.attr("fill", "#FFEC40");
        //hexagon.attr("stroke", "#FFEC40");
        hexagon.attr("stroke", "#EEDA40");
        hexagon.translate(position.x, position.y);
        return hexagon;
    }

    function drawRowOne() {
        var hex = drawHexagon({ x: hexagonMeasures.width * 2 + 1, y: 0 }),
            i = 1;
        attachEvents(hex);
        var clone = hex;
        storePlaceholderNumer(clone);
        for (i = 1; i < 5; i++) {
            clone = clone.clone();
            storePlaceholderNumer(clone);
            clone.translate(hexagonMeasures.width + 1, 0);
            attachEvents(clone);
        }
    }

    function drawRowTwo() {
        var hex = drawHexagon({ x: hexagonMeasures.width * 2 - (hexagonMeasures.width / 2) + 1, y: hexagonMeasures.height * 3 / 4 + 2});
        attachEvents(hex);
        var clone = hex;
        storePlaceholderNumer(clone);
        for (var i=1; i<6; i++) {
            clone = clone.clone();
            storePlaceholderNumer(clone);
            clone.translate(hexagonMeasures.width+1, 0);
            attachEvents(clone);
        }
    }

    function drawRowThree() {
        var hex = drawHexagon({ x: hexagonMeasures.width + 1, y: hexagonMeasures.height * 3 / 2 + 4});
        attachEvents(hex);
        var clone = hex;
        storePlaceholderNumer(clone);
        for (var i=1; i<7; i++) {
            clone = clone.clone();
            storePlaceholderNumer(clone);
            clone.translate(hexagonMeasures.width+1, 0);
            attachEvents(clone);
        }
    }

    function drawRowFour() {
        var hex = drawHexagon({ x: hexagonMeasures.width / 2 + 1, y: hexagonMeasures.height * 9 / 4 + 6});
        attachEvents(hex);
        var clone = hex;
        storePlaceholderNumer(clone);
        for (var i=1; i<8; i++) {
            clone = clone.clone();
            storePlaceholderNumer(clone);
            clone.translate(hexagonMeasures.width+1, 0);
            attachEvents(clone);
        }
    }

    function drawRowFive() {
        var hex = drawHexagon({ x: 1, y: hexagonMeasures.height * 3 + 8});
        attachEvents(hex);
        var clone = hex;
        storePlaceholderNumer(clone);
        for (var i=1; i<9; i++) {
            clone = clone.clone();
            storePlaceholderNumer(clone);
            clone.translate(hexagonMeasures.width+1, 0);
            attachEvents(clone);
        }
    }

    function drawRowSix() {
        var hex = drawHexagon({ x: hexagonMeasures.width / 2 + 1, y: hexagonMeasures.height * 15 / 4 + 10});
        attachEvents(hex);
        var clone = hex;
        storePlaceholderNumer(clone);
        for (var i=1; i<8; i++) {
            clone = clone.clone();
            storePlaceholderNumer(clone);
            clone.translate(hexagonMeasures.width + 1, 0);
            attachEvents(clone);
        }
    }

    function drawRowSeven() {
        var hex = drawHexagon({ x: hexagonMeasures.width + 1, y: hexagonMeasures.height * 9 / 2 + 12});
        attachEvents(hex);
        var clone = hex;
        storePlaceholderNumer(clone);
        for (var i=1; i<7; i++) {
            clone = clone.clone();
            storePlaceholderNumer(clone);
            clone.translate(hexagonMeasures.width+1, 0);
            attachEvents(clone);
        }
    }

    function drawRowEight() {
        var hex = drawHexagon({ x: hexagonMeasures.width * 2 - (hexagonMeasures.width / 2) + 1, y:  hexagonMeasures.height * 21 / 4 + 14});
        attachEvents(hex);
        var clone = hex;
        storePlaceholderNumer(clone);
        for (var i=1; i<6; i++) {
            clone = clone.clone();
            storePlaceholderNumer(clone);
            clone.translate(hexagonMeasures.width+1, 0);
            attachEvents(clone);
        }
    }

    function drawRowNine() {
        var hex = drawHexagon({ x: hexagonMeasures.width * 2 + 1, y: hexagonMeasures.height * 6 + 16});
        attachEvents(hex);
        var clone = hex;
        storePlaceholderNumer(clone);
        for (var i=1; i<5; i++) {
            clone = clone.clone();
            storePlaceholderNumer(clone);
            clone.translate(hexagonMeasures.width+1, 0);
            attachEvents(clone);
        }
    }

    function drawBoard() {
        drawRowOne();
        drawRowTwo();
        drawRowThree();
        drawRowFour();
        drawRowFive();
        drawRowSix();
        drawRowSeven();
        drawRowEight();
        drawRowNine();
    }

    function attachEvents(hexagon) {
        hexagon.mouseover(hexagonMouseOver);
        hexagon.mouseout(hexagonMouseOut);
        hexagon.click(hexagonClick);
        return hexagon;
    }

    function detachEvents(hexagon) {
        hexagon.unmouseover(hexagonMouseOver);
        hexagon.unmouseover(hexagonMouseOut);
        hexagon.unclick(hexagonClick);
        return hexagon;
    }

    function init() {
        // Creates canvas
        paper = Raphael("main");

        drawBoard();
    }

    return self = {
        draw: function() {
            init();
        },
        drawCpuPiece: function(pos, color) {
            var elem = paper.getById("id_"+pos);
            var bbox = elem.getBBox();
            var piece = Player.draw(paper, color);
            piece.translate(bbox.x+9, bbox.y+16);
        },
        getPaper: function() {
            return paper;
        }
    }
}