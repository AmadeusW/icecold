// Game constants
const sceneWidth = 600;
const sceneHeight = 800;
const paddleWidth = sceneWidth * 1.2;
const paddleStart = 750;
const wallWidth = 50;
const moveDelta = 3;
const maxYDelta = 150;
const frictionAtHole = 0.01;
const friction = 0.001; // default is 0.1
const victoryLabel = "victory";
const defeatLabel = "defeat";

// module aliases
var Engine = Matter.Engine,
    Render = Matter.Render,
    World = Matter.World,
    Bodies = Matter.Bodies,
    Events = Matter.Events,
    Body = Matter.Body,
    Detector = Matter.Detector;

// create an engine
var engine = Engine.create();

// create a renderer
var render = Render.create({
    canvas: document.getElementById('canvas'),
    options: {
        width: sceneWidth,
        height: sceneHeight,
    },
    engine: engine
});

var ball = Bodies.circle(sceneWidth/2, paddleStart - 50, 15, 80);
var paddle = Bodies.rectangle(sceneWidth/2, paddleStart, paddleWidth, 10, { isStatic: true });
var ground = Bodies.rectangle(sceneWidth/2, sceneHeight, sceneWidth, 20, { isStatic: true });
var wall1 = Bodies.rectangle(-wallWidth/2, sceneHeight/2, wallWidth, sceneHeight, { isStatic: true });
var wall2 = Bodies.rectangle(sceneWidth + wallWidth/2, sceneHeight/2, wallWidth, sceneHeight, { isStatic: true });

var sensorVictory = Bodies.circle(200, 300, 2, { isSensor: true, isStatic: true });
var sensorNearVictory = Bodies.circle(200, 300, 17, { isSensor: true, isStatic: true, label: victoryLabel });

var sensorX = Bodies.circle(400, 300, 5, { isSensor: true, isStatic: true });
var sensorNearX = Bodies.circle(400, 300, 20, { isSensor: true, isStatic: true, label: defeatLabel });

ball.friction = friction;
ball.density = 0.05; // default is 0.001
paddle.friction = friction;
engine.world.gravity.scale = 0.005; // default is 0.001

// add all of the bodies to the world
World.add(engine.world, [
    ball,
    paddle,
    ground, wall1, wall2,
    sensorVictory, sensorNearVictory, sensorX, sensorNearX]);

// run the engine
Engine.run(engine);

// run the renderer
Render.run(render);

var y1 = paddleStart;
var y2 = paddleStart;
var leftUp = false, leftDown = false, rightUp = false, rightDown = false;
var potentialEndBody = undefined;

var move = function(d1, d2) {
    var newy1 = y1 - d1;
    var newy2 = y2 - d2;
    var yDelta = newy1 - newy2;
    if (Math.abs(yDelta) >= maxYDelta)
        return;

    var midpoint = (newy1 + newy2) / 2;
    var angle  = Math.tan(-yDelta / paddleWidth)

    Body.set(paddle, { "angle": angle, "position": {x: sceneWidth/2, y: midpoint}}, 0);
    y1 = newy1;
    y2 = newy2;
}

Events.on(engine, "beforeUpdate", function(event) {
    var d1 = 0, d2 = 0;
    // Check end-game condition
    if (potentialEndBody !== undefined) {
        var rd = potentialEndBody.circleRadius - ball.circleRadius;
        if (Math.abs(ball.position.x - potentialEndBody.position.x) < rd
        && Math.abs(ball.position.y - potentialEndBody.position.y) < rd) {
            if (potentialEndBody.label === victoryLabel) {
                console.log("😸");
            } else if (potentialEndBody.label === defeatLabel) {
                console.log("💥");
            }
        }
    }
    // Handle pressed keys
    if (leftUp && !leftDown) {
        d1 = moveDelta;
    }
    if (leftDown && !leftUp) {
        d1 = -moveDelta;
    }
    if (rightUp && !rightDown) {
        d2 = moveDelta;
    }
    if (rightDown && !rightUp) {
        d2 = -moveDelta;
    }
    if (d1 != 0 || d2 != 0) {
        move(d1, d2);
    }
});

Events.on(engine, 'collisionStart', function(event) {
    var pairs = event.pairs;
    // Collision has started.
    // When we collide with the hole, we want to track its reference to validate end-game condition
    // When we collide with the center of the hole, we adjust friction of the ball
    for (var i = 0, j = pairs.length; i != j; ++i) {
        var pair = pairs[i];
        // So far, the ball is consistently bodyA
        if (pair.bodyB === sensorNearVictory) {
            potentialEndBody = pair.bodyB;
        }
        else if (pair.bodyB === sensorVictory) {
            ball.friction = frictionAtHole;
        }
        else if (pair.bodyB === sensorNearX) {
            potentialEndBody = pair.bodyB;
        }
        else if (pair.bodyB === sensorX) {
            ball.friction = frictionAtHole;
        }
    }
});

Events.on(engine, 'collisionEnd', function(event) {
    var pairs = event.pairs;
    
    for (var i = 0, j = pairs.length; i != j; ++i) {
        var pair = pairs[i];

        if (pair.bodyB === sensorNearVictory) {
            potentialEndBody = undefined;
        }
        else if (pair.bodyB === sensorVictory) {
            ball.friction = friction;
        }
        else if (pair.bodyB === sensorNearX) {
            potentialEndBody = undefined;
        }
        else if (pair.bodyB === sensorX) {
            ball.friction = friction;
        }
    }
});

document.addEventListener('keydown', function(event) {
    switch (event.keyCode)
    {
        case 74: // j = right down
            rightDown = true;
            break;
        case 75: // k = right up
            rightUp = true;
            break;
        case 85: // u = alternative right up
            rightUp = true;
            break;
        case 83: // s = left down
            leftDown = true;
            break;
        case 68: // d = left up
            leftUp = true;
            break;
        case 87: // w = alternative left up
            leftUp = true;
            break;
    }
});

document.addEventListener('keyup', function(event) {
    switch (event.keyCode)
    {
        case 74: // j = right down
            rightDown = false;
            break;
        case 75: // k = right up
            rightUp = false;
            break;
        case 85: // u = alternative right up
            rightUp = false;
            break;
        case 83: // s = left down
            leftDown = false;
            break;
        case 68: // d = left up
            leftUp = false;
            break;
        case 87: // w = alternative left up
            leftUp = false;
            break;
    }
});
