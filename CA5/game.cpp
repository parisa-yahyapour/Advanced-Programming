#include "game.hpp"
const int Y_LAST_LINE = 560;
const int LENGTH_EACH_LINE = 140;
const int LENGTH_GROUND_TEXTURE = 180;
const int LENGTH_BABY_TEXTURE = 100;
const int LENGTH_DIRECTION_CHANGER = 60;
const int LENGHT_ENEMY_1 = 75;
const int LENGHT_STAR_DIMOND = 60;
const int LENGTH_GATE_TEXTURE = 150;
const int EXTRA_WIDTH_GATE_TEXTURE = 66;
const int LENGHT_SPACE_IN_MAP = 50;
const int DIFFRENCE_HIGHT_BABY_GROUND = 70;
const int DIFFRENCE_HIGHT_CHANGER_GROUND = 60;
const int DIFFRENCE_HIGHT_ENEMY1 = 50;
const int JUMP_SPEED = -15;
const char GROUND_SPRITE = '.';
const char BABY_SPRITE = 'O';
const char EMPTY_SPRITE = ' ';
const char GATE_SPRITE = '$';
const char ENEMY_1_SPRITE = 'E';
const char ENEMY_2_SPRITE = 'M';
const char STAR_SPRITE = '*';
const char DIMOND_SPRITE = '^';
const char DIRECTION_CHANGER_SPRITE = 'B';
const string GROUND_ADDRESS = "./Picture/Grounds/ground.png";
const string GATE_ADDRESS = "./Picture/Grounds/gate.png";
const bool IS_LEFT = true;
const bool IS_RIGHT = false;
const float MOVE_SPEED = 5;
const float GRAVITY = 1;
const float GRAVITY_BABY = 10;
const float DIFFRENCE_GATE_GROUND = 66.5;
const float VELOCITY_LEFT_ENEMY1 = -10;
const float VELOCITY_TURTLE_AFTER_KILL = -30;
const int DIFFRENCE_SCORE_WITH_TURTLE_Y = 370;
const int DIFFRENCE_NUM_BABIES_WITH_TURTLE_Y = 300;
const int DIFFRENCE_SCORE_WITH_TURTLE_X = 400;
const int NUMBER_MOVE_ENEMY_AFTER_KIIL = 5;
const int INVALID = -1;
const string U_DIRECTION = "UP";
const string D_DIRECTION = "DOWN";
enum ColumnTexture
{
    GROUND,
    GATE,
    DIRECTION_CHANGER
};

vector<string> Turtix ::read_map_data_from_file(string file_address)
{
    ifstream map_data(file_address);
    vector<string> lines;
    string temp;
    int num_lines = 0;
    while (getline(map_data, temp))
    {
        num_lines++;
        lines.push_back(temp);
    }
    maximum_hight = num_lines * LENGTH_EACH_LINE;
    return lines;
}

void Turtix ::render(RenderWindow &window)
{
    window.clear();
    for (int index_object = 0; index_object < objects.size(); index_object++)
    {
        objects[index_object].draw_object(window);
    }
    gate.draw_object(window);
    for (int index_star_dimond = 0; index_star_dimond < stars_dimonds.size(); index_star_dimond++)
    {
        stars_dimonds[index_star_dimond]->draw_object(window);
    }
    for (int index_baby = 0; index_baby < baby_turtles.size(); index_baby++)
    {
        baby_turtles[index_baby]->draw_ceature(window);
    }
    for (int index_changer = 0; index_changer < direction_changers.size(); index_changer++)
    {
        direction_changers[index_changer]->draw_object(window);
    }
    for (int index_enemy = 0; index_enemy < enemy_1.size(); index_enemy++)
    {
        enemy_1[index_enemy]->draw_ceature(window);
    }
    for (int index_enemy = 0; index_enemy < enemy_2.size(); index_enemy++)
    {
        enemy_2[index_enemy]->draw_ceature(window);
    }
    turtle.render_heart(window);
    game_score.render_score(window, turtle.get_creature_position());
    turtle.draw_ceature(window);
}

