#include "SDL2/SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"


#include "../AI_Functions/AI.h" 
#include "../Game_Treatment/Board.h"
#include "../Useful/Constants.h"
#include "Download_Log.h"
#include "../AI_Functions/Evaluation.h"
#include "Graphics.h"
#include "../Game_Treatment/Log.h"
#include "../AI_Functions/Move_Generator.h"
#include "../AI_Functions/Move_Ordering.h"
#include "../Game_Treatment/Moves_Treatment.h"
#include "../AI_Data/Openings.h"
#include "../AI_Data/Pieces_Squares_Tables.h"
#include "../AI_Data/Pre_Computed_Data.h"
#include "../AI_Functions/Search.h"
#include "../Game_Treatment/Settings.h"
#include "../AI_Data/Transposition_Table.h"
#include "../Useful/Utility.h"


// initialize the window and the renderer
int is_running_game = -1; // setup to -1 for false before the initialization of the game
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;


///////////////////////////////////////////////////////////////////////////////
// Function to initialize our SDL window (+ IMG + ttf)
/**
 * @param window : the window to initialize that is a global variable
 * @param renderer : the renderer to initialize that is a global variable
 * @param backgroundTexture : the texture to initialize that is a global variable
 * @return true (1) if the initialization is successful, false (0) otherwise
**/
///////////////////////////////////////////////////////////////////////////////
int initialize_SDL(){
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        printf("SDL initialization failed: %s\n", SDL_GetError());
        return -1;
    }
    window = SDL_CreateWindow(
        "Chess Game using C & SDL",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WINDOW_WIDTH,
        WINDOW_HEIGHT,
        SDL_WINDOW_FULLSCREEN // SDL_WINDOW_FULLSCREEN can be used to make the window fullscreen, 0 to be in the window opened
    );
    if (!window) {
        printf("Window creation failed: %s\n", SDL_GetError());
        return -1;
    }

    // create the renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Renderer creation failed: %s\n", SDL_GetError());
        return -1;
    }

    // initializing SDL_image
    if (!(IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP) & (IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF | IMG_INIT_WEBP))) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return -1;
    }

    // initializing SDL_ttf
    if (TTF_Init() == -1) {
        printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
        return -1;
    }

    // if everything is ok, we return true
    return GAMEPLAY_CHOICE;
}


///////////////////////////////////////////////////////////////////////////////
// Function to clear the graphics (+ IMG + ttf)
/**
 * @param window : the window to destroy
 * @param renderer : the renderer to destroy 
**/
///////////////////////////////////////////////////////////////////////////////
void clear_and_close_SDL(SDL_Window* window, SDL_Renderer* renderer){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();
}


