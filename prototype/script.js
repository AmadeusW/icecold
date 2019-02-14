// module aliases
var Engine = Matter.Engine,
    Render = Matter.Render,
    World = Matter.World,
    Bodies = Matter.Bodies;

// create an engine
var engine = Engine.create();

// create a renderer
var render = Render.create({
    canvas: document.getElementById('canvas'),
    options: {
        width: 400,
        height: 800,
    },
    engine: engine
});

// create two boxes and a ground
var ball = Bodies.circle(200, 200, 20, 80);
var paddle = Bodies.rectangle(200, 700, 500, 30, { isStatic: true });
var ground = Bodies.rectangle(200, 800, 400, 20, { isStatic: true });
var wall1 = Bodies.rectangle(0, 400, 1, 800, { isStatic: true });
var wall2 = Bodies.rectangle(400, 400, 1, 800, { isStatic: true });

// add all of the bodies to the world
World.add(engine.world, [ball, paddle, ground, wall1, wall2]);

// run the engine
Engine.run(engine);

// run the renderer
Render.run(render);

var angle = 0;
var angleDelta = 0.1;
var maxAngle = 10;
document.addEventListener('keydown', function(event) {
    switch (event.keyCode)
    {
        case 74: // j = right down
            //Matter.Body.set(paddle, "position", {x: 200, y: 300});
            if (Math.abs(angle) >= maxAngle)
                break;
            angle -= angleDelta;
            Matter.Body.set(paddle, "angle", angle);
            break;
        case 75: // k = right up
            if (Math.abs(angle) >= maxAngle)
                break;
            angle += angleDelta;
            Matter.Body.set(paddle, "angle", angle);
            break;
        case 85: // u = alternative right up
            if (Math.abs(angle) >= maxAngle)
                break;
            angle += angleDelta;
            Matter.Body.set(paddle, "angle", angle);
            break;
        case 83: // s = left down
            if (Math.abs(angle) >= maxAngle)
                break;
            angle += angleDelta;
            Matter.Body.set(paddle, "angle", angle);
            break;
        case 68: // d = left up
            if (Math.abs(angle) >= maxAngle)
                break;
            angle -= angleDelta;
            Matter.Body.set(paddle, "angle", angle);
            break;
        case 87: // w = alternative left up
            if (Math.abs(angle) >= maxAngle)
                break;
            angle -= angleDelta;
            Matter.Body.set(paddle, "angle", angle);
            break;
    }
});