void Turtix ::set_objects(vector<string> lines)
{
    int current_x = 0, current_y = 0;
    for (int index_line = 0; index_line < lines.size(); index_line++)
    {
        current_y = index_line * LENGTH_EACH_LINE;
        current_x = 0;
        for (int index_char = 0; index_char < lines[index_line].size(); index_char++)
        {
            if (lines[index_line][index_char] == GROUND_SPRITE)
            {
                MapObjects temp;
                temp.set_object_texture(texture_map[GROUND]);
                temp.set_object_position(Vector2f(current_x, current_y));
                temp.set_object_scale(Vector2f(1.f, 0.7f));
                objects.push_back(temp);
                current_x += LENGTH_GROUND_TEXTURE;
            }
            if (lines[index_line][index_char] == GATE_SPRITE) 
            {
                gate.set_object_texture(texture_map[GATE]);
                gate.set_object_position(Vector2f(current_x, current_y - EXTRA_WIDTH_GATE_TEXTURE));
                position_gate = Vector2f(current_x, current_y - EXTRA_WIDTH_GATE_TEXTURE);
                gate.set_object_scale(Vector2f(0.7f, 0.7f));
                current_x += LENGTH_GATE_TEXTURE;
            }
            if (lines[index_line][index_char] == BABY_SPRITE)
            {
                BabyTurtle *temp = new BabyTurtle(Vector2f(current_x, current_y + DIFFRENCE_HIGHT_BABY_GROUND));
                baby_turtles.push_back(temp);
                current_x += LENGTH_BABY_TEXTURE;
                game_score.increase_num_babies();
            }
            if (lines[index_line][index_char] == DIRECTION_CHANGER_SPRITE)
            {
                DirectionChanger *temp = new DirectionChanger(Vector2f(current_x, current_y + DIFFRENCE_HIGHT_CHANGER_GROUND));
                direction_changers.push_back(temp);
                current_x += LENGTH_DIRECTION_CHANGER;
            }
            if (lines[index_line][index_char] == ENEMY_1_SPRITE)
            {
                Enemy1 *temp = new Enemy1(Vector2f(current_x, current_y + DIFFRENCE_HIGHT_ENEMY1));
                enemy_1.push_back(temp);
                current_x += LENGHT_ENEMY_1;
            }
            if (lines[index_line][index_char] == STAR_SPRITE)
            {
                StarDimond *temp = new StarDimond(Vector2f(current_x, current_y + DIFFRENCE_HIGHT_CHANGER_GROUND), STAR);
                stars_dimonds.push_back(temp);
                current_x += LENGHT_STAR_DIMOND;
            }
            if (lines[index_line][index_char] == DIMOND_SPRITE)
            {
                StarDimond *temp = new StarDimond(Vector2f(current_x, current_y + DIFFRENCE_HIGHT_CHANGER_GROUND), DIMOND);
                stars_dimonds.push_back(temp);
                current_x += LENGHT_STAR_DIMOND;
            }
            if (lines[index_line][index_char] == ENEMY_2_SPRITE)
            {
                Enemy2 *temp = new Enemy2(Vector2f(current_x, current_y + DIFFRENCE_HIGHT_ENEMY1));
                enemy_2.push_back(temp);
                current_x += LENGHT_ENEMY_1;
            }
            if (lines[index_line][index_char] == EMPTY_SPRITE)
            {
                current_x += LENGHT_SPACE_IN_MAP;
            }
        }
    }
}

void Turtix ::load_map_textures_from_file()
{
    Texture temp;
    temp.loadFromFile(GROUND_ADDRESS);
    texture_map.push_back(temp);
    temp.loadFromFile(GATE_ADDRESS);
    texture_map.push_back(temp);
}

void Turtix ::prepare_map(string file_address)
{
    load_map_textures_from_file();
    vector<string> lines = read_map_data_from_file(file_address);
    set_objects(lines);
    prepare_turtle(position_gate);
}

void Turtix ::prepare_turtle(Vector2f position)
{
    turtle.load_texture_from_file(turtle.create_address_vector_left(), turtle.create_address_vector_right());
    turtle.set_creature_texture(L_DIRECTION);
    turtle.set_creature_position(position);
}