///////////////////////////////////////////////////////////////////////////////
// Main function of the game (with all the SDL events)
///////////////////////////////////////////////////////////////////////////////
int main (){

    // initialize the SDL program
    is_running_game = initialize_SDL();

    // Creating all the structures to keep track of the game
    // Initialize the settings of the game
    create_game_settings();
    // some time variables
    float current_time = 0.0; // the current time of the game
    float last_time_recorded = 0.0; // the last time recorded
    float delta_time = 0.0; // the delta time between the current time and the last time recorded

    // Initializing the bitboards 
    init_bitboards();

    // Initialize the log 
    create_log();

    // Initialize the bit_board log 
    create_bitboards_log();

    // Initialize the capture pieces and the score
    create_captured_pieces_and_score();

    // Creating the buttons
    create_buttons();

    // Initialize all the precomputed datas
    initialize_pre_computed_data();

    // Initialize the random transposition table
    initialize_random_transposition_tables();

    // Initialize the transposition table
    int size_MB = 64;
    initialize_transposition_tables(size_MB);

    // initialize the attacks of the pieces 
    initialize_attacks();

    // loading the opening book
    load_opening_book();

    // keeping track of the number of clicks made on the screen
    bool is_clicked = false;
    // to track if a click (and only one) has been done on the board or not
    bool is_clicked_on_board = false; 
 
    // Corresponding to the move, will be updated by the players clicking input and the IA search
    int selected_piece_index=-1;
    int from_index = -1;
    int to_index = -1;

    // intializing the cosntant for the lvl7 AI so we can show some information about the precedent move
    move selected_move_lvl7 = 0;
    int selected_score_lvl7 = 0;
    bool is_move_taken_from_book_lvl7 = false;
    int depth_reached_lvl7 = 0;

    // SDL_rect to draw the red boundary when we move a piece to know it's the piece that is selected
    SDL_Rect draw_red_boundary_move={0, 0, 0, 0};

    // Constants to keep track of the mouvement of the pieces
    SDL_Rect piece_movement_rect = {OUTSIDE_BOARD, OUTSIDE_BOARD, SQUARE_SIZE, SQUARE_SIZE};
    int previous_piece_movement_x = OUTSIDE_BOARD;
    int previous_piece_movement_y = OUTSIDE_BOARD;

    // Creating an SDL_Event to handle the events
    SDL_Event event;

    // playing the game while we don't quit it
    while (is_running_game != -1){
        
        // gestion of the events
        while(SDL_PollEvent(&event)){
            
            // forcing to kil the .x file : option + command + esc
            // condition to quit the game
            if (event.type == SDL_QUIT){
                is_running_game = -1;
            }

            // what happens when a specific key is pressed on the keyboard (the escape key to quit the game), the others keys are used to fast things for the testings
            else if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    // quit the game if this key is pressed
                    case SDLK_ESCAPE:
                        // we download the log of the game
                        if (is_running_game == CHESSBOARD_RENDER || is_running_game == VICTORY_MENU){
                            download_log();
                        }
                        is_running_game=-1;
                        break;
                    // make an AIvAI match, to setup the test easily without having to click on the buttons, to gain time to test the different AI levels
                    case SDLK_a:
                        if (is_running_game == GAMEPLAY_CHOICE){
                            // setting up the players
                            game_settings->game_mode = AI_VS_AI;
                            game_settings->white_player_type = AI;
                            game_settings->black_player_type = AI;
                            game_settings->white_AI_difficulty = LVL2;
                            game_settings->black_AI_difficulty = LVL7;
                            // setting up the time
                            game_settings->time_at_start = 10*60;
                            game_settings->white_time_remaining = 10*60;
                            game_settings->black_time_remaining = 10*60;
                            game_settings->blitz_time = 0;
                            game_settings->is_game_lost_on_time = false;
                            // setting up to play the game
                            is_running_game = CHESSBOARD_RENDER;
                            game_settings->is_game_on_pause = false;
                        }
                        break;
                    // download the log of the game to a file
                    case SDLK_d:
                        if (is_running_game == CHESSBOARD_RENDER || is_running_game == VICTORY_MENU){
                            download_log();
                        }
                        break;
                    // generate all the possible moves for the player that is playing and all the moves currently in the log
                    case SDLK_g:
                        if (is_running_game == CHESSBOARD_RENDER){
                            int nb_moves = 0;
                            move* possibles_moves = generate_all_possible_moves(&nb_moves);
                            for (int i=0; i<nb_moves; i++){
                                printf("Move %d of value %d : %d %d\n", i+1, possibles_moves[i], get_from_square(possibles_moves[i]), get_to_square(possibles_moves[i]));
                            }
                            printf("\n");
                            printf("log content : \n");
                            for (int i=0; i<chess_log->actual_size; i++){
                                printf("move made %d of value %d : %d %d\n", i+1, chess_log->moves[i]->move_value, get_from_square(chess_log->moves[i]->move_value), get_to_square(chess_log->moves[i]->move_value));
                            }
                        }
                        break;
                    // make a human vs human game to test the timer 
                    case SDLK_h : 
                        if (is_running_game == GAMEPLAY_CHOICE){
                            // setting up the players
                            game_settings->game_mode = PLAYER_VS_PLAYER;
                            game_settings->white_player_type = HUMAN;
                            game_settings->black_player_type = HUMAN;
                            game_settings->white_AI_difficulty = NONE;
                            game_settings->black_AI_difficulty = NONE;
                            // setting up the time
                            game_settings->time_at_start = 10*60;
                            game_settings->white_time_remaining = 10*60;
                            game_settings->black_time_remaining = 10*60;
                            game_settings->blitz_time = 0;
                            game_settings->is_game_lost_on_time = false;
                            // setting up to play the game
                            is_running_game = CHESSBOARD_RENDER;
                            game_settings->is_game_on_pause = false;
                        }
                        break;
                    // selected the AI difficulty when in 1vAI mode, to setup the test easily without having to click on the buttons, to gain time to test the different AI levels, since there is no button to select the AI difficulty for now, it's to play as a human against the AI
                    case SDLK_l:
                        if (is_running_game == GAMEPLAY_CHOICE){
                            game_settings->game_mode = PLAYER_VS_AI;
                            game_settings->white_player_type = HUMAN;
                            game_settings->black_player_type = AI;
                            game_settings->white_AI_difficulty = NONE;
                            game_settings->black_AI_difficulty = LVL7;
                            // setting up the time
                            game_settings->time_at_start = 10*60;
                            game_settings->white_time_remaining = 10*60;
                            game_settings->black_time_remaining = 10*60;
                            game_settings->blitz_time = 0;
                            game_settings->is_game_lost_on_time = false;
                            // setting up to play the game
                            is_running_game = CHESSBOARD_RENDER;
                            game_settings->is_game_on_pause = false;
                        }
                    // opening the file to get the log and the game settings and put the game in the state of the log
                    case SDLK_o: 
                        if (is_running_game == GAMEPLAY_CHOICE){
                            bool has_opened = false;
                            open_file_and_setup_chess_game(&has_opened);
                            is_running_game = CHESSBOARD_RENDER;
                        }
                    // make a pause button to pause the game more easily than to click on the pause button
                    case SDLK_p:
                        if (is_running_game == CHESSBOARD_RENDER || is_running_game == VICTORY_MENU){
                            game_settings->is_game_on_pause = !game_settings->is_game_on_pause;
                        }
                        if (is_running_game == VICTORY_MENU){
                            undo_last_move();
                            // reset the opening book only when we use it
                            if (game_settings->white_AI_difficulty == LVL7 || game_settings->black_AI_difficulty == LVL7){
                                copy_file_into_file("Chess_Engine/AI_Data/Opening_Book_Init.txt", "Chess_Engine/AI_Data/Opening_Book_read.txt");
                                update_opening_book();
                            }
                        }
                        is_running_game = CHESSBOARD_RENDER;
                        break;
                    // restarting the game if we want to make the partie be played again 
                    case SDLK_r:
                        if (is_running_game == CHESSBOARD_RENDER || is_running_game == VICTORY_MENU){
                            // we need to reset the game
                            is_running_game = CHESSBOARD_RENDER;
                            // we reset the good settings parameters for the game
                            game_settings->player_that_is_playing = White_Player;
                            game_settings->color_of_player_that_is_playing = WHITE;
                            game_settings->loosing_player = Undetermined;
                            game_settings->white_time_remaining = game_settings->time_at_start;
                            game_settings->black_time_remaining = game_settings->time_at_start;
                            game_settings->is_game_lost_on_time = false;
                            game_settings->has_match_started = false;
                            game_settings->is_game_on_pause = false;
                            game_settings->is_pawn_promotion_happening = false;
                            game_settings->color_of_pawn_promotion = NO_COLOR;
                            // reset the board
                            reset_bitboards();
                            // reset the log
                            reset_log();
                            reset_bitboards_log();
                            // reset the captured pieces and the score
                            reset_captured_pieces_and_score();
                            // reset the transposition tables
                            reset_transposition_tables();
                            // reset the opening book only when we use it
                            if (game_settings->white_AI_difficulty == LVL7 || game_settings->black_AI_difficulty == LVL7){
                                copy_file_into_file("Chess_Engine/AI_Data/Opening_Book_Init.txt", "Chess_Engine/AI_Data/Opening_Book_read.txt");
                            }
                            // play the sound of the start of the game
                            play_sound("../../Sounds/chessstart.wav");
                        }
                        break;
                    // starting the game by clicking on the s key to start the game more easily than to click on the start button
                    case SDLK_s:
                        if (is_running_game == CHESSBOARD_RENDER){
                            game_settings->has_match_started = true;
                            // play the sound of the start of the game
                            play_sound("../../Sounds/chessstart.wav");
                            last_time_recorded = SDL_GetTicks();
                        }
                        break;
                    // show the number of zobrist key in the transpositions tables and the differents keys
                    case SDLK_t:
                        if (is_running_game == CHESSBOARD_RENDER){
                            int nb_zobrist_keys = 0;
                            for (int i = 0; i < transposition_tables->size; i++){
                                if (transposition_tables->entries[i].zobrist_key != 0){
                                    nb_zobrist_keys++;
                                    printf("Zobrist key at pos %d : %llu, with depth %d, value %d, cut flag %d, move %d\n", i, transposition_tables->entries[i].zobrist_key, transposition_tables->entries[i].depth, transposition_tables->entries[i].value, transposition_tables->entries[i].cut_flag, transposition_tables->entries[i].move);
                                }
                            }
                            printf("Number of zobrist keys : %d for a total of %d entries\n", nb_zobrist_keys, transposition_tables->size);
                            printf("\n");
                        }
                        break;
                    // undo the last move if this key is pressed, when the settings are letting us to do so, faster than to click on the undo button and to confirm it 
                    case SDLK_u:
                        if (game_settings->is_game_on_pause && (is_running_game == CHESSBOARD_RENDER || is_running_game == VICTORY_MENU)){
                            undo_last_move();
                            is_running_game = CHESSBOARD_RENDER;
                            // reset the opening book only when we use it
                            if (game_settings->white_AI_difficulty == LVL7 || game_settings->black_AI_difficulty == LVL7){
                                copy_file_into_file("Chess_Engine/AI_Data/Opening_Book_Init.txt", "Chess_Engine/AI_Data/Opening_Book_read.txt");
                                update_opening_book();
                            }
                        }
                        break;
                    // getting the zobrist key of the current board 
                    case SDLK_z:
                        if (is_running_game == CHESSBOARD_RENDER){
                            bit_board zobrist_key = get_zobrist_key();
                            printf("Zobrist key : %llu\n", zobrist_key);
                            int index = get_index_zobrist_in_TT(zobrist_key);
                            printf("Index in the transposition tables : %d\n", index);
                            printf("\n");
                        }
                        break;
                }

            }
        
            // taking the mouse event, here it's the mouse button down, so we've pressed the mouse button
            else if (event.type == SDL_MOUSEBUTTONDOWN) {
                
                // if we're on the gameplay choice menu, to choose the type of game we want to play
                if (is_running_game == GAMEPLAY_CHOICE){
                    
                    // if the button to select a 1v1 game is clicked but nothing has been clicked on before
                    if (is_point_in_rect(event.button.x, event.button.y, buttons[PLAYER_VS_PLAYER_BUTTON]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[PLAYER_VS_PLAYER_BUTTON]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[PLAYER_VS_PLAYER_BUTTON]->rect.x;
                        draw_red_boundary_move.y = buttons[PLAYER_VS_PLAYER_BUTTON]->rect.y;
                        draw_red_boundary_move.w = buttons[PLAYER_VS_PLAYER_BUTTON]->rect.w;
                        draw_red_boundary_move.h = buttons[PLAYER_VS_PLAYER_BUTTON]->rect.h;

                    }

                    // if the button to select a 1vAI game is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[PLAYER_VS_AI_BUTTON]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[PLAYER_VS_AI_BUTTON]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[PLAYER_VS_AI_BUTTON]->rect.x;
                        draw_red_boundary_move.y = buttons[PLAYER_VS_AI_BUTTON]->rect.y;
                        draw_red_boundary_move.w = buttons[PLAYER_VS_AI_BUTTON]->rect.w;
                        draw_red_boundary_move.h = buttons[PLAYER_VS_AI_BUTTON]->rect.h;

                    }

                    // if the button to select a AIvAI game is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[AI_VS_AI_BUTTON]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[AI_VS_AI_BUTTON]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[AI_VS_AI_BUTTON]->rect.x;
                        draw_red_boundary_move.y = buttons[AI_VS_AI_BUTTON]->rect.y;
                        draw_red_boundary_move.w = buttons[AI_VS_AI_BUTTON]->rect.w;
                        draw_red_boundary_move.h = buttons[AI_VS_AI_BUTTON]->rect.h;

                    }

                    // if the button to open a game based on a log file is clicked but nothing has been clicked on before 
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[OPEN_GAME_LOG_BUTTON]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[OPEN_GAME_LOG_BUTTON]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[OPEN_GAME_LOG_BUTTON]->rect.x;
                        draw_red_boundary_move.y = buttons[OPEN_GAME_LOG_BUTTON]->rect.y;
                        draw_red_boundary_move.w = buttons[OPEN_GAME_LOG_BUTTON]->rect.w;
                        draw_red_boundary_move.h = buttons[OPEN_GAME_LOG_BUTTON]->rect.h;

                    }

                    // if the button to quit the game is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[QUIT_BUTTON_GAME_CHOICE]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[QUIT_BUTTON_GAME_CHOICE]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[QUIT_BUTTON_GAME_CHOICE]->rect.x;
                        draw_red_boundary_move.y = buttons[QUIT_BUTTON_GAME_CHOICE]->rect.y;
                        draw_red_boundary_move.w = buttons[QUIT_BUTTON_GAME_CHOICE]->rect.w;
                        draw_red_boundary_move.h = buttons[QUIT_BUTTON_GAME_CHOICE]->rect.h;

                    }

                    // if the button selected is the next button when a click has been done
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[NEXT_BUTTON_GAME_CHOICE]->rect) && is_clicked == true){

                        // updating the click variables
                        is_clicked = false;
                        
                        // setting up the players and going to the next menu depending on the game mode selected
                        // if we previously clicked on the player vs player game mode
                        if (buttons[PLAYER_VS_PLAYER_BUTTON]->state == ACTIVE){
                            game_settings->game_mode = PLAYER_VS_PLAYER;
                            game_settings->white_player_type = HUMAN;
                            game_settings->black_player_type = HUMAN;
                            game_settings->white_AI_difficulty = NONE;
                            game_settings->black_AI_difficulty = NONE;
                            is_running_game = TIME_CHOICE;
                        }
                        // if we previously clicked on the player vs player game mode
                        else if (buttons[PLAYER_VS_AI_BUTTON]->state == ACTIVE){
                            game_settings->game_mode = PLAYER_VS_AI;
                            game_settings->white_player_type = HUMAN;
                            game_settings->black_player_type = AI;
                            game_settings->white_AI_difficulty = NONE;
                            game_settings->black_AI_difficulty = NONE;
                            is_running_game = COLOR_CHOICE;
                        }
                        // if we previously clicked on the player vs player game mode
                        else if (buttons[AI_VS_AI_BUTTON]->state == ACTIVE){
                            game_settings->game_mode = AI_VS_AI;
                            game_settings->white_player_type = AI;
                            game_settings->black_player_type = AI;
                            game_settings->white_AI_difficulty = NONE;
                            game_settings->black_AI_difficulty = NONE;
                            is_running_game = DIFFICULTY_CHOICE_WHITE_AI;
                        }

                        // if we previously clicked on openning a game log
                        if (buttons[OPEN_GAME_LOG_BUTTON]->state == ACTIVE){
                            bool has_opened = false;
                            open_file_and_setup_chess_game(&has_opened);
                            if (has_opened){
                                is_running_game = CHESSBOARD_RENDER;
                            }
                            else {
                                is_running_game = GAMEPLAY_CHOICE;
                            }
                        }
                        // if we previously clicked on the quit button
                        if (buttons[QUIT_BUTTON_GAME_CHOICE]->state == ACTIVE){
                            is_running_game = -1;
                        }

                        // reseting the button state
                        reset_buttons_state();
                        
                    }

                    // if the button selected is the not_next button  when a click has been done
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[NOT_NEXT_BUTTON_GAME_CHOICE]->rect) && is_clicked == true){
                        
                        // updating the click variables
                        is_clicked = false;
                        // reseting the buttons state
                        reset_buttons_state();

                    }

                }

                // if we're in the color choice menu
                else if (is_running_game == COLOR_CHOICE){
                    
                    // if we click on the black button but nothing has been click on before 
                    if (is_point_in_rect(event.button.x, event.button.y, buttons[BLACK_COLOR_BUTTON]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[BLACK_COLOR_BUTTON]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[BLACK_COLOR_BUTTON]->rect.x;
                        draw_red_boundary_move.y = buttons[BLACK_COLOR_BUTTON]->rect.y;
                        draw_red_boundary_move.w = buttons[BLACK_COLOR_BUTTON]->rect.w;
                        draw_red_boundary_move.h = buttons[BLACK_COLOR_BUTTON]->rect.h;

                    }

                    //  if we click on the white button but nothing has been click on before 
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[WHITE_COLOR_BUTTON]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[WHITE_COLOR_BUTTON]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[WHITE_COLOR_BUTTON]->rect.x;
                        draw_red_boundary_move.y = buttons[WHITE_COLOR_BUTTON]->rect.y;
                        draw_red_boundary_move.w = buttons[WHITE_COLOR_BUTTON]->rect.w;
                        draw_red_boundary_move.h = buttons[WHITE_COLOR_BUTTON]->rect.h;

                    }

                    // if the button to quit the game is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[QUIT_BUTTON_COLOR_CHOICE]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[QUIT_BUTTON_COLOR_CHOICE]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[QUIT_BUTTON_COLOR_CHOICE]->rect.x;
                        draw_red_boundary_move.y = buttons[QUIT_BUTTON_COLOR_CHOICE]->rect.y;
                        draw_red_boundary_move.w = buttons[QUIT_BUTTON_COLOR_CHOICE]->rect.w;
                        draw_red_boundary_move.h = buttons[QUIT_BUTTON_COLOR_CHOICE]->rect.h;

                    }

                    // if the button to go to the the main_menu is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect.x;
                        draw_red_boundary_move.y = buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect.y;
                        draw_red_boundary_move.w = buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect.w;
                        draw_red_boundary_move.h = buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect.h;

                    }

                    // if the button to go to back to the previous menu is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[BACK_BUTTON_COLOR_CHOICE]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[BACK_BUTTON_COLOR_CHOICE]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[BACK_BUTTON_COLOR_CHOICE]->rect.x;
                        draw_red_boundary_move.y = buttons[BACK_BUTTON_COLOR_CHOICE]->rect.y;
                        draw_red_boundary_move.w = buttons[BACK_BUTTON_COLOR_CHOICE]->rect.w;
                        draw_red_boundary_move.h = buttons[BACK_BUTTON_COLOR_CHOICE]->rect.h;

                    }

                    // if the button selected is the next button when a click has been done
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[NEXT_BUTTON_COLOR_CHOICE]->rect) && is_clicked == true){
                        
                        // updating the click variables
                        is_clicked = false;
                        
                        // setting up the players
                        // if we previously clicked on the white color
                        if (buttons[WHITE_COLOR_BUTTON]->state == ACTIVE){
                            game_settings->white_player_type = HUMAN;   
                            game_settings->black_player_type = AI;
                        }
                        // if we previously clicked on the black color
                        else if (buttons[BLACK_COLOR_BUTTON]->state == ACTIVE){
                            game_settings->white_player_type = AI;   
                            game_settings->black_player_type = HUMAN;
                        }

                        // if we previously clicked on the quit button
                        if (buttons[QUIT_BUTTON_COLOR_CHOICE]->state == ACTIVE){
                            is_running_game = -1;
                        }
                        // if we previously clicked on the main menu button
                        else if (buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->state == ACTIVE){
                            is_running_game = GAMEPLAY_CHOICE;
                        }
                        // if we previously clicked on the back button
                        else if (buttons[BACK_BUTTON_COLOR_CHOICE]->state == ACTIVE){
                            is_running_game = GAMEPLAY_CHOICE;
                        }
                        // the color choice happens only in one mode the 1vAI mode, and after the color choice we go to the difficulty choice
                        else {
                            is_running_game = DIFFICULTY_CHOICE;
                        }
                       
                        // reseting the button state
                        reset_buttons_state();

                    }

                    // if the button selected is the not_next button  when a click has been done
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[NOT_NEXT_BUTTON_COLOR_CHOICE]->rect) && is_clicked == true){
                        
                        // updating the click variables
                        is_clicked = false;
                        // reseting the buttons state
                        reset_buttons_state();

                    }

                }

                // if we're in the difficulty choice menu when playing 1vAI
                else if (is_running_game == DIFFICULTY_CHOICE){
                    
                    // if the button to select the easy difficulty is clicked but nothing has been clicked on before 
                    if (is_point_in_rect(event.button.x, event.button.y, buttons[LVL1_DIFFICULTY_BUTTON]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[LVL1_DIFFICULTY_BUTTON]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[LVL1_DIFFICULTY_BUTTON]->rect.x;
                        draw_red_boundary_move.y = buttons[LVL1_DIFFICULTY_BUTTON]->rect.y;
                        draw_red_boundary_move.w = buttons[LVL1_DIFFICULTY_BUTTON]->rect.w;
                        draw_red_boundary_move.h = buttons[LVL1_DIFFICULTY_BUTTON]->rect.h;

                    }

                    // if the button to select the medium difficulty is clicked but nothing has been clicked on before 
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[LVL2_DIFFICULTY_BUTTON]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[LVL2_DIFFICULTY_BUTTON]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[LVL2_DIFFICULTY_BUTTON]->rect.x;
                        draw_red_boundary_move.y = buttons[LVL2_DIFFICULTY_BUTTON]->rect.y;
                        draw_red_boundary_move.w = buttons[LVL2_DIFFICULTY_BUTTON]->rect.w;
                        draw_red_boundary_move.h = buttons[LVL2_DIFFICULTY_BUTTON]->rect.h;

                    }

                    // if the button to select the hard difficulty is clicked but nothing has been clicked on before 
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[LVL4_DIFFICULTY_BUTTON]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[LVL4_DIFFICULTY_BUTTON]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[LVL4_DIFFICULTY_BUTTON]->rect.x;
                        draw_red_boundary_move.y = buttons[LVL4_DIFFICULTY_BUTTON]->rect.y;
                        draw_red_boundary_move.w = buttons[LVL4_DIFFICULTY_BUTTON]->rect.w;
                        draw_red_boundary_move.h = buttons[LVL4_DIFFICULTY_BUTTON]->rect.h;
                    
                    }
                    
                    // if the button to select the expert difficulty is clicked but nothing has been clicked on before 
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[LVL7_DIFFICULTY_BUTTON]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[LVL7_DIFFICULTY_BUTTON]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[LVL7_DIFFICULTY_BUTTON]->rect.x;
                        draw_red_boundary_move.y = buttons[LVL7_DIFFICULTY_BUTTON]->rect.y;
                        draw_red_boundary_move.w = buttons[LVL7_DIFFICULTY_BUTTON]->rect.w;
                        draw_red_boundary_move.h = buttons[LVL7_DIFFICULTY_BUTTON]->rect.h;
                    
                    }
                    
                    // if the button to select the expert difficulty is clicked but nothing has been clicked on before 
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[LVL7_DIFFICULTY_BUTTON]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[LVL7_DIFFICULTY_BUTTON]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[LVL7_DIFFICULTY_BUTTON]->rect.x;
                        draw_red_boundary_move.y = buttons[LVL7_DIFFICULTY_BUTTON]->rect.y;
                        draw_red_boundary_move.w = buttons[LVL7_DIFFICULTY_BUTTON]->rect.w;
                        draw_red_boundary_move.h = buttons[LVL7_DIFFICULTY_BUTTON]->rect.h;
                    
                    }

                    // if the button to quit the game is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[QUIT_BUTTON_AI_CHOICE]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[QUIT_BUTTON_AI_CHOICE]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[QUIT_BUTTON_AI_CHOICE]->rect.x;
                        draw_red_boundary_move.y = buttons[QUIT_BUTTON_AI_CHOICE]->rect.y;
                        draw_red_boundary_move.w = buttons[QUIT_BUTTON_AI_CHOICE]->rect.w;
                        draw_red_boundary_move.h = buttons[QUIT_BUTTON_AI_CHOICE]->rect.h;

                    }
               
                    // if the button to go to the the main_menu is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[MAIN_MENU_BUTTON_AI_CHOICE]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[MAIN_MENU_BUTTON_AI_CHOICE]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[MAIN_MENU_BUTTON_AI_CHOICE]->rect.x;
                        draw_red_boundary_move.y = buttons[MAIN_MENU_BUTTON_AI_CHOICE]->rect.y;
                        draw_red_boundary_move.w = buttons[MAIN_MENU_BUTTON_AI_CHOICE]->rect.w;
                        draw_red_boundary_move.h = buttons[MAIN_MENU_BUTTON_AI_CHOICE]->rect.h;

                    }

                    // if the button to go to back to the previous menu is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[BACK_BUTTON_AI_CHOICE]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[BACK_BUTTON_AI_CHOICE]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[BACK_BUTTON_AI_CHOICE]->rect.x;
                        draw_red_boundary_move.y = buttons[BACK_BUTTON_AI_CHOICE]->rect.y;
                        draw_red_boundary_move.w = buttons[BACK_BUTTON_AI_CHOICE]->rect.w;
                        draw_red_boundary_move.h = buttons[BACK_BUTTON_AI_CHOICE]->rect.h;

                    }

                    // if the button selected is the next button when a click has been done
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[NEXT_BUTTON_AI_CHOICE]->rect) && is_clicked == true){
                        
                        // updating the click variables
                        is_clicked = false;
                        
                        // setting up the players
                        // if we previously clicked on the easy difficulty
                        if (buttons[LVL1_DIFFICULTY_BUTTON]->state == ACTIVE){
                            if (game_settings->white_player_type == AI){
                                game_settings->white_AI_difficulty = LVL1;
                                game_settings->black_AI_difficulty = NONE;
                            }
                            else if (game_settings->black_player_type == AI){
                                game_settings->white_AI_difficulty = NONE;
                                game_settings->black_AI_difficulty = LVL1;
                            }
                        }
                        // if we previously clicked on the moderate difficulty
                        else if (buttons[LVL2_DIFFICULTY_BUTTON]->state == ACTIVE){
                            if (game_settings->white_player_type == AI){
                                game_settings->white_AI_difficulty = LVL2;
                                game_settings->black_AI_difficulty = NONE;
                            }
                            else if (game_settings->black_player_type == AI){
                                game_settings->white_AI_difficulty = NONE;
                                game_settings->black_AI_difficulty = LVL2;
                            }
                        }
                        // if we previously clicked on the hard difficulty
                        else if (buttons[LVL4_DIFFICULTY_BUTTON]->state == ACTIVE){
                            if (game_settings->white_player_type == AI){
                                game_settings->white_AI_difficulty = LVL3;
                                game_settings->black_AI_difficulty = NONE;
                            }
                            else if (game_settings->black_player_type == AI){
                                game_settings->white_AI_difficulty = NONE;
                                game_settings->black_AI_difficulty = LVL3;
                            }
                        }
                        // if we previously clicked on the expert difficulty
                        else if (buttons[LVL7_DIFFICULTY_BUTTON]->state == ACTIVE){
                            if (game_settings->white_player_type == AI){
                                game_settings->white_AI_difficulty = LVL7;
                                game_settings->black_AI_difficulty = NONE;
                            }
                            else if (game_settings->black_player_type == AI){
                                game_settings->white_AI_difficulty = NONE;
                                game_settings->black_AI_difficulty = LVL7;
                            }
                        }
                        
                        // if we previously clicked on the quit button
                        if (buttons[QUIT_BUTTON_AI_CHOICE]->state == ACTIVE){
                            is_running_game = -1;
                        }
                        // if we previously clicked on the main menu button
                        else if (buttons[MAIN_MENU_BUTTON_AI_CHOICE]->state == ACTIVE){
                            is_running_game = GAMEPLAY_CHOICE;
                        }
                        // if we previously clicked on the back button
                        else if (buttons[BACK_BUTTON_AI_CHOICE]->state == ACTIVE){
                            is_running_game = COLOR_CHOICE;
                        }
                        // the difficulty choice happens only in one mode the 1vAI mode, and after the difficulty choice we go to the time choice
                        else {
                            is_running_game = TIME_CHOICE;  
                        }

                        // reseting the button state
                        reset_buttons_state();

                    }

                    // if the button selected is the not_next button  when a click has been done
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[NOT_NEXT_BUTTON_AI_CHOICE]->rect) && is_clicked == true){
                        
                        // updating the click variables
                        is_clicked = false;
                        // reseting the buttons state
                        reset_buttons_state();

                    }

                }

                // if we're in the white AI difficulty choice menu when playing AIvAI
                else if (is_running_game == DIFFICULTY_CHOICE_WHITE_AI){
                    
                    // if the button to select the easy difficulty is clicked but nothing has been clicked on before 
                    if (is_point_in_rect(event.button.x, event.button.y, buttons[LVL1_DIFFICULTY_BUTTON]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[LVL1_DIFFICULTY_BUTTON]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[LVL1_DIFFICULTY_BUTTON]->rect.x;
                        draw_red_boundary_move.y = buttons[LVL1_DIFFICULTY_BUTTON]->rect.y;
                        draw_red_boundary_move.w = buttons[LVL1_DIFFICULTY_BUTTON]->rect.w;
                        draw_red_boundary_move.h = buttons[LVL1_DIFFICULTY_BUTTON]->rect.h;

                    }

                    // if the button to select the medium difficulty is clicked but nothing has been clicked on before 
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[LVL2_DIFFICULTY_BUTTON]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[LVL2_DIFFICULTY_BUTTON]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[LVL2_DIFFICULTY_BUTTON]->rect.x;
                        draw_red_boundary_move.y = buttons[LVL2_DIFFICULTY_BUTTON]->rect.y;
                        draw_red_boundary_move.w = buttons[LVL2_DIFFICULTY_BUTTON]->rect.w;
                        draw_red_boundary_move.h = buttons[LVL2_DIFFICULTY_BUTTON]->rect.h;

                    }

                    // if the button to select the hard difficulty is clicked but nothing has been clicked on before 
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[LVL4_DIFFICULTY_BUTTON]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[LVL4_DIFFICULTY_BUTTON]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[LVL4_DIFFICULTY_BUTTON]->rect.x;
                        draw_red_boundary_move.y = buttons[LVL4_DIFFICULTY_BUTTON]->rect.y;
                        draw_red_boundary_move.w = buttons[LVL4_DIFFICULTY_BUTTON]->rect.w;
                        draw_red_boundary_move.h = buttons[LVL4_DIFFICULTY_BUTTON]->rect.h;
                    
                    }
                    
                    // if the button to select the expert difficulty is clicked but nothing has been clicked on before 
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[LVL7_DIFFICULTY_BUTTON]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[LVL7_DIFFICULTY_BUTTON]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[LVL7_DIFFICULTY_BUTTON]->rect.x;
                        draw_red_boundary_move.y = buttons[LVL7_DIFFICULTY_BUTTON]->rect.y;
                        draw_red_boundary_move.w = buttons[LVL7_DIFFICULTY_BUTTON]->rect.w;
                        draw_red_boundary_move.h = buttons[LVL7_DIFFICULTY_BUTTON]->rect.h;
                    
                    }

                    // if the button to quit the game is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[QUIT_BUTTON_AI_CHOICE]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[QUIT_BUTTON_AI_CHOICE]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[QUIT_BUTTON_AI_CHOICE]->rect.x;
                        draw_red_boundary_move.y = buttons[QUIT_BUTTON_AI_CHOICE]->rect.y;
                        draw_red_boundary_move.w = buttons[QUIT_BUTTON_AI_CHOICE]->rect.w;
                        draw_red_boundary_move.h = buttons[QUIT_BUTTON_AI_CHOICE]->rect.h;

                    }
               
                    // if the button to go to the the main_menu is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[MAIN_MENU_BUTTON_AI_CHOICE]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[MAIN_MENU_BUTTON_AI_CHOICE]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[MAIN_MENU_BUTTON_AI_CHOICE]->rect.x;
                        draw_red_boundary_move.y = buttons[MAIN_MENU_BUTTON_AI_CHOICE]->rect.y;
                        draw_red_boundary_move.w = buttons[MAIN_MENU_BUTTON_AI_CHOICE]->rect.w;
                        draw_red_boundary_move.h = buttons[MAIN_MENU_BUTTON_AI_CHOICE]->rect.h;

                    }

                    // if the button to go to back to the previous menu is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[BACK_BUTTON_AI_CHOICE]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[BACK_BUTTON_AI_CHOICE]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[BACK_BUTTON_AI_CHOICE]->rect.x;
                        draw_red_boundary_move.y = buttons[BACK_BUTTON_AI_CHOICE]->rect.y;
                        draw_red_boundary_move.w = buttons[BACK_BUTTON_AI_CHOICE]->rect.w;
                        draw_red_boundary_move.h = buttons[BACK_BUTTON_AI_CHOICE]->rect.h;

                    }

                    // if the button selected is the next button when a click has been done
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[NEXT_BUTTON_AI_CHOICE]->rect) && is_clicked == true){
                        
                        // updating the click variables
                        is_clicked = false;
                        
                        // setting up the players
                        // if we previously clicked on the easy difficulty
                        if (buttons[LVL1_DIFFICULTY_BUTTON]->state == ACTIVE){
                            game_settings->white_AI_difficulty = LVL1;
                        }
                        // if we previously clicked on the moderate difficulty
                        else if (buttons[LVL2_DIFFICULTY_BUTTON]->state == ACTIVE){
                            game_settings->white_AI_difficulty = LVL2;
                        }
                        // if we previously clicked on the hard difficulty
                        else if (buttons[LVL4_DIFFICULTY_BUTTON]->state == ACTIVE){
                            game_settings->white_AI_difficulty = LVL4;
                        }
                        // if we previously clicked on the expert difficulty
                        else if (buttons[LVL7_DIFFICULTY_BUTTON]->state == ACTIVE){
                            game_settings->white_AI_difficulty = LVL7;
                        }
                        
                        // if we previously clicked on the quit button
                        if (buttons[QUIT_BUTTON_AI_CHOICE]->state == ACTIVE){
                            is_running_game = -1;
                        }
                        // if we previously clicked on the main menu button
                        else if (buttons[MAIN_MENU_BUTTON_AI_CHOICE]->state == ACTIVE){
                            is_running_game = GAMEPLAY_CHOICE;
                        }
                        // if we previously clicked on the back button
                        else if (buttons[BACK_BUTTON_AI_CHOICE]->state == ACTIVE){
                            is_running_game = GAMEPLAY_CHOICE;
                        }
                        // the difficulty of the white AI has been chosen, we go to the difficulty choice of the black AI
                        else {
                            is_running_game = DIFFICULTY_CHOICE_BLACK_AI;  
                        }

                        // reseting the button state
                        reset_buttons_state();

                    }

                    // if the button selected is the not_next button  when a click has been done
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[NOT_NEXT_BUTTON_AI_CHOICE]->rect) && is_clicked == true){
                        
                        // updating the click variables
                        is_clicked = false;
                        // reseting the buttons state
                        reset_buttons_state();

                    }
                    
                }

                // if we're in the black AI difficulty choice menu when playing AIvAI
                else if (is_running_game == DIFFICULTY_CHOICE_BLACK_AI){
                    
                    // if the button to select the easy difficulty is clicked but nothing has been clicked on before 
                    if (is_point_in_rect(event.button.x, event.button.y, buttons[LVL1_DIFFICULTY_BUTTON]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[LVL1_DIFFICULTY_BUTTON]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[LVL1_DIFFICULTY_BUTTON]->rect.x;
                        draw_red_boundary_move.y = buttons[LVL1_DIFFICULTY_BUTTON]->rect.y;
                        draw_red_boundary_move.w = buttons[LVL1_DIFFICULTY_BUTTON]->rect.w;
                        draw_red_boundary_move.h = buttons[LVL1_DIFFICULTY_BUTTON]->rect.h;

                    }

                    // if the button to select the medium difficulty is clicked but nothing has been clicked on before 
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[LVL2_DIFFICULTY_BUTTON]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[LVL2_DIFFICULTY_BUTTON]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[LVL2_DIFFICULTY_BUTTON]->rect.x;
                        draw_red_boundary_move.y = buttons[LVL2_DIFFICULTY_BUTTON]->rect.y;
                        draw_red_boundary_move.w = buttons[LVL2_DIFFICULTY_BUTTON]->rect.w;
                        draw_red_boundary_move.h = buttons[LVL2_DIFFICULTY_BUTTON]->rect.h;

                    }
                    
                    // if the button to select the hard difficulty is clicked but nothing has been clicked on before 
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[LVL4_DIFFICULTY_BUTTON]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[LVL4_DIFFICULTY_BUTTON]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[LVL4_DIFFICULTY_BUTTON]->rect.x;
                        draw_red_boundary_move.y = buttons[LVL4_DIFFICULTY_BUTTON]->rect.y;
                        draw_red_boundary_move.w = buttons[LVL4_DIFFICULTY_BUTTON]->rect.w;
                        draw_red_boundary_move.h = buttons[LVL4_DIFFICULTY_BUTTON]->rect.h;
                    
                    }
                    
                    // if the button to select the expert difficulty is clicked but nothing has been clicked on before 
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[LVL7_DIFFICULTY_BUTTON]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[LVL7_DIFFICULTY_BUTTON]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[LVL7_DIFFICULTY_BUTTON]->rect.x;
                        draw_red_boundary_move.y = buttons[LVL7_DIFFICULTY_BUTTON]->rect.y;
                        draw_red_boundary_move.w = buttons[LVL7_DIFFICULTY_BUTTON]->rect.w;
                        draw_red_boundary_move.h = buttons[LVL7_DIFFICULTY_BUTTON]->rect.h;
                    
                    }

                    // if the button to quit the game is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[QUIT_BUTTON_AI_CHOICE]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[QUIT_BUTTON_AI_CHOICE]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[QUIT_BUTTON_AI_CHOICE]->rect.x;
                        draw_red_boundary_move.y = buttons[QUIT_BUTTON_AI_CHOICE]->rect.y;
                        draw_red_boundary_move.w = buttons[QUIT_BUTTON_AI_CHOICE]->rect.w;
                        draw_red_boundary_move.h = buttons[QUIT_BUTTON_AI_CHOICE]->rect.h;

                    }
               
                    // if the button to go to the the main_menu is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[MAIN_MENU_BUTTON_AI_CHOICE]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[MAIN_MENU_BUTTON_AI_CHOICE]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[MAIN_MENU_BUTTON_AI_CHOICE]->rect.x;
                        draw_red_boundary_move.y = buttons[MAIN_MENU_BUTTON_AI_CHOICE]->rect.y;
                        draw_red_boundary_move.w = buttons[MAIN_MENU_BUTTON_AI_CHOICE]->rect.w;
                        draw_red_boundary_move.h = buttons[MAIN_MENU_BUTTON_AI_CHOICE]->rect.h;

                    }

                    // if the button to go to back to the previous menu is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[BACK_BUTTON_AI_CHOICE]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[BACK_BUTTON_AI_CHOICE]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[BACK_BUTTON_AI_CHOICE]->rect.x;
                        draw_red_boundary_move.y = buttons[BACK_BUTTON_AI_CHOICE]->rect.y;
                        draw_red_boundary_move.w = buttons[BACK_BUTTON_AI_CHOICE]->rect.w;
                        draw_red_boundary_move.h = buttons[BACK_BUTTON_AI_CHOICE]->rect.h;

                    }

                    // if the button selected is the next button when a click has been done
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[NEXT_BUTTON_AI_CHOICE]->rect) && is_clicked == true){
                        
                        // updating the click variables
                        is_clicked = false;
                        
                        // setting up the players
                        // if we previously clicked on the easy difficulty
                        if (buttons[LVL1_DIFFICULTY_BUTTON]->state == ACTIVE){
                            game_settings->black_AI_difficulty = LVL1;
                        }
                        // if we previously clicked on the moderate difficulty
                        else if (buttons[LVL2_DIFFICULTY_BUTTON]->state == ACTIVE){
                            game_settings->black_AI_difficulty = LVL2;
                        }
                        // if we previously clicked on the hard difficulty
                        else if (buttons[LVL4_DIFFICULTY_BUTTON]->state == ACTIVE){
                            game_settings->black_AI_difficulty = LVL4;
                        }
                        // if we previously clicked on the expert difficulty
                        else if (buttons[LVL7_DIFFICULTY_BUTTON]->state == ACTIVE){
                            game_settings->black_AI_difficulty = LVL7;
                        }
                        
                        // if we previously clicked on the quit button
                        if (buttons[QUIT_BUTTON_AI_CHOICE]->state == ACTIVE){
                            is_running_game = -1;
                        }
                        // if we previously clicked on the main menu button
                        else if (buttons[MAIN_MENU_BUTTON_AI_CHOICE]->state == ACTIVE){
                            is_running_game = GAMEPLAY_CHOICE;
                        }
                        // if we previously clicked on the back button
                        else if (buttons[BACK_BUTTON_AI_CHOICE]->state == ACTIVE){
                            is_running_game = DIFFICULTY_CHOICE_WHITE_AI;
                        }
                        // the difficulty of the black AI has been chosen, we go to the time choice
                        else {
                            is_running_game = TIME_CHOICE;  
                        }

                        // reseting the button state
                        reset_buttons_state();

                    }

                    // if the button selected is the not_next button  when a click has been done
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[NOT_NEXT_BUTTON_AI_CHOICE]->rect) && is_clicked == true){
                        
                        // updating the click variables
                        is_clicked = false;
                        // reseting the buttons state
                        reset_buttons_state();

                    }
                
                }

                // if we're in the time choice menu
                else if (is_running_game == TIME_CHOICE){
                    
                    // if the button to select the short blitz time mode is clicked but nothing has been clicked on before
                    if (is_point_in_rect(event.button.x, event.button.y, buttons[SHORT_BLITZ_BUTTON]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[SHORT_BLITZ_BUTTON]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[SHORT_BLITZ_BUTTON]->rect.x;
                        draw_red_boundary_move.y = buttons[SHORT_BLITZ_BUTTON]->rect.y;
                        draw_red_boundary_move.w = buttons[SHORT_BLITZ_BUTTON]->rect.w;
                        draw_red_boundary_move.h = buttons[SHORT_BLITZ_BUTTON]->rect.h;

                    }

                    // if the button to select the long blitz time mode is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[LONG_BLITZ_BUTTON]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[LONG_BLITZ_BUTTON]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[LONG_BLITZ_BUTTON]->rect.x;
                        draw_red_boundary_move.y = buttons[LONG_BLITZ_BUTTON]->rect.y;
                        draw_red_boundary_move.w = buttons[LONG_BLITZ_BUTTON]->rect.w;
                        draw_red_boundary_move.h = buttons[LONG_BLITZ_BUTTON]->rect.h;

                    }

                    // if the button to select the short time mode is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[SHORT_BUTTON]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[SHORT_BUTTON]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[SHORT_BUTTON]->rect.x;
                        draw_red_boundary_move.y = buttons[SHORT_BUTTON]->rect.y;
                        draw_red_boundary_move.w = buttons[SHORT_BUTTON]->rect.w;
                        draw_red_boundary_move.h = buttons[SHORT_BUTTON]->rect.h;

                    }

                    // if the button to select the moderate time mode is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[MODERATE_BUTTON]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[MODERATE_BUTTON]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[MODERATE_BUTTON]->rect.x;
                        draw_red_boundary_move.y = buttons[MODERATE_BUTTON]->rect.y;
                        draw_red_boundary_move.w = buttons[MODERATE_BUTTON]->rect.w;
                        draw_red_boundary_move.h = buttons[MODERATE_BUTTON]->rect.h;

                    }

                    // if the button to select the long time mode is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[LONG_BUTTON]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[LONG_BUTTON]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[LONG_BUTTON]->rect.x;
                        draw_red_boundary_move.y = buttons[LONG_BUTTON]->rect.y;
                        draw_red_boundary_move.w = buttons[LONG_BUTTON]->rect.w;
                        draw_red_boundary_move.h = buttons[LONG_BUTTON]->rect.h;

                    }

                    // if the button to quit the game is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[QUIT_BUTTON_TIME_CHOICE]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[QUIT_BUTTON_TIME_CHOICE]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[QUIT_BUTTON_TIME_CHOICE]->rect.x;
                        draw_red_boundary_move.y = buttons[QUIT_BUTTON_TIME_CHOICE]->rect.y;
                        draw_red_boundary_move.w = buttons[QUIT_BUTTON_TIME_CHOICE]->rect.w;
                        draw_red_boundary_move.h = buttons[QUIT_BUTTON_TIME_CHOICE]->rect.h;

                    }

                    // if the button to go to the the main_menu is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect.x;
                        draw_red_boundary_move.y = buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect.y;
                        draw_red_boundary_move.w = buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect.w;
                        draw_red_boundary_move.h = buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect.h;

                    }

                    // if the button to go to back to the previous menu is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[BACK_BUTTON_TIME_CHOICE]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[BACK_BUTTON_TIME_CHOICE]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[BACK_BUTTON_TIME_CHOICE]->rect.x;
                        draw_red_boundary_move.y = buttons[BACK_BUTTON_TIME_CHOICE]->rect.y;
                        draw_red_boundary_move.w = buttons[BACK_BUTTON_TIME_CHOICE]->rect.w;
                        draw_red_boundary_move.h = buttons[BACK_BUTTON_TIME_CHOICE]->rect.h;

                    }

                    // if the button selected is the load button when a click has been done
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[LOAD_BUTTON]->rect) && is_clicked == true){
                        
                        // updating the click variables
                        is_clicked = false;
                        
                        // setting up the players
                        // if we previously clicked on the short blitz time mode
                        if (buttons[SHORT_BLITZ_BUTTON]->state == ACTIVE){
                            game_settings->time_mode = SHORT_BLITZ;
                            // a short blitz game is a game with 3 minutes for each player, each play give 5 seconds to the player that played it
                            game_settings->time_at_start = 3*60;
                            game_settings->white_time_remaining = 3*60;
                            game_settings->black_time_remaining = 3*60;
                            game_settings->blitz_time = 5;
                            game_settings->is_game_lost_on_time = false;
                        }
                        // if we previously clicked on the long blitz time mode
                        else if (buttons[LONG_BLITZ_BUTTON]->state == ACTIVE){
                            game_settings->time_mode = LONG_BLITZ;
                            // a long blitz game is a game with 5 minutes for each player, each play give 3 seconds to the player that played it
                            game_settings->time_at_start = 5*60;
                            game_settings->white_time_remaining = 5*60;
                            game_settings->black_time_remaining = 5*60;
                            game_settings->blitz_time = 3;
                            game_settings->is_game_lost_on_time = false;
                        }
                        // if we previously clicked on the short time mode
                        else if (buttons[SHORT_BUTTON]->state == ACTIVE){
                            game_settings->time_mode = SHORT;
                            // a short game is a game with 10 minutes for each player, no time is given after a play
                            game_settings->time_at_start = 10*60;
                            game_settings->white_time_remaining = 10*60;
                            game_settings->black_time_remaining = 10*60;
                            game_settings->blitz_time = 0;
                            game_settings->is_game_lost_on_time = false;
                        }
                        // if we previously clicked on the moderate time mode
                        else if (buttons[MODERATE_BUTTON]->state == ACTIVE){
                            game_settings->time_mode = MODERATE;
                            // a moderate game is a game with 30 minutes for each player, no time is given after a play
                            game_settings->time_at_start = 30*60;
                            game_settings->white_time_remaining = 30*60;
                            game_settings->black_time_remaining = 30*60;
                            game_settings->blitz_time = 0;
                            game_settings->is_game_lost_on_time = false;
                        }
                        // if we previously clicked on the long time mode
                        else if (buttons[LONG_BUTTON]->state == ACTIVE){
                            game_settings->time_mode = LONG;
                            // a long game is a game with 60 minutes for each player, no time is given after a play
                            game_settings->time_at_start = 60*60;
                            game_settings->white_time_remaining = 60*60;
                            game_settings->black_time_remaining = 60*60;
                            game_settings->blitz_time = 0;
                            game_settings->is_game_lost_on_time = false;
                        }
                        
                        // if we previously clicked on the quit button
                        if (buttons[QUIT_BUTTON_TIME_CHOICE]->state == ACTIVE){
                            is_running_game = -1;
                        }
                        // if we previously clicked on the main menu button
                        else if (buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->state == ACTIVE){
                            is_running_game = GAMEPLAY_CHOICE;
                        }
                        // if we previously clicked on the back button
                        else if (buttons[BACK_BUTTON_TIME_CHOICE]->state == ACTIVE){
                            // depending on the game mode we go back to different menus
                            if (game_settings->game_mode == PLAYER_VS_PLAYER){
                                is_running_game = GAMEPLAY_CHOICE;
                            }
                            else if (game_settings->game_mode == PLAYER_VS_AI){
                                is_running_game = DIFFICULTY_CHOICE;
                            }
                            else if (game_settings->game_mode == AI_VS_AI){
                                is_running_game = DIFFICULTY_CHOICE_BLACK_AI;
                            }
                        }
                        // the time choice happens happens in all mode and is the one before the game start
                        else {
                            is_running_game = CHESSBOARD_RENDER;
                        }

                        // reseting the button state
                        reset_buttons_state();

                    }

                    // if the button selected is the not_load button  when a click has been done
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[NOT_LOAD_BUTTON]->rect) && is_clicked == true){
                        
                        // updating the click variables
                        is_clicked = false;
                        // reseting the buttons state
                        reset_buttons_state();

                    }
                
                }

                // if we're on in the game
                else if (is_running_game == CHESSBOARD_RENDER){

                    // making the translation of the mouse click to the row and the column of the board
                    int row = (event.button.y-WINDOW_TOP_MARGIN) / SQUARE_SIZE;
                    int col = (event.button.x-WINDOW_LEFT_MARGIN) / SQUARE_SIZE;

                    // we need to know if the player playing if human 
                    bool is_player_playing_human = true;
                    if (game_settings->player_that_is_playing == White_Player && game_settings->white_player_type == AI){
                        is_player_playing_human = false;
                    }
                    else if (game_settings->player_that_is_playing == Black_Player && game_settings->black_player_type == AI){
                        is_player_playing_human = false;
                    }

                    // if we click on the board, for a human player when the match has started and there is no pawn promotion happening
                    // it's for the click that is selecting a piece
                    if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE && is_clicked == false && is_clicked_on_board == false && game_settings->has_match_started == true && is_player_playing_human == true && game_settings->is_pawn_promotion_happening == false){

                        // get from where the move started (board index are not the same as what we think when we see the board)
                        from_index = get_index(7-row, col);
                        // useful for printing the piece deplacement
                        selected_piece_index = from_index;
                        // to use the movement of the piece
                        piece_movement_rect.x = col * SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_LEFT_MARGIN;
                        piece_movement_rect.y = row * SQUARE_SIZE+SQUARE_SIZE/2+WINDOW_TOP_MARGIN;
                        // to keep track to where to put the selected piece if the move don't work
                        previous_piece_movement_x = piece_movement_rect.x;
                        previous_piece_movement_y = piece_movement_rect.y;
                        // draw the red boundary here since it's the first click and the destination is not yet selected, it's the start of the move
                        draw_red_boundary_move.x = col * SQUARE_SIZE+WINDOW_LEFT_MARGIN;
                        draw_red_boundary_move.y = row * SQUARE_SIZE+WINDOW_TOP_MARGIN;
                        draw_red_boundary_move.w = SQUARE_SIZE;
                        draw_red_boundary_move.h = SQUARE_SIZE;
                        // if we play with the black pieces, we need to reverse the row (against an IA or in a 1V1)
                        if (game_settings->black_player_type == HUMAN && game_settings->player_that_is_playing == Black_Player){
                            from_index = get_index(row, 7-col);
                            selected_piece_index = from_index;
                        }
                        // the first click has been made
                        is_clicked = true;
                        // the click on the board has been made 
                        is_clicked_on_board = true;

                    }
                    
                    // if the pawn promotion is happening, we need to know which piece the player wants to promote the pawn to (some buttons still need to be available)
                    else if (game_settings->is_pawn_promotion_happening == true){
                        
                        // if we cliked on the queen button, then we need to udpate the type of the pawn that has been promoted in the log and on the board
                        // we also need to tell that the pawn promotion is not happening anymore
                        
                        // if we select the queen button
                        if (is_point_in_rect(event.button.x, event.button.y, buttons[QUEEN_BUTTON]->rect)){
                            
                            // updating the click variables
                            is_clicked = true;
                            // updating the state of the button
                            buttons[QUEEN_BUTTON]->state = ACTIVE;
                            // draw the red rectangle circling the button clicked on
                            draw_red_boundary_move.x = buttons[QUEEN_BUTTON]->rect.x;
                            draw_red_boundary_move.y = buttons[QUEEN_BUTTON]->rect.y;
                            draw_red_boundary_move.w = buttons[QUEEN_BUTTON]->rect.w;
                            draw_red_boundary_move.h = buttons[QUEEN_BUTTON]->rect.h;

                        }

                        // if we select the rook button but nothing has been clicked on before
                        else if (is_point_in_rect(event.button.x, event.button.y, buttons[ROOK_BUTTON]->rect) && is_clicked == false){
                            
                            // updating the click variables
                            is_clicked = true;
                            // updating the state of the button
                            buttons[ROOK_BUTTON]->state = ACTIVE;
                            // draw the red rectangle circling the button clicked on
                            draw_red_boundary_move.x = buttons[ROOK_BUTTON]->rect.x;
                            draw_red_boundary_move.y = buttons[ROOK_BUTTON]->rect.y;
                            draw_red_boundary_move.w = buttons[ROOK_BUTTON]->rect.w;
                            draw_red_boundary_move.h = buttons[ROOK_BUTTON]->rect.h;

                        }

                        // if we select the bishop button but nothing has been clicked on before
                        else if (is_point_in_rect(event.button.x, event.button.y, buttons[BISHOP_BUTTON]->rect) && is_clicked == false){
                            
                            // updating the click variables
                            is_clicked = true;
                            // updating the state of the button
                            buttons[BISHOP_BUTTON]->state = ACTIVE;
                            // draw the red rectangle circling the button clicked on
                            draw_red_boundary_move.x = buttons[BISHOP_BUTTON]->rect.x;
                            draw_red_boundary_move.y = buttons[BISHOP_BUTTON]->rect.y;
                            draw_red_boundary_move.w = buttons[BISHOP_BUTTON]->rect.w;
                            draw_red_boundary_move.h = buttons[BISHOP_BUTTON]->rect.h;

                        }

                        // if we select the knight button but nothing has been clicked on before
                        else if (is_point_in_rect(event.button.x, event.button.y, buttons[KNIGHT_BUTTON]->rect) && is_clicked == false){
                            
                            // updating the click variables
                            is_clicked = true;
                            // updating the state of the button
                            buttons[KNIGHT_BUTTON]->state = ACTIVE;
                            // draw the red rectangle circling the button clicked on
                            draw_red_boundary_move.x = buttons[KNIGHT_BUTTON]->rect.x;
                            draw_red_boundary_move.y = buttons[KNIGHT_BUTTON]->rect.y;
                            draw_red_boundary_move.w = buttons[KNIGHT_BUTTON]->rect.w;
                            draw_red_boundary_move.h = buttons[KNIGHT_BUTTON]->rect.h;

                        }

                        // if we select the quit button but nothing has been clicked on before
                        else if (is_point_in_rect(event.button.x, event.button.y, buttons[QUIT_BUTTON_IN_GAME]->rect) && is_clicked == false){
                            
                            // updating the click variables
                            is_clicked = true;
                            // updating the state of the button
                            buttons[QUIT_BUTTON_IN_GAME]->state = ACTIVE;
                            // draw the red rectangle circling the button clicked on
                            draw_red_boundary_move.x = buttons[QUIT_BUTTON_IN_GAME]->rect.x;
                            draw_red_boundary_move.y = buttons[QUIT_BUTTON_IN_GAME]->rect.y;
                            draw_red_boundary_move.w = buttons[QUIT_BUTTON_IN_GAME]->rect.w;
                            draw_red_boundary_move.h = buttons[QUIT_BUTTON_IN_GAME]->rect.h;

                        }
                        
                        // if we select the next button but nothing has been clicked on before
                        else if (is_point_in_rect(event.button.x, event.button.y, buttons[NEXT_BUTTON_IN_GAME]->rect) && is_clicked == true){
                            
                            // updating the click variables
                            is_clicked = false;
                            
                            // if we previously clicked on the queen button
                            if (buttons[QUEEN_BUTTON]->state == ACTIVE){
                                if (game_settings->color_of_pawn_promotion == Black_Player){
                                    // updating the type of the pawn that has been promoted in the log 
                                    add_flag_to_move(&chess_log->moves[chess_log->actual_size-1]->move_value, Promote_To_Queen_Flag);
                                    // updating the board
                                    bitboards[PAWN_BLACK] &= ~(1ULL << get_to_square(chess_log->moves[chess_log->actual_size-1]->move_value));
                                    bitboards[QUEEN_BLACK] |= (1ULL << get_to_square(chess_log->moves[chess_log->actual_size-1]->move_value));
                                }
                                else if (game_settings->color_of_pawn_promotion == White_Player){
                                    // updating the type of the pawn that has been promoted in the log
                                    add_flag_to_move(&chess_log->moves[chess_log->actual_size-1]->move_value, Promote_To_Queen_Flag);
                                    // updating the board
                                    bitboards[PAWN_WHITE] &= ~(1ULL << get_to_square(chess_log->moves[chess_log->actual_size-1]->move_value));
                                    bitboards[QUEEN_WHITE] |= (1ULL << get_to_square(chess_log->moves[chess_log->actual_size-1]->move_value));
                                }
                            }
                            // if we previously clicked on the rook button
                            else if (buttons[ROOK_BUTTON]->state == ACTIVE){
                                if (game_settings->color_of_pawn_promotion == Black_Player){
                                    // updating the type of the pawn that has been promoted in the log
                                    add_flag_to_move(&chess_log->moves[chess_log->actual_size-1]->move_value, Promote_To_Rook_Flag);
                                    // updating the board
                                    bitboards[PAWN_BLACK] &= ~(1ULL << get_to_square(chess_log->moves[chess_log->actual_size-1]->move_value));
                                    bitboards[ROOK_BLACK] |= (1ULL << get_to_square(chess_log->moves[chess_log->actual_size-1]->move_value));
                                }
                                else if (game_settings->color_of_pawn_promotion == White_Player){
                                    // updating the type of the pawn that has been promoted in the log
                                    add_flag_to_move(&chess_log->moves[chess_log->actual_size-1]->move_value, Promote_To_Rook_Flag);
                                    // updating the board
                                    bitboards[PAWN_WHITE] &= ~(1ULL << get_to_square(chess_log->moves[chess_log->actual_size-1]->move_value));
                                    bitboards[ROOK_WHITE] |= (1ULL << get_to_square(chess_log->moves[chess_log->actual_size-1]->move_value));
                                }
                            }
                            // if we previously clicked on the bishop button
                            else if (buttons[BISHOP_BUTTON]->state == ACTIVE){
                                if (game_settings->color_of_pawn_promotion == Black_Player){
                                    // updating the type of the pawn that has been promoted in the log
                                    add_flag_to_move(&chess_log->moves[chess_log->actual_size-1]->move_value, Promote_To_Bishop_Flag);
                                    // updating the board
                                    bitboards[PAWN_BLACK] &= ~(1ULL << get_to_square(chess_log->moves[chess_log->actual_size-1]->move_value));
                                    bitboards[BISHOP_BLACK] |= (1ULL << get_to_square(chess_log->moves[chess_log->actual_size-1]->move_value));
                                }
                                else if (game_settings->color_of_pawn_promotion == White_Player){
                                    // updating the type of the pawn that has been promoted in the log
                                    add_flag_to_move(&chess_log->moves[chess_log->actual_size-1]->move_value, Promote_To_Bishop_Flag);
                                    // updating the board
                                    bitboards[PAWN_WHITE] &= ~(1ULL << get_to_square(chess_log->moves[chess_log->actual_size-1]->move_value));
                                    bitboards[BISHOP_WHITE] |= (1ULL << get_to_square(chess_log->moves[chess_log->actual_size-1]->move_value));
                                }
                            }
                            // if we previously clicked on the knight button
                            else if (buttons[KNIGHT_BUTTON]->state == ACTIVE){
                                if (game_settings->color_of_pawn_promotion == Black_Player){
                                    // updating the type of the pawn that has been promoted in the log
                                    add_flag_to_move(&chess_log->moves[chess_log->actual_size-1]->move_value, Promote_To_Knight_Flag);
                                    // updating the board
                                    bitboards[PAWN_BLACK] &= ~(1ULL << get_to_square(chess_log->moves[chess_log->actual_size-1]->move_value));
                                    bitboards[KNIGHT_BLACK] |= (1ULL << get_to_square(chess_log->moves[chess_log->actual_size-1]->move_value));
                                }
                                else if (game_settings->color_of_pawn_promotion == White_Player){
                                    // updating the type of the pawn that has been promoted in the log
                                    add_flag_to_move(&chess_log->moves[chess_log->actual_size-1]->move_value, Promote_To_Knight_Flag);
                                    // updating the board
                                    bitboards[PAWN_WHITE] &= ~(1ULL << get_to_square(chess_log->moves[chess_log->actual_size-1]->move_value));
                                    bitboards[KNIGHT_WHITE] |= (1ULL << get_to_square(chess_log->moves[chess_log->actual_size-1]->move_value));
                                }
                            }

                            // stating that the pawn promotion is not happening anymore
                            game_settings->is_pawn_promotion_happening = false;
                            // reseting the button state
                            reset_buttons_state();
                            
                            goto end_promotion; // it put us directly at the part where we need to update the check state of the kings in the log after the move
                        }

                        // if we select the not_next button but nothing has been clicked on before
                        else if (is_point_in_rect(event.button.x, event.button.y, buttons[NOT_NEXT_BUTTON_IN_GAME]->rect) && is_clicked == true){
                            
                            // updating the click variables
                            is_clicked = false;
                            // reseting the buttons state
                            reset_buttons_state();

                        }
                    
                    }

                    // if the button to start the game is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[START_BUTTON_IN_GAME]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[START_BUTTON_IN_GAME]->state = ACTIVE;

                    }

                    // if the button to restart the game is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[RESTART_BUTTON_IN_GAME]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[RESTART_BUTTON_IN_GAME]->state = ACTIVE;

                    }

                    // if the button to have a new game is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[NEW_GAME_BUTTON_IN_GAME]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[NEW_GAME_BUTTON_IN_GAME]->state = ACTIVE;

                    }

                    // if the button to quit the game is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[QUIT_BUTTON_IN_GAME]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[QUIT_BUTTON_IN_GAME]->state = ACTIVE;

                    }

                    // if the button to undo the last move is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[UNDO_BUTTON_IN_GAME]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[UNDO_BUTTON_IN_GAME]->state = ACTIVE;

                    }

                    // if the button to download the game log is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[DL_LOG_IN_GAME_BUTTON]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[DL_LOG_IN_GAME_BUTTON]->state = ACTIVE;

                    }

                    // if the button to make a pause is clicked on but nothing has been clicked on before, the game will need to be in AI vs AI mode
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[PAUSE_BUTTON]->rect) && is_clicked == false && (game_settings->game_mode == AI_VS_AI || game_settings->game_mode == PLAYER_VS_AI)){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[PAUSE_BUTTON]->state = ACTIVE;

                    }
                    
                    // if the button selected is the next button when a click has been done
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[NEXT_BUTTON_IN_GAME]->rect) && is_clicked == true){
                        
                        // updating the click variables
                        is_clicked = false;
                        
                        // if we previously clicked on the start button
                        if (buttons[START_BUTTON_IN_GAME]->state == ACTIVE){
                            // the game has started
                            game_settings->has_match_started = true;
                            last_time_recorded = SDL_GetTicks();
                            // play the sound of the start of the game
                            play_sound("../../Sounds/chessstart.wav");
                        }
                        // if we previously clicked on the restart button
                        else if (buttons[RESTART_BUTTON_IN_GAME]->state == ACTIVE){
                            // we need to reset the game
                            is_running_game = CHESSBOARD_RENDER;
                            // we reset the good settings parameters for the game
                            game_settings->player_that_is_playing = White_Player;
                            game_settings->color_of_player_that_is_playing = WHITE;
                            game_settings->loosing_player = Undetermined;
                            game_settings->white_time_remaining = game_settings->time_at_start;
                            game_settings->black_time_remaining = game_settings->time_at_start;
                            game_settings->is_game_lost_on_time = false;
                            game_settings->has_match_started = false;
                            game_settings->is_game_on_pause = false;
                            game_settings->is_pawn_promotion_happening = false;
                            game_settings->color_of_pawn_promotion = NO_COLOR;
                            // reset the board
                            reset_bitboards();
                            // reset the log
                            reset_log();
                            reset_bitboards_log();
                            // reset the captured pieces and the score
                            reset_captured_pieces_and_score();
                            // reset the transposition tables 
                            reset_transposition_tables();
                            // reset the opening book only when we use it
                            if (game_settings->white_AI_difficulty == LVL7 || game_settings->black_AI_difficulty == LVL7){
                                copy_file_into_file("Chess_Engine/AI_Data/Opening_Book_Init.txt", "Chess_Engine/AI_Data/Opening_Book_read.txt");
                            }
                            // play the sound of the start of the game
                            play_sound("../../Sounds/chessstart.wav");
                        }
                        // if we previously clicked on the new game button
                        else if (buttons[NEW_GAME_BUTTON_IN_GAME]->state == ACTIVE){
                            // we go back to the gameplay choice menu
                            is_running_game = GAMEPLAY_CHOICE;
                        }
                        // if we previously clicked on the quit button
                        else if (buttons[QUIT_BUTTON_IN_GAME]->state == ACTIVE){
                            is_running_game = -1;
                            // we download the log of the game
                            download_log();
                        }
                        // if we previously clicked on the undo button
                        else if (buttons[UNDO_BUTTON_IN_GAME]->state == ACTIVE){
                            undo_last_move();
                            // reset the opening book only when we use it
                            if (game_settings->white_AI_difficulty == LVL7 || game_settings->black_AI_difficulty == LVL7){
                                copy_file_into_file("Chess_Engine/AI_Data/Opening_Book_Init.txt", "Chess_Engine/AI_Data/Opening_Book_read.txt");
                                update_opening_book();
                            }
                        }
                        // if we previously clicked on the download log button
                        else if (buttons[DL_LOG_IN_GAME_BUTTON]->state == ACTIVE){
                            // we need to download the log of the game
                            download_log();
                        }
                        // if we previously clicked on the pause button
                        else if (buttons[PAUSE_BUTTON]->state == ACTIVE){
                            // we need to pause the game if it's not already paused
                            if (game_settings->is_game_on_pause == false){
                                game_settings->is_game_on_pause = true;
                            }
                            // we need to unpause the game if it's already paused
                            else if (game_settings->is_game_on_pause == true){
                                game_settings->is_game_on_pause = false;
                            }
                        }

                        // reseting the button state
                        reset_buttons_state();

                }

                    // if the button selected is the not_next button when a click has been done
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[NOT_NEXT_BUTTON_IN_GAME]->rect) && is_clicked == true){
                        
                        // updating the click variables
                        is_clicked = false;
                        // reseting the buttons state
                        reset_buttons_state();

                    }

                }

                // if we're on the victory menu
                else if (is_running_game == VICTORY_MENU){

                    // if the button to go quit the game is clicked but nothing has been clicked on before
                    if (is_point_in_rect(event.button.x, event.button.y, buttons[QUIT_BUTTON_VICTORY_MENU]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[QUIT_BUTTON_VICTORY_MENU]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[QUIT_BUTTON_VICTORY_MENU]->rect.x;
                        draw_red_boundary_move.y = buttons[QUIT_BUTTON_VICTORY_MENU]->rect.y;
                        draw_red_boundary_move.w = buttons[QUIT_BUTTON_VICTORY_MENU]->rect.w;
                        draw_red_boundary_move.h = buttons[QUIT_BUTTON_VICTORY_MENU]->rect.h;

                    }

                    // if the button to go to the main menu is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[NEW_GAME_BUTTON_VICTORY_MENU]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[NEW_GAME_BUTTON_VICTORY_MENU]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[NEW_GAME_BUTTON_VICTORY_MENU]->rect.x;
                        draw_red_boundary_move.y = buttons[NEW_GAME_BUTTON_VICTORY_MENU]->rect.y;
                        draw_red_boundary_move.w = buttons[NEW_GAME_BUTTON_VICTORY_MENU]->rect.w;
                        draw_red_boundary_move.h = buttons[NEW_GAME_BUTTON_VICTORY_MENU]->rect.h;

                    }

                    // if the button to restart the game is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[RESTART_BUTTON_VICTORY_MENU]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[RESTART_BUTTON_VICTORY_MENU]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[RESTART_BUTTON_VICTORY_MENU]->rect.x;
                        draw_red_boundary_move.y = buttons[RESTART_BUTTON_VICTORY_MENU]->rect.y;
                        draw_red_boundary_move.w = buttons[RESTART_BUTTON_VICTORY_MENU]->rect.w;
                        draw_red_boundary_move.h = buttons[RESTART_BUTTON_VICTORY_MENU]->rect.h;

                    }

                    // if the button to undo the last move is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[UNDO_ENDING_MOVE_BUTTON]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[UNDO_ENDING_MOVE_BUTTON]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[UNDO_ENDING_MOVE_BUTTON]->rect.x;
                        draw_red_boundary_move.y = buttons[UNDO_ENDING_MOVE_BUTTON]->rect.y;
                        draw_red_boundary_move.w = buttons[UNDO_ENDING_MOVE_BUTTON]->rect.w;
                        draw_red_boundary_move.h = buttons[UNDO_ENDING_MOVE_BUTTON]->rect.h;

                    }

                    // if the button to pause the AI, so when we undo the last move, the game doesn't stop immediately after that 
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[PAUSE_BUTTON_VICTORY_MENU]->rect) && is_clicked == false && game_settings->game_mode == AI_VS_AI){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[PAUSE_BUTTON_VICTORY_MENU]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[PAUSE_BUTTON_VICTORY_MENU]->rect.x;
                        draw_red_boundary_move.y = buttons[PAUSE_BUTTON_VICTORY_MENU]->rect.y;
                        draw_red_boundary_move.w = buttons[PAUSE_BUTTON_VICTORY_MENU]->rect.w;
                        draw_red_boundary_move.h = buttons[PAUSE_BUTTON_VICTORY_MENU]->rect.h;

                    }

                    // if the button to download the game log is clicked but nothing has been clicked on before
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[DL_LOG_VICTORY_MENU_BUTTON]->rect) && is_clicked == false){
                        
                        // updating the click variables
                        is_clicked = true;
                        // updating the state of the button
                        buttons[DL_LOG_VICTORY_MENU_BUTTON]->state = ACTIVE;
                        // draw the red rectangle circling the button clicked on
                        draw_red_boundary_move.x = buttons[DL_LOG_VICTORY_MENU_BUTTON]->rect.x;
                        draw_red_boundary_move.y = buttons[DL_LOG_VICTORY_MENU_BUTTON]->rect.y;
                        draw_red_boundary_move.w = buttons[DL_LOG_VICTORY_MENU_BUTTON]->rect.w;
                        draw_red_boundary_move.h = buttons[DL_LOG_VICTORY_MENU_BUTTON]->rect.h;

                    }

                    // if the button selected is the next button when a click has been done
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[NEXT_BUTTON_VICTORY_MENU]->rect) && is_clicked == true){
                        
                        // updating the click variables
                        is_clicked = false;
                        
                        // if we previously clicked on the quit button
                        if (buttons[QUIT_BUTTON_VICTORY_MENU]->state == ACTIVE){
                            is_running_game = -1;
                            // we download the log of the game
                            download_log();
                        }
                        // if we previously clicked on the new game button
                        else if (buttons[NEW_GAME_BUTTON_VICTORY_MENU]->state == ACTIVE){
                            // we go back to the gameplay choice menu
                            is_running_game = GAMEPLAY_CHOICE;
                        }
                        // if we previously clicked on the restart button
                        else if (buttons[RESTART_BUTTON_VICTORY_MENU]->state == ACTIVE){
                            // we go back to the chessboard screen
                            is_running_game = CHESSBOARD_RENDER;
                            // we reset the good settings parameters for the game
                            // since the chess board render part doesn't do that
                            game_settings->player_that_is_playing = White_Player;
                            game_settings->color_of_player_that_is_playing = WHITE;
                            game_settings->loosing_player = Undetermined;
                            game_settings->white_time_remaining = game_settings->time_at_start;
                            game_settings->black_time_remaining = game_settings->time_at_start;
                            game_settings->is_game_lost_on_time = false;
                            game_settings->has_match_started = false;
                            game_settings->is_game_on_pause = false;
                            game_settings->is_pawn_promotion_happening = false;
                            game_settings->is_board_reversed = false;
                            // reset the board
                            reset_bitboards();
                            // reset the log
                            reset_log();
                            reset_bitboards_log();
                            // reset the captured pieces and the score
                            reset_captured_pieces_and_score();
                            // reset the transposition tables 
                            reset_transposition_tables();
                        }
                        // if we previously clicked on the undo button
                        else if (buttons[UNDO_ENDING_MOVE_BUTTON]->state == ACTIVE){
                            // undo the last move
                            undo_last_move();
                            // reset the opening book only when we use it
                            if (game_settings->white_AI_difficulty == LVL7 || game_settings->black_AI_difficulty == LVL7){
                                copy_file_into_file("Chess_Engine/AI_Data/Opening_Book_Init.txt", "Chess_Engine/AI_Data/Opening_Book_read.txt");
                                update_opening_book();
                            }
                            // we go back to the chessboard screen
                            is_running_game = CHESSBOARD_RENDER;
                        }
                        // if we previously clicked on the pause button
                        else if (buttons[PAUSE_BUTTON_VICTORY_MENU]->state == ACTIVE){
                            // we need to pause the game if it's not already paused
                            if (game_settings->is_game_on_pause == false){
                                game_settings->is_game_on_pause = true;
                            }
                            // we need to unpause the game if it's already paused
                            else if (game_settings->is_game_on_pause == true){
                                game_settings->is_game_on_pause = false;
                            }
                        }
                        // if we previously clicked on the download log button
                        else if (buttons[DL_LOG_VICTORY_MENU_BUTTON]->state == ACTIVE){
                            // we need to download the log of the game
                            download_log();
                        }

                        // reseting the button state
                        reset_buttons_state();

                    }

                    // if the button selected is the not_next button when a click has been done
                    else if (is_point_in_rect(event.button.x, event.button.y, buttons[NOT_NEXT_BUTTON_VICTORY_MENU]->rect) && is_clicked == true){
                        
                        // updating the click variables
                        is_clicked = false;
                        // reseting the buttons state
                        reset_buttons_state();

                    }

                }

            }

            // taking the mouse event, here it's tracking the mouse pointer, to make piece moves 
            else if (event.type == SDL_MOUSEMOTION){
                
                // the moving of the mouse is effective only when we've clicked on the board once and we're on the chessboard screen
                // but the click needs to be on the board
                if (is_clicked == true && is_clicked_on_board == true && game_settings->has_match_started == true  && game_settings->is_pawn_promotion_happening == false && is_running_game == CHESSBOARD_RENDER){
                    // it's supposed to be the middle of the piece, the shift will be done by the function that show the board
                    // the piece needs to be the same color as the player that is playing
                    if (((bitboards[WHITE_PIECES] & (1ULL << from_index)) && game_settings->color_of_player_that_is_playing == WHITE) || ((bitboards[BLACK_PIECES] & (1ULL << from_index)) && game_settings->color_of_player_that_is_playing == BLACK)){
                        piece_movement_rect.x = event.button.x;
                        piece_movement_rect.y = event.button.y;
                    }
                }

            }

            // taking the mouse event, of realising the mouse, to avoid having a second click to do, realising the click will make the move happens (or not if not valid)
            else if (event.type == SDL_MOUSEBUTTONUP){

                // making the translation of the mouse click to the row and the column of the board
                int row = (event.button.y-WINDOW_TOP_MARGIN) / SQUARE_SIZE;
                int col = (event.button.x-WINDOW_LEFT_MARGIN) / SQUARE_SIZE;

                // we need to know if the player playing if human 
                bool is_player_playing_human = true;
                if (game_settings->player_that_is_playing == White_Player && game_settings->white_player_type == AI){
                    is_player_playing_human = false;
                }
                else if (game_settings->player_that_is_playing == Black_Player && game_settings->black_player_type == AI){
                    is_player_playing_human = false;
                }
                
                // the moving of the mouse is effective only when we've clicked on the board once and we're on the chessboard screen
                // but the click needs to be on the board
                if (is_clicked == true && is_clicked_on_board == true && game_settings->has_match_started == true && is_player_playing_human == true && game_settings->is_pawn_promotion_happening == false && is_running_game == CHESSBOARD_RENDER){
                    // update the position of the destination with the position of the mouse
                    to_index = get_index(7-row, col);
                    // if we play with the black pieces, we need to reverse the row (against an IA or in a 1V1)
                    if (game_settings->black_player_type == HUMAN && game_settings->player_that_is_playing == Black_Player){
                        to_index = get_index(row, 7-col);
                    }
                    // we kept track of the beginning of the move, if it's not a valid on it will be pratical
                    piece_movement_rect.x = previous_piece_movement_x;
                    piece_movement_rect.y = previous_piece_movement_y;
                    // the second click has been made
                    // reseting the clicks 
                    is_clicked = false;
                    is_clicked_on_board = false;

                    // function to be able to get the flag, since those are different and doesn't interfere with one another, having one allows us to skip the others 
                    // we look for the less time costly flag first
                    int flag = No_Flag;
                    bool is_pawn_promotion_happening = false; // not in the AI part
                    bool castling = false; // not in the AI part
                    int piece_taken_type = NOTHING;
                    if (is_promotion_possible(game_settings->color_of_player_that_is_playing, bitboards, from_index, to_index)){
                        // promotion flag is handled in the pawn promotion part of the code
                        is_pawn_promotion_happening = true;
                    }
                    else if (has_pawn_moved_two_squares(game_settings->color_of_player_that_is_playing, bitboards, from_index, to_index)){
                        flag = Pawn_Two_Up_Flag;
                    }
                    else if (is_en_passant_possible(game_settings->color_of_player_that_is_playing, bitboards, from_index, to_index, chess_log)){
                        flag = En_Passant_Flag;
                        piece_taken_type = get_type_of_piece(bitboards, (game_settings->color_of_player_that_is_playing == WHITE) ? to_index-8 : to_index+8);
                    }
                    else if (is_castle_possible(game_settings->color_of_player_that_is_playing, bitboards, from_index, to_index, chess_log)){
                        flag = Castle_Flag;
                        castling = true;
                    }
                    // if the move is a capture, we need to know if it's a capture, to play the sound of the capture (not needed when we will consider the AI move as a useful part)
                    if (will_capture(game_settings->color_of_player_that_is_playing, bitboards, to_index)){
                        piece_taken_type = get_type_of_piece(bitboards, to_index);
                    }

                    // looking if the move is legal and getting the type of piece that will be moved
                    int type_move_legal_attacking = is_legal_move(game_settings->color_of_player_that_is_playing, bitboards, from_index, to_index, flag);
                    if (type_move_legal_attacking != NOTHING){

                        // adding into a move value the information of the move                    
                        int move_value = get_move_value(from_index, to_index, flag);

                        game_settings->is_pawn_promotion_happening = is_pawn_promotion_happening;
                        // updating what's happening concerning the pawn promotion 
                        if (is_pawn_promotion_happening){
                            // we need to know the color of the pawn that is being promoted
                            game_settings->is_pawn_promotion_happening = true;
                            game_settings->color_of_pawn_promotion = game_settings->color_of_player_that_is_playing;
                        }

                        // udpate the first part of the log and the captured piece and score 
                        update_log_and_captured_piece_and_score(move_value, piece_taken_type);
                        // all put in a make move function 
                        make_move(from_index, to_index, flag, type_move_legal_attacking);

                        // if the pawn promotion is happening, we need not to do the following part of the code, we skipped that and when the piece is choosed, we go back to it 
                        if (game_settings->is_pawn_promotion_happening){
                            goto start_promotion;
                        }
                        // where the end of the pawn promotion get us to 
                        end_promotion: 

                        // updating the log with all the castle related information
                        update_castle_state_in_log(from_index, to_index, flag, 1-game_settings->color_of_player_that_is_playing);
                        
                        // adding the bitboards to the log 
                        add_bitboards_to_log(bitboards);

                        // changing the player that is playing for the next turn if the move was done
                        change_player_that_is_playing();

                        // but also get the check state after the move for the previous player to see if the move was legal after all
                        // because looking for a legal move don't assure us that we were not in check after the move
                        // a checkmate is not looked for here, it's done every time a graphic need to be showed
                        int check_state_after_move = is_check(1-game_settings->color_of_player_that_is_playing, bitboards, chess_log);
                        // if there is a check situation (for the player that just played after its move), we need to undo the move
                        if (check_state_after_move == CHECK && get_king_index(bitboards, 1-game_settings->color_of_player_that_is_playing) != -1){

                            // we need to undo the move that has been done, since it's not legal because it puts the player in check after playing
                            // and there is a legal move since no checkmate has been found 
                            undo_last_move();

                        }
                        // a move has been made, so we add the blitz time mode to the player that just played
                        else if (check_state_after_move == NO_CHECK){
                            // if the white player is playing, we need to udpate the time of the black player
                            if (game_settings->color_of_player_that_is_playing == WHITE){
                                game_settings->black_time_remaining += game_settings->blitz_time;
                            }
                            // if the black player is playing, we need to udpate the time of the white player
                            else if (game_settings->color_of_player_that_is_playing == BLACK){
                                game_settings->white_time_remaining += game_settings->blitz_time;
                            }
                        }

                        // playing the correct type of sound depending on the move made 
                        if (check_state_after_move == CHECK){
                            play_sound("../../Sounds/check.wav");
                        }
                        else if (castling && check_state_after_move == NO_CHECK){
                            play_sound("../../Sounds/castle.wav");
                        }
                        else if (piece_taken_type != NOTHING && check_state_after_move == NO_CHECK){
                            play_sound("../../Sounds/take.wav");
                        }
                        else if (check_state_after_move == NO_CHECK){
                            play_sound("../../Sounds/chess.wav");
                        }

                    }

                }

            }
            
        }


        // the timer is also present when we're in the game (the game needs to be running to have a timer), this one is only for the player, the ia has its own timer (taking the time of response of the ia)
        if (is_running_game == CHESSBOARD_RENDER && game_settings->has_match_started == true){

            // we now need to get the time that has passed since the last time we checked the time
            current_time = SDL_GetTicks();
            delta_time = current_time - last_time_recorded;
            // udpatin the last time recorded
            last_time_recorded = current_time;

            // updating the time remaining for the player that is playing
            // if the player is a white human
            if (game_settings->color_of_player_that_is_playing == WHITE && game_settings->white_player_type == HUMAN){
                // if the time remaining is above 0, we need to update it
                if (game_settings->white_time_remaining > 0){
                    game_settings->white_time_remaining -= delta_time / 1000; // the SDL_GetTicks() function gives us the time in milliseconds
                }
                // if the time remaining is below 0, the player has lost
                else { 
                    game_settings->loosing_player = White_Player;
                    is_running_game = VICTORY_MENU;
                    game_settings->is_game_lost_on_time = true;
                }
            }
            // if the player is a black human
            else if (game_settings->color_of_player_that_is_playing == BLACK && game_settings->black_player_type == HUMAN){
                // if the time remaining is above 0, we need to update it
                if (game_settings->black_time_remaining > 0){
                    game_settings->black_time_remaining -= delta_time / 1000; // the SDL_GetTicks() function gives us the time in milliseconds
                }
                // if the time remaining is below 0, the player has lost
                else {
                    game_settings->loosing_player = Black_Player;
                    is_running_game = VICTORY_MENU;
                    game_settings->is_game_lost_on_time = true;
                }
            }

        }


        // where the start of the pawn promotion get us to 
        start_promotion:
        // if we're in the menus, we show them and update the structure of the game accordingly
        if (is_running_game == GAMEPLAY_CHOICE || is_running_game == COLOR_CHOICE || is_running_game == DIFFICULTY_CHOICE || is_running_game == DIFFICULTY_CHOICE_WHITE_AI || is_running_game == DIFFICULTY_CHOICE_BLACK_AI || is_running_game == TIME_CHOICE){
        
            // reset the renderer, the screen of the graphic card
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
            // show the load menu
            show_load_menu(renderer, is_running_game, is_clicked, draw_red_boundary_move);
            // update the renderer by presenting the new screen
            SDL_RenderPresent(renderer);

            // we reset the good settings parameters for the game
            game_settings->player_that_is_playing = White_Player;
            game_settings->color_of_player_that_is_playing = WHITE;
            game_settings->loosing_player = Undetermined;
            game_settings->white_time_remaining = game_settings->time_at_start;
            game_settings->black_time_remaining = game_settings->time_at_start;
            game_settings->is_game_lost_on_time = false;
            game_settings->has_match_started = false;
            game_settings->is_game_on_pause = false;
            game_settings->is_pawn_promotion_happening = false;
            game_settings->color_of_pawn_promotion = NO_COLOR;
            game_settings->is_board_reversed = false;

            // reset the board
            reset_bitboards();
            // reset the log
            reset_log();
            reset_bitboards_log();
            // reset the captured pieces and the score
            reset_captured_pieces_and_score();
            // reset the transposition tables 
            reset_transposition_tables();
        }

        // if we're in the game, we show the chess board
        else if (is_running_game == CHESSBOARD_RENDER){

            // reset the renderer, the screen of the graphic card
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);

            // show buttons in the game
            show_menu_button_in_game(renderer);

            // looking if the board has to be reversed
            game_settings->is_board_reversed = false;
            if (game_settings->player_that_is_playing == Black_Player && game_settings->black_player_type == HUMAN){
                game_settings->is_board_reversed = true;
            }

            // show the captured pieces and the score
            show_captured_pieces(renderer);
            show_score(renderer);

            // show the timers
            show_updated_timer(renderer);

            // showing the log (only if a pawn promotion is not happening)
            show_log(renderer);

            // add the AI graphic part here
            show_AI_values(renderer, selected_move_lvl7, selected_score_lvl7, is_move_taken_from_book_lvl7, depth_reached_lvl7);

            // show chess board
            show_chess_board(renderer, is_clicked, draw_red_boundary_move, selected_piece_index, piece_movement_rect);

            // show the trajectories possible for the selected piece
            show_trajectory(renderer, is_clicked, is_clicked_on_board, selected_piece_index);

            // if a click has been done but not on the board, we need to show the confirmation button
            if (is_clicked == true && is_clicked_on_board == false){
                show_confirmation_menu(renderer);
            }

            // update the renderer by presenting the new screen
            SDL_RenderPresent(renderer);

            // needs some check to see if there is a loosing player or if a draw has happened
            int draw_type = is_draw_forced_by_rules();
            int check_state = get_check_state(game_settings->color_of_player_that_is_playing);
            if (draw_type != NO_DRAW){
                // we update the loosing player to the draw corresponding to the draw type, to print the correct message
                if (draw_type == DRAW_BY_3_RULES){
                    game_settings->loosing_player = Draw_by_3_rules;
                }
                else if (draw_type == DRAW_BY_50_RULES){
                    game_settings->loosing_player = Draw_by_50_rules;
                }
                else if (draw_type == DRAW_BY_INSUFFICIENT_MATERIAL){
                    game_settings->loosing_player = Draw_by_insufficient_material;
                }
                is_running_game = VICTORY_MENU;
                // playing the sound of the draw
                play_sound("../../Sounds/endgame.wav");
            }
            else if (check_state == CHECK_MATE || check_state == STALEMATE){
                if (check_state == STALEMATE){
                    game_settings->loosing_player = Draw_by_stalemate;
                }
                else if (check_state == CHECK_MATE){
                    game_settings->loosing_player = game_settings->player_that_is_playing;
                }
                is_running_game = VICTORY_MENU;
                // playing the sound of the checkmate
                play_sound("../../Sounds/endgame.wav");
            }

        }

        // if we're in the victory menu, we show the victory menu
        else if (is_running_game == VICTORY_MENU){
        
            // reset the renderer, the screen of the graphic card
            SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
            SDL_RenderClear(renderer);
           
            // show buttons in the game
            show_menu_button_in_game(renderer);

            // looking if the board has to be reversed
            game_settings->is_board_reversed = false;
            if (game_settings->player_that_is_playing == Black_Player && game_settings->black_player_type == HUMAN){
                game_settings->is_board_reversed = true;
            }

            // show the captured pieces and the score
            show_captured_pieces(renderer);
            show_score(renderer);

            // show the timers
            show_updated_timer(renderer);

            // showing the log (only if a pawn promotion is not happening)
            show_log(renderer);

            // show chess board
            show_chess_board(renderer, is_clicked, draw_red_boundary_move, selected_piece_index, piece_movement_rect);

            // show the trajectories possible for the selected piece
            show_trajectory(renderer, is_clicked, is_clicked_on_board, selected_piece_index);

            // Apply a blur to this screen
            applyBlur(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, 5);

            // show the victory menu
            show_victory_menu(renderer, is_clicked, draw_red_boundary_move);
           
            // update the renderer by presenting the new screen
            SDL_RenderPresent(renderer);

        }
        
   
        // AI playing
        // the AI is playing only when the match has started and the game is not on pause
        if (is_running_game == CHESSBOARD_RENDER && game_settings->has_match_started == true && game_settings->is_game_on_pause == false && ((game_settings->color_of_player_that_is_playing == WHITE && game_settings->white_player_type == AI) || (game_settings->color_of_player_that_is_playing == BLACK && game_settings->black_player_type == AI))){

            // we let a delay between our play and the AI one; to be able to see the move we made and the one from the AI
            if (game_settings->game_mode == PLAYER_VS_AI){
                SDL_Delay(1000);
            }
            // looking for a checkmate before the AI is playing, because, we're here before going to the part where it's considered
            if (get_check_state(game_settings->color_of_player_that_is_playing) == CHECK_MATE){
                game_settings->loosing_player = game_settings->color_of_player_that_is_playing;
                // we go to the victory menu
                is_running_game = VICTORY_MENU;
                // we need to play the sound of the checkmate
                play_sound("../Sounds/endgame.wav");
                continue;
            }

            // getting the time before the AI is making its search
            float time_before_AI_search = SDL_GetTicks();

            // getting the level of the AI playing
            int level_of_AI = NONE;
            if (game_settings->color_of_player_that_is_playing == WHITE){
                level_of_AI = game_settings->white_AI_difficulty;
            }
            else if (game_settings->color_of_player_that_is_playing == BLACK){
                level_of_AI = game_settings->black_AI_difficulty;
            }
            // AI search of the move to play for the IA 
            make_AI_play(level_of_AI, &selected_move_lvl7, &selected_score_lvl7, &is_move_taken_from_book_lvl7, &depth_reached_lvl7);

            // getting the time after the AI did its search
            float time_after_AI_search = SDL_GetTicks();
            // getting the time the AI took to make its search
            float time_AI_search = time_after_AI_search - time_before_AI_search;
            last_time_recorded = time_after_AI_search;
            // udpating the time remaining for the player that is playing
            // a white player now playing means that we need to update the time of the black player
            if (game_settings->color_of_player_that_is_playing == WHITE){
                game_settings->black_time_remaining -= time_AI_search / 1000; // the SDL_GetTicks() function gives us the time in milliseconds
                game_settings->black_time_remaining += game_settings->blitz_time; // adding the blitz time to the black player
            }
            // a black player now playing means that we need to update the time of the white player
            else if (game_settings->color_of_player_that_is_playing == BLACK){
                game_settings->white_time_remaining -= time_AI_search / 1000; // the SDL_GetTicks() function gives us the time in milliseconds
                game_settings->white_time_remaining += game_settings->blitz_time; // adding the blitz time to the white player
            }

        }

    }

    // free the game settings
    destroy_game_settings();

    // free the bitboards
    destroy_bitboards();

    // free the log
    destroy_log();

    // free the bitboards log 
    destroy_bitboards_log();

    // free the captured pieces and the score
    destroy_captured_pieces_and_score();

    // free the precomputed data
    free_pre_computed_data();

    // free the ramdom precomputed transposition table
    free_random_transposition_tables();

    // free the transposition tables
    free_transposition_tables();

    // free the buttons
    destroy_buttons();

    // free the memory and quit the SDL_program
    clear_and_close_SDL(window, renderer);

    return EXIT_SUCCESS;
}
