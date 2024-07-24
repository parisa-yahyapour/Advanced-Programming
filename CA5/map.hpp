#ifndef _MAP_HPP_
#define _MAP_HPP_

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
using namespace std;
using namespace sf;

const string ADDRESS_START = "./Picture/Stars_Dimonds/star.png";
const string ADDRESS_DIMOND = "./Picture/Stars_Dimonds/dimond.png";
const string DIMOND = "^";
const string STAR = "*";
const int SCORE_STAR = 200;
const int SCORE_DIMOND = 400;

enum StausDirectionChanger
{
    OPEN,
    CLOSE
};

class MapObjects
{
private:
    Sprite object_sprite;

public:
    void draw_object(RenderWindow &window);
    void set_object_texture(Texture &object_texture);
    void set_object_position(Vector2f position);
    void set_object_scale(Vector2f scale_percentage);
    FloatRect get_global_bounds_object();
    Vector2f get_position_object();
};

class DirectionChanger : public MapObjects
{
    private:
    int pelan = 0;
    bool is_open = false;
    vector<Texture> direction_changer_texture;
    vector<string> create_direction_changer_texture_address();
    void load_textures_from_file(vector<string> address);
    public:
    DirectionChanger(Vector2f position)
    {
        load_textures_from_file(create_direction_changer_texture_address());
        set_object_position(position);
        set_object_texture(direction_changer_texture[CLOSE]);
        set_object_scale(Vector2f(1.2f,1.2f));
    };
    bool is_direction_changer_open();
    void open_direction_changer();
    void close_direction_changer();
};

class StarDimond : public MapObjects
{
    private:
    Texture texture;
    int score;
    public:
    StarDimond(Vector2f position, string type)
    {
        if (type == DIMOND)
        {
            texture.loadFromFile(ADDRESS_DIMOND);
            score = SCORE_DIMOND;
        }
        else
        {
            texture.loadFromFile(ADDRESS_START);
            score = SCORE_STAR;
        }
        set_object_texture(texture);
        set_object_position(position);
    };
    int get_score();
};

#endif