void Turtix ::process_events(RenderWindow &window)
{
    Vector2f new_velocity(0, 0);
    int operation_status;
    while (window.isOpen())
    {
        Event event;
        new_velocity.x = 0;
        if (!is_turtle_alive())
        {
            operation_status = LOSER;
            break;
        }
        while (window.pollEvent(event))
        {
            if (event.type == Event ::Closed)
            {
                window.close();
            }
            if (event.key.code == Keyboard ::Left)
            {
                new_velocity.x = -MOVE_SPEED;
                turtle.move_creature(new_velocity);
                turtle.set_pelan_left();
                turtle.set_creature_texture(L_DIRECTION);
                turtle.set_direction(L_DIRECTION);
            }
            else if (event.key.code == Keyboard ::Right)
            {
                new_velocity.x = MOVE_SPEED;
                turtle.move_creature(Vector2f(10, 0));
                turtle.set_pelan_right();
                turtle.set_creature_texture(R_DIRECTION);
                turtle.set_direction(R_DIRECTION);
            }
            if (event.key.code == Keyboard ::Up)
            {
                new_velocity.y = JUMP_SPEED;
                turtle.move_creature(new_velocity);
            }
        }
        if (!check_intersection_with_ground(turtle))
        {
            new_velocity.y += GRAVITY;
        }
        else
        {
            new_velocity.y = 0;
        }
        if (check_winning_consitions() == WINNER)
        {
            operation_status = WINNER;
            break;
        }
        move_enemy();
        check_turtle_intersection_with_enemy1();
        check_turtle_intersection_with_enemy2();
        check_turtle_hight();
        delete_dead_enemy();
        check_turtle_intersection_with_babies();
        check_intersection_with_direction_changer();
        check_turtle_intersection_with_stars_dimonds();
        move_free_baby_turtles();
        put_dead_babies_in_cage();
        check_saved_baby_turtles();
        turtle.move_creature(new_velocity);
        View temp(turtle.get_creature_position(), Vector2f(800, 700));
        window.setView(temp);
        window.clear();
        render(window);
        window.display();
    }
    handle_result(operation_status, turtle.get_creature_position(), window);
}

int DataOutPut ::get_score()
{
    return score;
}

void Turtix ::handle_result(int status_game, Vector2f position_turtle, RenderWindow &window)
{
    GameResult final_result(game_score.get_score(), status_game, position_turtle);
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (Mouse ::isButtonPressed(Mouse ::Left))
            {
                return;
            }
        }
        final_result.render_result(window);
    }
}

void GameResult ::render_result(RenderWindow &window)
{
    window.clear();
    if (status_game == WINNER)
    {
        window.draw(winner);
    }
    else if (status_game == LOSER)
    {
        window.draw(loser);
    }
    window.draw(score);
    window.display();
}

Vector2f Turtix ::get_position_gate()
{
    return position_gate;
}

bool Turtix ::check_intersection_with_ground(Creature creature)
{
    FloatRect creature_bounds = creature.get_global_bounds();
    for (int index_object = 0; index_object < objects.size(); index_object++)
    {
        FloatRect object_bounds = objects[index_object].get_global_bounds_object();
        if (object_bounds.intersects(creature_bounds))
        {
            if (creature_bounds.top < object_bounds.top &&
                creature_bounds.top + creature_bounds.height < object_bounds.top + object_bounds.height &&
                creature_bounds.left < object_bounds.left + object_bounds.width &&
                creature_bounds.left + creature_bounds.width > object_bounds.left)
            {
                return true;
            }
        }
    }
    FloatRect gate_bounds = gate.get_global_bounds_object();
    gate_bounds.height -= DIFFRENCE_GATE_GROUND;
    gate_bounds.top += DIFFRENCE_GATE_GROUND;
    if (creature_bounds.top < gate_bounds.top &&
        creature_bounds.top + creature_bounds.height < gate_bounds.top + gate_bounds.height &&
        creature_bounds.left < gate_bounds.left + gate_bounds.width &&
        creature_bounds.left + creature_bounds.width > gate_bounds.left)
    {
        return true;
    }
    return false;
}

bool Turtix ::check_top_intersection(FloatRect turtle_bounds, FloatRect object_bounds)
{
    if (object_bounds.intersects(turtle_bounds))
    {
        if (turtle_bounds.top < object_bounds.top &&
            turtle_bounds.top + turtle_bounds.height < object_bounds.top + object_bounds.height &&
            turtle_bounds.left < object_bounds.left + object_bounds.width &&
            turtle_bounds.left + turtle_bounds.width > object_bounds.left)
        {
            return true;
        }
    }
    return false;
}

