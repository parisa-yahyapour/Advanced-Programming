#include "creature.hpp"
const int NUM_TURTLE_TEXTURE = 4;
const int NUM_BABY_TEXTURE = 4;
const Vector2f BABY_VELOCITY_LEFT(-5, 0);
const Vector2f BABY_VELOCITY_RIGHT(5, 0);
const int NUM_ENEMY1_TEXTURE = 1;
const int NUM_ENEMY2_TEXTURE = 5;
const float LEFT_VELOCITY_ENEMY = -5;
const float RIGHT_VELOCITY_ENEMY = 5;
const int DIFFRENCE_TURTLE_POSRIOTN_WITH_WINDOW_X = 350;
const int DIFFRENCE_TURTLE_POSRIOTN_WITH_WINDOW_Y = 350;
const int LENGTH_HEART = 50;
const int NUM_PELANS_FOR_CHANGE_TEXTURE = 20;

void Creature ::load_texture_from_file(vector<string> address_left, vector<string> address_right)
{
    for (int index_address_left = 0; index_address_left < address_left.size(); index_address_left++)
    {
        Texture temp;
        temp.loadFromFile(address_left[index_address_left]);
        creature_left_textures.push_back(temp);
    }
    for (int index_address_right = 0; index_address_right < address_right.size(); index_address_right++)
    {
        Texture temp;
        temp.loadFromFile(address_right[index_address_right]);
        creature_right_textures.push_back(temp);
    }
}

vector<string> Turtle ::create_address_vector_left()
{
    vector<string> address;
    string temp = "./Picture/Turtle/";
    string file_type = ".png";
    for (int index_turtle = 1; index_turtle <= NUM_TURTLE_TEXTURE; index_turtle++)
    {
        address.push_back(temp + to_string(index_turtle) + file_type);
    }
    return address;
}

vector<string> Turtle ::create_address_vector_right()
{
    vector<string> address;
    string temp = "./Picture/Turtle/R";
    string file_type = ".png";
    for (int index_turtle = 1; index_turtle <= NUM_TURTLE_TEXTURE; index_turtle++)
    {
        address.push_back(temp + to_string(index_turtle) + file_type);
    }
    return address;
}

void Creature ::set_creature_position(Vector2f position)
{
    creature_sprite.setPosition(position);
}

void Creature ::set_creature_texture(string current_direction)
{
    if (current_direction == L_DIRECTION)
    {
        creature_sprite.setTexture(creature_left_textures[pelan_left]);
        creature_sprite.setScale(0.7f, 0.7f);
        set_pelan_to_zero(R_DIRECTION);
    }
    else
    {
        creature_sprite.setTexture(creature_right_textures[pelan_right]);
        creature_sprite.setScale(0.7f, 0.7f);
        set_pelan_to_zero(L_DIRECTION);
    }
}

void Creature ::set_pelan_to_zero(string direction)
{
    if (direction == R_DIRECTION)
    {
        pelan_right = 0;
    }
    else
    {
        pelan_left = 0;
    }
}

void Creature ::draw_ceature(RenderWindow &window)
{
    window.draw(creature_sprite);
}

void Creature ::move_creature(Vector2f next_position)
{
    creature_sprite.move(next_position);
}

void Creature ::get_next_possible_position(Vector2f offset)
{
    creature_sprite.setPosition(creature_sprite.getPosition() + offset);
}

Vector2f Creature ::get_creature_position()
{
    return creature_sprite.getPosition();
}

int Creature ::calculate_pelan_number(int current_pelan)
{
    return current_pelan % creature_left_textures.size();
}

void Creature ::set_pelan_left()
{
    pelan_left = calculate_pelan_number(pelan_left + 1);
}

void Creature ::set_pelan_right()
{
    pelan_right = calculate_pelan_number(pelan_right + 1);
}

void Creature ::set_direction(string direction)
{
    last_direction = direction;
}

bool Creature ::check_last_direction(string current_direction)
{
    return (current_direction == last_direction);
}

FloatRect Creature::get_global_bounds()
{
    return creature_sprite.getGlobalBounds();
}

void Creature ::set_velocity(Vector2f new_velocity)
{
    creature_velocity = new_velocity;
}

vector<string> BabyTurtle ::create_address_vector_left()
{
    vector<string> address;
    string temp = "./Picture/Baby/babyleft";
    string file_type = ".png";
    for (int index_turtle = 1; index_turtle <= NUM_BABY_TEXTURE; index_turtle++)
    {
        address.push_back(temp + to_string(index_turtle) + file_type);
    }
    return address;
}

