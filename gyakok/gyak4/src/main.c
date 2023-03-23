#include "game.h"

/**
 * Main function
 */
 
#pragma GCC diagnostic ignored "-Wunused-parameter"
int main(int argc, char* argv[])
{
    Game game;

    init_game(&game, 800, 600);
    while (game.is_running) {
        handle_game_events(&game);
        update_game(&game);
        render_game(&game);
    }
    destroy_game(&game);

    return 0;
}
#pragma GCC diagnostic pop