bool Turtix ::check_down_intersection(FloatRect turtle_bounds, FloatRect object_bounds)
{
    if (object_bounds.intersects(turtle_bounds))
    {
        if (turtle_bounds.top > object_bounds.top &&
            turtle_bounds.top + turtle_bounds.height > object_bounds.top + object_bounds.height &&
            turtle_bounds.left < object_bounds.left + object_bounds.width &&
            turtle_bounds.left + turtle_bounds.width > object_bounds.left)
        {
            return true;
        }
    }
    return false;
}

void Turtix ::check_turtle_intersection_with_babies()
{
    FloatRect turtle_bounds = turtle.get_global_bounds();
    for (int baby_index = 0; baby_index < baby_turtles.size(); baby_index++)
    {
        FloatRect baby_bounds = baby_turtles[baby_index]->get_global_bounds();
        if (check_top_intersection(turtle_bounds, baby_bounds) && baby_turtles[baby_index]->is_baby_in_cage())
        {
            baby_turtles[baby_index]->make_baby_free();
        }
    }
}

void Turtix ::check_intersection_with_direction_changer()
{
    FloatRect turtle_bounds = turtle.get_global_bounds();
    for (int direction_changer_index = 0; direction_changer_index < direction_changers.size(); direction_changer_index++)
    {
        FloatRect direction_changer_bounds = direction_changers[direction_changer_index]->get_global_bounds_object();
        if (check_top_intersection(turtle_bounds, direction_changer_bounds))
        {
            if (!direction_changers[direction_changer_index]->is_direction_changer_open())
            {
                direction_changers[direction_changer_index]->open_direction_changer();
            }
            else
            {
                direction_changers[direction_changer_index]->close_direction_changer();
            }
        }
    }
}

void Turtix ::move_free_baby_turtles()
{
    for (int index_baby = 0; index_baby < baby_turtles.size(); index_baby++)
    {
        float new_velocity_y = 0;
        if (!baby_turtles[index_baby]->is_baby_in_cage())
        {
            if (!check_intersection_with_ground(*(baby_turtles[index_baby])))
            {
                new_velocity_y = GRAVITY_BABY;
            }
            else
            {
                new_velocity_y = 0;
            }
            if (change_direction(*(baby_turtles[index_baby])))
            {
                baby_turtles[index_baby]->change_baby_direction();
            }
            baby_turtles[index_baby]->move_baby(new_velocity_y);
        }
    }
}

void Turtix ::move_enemy()
{
    for (int index_enemy = 0; index_enemy < enemy_1.size(); index_enemy++)
    {
        if (check_intersection_with_ground(*(enemy_1[index_enemy])))
        {
            enemy_1[index_enemy]->move_enemy_type_1();
        }
        else
        {
            enemy_1[index_enemy]->change_enemy1_direction();
            enemy_1[index_enemy]->move_enemy_type_1();
        }
    }
    for (int index_enemy = 0; index_enemy < enemy_2.size(); index_enemy++)
    {
        if (check_intersection_with_ground(*(enemy_2[index_enemy])))
        {
            enemy_2[index_enemy]->move_enemy_type_2();
        }
        else
        {
            enemy_2[index_enemy]->change_enemy2_direction();
            enemy_2[index_enemy]->move_enemy_type_2();
        }
    }
}

bool Turtix ::change_direction(Creature &creature)
{
    FloatRect creature_bounds = creature.get_global_bounds();
    for (int index_changer = 0; index_changer < direction_changers.size(); index_changer++)
    {
        FloatRect direction_changer_bounds = direction_changers[index_changer]->get_global_bounds_object();
        if (creature.check_last_direction(L_DIRECTION) &&
            check_right_intersection(creature_bounds, direction_changer_bounds) &&
            direction_changers[index_changer]->is_direction_changer_open())
        {
            return true;
        }
        else if (creature.check_last_direction(R_DIRECTION) &&
                 check_left_intersection(creature_bounds, direction_changer_bounds) &&
                 direction_changers[index_changer]->is_direction_changer_open())
        {
            return true;
        }
    }
    return false;
}

void Turtix ::put_dead_babies_in_cage()
{
    for (int index_baby = 0; index_baby < baby_turtles.size(); index_baby++)
    {
        if (baby_turtles[index_baby]->is_baby_dead(maximum_hight) || check_intersection_babies_with_enemies(baby_turtles[index_baby]))
        {
            baby_turtles[index_baby]->put_baby_cage();
        }
    }
}