vector<string> BabyTurtle ::create_address_vector_right()
{
    vector<string> address;
    string temp = "./Picture/Baby/babyright";
    string file_type = ".png";
    for (int index_turtle = 1; index_turtle <= NUM_BABY_TEXTURE; index_turtle++)
    {
        address.push_back(temp + to_string(index_turtle) + file_type);
    }
    return address;
}

void Creature ::set_specific_texture(Texture &wanted_texture)
{
    creature_sprite.setTexture(wanted_texture);
    creature_sprite.setScale(0.7f, 0.7f);
}

bool BabyTurtle ::is_baby_in_cage()
{
    return !is_free;
}

void BabyTurtle ::make_baby_free()
{
    is_free = true;
    set_velocity(BABY_VELOCITY_LEFT);
    set_creature_texture(L_DIRECTION);
}

Vector2f Creature ::get_creature_velocity()
{
    return creature_velocity;
}

void BabyTurtle ::move_baby(float velocity_y)
{
    Vector2f current_position = get_creature_position();
    current_position.y += velocity_y;
    if (check_last_direction(L_DIRECTION))
    {
        current_position.x += BABY_VELOCITY_LEFT.x;
        set_pelan_left();
        set_creature_texture(L_DIRECTION);
    }
    else
    {
        current_position.x += BABY_VELOCITY_RIGHT.x;
        set_pelan_right();
        set_creature_texture(R_DIRECTION);
    }
    set_creature_position(current_position);
}

bool BabyTurtle ::is_baby_dead(int max_hight)
{
    return get_creature_position().y > max_hight;
}

void BabyTurtle ::put_baby_cage()
{
    set_creature_position(first_position);
    set_specific_texture(cage);
    set_direction(L_DIRECTION);
    is_free = false;
}

void BabyTurtle ::change_baby_direction()
{
    if (check_last_direction(L_DIRECTION))
    {
        set_direction(R_DIRECTION);
        set_creature_texture(R_DIRECTION);
        set_velocity(BABY_VELOCITY_RIGHT);
    }
    else if (check_last_direction(R_DIRECTION))
    {
        set_direction(L_DIRECTION);
        set_creature_texture(L_DIRECTION);
        set_velocity(BABY_VELOCITY_LEFT);
    }
}

void Enemy1 ::change_enemy1_direction()
{
    if (check_last_direction(L_DIRECTION))
    {
        set_direction(R_DIRECTION);
        set_creature_texture(R_DIRECTION);
        set_velocity(Vector2f(RIGHT_VELOCITY_ENEMY, 0));
    }
    else if (check_last_direction(R_DIRECTION))
    {
        set_direction(L_DIRECTION);
        set_creature_texture(L_DIRECTION);
        set_velocity(Vector2f(LEFT_VELOCITY_ENEMY, 0));
    }
}

void Enemy2 ::change_enemy2_direction()
{
    if (check_last_direction(L_DIRECTION))
    {
        set_direction(R_DIRECTION);
        set_creature_texture(R_DIRECTION);
        set_velocity(Vector2f(RIGHT_VELOCITY_ENEMY, 0));
    }
    else if (check_last_direction(R_DIRECTION))
    {
        set_direction(L_DIRECTION);
        set_creature_texture(L_DIRECTION);
        set_velocity(Vector2f(LEFT_VELOCITY_ENEMY, 0));
    }
}

vector<string> Enemy1 ::create_address_vector_left()
{
    vector<string> address;
    string name = "./Picture/Enemy/enemy_1_left", type = ".png";
    for (int i = 1; i <= NUM_ENEMY1_TEXTURE; i++)
    {
        string temp = name + to_string(i) + type;
        address.push_back(temp);
    }
    return address;
}
vector<string> Enemy1 ::create_address_vector_right()
{
    vector<string> address;
    string name = "./Picture/Enemy/enemy_1_right", type = ".png";
    for (int i = 1; i <= NUM_ENEMY1_TEXTURE; i++)
    {
        string temp = name + to_string(i) + type;
        address.push_back(temp);
    }
    return address;
}

void Creature ::set_creatue_scale(Vector2f scale)
{
    creature_sprite.setScale(scale);
}

void Enemy1 ::move_enemy_type_1()
{
    Vector2f position = get_creature_position();
    if (check_last_direction(L_DIRECTION))
    {
        position.x += LEFT_VELOCITY_ENEMY;
        if (is_near_to_death)
        {
            set_dead_texture();
        }
        else
        {
            set_creature_texture(L_DIRECTION);
        }
    }
    else
    {
        position.x += RIGHT_VELOCITY_ENEMY;
        if (is_near_to_death)
        {
            set_dead_texture();
        }
        else
        {
            set_creature_texture(R_DIRECTION);
        }
    }
    set_creatue_scale(Vector2f(1.05f, 1.05f));
    set_creature_position(position);
}

