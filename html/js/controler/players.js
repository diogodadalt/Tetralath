/**
 * Created by JetBrains PhpStorm.
 * User: Diogo
 * Date: 29/04/12
 * Time: 04:45
 * To change this template use File | Settings | File Templates.
 */

var Player = new function() {

    var self,
        measures = {
            w: 26,
            h: 26,
            r: 26
        };

    return self = {
        draw: function(paper, color) {
            var circle = paper.circle(measures.w, measures.h, measures.r);
            circle.attr("fill", color);
            return circle;
        }
    }
}