bool Turtix ::check_left_intersection(FloatRect turtle_bound, FloatRect object_bound)
{
    if (turtle_bound.left < object_bound.left &&
        turtle_bound.left + turtle_bound.width < object_bound.left + object_bound.width &&
        turtle_bound.top < object_bound.top + object_bound.height &&
        turtle_bound.top + turtle_bound.height > object_bound.top)
    {
        return true;
    }
    return false;
}

bool Turtix ::check_right_intersection(FloatRect turtle_bound, FloatRect object_bound)
{
    if (turtle_bound.left > object_bound.left &&
        turtle_bound.left + turtle_bound.width > object_bound.left + object_bound.width &&
        turtle_bound.top < object_bound.top + object_bound.height &&
        turtle_bound.top + turtle_bound.height > object_bound.top)
    {
        return true;
    }
    return false;
}

bool Turtix ::check_intersection_babies_with_enemies(BabyTurtle *baby)
{
    FloatRect baby_bound = baby->get_global_bounds();
    for (int index_enemy = 0; index_enemy < enemy_1.size(); index_enemy++)
    {
        FloatRect enemy_bound = enemy_1[index_enemy]->get_global_bounds();
        if ((enemy_bound.intersects(baby_bound)) && !baby->is_baby_in_cage())
        {
            return true;
        }
    }
    return false;
}

void Turtix ::check_turtle_intersection_with_enemy1()
{
    FloatRect turtle_bound = turtle.get_global_bounds();
    for (int index_enemy = 0; index_enemy < enemy_1.size(); index_enemy++)
    {
        FloatRect enemy_bound = enemy_1[index_enemy]->get_global_bounds();
        if (enemy_bound.intersects(turtle_bound))
        {
            if (check_top_intersection(turtle_bound, enemy_bound))
            {
                enemy_1[index_enemy]->decrease_enemy_heart();
                Vector2f velocity_turtle;
                for (int i = 0; i < 10; i++)
                {
                    enemy_1[index_enemy]->move_enemy_type_1();
                }
                velocity_turtle.y = VELOCITY_TURTLE_AFTER_KILL;
                turtle.move_creature(velocity_turtle);
            }
            else
            {
                turtle.decrease_num_turtle_hearts();
                turtle.set_creature_position(position_gate);
            }
        }
    }
}

void Turtix ::check_turtle_intersection_with_enemy2()
{
    FloatRect turtle_bound = turtle.get_global_bounds();
    for (int index_enemy = 0; index_enemy < enemy_2.size(); index_enemy++)
    {
        FloatRect enemy_bound = enemy_2[index_enemy]->get_global_bounds();
        if (enemy_bound.intersects(turtle_bound))
        {
            if (check_top_intersection(turtle_bound, enemy_bound) && enemy_2[index_enemy]->is_possible_to_kill())
            {
                enemy_2[index_enemy]->decrease_enemy_heart();
                Vector2f velocity_turtle;
                for (int num_move = 0; num_move < NUMBER_MOVE_ENEMY_AFTER_KIIL; num_move++)
                {
                    enemy_2[index_enemy]->move_enemy_type_2();
                }
                velocity_turtle.y = VELOCITY_TURTLE_AFTER_KILL;
                turtle.move_creature(velocity_turtle);
            }
            else
            {
                turtle.decrease_num_turtle_hearts();
                turtle.set_creature_position(position_gate);
            }
        }
    }
}

void Turtix ::delete_dead_enemy()
{
    for (int index_enemy = 0; index_enemy < enemy_1.size(); index_enemy++)
    {
        if (enemy_1[index_enemy]->is_enemy_dead())
        {
            enemy_1.erase(enemy_1.begin() + index_enemy);
        }
    }
    for (int index_enemy = 0; index_enemy < enemy_2.size(); index_enemy++)
    {
        if (enemy_2[index_enemy]->is_enemy_dead())
        {
            enemy_2.erase(enemy_2.begin() + index_enemy);
        }
    }
}

void Turtix ::check_turtle_intersection_with_stars_dimonds()
{
    FloatRect turtle_bound = turtle.get_global_bounds();
    for (int index_star = 0; index_star < stars_dimonds.size(); index_star++)
    {
        FloatRect star_bound = stars_dimonds[index_star]->get_global_bounds_object();
        if (star_bound.intersects(turtle_bound))
        {
            game_score.increase_score(stars_dimonds[index_star]->get_score());
            delete_used_star_dimonds(index_star);
        }
    }
}

