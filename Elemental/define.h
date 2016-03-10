#ifndef DEFINE_H
#define DEFINE_H
//colors
#define BLACK al_map_rgb(0, 0, 0)
#define WHITE al_map_rgb(255,255,255)
#define MASK al_map_rgb(255,0,255)
#define RED al_map_rgb(255,0,0)
#define GREEN al_map_rgb(0,255,0)
#define BLUE al_map_rgb(0,0,255)
#define DEGREE_90  1.5707963268
#define DEGREE_180  3.1415926536
#define DEGREE_270 4.7123889804
const int SCROLL_SPEED = 18;
const int DEFAULT_SCROLL_DELAY = 100;
const int TILES_IN_ROW = 9;
const int PLAYER_X = 256;
const int PLAYER_Y = 64;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;
const float PLAYER_SPEED = 2.0;
const int MOVE_X = 0;
const int MOVE_Y = 0;
const int ATTACK_X = 384;
const int ATTACK_Y = 0;
const int IDLE_X = 1152;
const int IDLE_Y = 256;
const int DEAD_X = 768;
const int DEAD_Y = 0;
const int PRIMARY_SKILL_X = 0;
const int SECONDARY_SKILL_X = 384;
const int PRIMARY_SKILL_Y = 256;
const int SECONDARY_SKILL_Y = 256;
const int ULTIMATE_SKILL_X = 768;
const int ULTIMATE_SKILL_Y = 256;
const int SPRITESHEET_Y = 512;
const int IDLE_WAIT = 200; //number of ticks before animation fires
const int MAP_X =100; //X size of map
const int MAP_Y = 100;//Y size of map
const int TILE_SIZE = 96;// size of Tile in pixels
//const int PLAYER_SIZE = 64;
const int MAX_SPRITES = 100; //maximum amount of sprites
const int MAX_BUTTONS=10;
const int DOOR_HEIGHT = 8;
const int DOOR_WIDTH = TILE_SIZE;

enum BUTTONS{ BUTTON_PRIMARY_SKILL, BUTTON_SECONDARY_SKILL, BUTTON_ULTIMATE_SKILL,BUTTON_SCROLL_NORTH,BUTTON_SCROLL_WEST,BUTTON_SCROLL_EAST,BUTTON_SCROLL_SOUTH};
enum FILE_POSITON{TILE_FILE_Y=TILE_SIZE*3};
enum DIRECTION{ NORTH, WEST, EAST, SOUTH, MAX_DIRECTION };

enum KEYS { UP, DOWN, LEFT, RIGHT,OPEN };

enum TILE_TYPE{ EMPTY_TILE, WALL_TILE, FLOOR_TILE, WATER_TILE, LAVA_TILE, MAX_TILE_TYPES };//basic type of tile

enum WALL_TYPE  { EMPTY_TYPE, WALL_0, WALL_1, WALL_2, WALL_3, WALL_4, WALL_5, WALL_6, WALL_7, WALL_8 };
enum FLOOR_TYPE {
	FLOOR_0, FLOOR_1, FLOOR_2, FLOOR_3, FLOOR_4, FLOOR_5, FLOOR_6, FLOOR_7, FLOOR_8 }; //exact texture of .tile
enum WATER_TYPE{ WATER_O, WATER_1 };
enum LAVA_TYPE{LAVA_0, LAVA_1};

enum TILE_OBJECT{ EMPTY_OBJECT, DOOR, TRAP, ENTRANCE, EXIT, DECORATION, LEVER, TELEPORT,MAX_TILE_OBJECT }; //basic type of object 
enum ID_OBJECT{	EMPTY_ID, DOOR_0, DOOR_1, DOOR_2, DOOR_3, DOOR_4, TRAP_0, TRAP_1, TRAP_2, TRAP_3, TRAP_4,//exact texture of .object
				ENTRANCE_TILE, EXIT_TILE, DECORATION_0, DECORATION_1, DECORATION_2, DECORATION_3,
				DECORATION_4, LEVER_0, LEVER_01, LEVER_02, LEVER_03, LEVER_04, TELEPORT_01, TELEPORT_02,
				TELEPORT_03, TELEPORT_04,MAX_ID_OBJECT };
enum DOOR_STATUS{ CLOSED_DOOR, LOCKED_BRONZE_DOOR, LOCKED_SILVER_DOOR, LOCKED_GOLD_DOOR, BLOCKED_DOOR, LEVER_DOOR_0, LEVER_DOOR_1, LEVER_DOOR_2, LEVER_DOOR_3, LEVER_DOOR_4, OPENING_DOOR, CLOSING_DOOR, OPEN_DOOR, MAX_DOOR_STATUS };// obje
enum SPRITE_TYPE{ CRYSTAL,WEREBULL,AMFIR,THORWAL,ENEMY_0, ENEMY_1,ENEMY_2, ENEMY_3, ENEMY_4, ENEMY_5, ENEMY_6, ENEMY_7};
enum TILE_VARS{TILE,TILE_ID,TILE_STATE,OBJECT,OBJECT_ID,STATUS,FRAME_COUNT,FRAME_DELAY,ANIMATION_DIRECTION,POS_X,POS_Y, MAX_TILE_VARS};
enum EDITOR{ CLEAR_TILE, CLEAR_OBJECT, CREATE_FLOOR, CREATE_WALL, CREATE_DOOR, CREATE_SPRITE_0, CREATE_SPRITE_1, CREATE_SPRITE_2, CREATE_SPRITE_3, CREATE_SPRITE_4,MAX_KEYS };
enum SPRITE_STATUS{ SPRITE_MOVE, SPRITE_ATTACK, SPRITE_DEAD, SPRITE_HURT, SPRITE_DYING, SPRITE_PRIMARY_SKILL,SPRITE_SECONDARY_SKILL,SPRITE_ULTIMATE_SKILL,SPRITE_IDLE,SPRITE_NOT_ACTIVE, MAX_SPRITE_STATUS };
#endif
