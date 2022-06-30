#ifndef DEFINES_H
#define DEFINES_H
//#define NDEBUG //Uncomment to deactivate assert

#define MAX_FPS (60)


//CUSTOM LEVEL SCREEN PROPERTIES
#define CUSTOMLEVEL_BUTTON_WIDTH 100
#define CUSTOMLEVEL_BUTTON_HEIGHT 40
#define MIN_BLOCK_DIMENSION 40

//powerup properties
#define POWERUP_FALL_SPEED 5
#define POWER_UP_SIZE 50

//quitscreen properties
#define QUITSCREEN_BUTTON_WIDTH 400
#define QUITSCREEN_BUTTON_HEIGHT 200
#define QUITSCREEN_MARGIN 50

//pausescreen properties
#define PAUSESCREEN_BUTTON_WIDTH 400
#define PAUSESCREEN_BUTTON_HEIGHT 200
#define PAUSESCREEN_MARGIN 50

//winscreen properties
#define WINSCREEN_BUTTON_WIDTH 400
#define WINSCREEN_BUTTON_HEIGHT 200
#define WINSCREEN_MARGIN 50

//lostscreen properties
#define LOSTSCREEN_BUTTON_WIDTH 400
#define LOSTSCREEN_BUTTON_HEIGHT 200
#define LOSTSCREEN_MARGIN 50

//Ball properties
#define BALL_RADIUS 20
#define BALL_DAMAMGE 40
#define BALL_SPEED_CHANGE 150
#define BALL_MIN_SPEED 200
#define BALL_DEFAULT_SPEED 500
#define FIREBALL_DAMAMGE 1000
#define CRAZYBALL_DAMAMGE 40


//level properties
#define LEVEL_WIDTH 1500
#define TOP_MARGIN 150
#define DEFAULT_INITIAL_LIVES 5
#define SCORE_TEXT_POS 10,50
#define BLOCK_BREAK_SCORE 30
#define BLOCK_COLLIDE_SCORE 10
#define LIVES_SIZE 60

//planc properties
#define PLANC_DIST_FROM_BOTTOM 10
#define PLANC_HEIGHT 50
#define DEFAULT_PLANC_WIDTH 400
#define MAX_PLANC_WIDTH 600
#define MIN_PLANC_WIDTH 200
#define PLANC_WIDTH_CHANGE 100
#define MOMENTUM_TIME 10
#define DEFAULT_PLANC_SPEED 1000
#define MAX_PLANC_SPEED 2000
#define MIN_PLANC_SPEED 500
#define PLANC_SPEED_CHANGE 50
#define MOMENTUM_RETARDATION 10

//file properties
#define LEVEL_INFO_FILE "level_info.dat"
#define PLAYER_INFO_FILE "player_info.dat"
#define MAX_USERNAME_LENGTH 10

//button properies
#define BUTTON_BORDER_THICKNESS (5)
#define DEFAULT_BUTTON_IDLE_COLOR 51, 51, 255, 255
#define DEFAULT_BUTTON_HOVER_COLOR 102, 102, 255, 255
#define DEFAULT_BUTTON_CLICKED_COLOR 102, 178, 255, 255
#define DEFAULT_BUTTON_BORDER_COLOR 32, 32, 32, 255

//textbox properties
#define TEXTBOX_HEIGHT 50
#define TEXTBOX_TEXT_COLOR 0, 0, 0, 255
#define TEXTBOX_BACKGROUND_COLOR 255, 255, 255, 255
#define TEXTBOX_UNSELECTED_BORDER_COLOR 32, 32, 32, 255
#define TEXTBOX_SELECTED_BORDER_COLOR 0, 0, 150, 255
#define TEXTBOX_HOVER_BORDER_COLOR 255, 0, 0, 255

//leaderboard properties
#define MAX_LEADERS 5
#define LEADERBORAD_CHAR_SIZE 40
#define LEADERBOARD_HEADER_COLOR 80, 203, 147, 255
#define LEADERBOARD_BODY_COLOR 0, 0, 0, 200
#define LEADERBOARD_WIDTH 500
#define LEADERBOARD_ROW_HEIGHT 50

//block properties
#define BLOCK1_HEALTH 10
#define BLOCK2_HEALTH 20
#define BLOCK3_HEALTH 50
#define BLOCK4_HEALTH 20
#define BLOCK1_POWERUP_PROB 0
#define BLOCK2_POWERUP_PROB 10
#define BLOCK3_POWERUP_PROB 20
#define BLOCK4_POWERUP_PROB 30
#define POWERUPMARKERSIZE 40

//level screen properties
#define GRID_ROWS 4
#define GRID_COLS 9
#define LEVEL_MARGIN 30
#define LEVEL_DELETE_BUTTON_HEIGHT 30

//blockStyle
enum class BlockStyle
{
    Style1,
    Style2,
    Style3,
    Style4
};
//planc styles
enum class PlancStyle
{
    Style1,
    Style2
};
//Use for ImageHolder
enum class ImageID
{
    tempImage1,
    tempImage2
};
//Use for TextureHolder
enum class TextureID
{
    Logo,
    MenuBackground,
    CloseButton,
    Planc1,
    Planc2,
    Planc3,
    Planc4,
    Planc5,
    Block1,
    Block2,
    Block3,
    Block4,
    SoundOn,
    SoundOff,
    PageButton,
    PageButtonDeactivated,
    LevelDeleteButton,
    Ball,
    FireBall,
    CrazyBall,
    Wall,
    LevelBackground,
    Lives,
    FastPlancPowerUp,
    SlowPlancPowerUp,
    LongPlancPowerUp,
    ShortPlancPowerUp,
    MomentumPowerUp,
    BlockHasPowerUp
};
//Use for FontHolder
enum class FontID
{
    TextFont,
    ButtonFont,
    tempFont1,
    tempFont2
};
//Use for SoundHolder
enum class SoundID
{
    TextboxType,
    TextboxError,
    ButtonClicked,
    ButtonHoverOver,
    BallBounce,
    LiveLost,
    NewBall
};
//Use for MusicHolder
enum class MusicID
{
    tempMusic1
};

enum class PowerUp
{
    NoPowerUp,
    Momentum,
    IncreasePlancLength,
    DecreadePlancLength,
    IncreasePlancSpeed,
    DecreasePlancSpeed,
    TenBalls,
    TwoBalls,
    ExtraLife,
    SlowDownBalls,
    SpeedUpBalls,
    FireBall,
    CrazyBall
};
#endif