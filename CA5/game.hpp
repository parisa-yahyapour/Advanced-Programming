#ifndef _GAME_HPP_
#define _GAME_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "map.hpp"
#include "creature.hpp"
using namespace std;
using namespace sf;
const string ADDRESS_FONT = "./Font/turtix.ttf";
const Vector2f POSITION_START_GAME = Vector2f(600,320);
const Vector2f POSITION_EXIT_GAME = Vector2f(600,470);
const Vector2f SPEED_CURSOR = Vector2f(0, 150);
const Vector2f POSITION_EXIT_OPTION = Vector2f(350, 450);
const Vector2f POSITION_START_OPTION = Vector2f(200, 300);
const Vector2f POSITION_GAME_NAME = Vector2f(250, 100);
const Vector2f POSITION_CURSOR = Vector2f(600, 320);
const int VERY_BIG_SIZE = 80;
const int BIG_SIZE = 60;
const int MEDIUM_SIZE = 40;
const int SMALL_SIZE = 30;
const int RADIUS_CURSOR = 20;
const int DIFFRENCE_SCORE_WITH_TURTLE = 100;
const int DIFFRENCE_LOSE_WINNER_WITH_TURTLE = 200;
enum Operation
{
    START_GAME,
    EXIT_GAME,
    LOSER,
    WINNER,
    COUNTINUE
};

class DataOutPut
{
private:
    int score = 0;
    int num_babies = 0;
    Font font;
    Text text_score;
    Text text_baby_turtles;
    Text sentence;

public:
    DataOutPut()
    {
        font.loadFromFile(ADDRESS_FONT);
        text_score.setFont(font);
        text_baby_turtles.setFont(font);
        sentence.setFont(font);
        text_score.setFillColor(Color ::White);
        text_baby_turtles.setFillColor(Color ::White);
        sentence.setFillColor(Color ::White);
        text_score.setCharacterSize(BIG_SIZE);
        text_baby_turtles.setCharacterSize(MEDIUM_SIZE);
        sentence.setCharacterSize(SMALL_SIZE);
        text_score.setString(to_string(score));
        text_baby_turtles.setString(to_string(num_babies));
        sentence.setString("Baby Turtles: ");
    }
    void increase_score(int offset);
    void increase_num_babies();
    void decrese_num_babies();
    void render_score(RenderWindow &window, Vector2f position_turtle);
    int get_num_left_babies();
    int get_score();
};

class Turtix
{
private:
    DataOutPut game_score;
    vector<BabyTurtle *> baby_turtles;
    vector<StarDimond *> stars_dimonds;
    vector<Texture> texture_map;
    vector<MapObjects> objects;
    vector<DirectionChanger *> direction_changers;
    vector<Enemy1 *> enemy_1;
    vector<Enemy2 *> enemy_2;
    MapObjects gate;
    Turtle turtle;
    Vector2f position_gate;
    int maximum_hight;
    vector<string> read_map_data_from_file(string file_addrees);
    void load_map_textures_from_file();
    void set_objects(vector<string> lines);
    bool check_intersection_with_ground(Creature creature);
    bool check_top_intersection(FloatRect turtle_bound, FloatRect object_bound);
    bool check_left_intersection(FloatRect turtle_bound, FloatRect object_bound);
    bool check_right_intersection(FloatRect turtle_bound, FloatRect object_bound);
    bool check_down_intersection(FloatRect turtle_bound, FloatRect object_bound);
    bool change_direction(Creature &creature);
    void delete_dead_enemy();
    void delete_used_star_dimonds(int index_star);
    bool is_turtle_alive();
    void handle_result(int status_game, Vector2f position_turtle, RenderWindow& window);
    void check_turtle_hight();

public:
    void render(RenderWindow &window);
    void prepare_map(string file_address);
    void prepare_turtle(Vector2f position);
    void process_events(RenderWindow &window);
    Vector2f get_position_gate();
    void check_turtle_intersection_with_babies();
    void move_free_baby_turtles();
    void put_dead_babies_in_cage();
    void check_intersection_with_direction_changer();
    void move_enemy();
    bool check_intersection_babies_with_enemies(BabyTurtle *baby);
    void check_turtle_intersection_with_enemy1();
    void check_turtle_intersection_with_enemy2();
    void check_turtle_intersection_with_stars_dimonds();
    void check_saved_baby_turtles();
    int check_winning_consitions();
    
};

class Menu
{
private:
    Font font_menu;
    Text start;
    Text exit;
    Text game_name;
    CircleShape cersor = CircleShape(RADIUS_CURSOR);
    Vector2f speed_cersor = SPEED_CURSOR;
    int check_operation();

public:
    Menu()
    {
        font_menu.loadFromFile(ADDRESS_FONT);
        start.setFont(font_menu);
        exit.setFont(font_menu);
        game_name.setFont(font_menu);
        start.setFillColor(Color ::White);
        exit.setFillColor(Color ::White);
        game_name.setFillColor(Color :: Red);
        start.setCharacterSize(BIG_SIZE);
        exit.setCharacterSize(BIG_SIZE);
        game_name.setCharacterSize(VERY_BIG_SIZE);
        start.setPosition(POSITION_START_OPTION);
        exit.setPosition(POSITION_EXIT_OPTION);
        game_name.setPosition(POSITION_GAME_NAME);
        start.setString("Start Game");
        exit.setString("Exit");
        game_name.setString("Turtix");
        cersor.setFillColor(Color ::Yellow);
        cersor.setPosition(POSITION_CURSOR);
    };
    void render_menu(RenderWindow &window);
    void move_cersor(string direction);
    int process_menu(RenderWindow &window);
};

class GameResult
{
    private:
    int status_game;
    int final_score;
    Text winner;
    Text loser;
    Text score;
    Font font_result;
    public:
    GameResult(int last_score, int status, Vector2f position_turtle)
    {
        font_result.loadFromFile(ADDRESS_FONT);
        final_score = last_score;
        status_game = status;
        winner.setFont(font_result);
        loser.setFont(font_result);
        score.setFont(font_result);
        winner.setFillColor(Color ::Green);
        loser.setFillColor(Color ::Red);
        score.setFillColor(Color :: White);
        score.setCharacterSize(BIG_SIZE);
        winner.setCharacterSize(VERY_BIG_SIZE);
        loser.setCharacterSize(VERY_BIG_SIZE);
        score.setPosition(position_turtle.x - DIFFRENCE_SCORE_WITH_TURTLE, position_turtle.y - DIFFRENCE_SCORE_WITH_TURTLE);
        loser.setPosition(position_turtle.x - DIFFRENCE_LOSE_WINNER_WITH_TURTLE, position_turtle.y - DIFFRENCE_LOSE_WINNER_WITH_TURTLE);
        winner.setPosition(position_turtle.x - DIFFRENCE_LOSE_WINNER_WITH_TURTLE, position_turtle.y - DIFFRENCE_LOSE_WINNER_WITH_TURTLE);
        winner.setString("You Win!");
        loser.setString("You Lost!");
        score.setString(to_string(final_score));
    }
    void render_result(RenderWindow &window);
};

#endif