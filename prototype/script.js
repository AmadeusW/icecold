// Game constants
const sceneWidth = 600;
const sceneHeight = 800;
const paddleWidth = sceneWidth * 1.2;
const paddleStart = 750;
const wallWidth = 50;
const moveDelta = 3;
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
        wireframes: false,
        //showVelocity: true,
        //showCollisions: true,
    },
    engine: engine
});
//Matter.Resolver._restingThresh = 0.1;

var ballOuter = Bodies.circle(sceneWidth/2, paddleStart - 50, 12);
var ballInner = Bodies.circle(sceneWidth/2, paddleStart - 50, 2);
var ball = Body.create({parts: [ballOuter, ballInner], frictionAir: 0, friction: friction, restitution: 0.2 });

var paddle = Bodies.rectangle(sceneWidth/2, paddleStart, paddleWidth, 10, { isStatic: true, friction: 0 });

var ground = Bodies.rectangle(sceneWidth/2, sceneHeight, sceneWidth, 20, { isStatic: true });
var wall1 = Bodies.rectangle(-wallWidth/2, sceneHeight/2, wallWidth, sceneHeight, { isStatic: true });
var wall2 = Bodies.rectangle(sceneWidth + wallWidth/2, sceneHeight/2, wallWidth, sceneHeight, { isStatic: true });

var background = Bodies.rectangle(0, 0, sceneWidth, sceneHeight, {
    isSensor: true,
    isStatic: true,
    render: {
        strokeStyle: '#ffffff',
        sprite: {
            texture: './holes.jpg',
            xOffset: -0.5,
            yOffset: -0.5,
            xScale: 0.2923,
            yScale: 0.2649,
        }
    }
    });

World.add(engine.world, [background, ball, paddle, ground, wall1, wall2]);

var victorySpots = [[303,567], [472,547], [123,506], [383,453], [219,373], [453,286], [297,244], [127,197], [379,132], [222,91]];
for (var i = 0; i < victorySpots.length; i++) {
    var spot = victorySpots[i];
    var sensorVictory = Bodies.circle(spot[0], spot[1], 4, { isSensor: true, isStatic: true, label: victoryTag });
    var sensorNearVictory = Bodies.circle(spot[0], spot[1], 14, { isSensor: true, isStatic: true, label: nearTag, render: {fillStyle: '#228822', strokeStyle: '#66cc66'} });
    World.add(engine.world, [sensorVictory, sensorNearVictory]);
}

var lossSpots = [[497,605], [533,544], [549,511], [547,463], [491,503], [426,520], [376,504], [371,548], [303,521], [237,545], [179,548], [107,565], [64,523], [40,471], [161,478], [123,428], [171,391], [208,421], [247,443], [304,467], [275,415], [315,373], [349,396], [394,398], [433,452], [493,390], [21,294], [52,337], [80,375], [125,356], [173,334], [207,305], [262,273], [301,312], [334,278], [384,288], [417,317], [449,349], [515,322], [526,285], [544,249], [490,249], [450,220], [376,241], [89,102], [128,143], [81,156], [62,199], [23,217], [81,239], [132,255], [173,239], [226,246], [187,195], [261,210], [294,177], [330,212], [381,185], [415,163], [443,133], [525,119], [413,100], [381,71], [350,104], [319,136], [289,93], [257,119], [226,150], [196,121], [161,90], [190,62], [254,62]];
for (var i = 0; i < lossSpots.length; i++) {
    var spot = lossSpots[i];
    var sensorX = Bodies.circle(spot[0], spot[1], 6, { isSensor: true, isStatic: true, label: lossTag });
    var sensorNearX = Bodies.circle(spot[0], spot[1], 16, { isSensor: true, isStatic: true, label: nearTag, render: {fillStyle: '#882222', strokeStyle: '#cc6666'}  });
    World.add(engine.world, [sensorX, sensorNearX]);
}

ball.density = 0.05; // default is 0.001
engine.world.gravity.scale = 0.003; // default is 0.001

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
