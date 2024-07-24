#ifndef _CREATURE_HPP_
#define _CREATURE_HPP_

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
using namespace sf;
const string R_DIRECTION = "R";
const string L_DIRECTION = "L";
const string NO_DIRECTION = "N";
const string ADDRESS_DEAD_RIGHT_ENEMY1 = "./Picture/Enemy/enemy_1_d_right.png";
const string ADDRESS_DEAD_LEFT_ENEMY1 = "./Picture/Enemy/enemy_1_d_left.png";
const string ADDRESS_DEAD_RIGHT_ENEMY2 = "./Picture/Enemy/enemy_2_d_right.png";
const string ADDRESS_DEAD_LEFT_ENEMY2 = "./Picture/Enemy/enemy_2_d_left.png";
const string ADDRESS_HEART = "./Picture/Turtle/heart.png";
const int MAXIMUM_HEART_TURTLE = 3;
const int MAXIMUM_HEART_ENEMY = 2;

class Creature
{
private:
    vector<Texture> creature_left_textures;
    vector<Texture> creature_right_textures;
    Sprite creature_sprite;
    Vector2f creature_velocity;
    int pelan_left = 0;
    int pelan_right = 0;
    string last_direction = L_DIRECTION;
    int calculate_pelan_number(int current_pelan);

public:
    void set_velocity(Vector2f new_velocity);
    void draw_ceature(RenderWindow &window);
    void load_texture_from_file(vector<string> address_left, vector<string> address_right);
    void set_creature_position(Vector2f position);
    void set_creature_texture(string current_direction);
    void move_creature(Vector2f next_position);
    Vector2f get_creature_position();
    void set_pelan_left();
    void set_pelan_right();
    void set_direction(string direction);
    bool check_last_direction(string direction);
    void set_pelan_to_zero(string direction);
    FloatRect get_global_bounds();
    void get_next_possible_position(Vector2f offset);
    void set_specific_texture(Texture &wanted_texture);
    Vector2f get_creature_velocity();
    void set_creatue_scale(Vector2f scale);
    int get_pelan(string direction);
};

class Turtle : public Creature
{
private:
    int num_hearts = MAXIMUM_HEART_TURTLE;
    Texture heart_texture;
    Sprite heart;

public:
    vector<string> create_address_vector_left();
    vector<string> create_address_vector_right();
    Turtle()
    {
        heart_texture.loadFromFile(ADDRESS_HEART);
        heart.setTexture(heart_texture);
    };
    void render_heart(RenderWindow &window);
    void decrease_num_turtle_hearts();
    bool is_alive();
};

class BabyTurtle : public Creature
{
private:
    Texture cage;
    bool is_free = false;
    Vector2f first_position;

public:
    vector<string> create_address_vector_left();
    vector<string> create_address_vector_right();
    bool is_baby_in_cage();
    void make_baby_free();
    BabyTurtle(Vector2f position)
    {
        first_position = position;
        load_texture_from_file(create_address_vector_left(), create_address_vector_right());
        cage.loadFromFile("./Picture/Baby/babycage.png");
        set_specific_texture(cage);
        set_creature_position(position);
    };
    void move_baby(float velocity_y);
    bool is_baby_dead(int maxi_hight);
    void put_baby_cage();
    void change_baby_direction();
};

class Enemy1 : public Creature
{
private:
    int num_heart = MAXIMUM_HEART_ENEMY;
    bool is_near_to_death = false;
    bool is_dead = false;
    Texture dead_right;
    Texture dead_left;
    vector<string> create_address_vector_left();
    vector<string> create_address_vector_right();
    void set_dead_texture();

public:
    Enemy1(Vector2f position)
    {
        load_texture_from_file(create_address_vector_left(), create_address_vector_right());
        dead_right.loadFromFile(ADDRESS_DEAD_RIGHT_ENEMY1);
        dead_left.loadFromFile(ADDRESS_DEAD_LEFT_ENEMY1);
        set_creature_texture(L_DIRECTION);
        set_creature_position(position);
        set_creatue_scale(Vector2f(1.05f, 1.05f));
        set_direction(L_DIRECTION);
    };
    void move_enemy_type_1();
    void change_enemy1_direction();
    void decrease_enemy_heart();
    bool is_enemy_dead();
};

class Enemy2 : public Creature
{
private:
    int num_heart = MAXIMUM_HEART_ENEMY;
    int num_steps = 0;
    bool is_near_to_death = false;
    bool is_dead = false;
    bool can_be_killed = true;
    vector<string> create_address_vector_left();
    vector<string> create_address_vector_right();
    Texture dead_right;
    Texture dead_left;
    void set_dead_texture();
    void put_enemy2_in_defeat_mode(string direction);

public:
    Enemy2(Vector2f position)
    {
        load_texture_from_file(create_address_vector_left(), create_address_vector_right());
        dead_right.loadFromFile(ADDRESS_DEAD_RIGHT_ENEMY2);
        dead_left.loadFromFile(ADDRESS_DEAD_LEFT_ENEMY2);
        set_creature_texture(L_DIRECTION);
        set_creature_position(position);
        set_creatue_scale(Vector2f(1.05f, 1.05f));
        set_direction(L_DIRECTION);
    };
    void move_enemy_type_2();
    void change_enemy2_direction();
    void decrease_enemy_heart();
    bool is_enemy_dead();
    bool is_possible_to_kill();
};

#endif