void Enemy1 ::set_dead_texture()
{
    if (check_last_direction(L_DIRECTION))
    {
        set_specific_texture(dead_left);
    }
    else if (check_last_direction(R_DIRECTION))
    {
        set_specific_texture(dead_right);
    }
}

void Enemy2 ::set_dead_texture()
{
    if (check_last_direction(L_DIRECTION))
    {
        set_specific_texture(dead_left);
    }
    else if (check_last_direction(R_DIRECTION))
    {
        set_specific_texture(dead_right);
    }
}

void Turtle ::render_heart(RenderWindow &window)
{
    Vector2f position_first_heart, turtle_position = get_creature_position();
    position_first_heart.y = turtle_position.y - DIFFRENCE_TURTLE_POSRIOTN_WITH_WINDOW_Y;
    position_first_heart.x = turtle_position.x + DIFFRENCE_TURTLE_POSRIOTN_WITH_WINDOW_X;
    for (int index_heart = 0; index_heart < num_hearts; index_heart++)
    {
        heart.setPosition(position_first_heart);
        window.draw(heart);
        position_first_heart.x -= LENGTH_HEART;
    }
}

void Turtle ::decrease_num_turtle_hearts()
{
    num_hearts--;
}

void Enemy1 ::decrease_enemy_heart()
{
    num_heart--;
    if (num_heart == 1)
    {
        is_near_to_death = true;
    }
    else if (num_heart == 0)
    {
        is_dead = true;
    }
}

bool Enemy1 ::is_enemy_dead()
{
    return is_dead;
}

bool Enemy2 ::is_enemy_dead()
{
    return is_dead;
}

bool Turtle ::is_alive()
{
    if (num_hearts == 0)
    {
        return false;
    }
    return true;
}

vector<string> Enemy2 ::create_address_vector_left()
{
    vector<string> address;
    string name = "./Picture/Enemy/enemy_2_left", type = ".png";
    for (int num = 1; num <= NUM_ENEMY2_TEXTURE; num++)
    {
        string temp = name + to_string(num) + type;
        address.push_back(temp);
    }
    return address;
}

vector<string> Enemy2::create_address_vector_right()
{
    vector<string> address;
    string name = "./Picture/Enemy/enemy_2_right", type = ".png";
    for (int num = 1; num <= NUM_ENEMY2_TEXTURE; num++)
    {
        string temp = name + to_string(num) + type;
        address.push_back(temp);
    }
    return address;
}

void Enemy2 ::move_enemy_type_2()
{
    Vector2f position = get_creature_position();
    if (check_last_direction(L_DIRECTION))
    {
        position.x += LEFT_VELOCITY_ENEMY;
        if (is_near_to_death)
        {
            set_dead_texture();
        }
        else
        {
            num_steps++;
            if (num_steps == NUM_PELANS_FOR_CHANGE_TEXTURE)
            {
                set_creature_texture(L_DIRECTION);
                put_enemy2_in_defeat_mode(L_DIRECTION);
                set_pelan_left();
                num_steps = 0;
            }
        }
    }
    else
    {
        position.x += RIGHT_VELOCITY_ENEMY;
        if (is_near_to_death)
        {
            set_dead_texture();
        }
        else
        {
            num_steps++;
            if (num_steps == NUM_PELANS_FOR_CHANGE_TEXTURE)
            {
                set_creature_texture(R_DIRECTION);
                put_enemy2_in_defeat_mode(R_DIRECTION);
                set_pelan_right();
                num_steps = 0;
            }
        }
    }
    set_creatue_scale(Vector2f(1.05f, 1.05f));
    set_creature_position(position);
}

int Creature ::get_pelan(string direction)
{
    if (direction == L_DIRECTION)
    {
        return pelan_left;
    }
    return pelan_right;
}

void Enemy2 ::put_enemy2_in_defeat_mode(string direction)
{
    int pelan = get_pelan(direction);
    if (pelan != 0 && pelan != 1)
    {
        can_be_killed = false;
    }
    else
    {
        can_be_killed = true;
    }
}

void Enemy2 ::decrease_enemy_heart()
{
    num_heart--;
    if (num_heart == 1)
    {
        is_near_to_death = true;
        can_be_killed = true;
    }
    else if (num_heart == 0)
    {
        is_dead = true;
    }
}

bool Enemy2 :: is_possible_to_kill()
{
    return can_be_killed;
}