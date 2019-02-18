// Game constants
const sceneWidth = 600;
const sceneHeight = 800;
const paddleWidth = sceneWidth * 1.2;
const paddleStart = 750;
const wallWidth = 50;
const moveDelta = 4;
const maxYDelta = 150;
const friction = 0;
const victoryTag = "win";
const lossTag = "loss";
const nearTag = "near";

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
        //wireframes: false,
        showVelocity: true,
        showCollisions: true,
    },
    engine: engine
});
//Matter.Resolver._restingThresh = 0.1;

var ballOuter = Bodies.circle(sceneWidth/2, paddleStart - 50, 15);
var ballInner = Bodies.circle(sceneWidth/2, paddleStart - 50, 3);
var ball = Body.create({parts: [ballOuter, ballInner], frictionAir: 0, friction: friction, restitution: 0.2 });
var paddle = Bodies.rectangle(sceneWidth/2, paddleStart, paddleWidth, 10, { isStatic: true, friction: 0 });
var ground = Bodies.rectangle(sceneWidth/2, sceneHeight, sceneWidth, 20, { isStatic: true });
var wall1 = Bodies.rectangle(-wallWidth/2, sceneHeight/2, wallWidth, sceneHeight, { isStatic: true });
var wall2 = Bodies.rectangle(sceneWidth + wallWidth/2, sceneHeight/2, wallWidth, sceneHeight, { isStatic: true });
World.add(engine.world, [ball, paddle, ground, wall1, wall2]);

var victorySpots = [[200, 200], [100, 100], [300, 100]];
for (var i = 0; i < victorySpots.length; i++) {
    var spot = victorySpots[i];
    var sensorVictory = Bodies.circle(spot[0], spot[1], 3, { isSensor: true, isStatic: true, label: victoryTag });
    var sensorNearVictory = Bodies.circle(spot[0], spot[1], 17, { isSensor: true, isStatic: true, label: nearTag });
    World.add(engine.world, [sensorVictory, sensorNearVictory]);
}

var lossSpots = [[59,518], [143,558], [268,533], [443,493], [517,575], [557,429], [460,350], [254,396], [192,350], [91,396], [55,240], [106,140], [160,182], [315,193], [372,117], [485,172], [562,89], [66,30]];
for (var i = 0; i < lossSpots.length; i++) {
    var spot = lossSpots[i];
    var sensorX = Bodies.circle(spot[0], spot[1], 7, { isSensor: true, isStatic: true, label: lossTag });
    var sensorNearX = Bodies.circle(spot[0], spot[1], 20, { isSensor: true, isStatic: true, label: nearTag });
    World.add(engine.world, [sensorX, sensorNearX]);
}

ball.density = 0.05; // default is 0.001
engine.world.gravity.scale = 0.004; // default is 0.001

// run the engine
Engine.run(engine);

// run the renderer
Render.run(render);

var y1 = paddleStart;
var y2 = paddleStart;
var leftUp = false, leftDown = false, rightUp = false, rightDown = false;
var wins = 0;
var losses = 0;

var updateUi = function() {
    document.getElementById("winsText").innerText = wins;
    document.getElementById("lossesText").innerText = losses;
}

var restart = function() {
    y1 = paddleStart;
    y2 = paddleStart;
    Body.set(paddle, { "angle": 0, "position": {x: sceneWidth/2, y: paddleStart}});
    Body.set(ball, { "position": {x: sceneWidth/2, y: paddleStart - 50}});
}

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
        // Add a random element to make it harder to just go up
        d1 *= Math.random() * 0.4 + 0.8;
        d2 *= Math.random() * 0.4 + 0.8;
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
        if (pair.bodyA !== ballInner) {
            // We're only interested in collisions of the inner part.
            // So far, the ball is consistently the bodyA
            continue;
        }
        if (pair.bodyB.label === nearTag) {
        }
        else if (pair.bodyB.label === victoryTag) {
            wins++;
            updateUi();
            restart();
        }
        else if (pair.bodyB.label === lossTag) {
            losses++;
            updateUi();
            restart();
        }
    }
});

Events.on(engine, 'collisionEnd', function(event) {
    var pairs = event.pairs;

    for (var i = 0, j = pairs.length; i != j; ++i) {
        var pair = pairs[i];

        if (pair.bodyB.label === nearTag) {
        }
    }
});

document.addEventListener('keydown', function(event) {
    switch (event.keyCode)
    {
        case 74: // j = right down
            rightDown = true;
            break;
        case 40: // arrow down = right down
            rightDown = true;
            break;
        case 75: // k = right up
            rightUp = true;
            break;
        case 85: // u = alternative right up
            rightUp = true;
            break;
        case 38: // arrow up = right up
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
        case 40: // arrow down = right down
            rightDown = false;
            break;
        case 75: // k = right up
            rightUp = false;
            break;
        case 85: // u = alternative right up
            rightUp = false;
            break;
        case 38: // arrow up = right up
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

// World building:
var clicked = [];
document.getElementById("canvas").addEventListener('mousedown', function(event) {
    clicked.push([event.clientX - 8, event.clientY - 8]);
    console.log("[[" + clicked.join("], [") + "]]" );
});