void DataOutPut ::increase_score(int offset)
{
    score += offset;
    text_score.setString(to_string(score));
}

void Turtix ::delete_used_star_dimonds(int index)
{
    stars_dimonds.erase(stars_dimonds.begin() + index);
}

void DataOutPut ::render_score(RenderWindow &window, Vector2f turtle_position)
{
    Vector2f position_score;
    position_score.y = turtle_position.y - DIFFRENCE_SCORE_WITH_TURTLE_Y;
    position_score.x = turtle_position.x - DIFFRENCE_SCORE_WITH_TURTLE_X;
    text_score.setPosition(position_score);
    position_score.y = turtle_position.y - DIFFRENCE_NUM_BABIES_WITH_TURTLE_Y;
    sentence.setPosition(position_score);
    position_score.y -= 10;
    position_score.x += 260;
    text_baby_turtles.setPosition(position_score);
    window.draw(text_score);
    window.draw(text_baby_turtles);
    window.draw(sentence);
}

void DataOutPut ::increase_num_babies()
{
    num_babies++;
    text_baby_turtles.setString(to_string(num_babies));
}

void DataOutPut ::decrese_num_babies()
{
    num_babies--;
    text_baby_turtles.setString(to_string(num_babies));
}

void Turtix ::check_saved_baby_turtles()
{
    FloatRect gate_bound = gate.get_global_bounds_object();
    for (int index_baby = 0; index_baby < baby_turtles.size(); index_baby++)
    {
        FloatRect baby_bound = baby_turtles[index_baby]->get_global_bounds();
        if (gate_bound.intersects(baby_bound))
        {
            baby_turtles.erase(baby_turtles.begin() + index_baby);
            game_score.decrese_num_babies();
        }
    }
}

void Menu ::render_menu(RenderWindow &window)
{
    window.clear();
    window.draw(game_name);
    window.draw(start);
    window.draw(exit);
    window.draw(cersor);
    window.display();
}

void Menu ::move_cersor(string direction)
{
    Vector2f cersor_position = cersor.getPosition();
    if (direction == U_DIRECTION)
    {
        cersor.setPosition(cersor_position.x, cersor_position.y - speed_cersor.y);
    }
    else
    {
        cersor.setPosition(cersor_position.x, cersor_position.y + speed_cersor.y);
    }
}

int Menu ::process_menu(RenderWindow &window)
{
    int counter_up = 1, counter_down = 0, code_operation = INVALID;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event ::Closed)
            {
                window.close();
            }
            if (event.type == Event ::KeyPressed)
            {
                if (event.key.code == Keyboard ::Up && counter_up == 0)
                {
                    move_cersor(U_DIRECTION);
                    counter_down = 0;
                    counter_up++;
                }
                if (event.key.code == Keyboard ::Down && counter_down == 0)
                {
                    move_cersor(D_DIRECTION);
                    counter_up = 0;
                    counter_down++;
                }
                if (event.key.code == Keyboard ::Enter)
                {
                    code_operation = check_operation();
                    break;
                }
            }
        }
        if (code_operation != INVALID)
        {
            break;
        }
        render_menu(window);
    }
    return code_operation;
}

int Menu ::check_operation()
{
    if (cersor.getPosition() == POSITION_START_GAME)
    {
        return START_GAME;
    }
    return EXIT_GAME;
}

bool Turtix ::is_turtle_alive()
{
    return turtle.is_alive();
}

int Turtix ::check_winning_consitions()
{
    FloatRect turtle_bound = turtle.get_global_bounds(), gate_bound = gate.get_global_bounds_object();
    if (game_score.get_num_left_babies() == 0 &&
        is_turtle_alive() &&
        gate_bound.intersects(turtle_bound))
    {
        return WINNER;
    }
    return COUNTINUE;
}

int DataOutPut ::get_num_left_babies()
{
    return num_babies;
}

void Turtix ::check_turtle_hight()
{
    if (turtle.get_creature_position().y > maximum_hight)
    {
        turtle.decrease_num_turtle_hearts();
        turtle.set_creature_position(position_gate);
    }
}