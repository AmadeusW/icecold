#ifndef GameState_h
#define GameState_h

struct GameState {
    enum GameMode {
        IDLE,
        RELEASING_BALL,
        PLAYER_CONTROL,
        BALL_OUT, // ball is out of the playfield, either through winning or incorrect target
        GAME_OVER_WON,
        GAME_OVER_LOST,
        _MAX_STATE
    }
    GameMode mode = IDLE;

    // Game state
    int balls;
    int level;
    int score;

    // Input values
    bool inputLeftUp;
    bool inputLeftDown;
    bool inputRightUp;
    bool inputRightDown;

    bool limitAngle;
    bool limitLeftUp;
    bool limitLeftDown;
    bool limitRightUp;
    bool limitRightDown;

    bool ballOnTarget;
    bool ballReady;

    // Configuration
    int speedDown = 30;
    int speedUp = 40;

    // Output
    bool motorLeftUp;
    bool motorLeftDown;
    bool motorRightUp;
    bool motorRightDown;

    void reset()
    {
        lives = 10;
        level = 1;
        score = 0;
        motorLeftUp = false;
        motorLeftDown = false;
        motorRightUp = false;
        motorRightDown = false;
    }
};

extern GameState gameState;
#endif