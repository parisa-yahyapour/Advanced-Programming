#include "game.hpp"
const string ADDRESS_SOUND = "./Music/Sound.ogg";
const string TITLE = "Turtix";
const string ADDRESS_MAP = "map.txt";
const int LENGHT_WINDOW = 800;
const int HIGHT_WINDOW = 700;
const int FRAME_LIMIT = 30;
const float X_CENTER_ORIGINAL_WINDOW = 400;
const float Y_CENTER_ORIGINAL_WINDOW = 350;

int main()
{
    RenderWindow window(VideoMode(LENGHT_WINDOW, HIGHT_WINDOW), TITLE);
    window.setFramerateLimit(FRAME_LIMIT);
    Menu game_menu;
    int operation;
    Music music_buffer;
    music_buffer.openFromFile(ADDRESS_SOUND);
    while (window.isOpen())
    {
        music_buffer.play();
        operation = game_menu.process_menu(window);
        if (operation == START_GAME)
        {
            Turtix game;
            game.prepare_map(ADDRESS_MAP);
            View game_view(game.get_position_gate(), Vector2f(LENGHT_WINDOW, HIGHT_WINDOW));
            window.setView(game_view);
            game.process_events(window);
            game_view.setCenter(X_CENTER_ORIGINAL_WINDOW,Y_CENTER_ORIGINAL_WINDOW);
            window.setView(game_view);
        }
        if (operation == EXIT_GAME)
        {
            window.close();
        }
    }
    return 0;
}
