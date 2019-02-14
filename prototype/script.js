initialize = function() {
    bx = width/2;
    by = (y1+y2)/2;
    update();
}

update = function() {
    var angle = Math.atan((y2 - y1)/width);
    by = (y1+y2)/2;
    bx -= angle;
    render();
}

render = function() {
    ctx.clearRect(0, 0, width, height);

    // Paddle
    ctx.beginPath();
    ctx.moveTo(0, height-y1);
    ctx.lineTo(width, height-y2);
    ctx.closePath();
    ctx.strokeStyle = 'blue';
    ctx.lineWidth = 10;
    ctx.stroke();

    // Ball
    ctx.beginPath();
    ctx.ellipse(bx, height-by, 20, 20, 0, 0, 2 * Math.PI);
    ctx.closePath();
    ctx.strokeStyle = 'silver';
    ctx.lineWidth = 2;
    ctx.stroke();
}

const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');
var width = canvas.width;
var height = canvas.height;
// Paddle:
var y1 = 10;
var y2 = 10;
// Ball:
var bx = 0;
var by = 0;
initialize();
update();

document.addEventListener('keydown', function(event) {
    switch (event.keyCode)
    {
        case 74: // j = right down
            y2--;
            update();
            break;
        case 75: // k = right up
            y2++;
            update();
            break;
        case 85: // u = alternative right up
            y2++;
            update();
            break;
        case 83: // s = left down
            y1--;
            update();
            break;
        case 68: // d = left up
            y1++;
            update();
            break;
        case 87: // w = alternative left up
            y1++;
            update();
            break;
    }
});