#include "map.hpp"
const int NUM_DIRECTION_CHANGER_TEXTURE = 2;

void MapObjects ::set_object_texture(Texture &object_texture)
{
    object_sprite.setTexture(object_texture);
}

void MapObjects ::draw_object(RenderWindow &window)
{
    window.draw(object_sprite);
}

void MapObjects ::set_object_position(Vector2f position)
{
    object_sprite.setPosition(position);
}

void MapObjects ::set_object_scale(Vector2f scale_percentage)
{
    object_sprite.setScale(scale_percentage);
}

FloatRect MapObjects ::get_global_bounds_object()
{
    return object_sprite.getGlobalBounds();
}

Vector2f MapObjects ::get_position_object()
{
    return object_sprite.getPosition();
}

vector<string> DirectionChanger ::create_direction_changer_texture_address()
{
    vector<string> address;
    string name = "./Picture/Grounds/directionchanger", file_type = ".png";
    for (int index_texture = 1; index_texture <= NUM_DIRECTION_CHANGER_TEXTURE; index_texture++)
    {
        string temp = name + to_string(index_texture) + file_type;
        address.push_back(temp);
    }
    return address;
}

void DirectionChanger ::load_textures_from_file(vector<string> address)
{
    for (int index_texture = 0; index_texture < address.size(); index_texture++)
    {
        Texture temp;
        if (!temp.loadFromFile(address[index_texture]))
        {
            cout << "error in opening pic direction changer\n";
        }
        direction_changer_texture.push_back(temp);
    }
}

bool DirectionChanger ::is_direction_changer_open()
{
    return is_open;
}

void DirectionChanger ::open_direction_changer()
{
    is_open = true;
    set_object_texture(direction_changer_texture[OPEN]);
}

void DirectionChanger ::close_direction_changer()
{
    is_open = false;
    set_object_texture(direction_changer_texture[CLOSE]);
}

int StarDimond ::get_score()
{
    return score;
}