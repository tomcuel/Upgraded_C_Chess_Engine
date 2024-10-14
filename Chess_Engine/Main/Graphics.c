#include "Graphics.h"


Button** buttons;


void create_buttons(){
    
    buttons = (Button**)malloc(NUMBER_OF_BUTTONS * sizeof(Button*));
    // looking for a malloc error
    if (buttons == NULL){
        printf("Error: malloc failed in Create_Buttons\n");
        return;
    }

    // for each button, we create it
    for (int i = 0; i < NUMBER_OF_BUTTONS; i++){
        buttons[i] = (Button*)malloc(sizeof(Button));
        // looking for a malloc error
        if (buttons[i] == NULL){
            printf("Error: malloc failed in Create_Buttons\n");
            return;
        }
        // setting the state to UNACTIVE for every button
        buttons[i]->state = UNACTIVE;
    }

    // buttons for the load menu : game play choice
    buttons[PLAYER_VS_PLAYER_BUTTON]->rect.x = 150;
    buttons[PLAYER_VS_PLAYER_BUTTON]->rect.y = 300;
    buttons[PLAYER_VS_PLAYER_BUTTON]->rect.w = 300;
    buttons[PLAYER_VS_PLAYER_BUTTON]->rect.h = 200;

    buttons[PLAYER_VS_AI_BUTTON]->rect.x = WINDOW_WIDTH/2 - 150;
    buttons[PLAYER_VS_AI_BUTTON]->rect.y = 300;
    buttons[PLAYER_VS_AI_BUTTON]->rect.w = 300;
    buttons[PLAYER_VS_AI_BUTTON]->rect.h = 200;

    buttons[AI_VS_AI_BUTTON]->rect.x = WINDOW_WIDTH-150-300;
    buttons[AI_VS_AI_BUTTON]->rect.y = 300;
    buttons[AI_VS_AI_BUTTON]->rect.w = 300;
    buttons[AI_VS_AI_BUTTON]->rect.h = 200;

    buttons[OPEN_GAME_LOG_BUTTON]->rect.x = 200;
    buttons[OPEN_GAME_LOG_BUTTON]->rect.y = 650;
    buttons[OPEN_GAME_LOG_BUTTON]->rect.w = 300;
    buttons[OPEN_GAME_LOG_BUTTON]->rect.h = 200;

    buttons[QUIT_BUTTON_GAME_CHOICE]->rect.x = WINDOW_WIDTH - 200 - 300;
    buttons[QUIT_BUTTON_GAME_CHOICE]->rect.y = 650;
    buttons[QUIT_BUTTON_GAME_CHOICE]->rect.w = 300;
    buttons[QUIT_BUTTON_GAME_CHOICE]->rect.h = 200;

    buttons[NEXT_BUTTON_GAME_CHOICE]->rect.x = WINDOW_WIDTH/2 + 400 - 150;
    buttons[NEXT_BUTTON_GAME_CHOICE]->rect.y = 500;
    buttons[NEXT_BUTTON_GAME_CHOICE]->rect.w = 300;
    buttons[NEXT_BUTTON_GAME_CHOICE]->rect.h = 200;
    
    buttons[NOT_NEXT_BUTTON_GAME_CHOICE]->rect.x = WINDOW_WIDTH/2 - 400 - 150;
    buttons[NOT_NEXT_BUTTON_GAME_CHOICE]->rect.y = 500;
    buttons[NOT_NEXT_BUTTON_GAME_CHOICE]->rect.w = 300;
    buttons[NOT_NEXT_BUTTON_GAME_CHOICE]->rect.h = 200;

    // buttons for the color choice menu
    buttons[BLACK_COLOR_BUTTON]->rect.x = 250;
    buttons[BLACK_COLOR_BUTTON]->rect.y = 300;
    buttons[BLACK_COLOR_BUTTON]->rect.w = 300;
    buttons[BLACK_COLOR_BUTTON]->rect.h = 200;

    buttons[WHITE_COLOR_BUTTON]->rect.x = WINDOW_WIDTH-550;
    buttons[WHITE_COLOR_BUTTON]->rect.y = 300;
    buttons[WHITE_COLOR_BUTTON]->rect.w = 300;
    buttons[WHITE_COLOR_BUTTON]->rect.h = 200;
    
    buttons[QUIT_BUTTON_COLOR_CHOICE]->rect.x = 50;
    buttons[QUIT_BUTTON_COLOR_CHOICE]->rect.y = 650;
    buttons[QUIT_BUTTON_COLOR_CHOICE]->rect.w = 300;
    buttons[QUIT_BUTTON_COLOR_CHOICE]->rect.h = 200;

    buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect.x = WINDOW_WIDTH/2 - 150;
    buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect.y = 650;
    buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect.w = 300;
    buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect.h = 200;

    buttons[BACK_BUTTON_COLOR_CHOICE]->rect.x = WINDOW_WIDTH - 50 - 300;
    buttons[BACK_BUTTON_COLOR_CHOICE]->rect.y = 650;
    buttons[BACK_BUTTON_COLOR_CHOICE]->rect.w = 300;
    buttons[BACK_BUTTON_COLOR_CHOICE]->rect.h = 200;

    buttons[NEXT_BUTTON_COLOR_CHOICE]->rect.x = WINDOW_WIDTH/2 + 400 - 150;
    buttons[NEXT_BUTTON_COLOR_CHOICE]->rect.y = 500;
    buttons[NEXT_BUTTON_COLOR_CHOICE]->rect.w = 300;
    buttons[NEXT_BUTTON_COLOR_CHOICE]->rect.h = 200;
    
    buttons[NOT_NEXT_BUTTON_COLOR_CHOICE]->rect.x = WINDOW_WIDTH/2 - 400 - 150;
    buttons[NOT_NEXT_BUTTON_COLOR_CHOICE]->rect.y = 500;
    buttons[NOT_NEXT_BUTTON_COLOR_CHOICE]->rect.w = 300;
    buttons[NOT_NEXT_BUTTON_COLOR_CHOICE]->rect.h = 200;


    // buttons for the difficulty choice menu
    buttons[LVL1_DIFFICULTY_BUTTON]->rect.x = 200;
    buttons[LVL1_DIFFICULTY_BUTTON]->rect.y = 200;
    buttons[LVL1_DIFFICULTY_BUTTON]->rect.w = 300;
    buttons[LVL1_DIFFICULTY_BUTTON]->rect.h = 200;

    buttons[LVL2_DIFFICULTY_BUTTON]->rect.x = 200;
    buttons[LVL2_DIFFICULTY_BUTTON]->rect.y = 400;
    buttons[LVL2_DIFFICULTY_BUTTON]->rect.w = 300;
    buttons[LVL2_DIFFICULTY_BUTTON]->rect.h = 200;

    buttons[LVL4_DIFFICULTY_BUTTON]->rect.x = WINDOW_WIDTH - 200 - 300;
    buttons[LVL4_DIFFICULTY_BUTTON]->rect.y = 200;
    buttons[LVL4_DIFFICULTY_BUTTON]->rect.w = 300;
    buttons[LVL4_DIFFICULTY_BUTTON]->rect.h = 200;

    buttons[LVL7_DIFFICULTY_BUTTON]->rect.x = WINDOW_WIDTH - 200 - 300;
    buttons[LVL7_DIFFICULTY_BUTTON]->rect.y = 400;
    buttons[LVL7_DIFFICULTY_BUTTON]->rect.w = 300;
    buttons[LVL7_DIFFICULTY_BUTTON]->rect.h = 200;

    buttons[QUIT_BUTTON_AI_CHOICE]->rect.x = 50;
    buttons[QUIT_BUTTON_AI_CHOICE]->rect.y = 650;
    buttons[QUIT_BUTTON_AI_CHOICE]->rect.w = 300;
    buttons[QUIT_BUTTON_AI_CHOICE]->rect.h = 200;

    buttons[MAIN_MENU_BUTTON_AI_CHOICE]->rect.x = WINDOW_WIDTH/2 - 150;
    buttons[MAIN_MENU_BUTTON_AI_CHOICE]->rect.y = 650;
    buttons[MAIN_MENU_BUTTON_AI_CHOICE]->rect.w = 300;
    buttons[MAIN_MENU_BUTTON_AI_CHOICE]->rect.h = 200;

    buttons[BACK_BUTTON_AI_CHOICE]->rect.x = WINDOW_WIDTH - 50 - 300;
    buttons[BACK_BUTTON_AI_CHOICE]->rect.y = 650;
    buttons[BACK_BUTTON_AI_CHOICE]->rect.w = 300;
    buttons[BACK_BUTTON_AI_CHOICE]->rect.h = 200;

    buttons[NEXT_BUTTON_AI_CHOICE]->rect.x = WINDOW_WIDTH/2 + 400 - 150;
    buttons[NEXT_BUTTON_AI_CHOICE]->rect.y = 500;
    buttons[NEXT_BUTTON_AI_CHOICE]->rect.w = 300;
    buttons[NEXT_BUTTON_AI_CHOICE]->rect.h = 200;
    
    buttons[NOT_NEXT_BUTTON_AI_CHOICE]->rect.x = WINDOW_WIDTH/2 - 400 - 150;
    buttons[NOT_NEXT_BUTTON_AI_CHOICE]->rect.y = 500;
    buttons[NOT_NEXT_BUTTON_AI_CHOICE]->rect.w = 300;
    buttons[NOT_NEXT_BUTTON_AI_CHOICE]->rect.h = 200;


    // buttons for the time choice menu
    buttons[SHORT_BLITZ_BUTTON]->rect.x = WINDOW_WIDTH/2 - 400 - 150;
    buttons[SHORT_BLITZ_BUTTON]->rect.y = 200;
    buttons[SHORT_BLITZ_BUTTON]->rect.w = 300;
    buttons[SHORT_BLITZ_BUTTON]->rect.h = 200;

    buttons[LONG_BLITZ_BUTTON]->rect.x = WINDOW_WIDTH/2 + 400 - 150;
    buttons[LONG_BLITZ_BUTTON]->rect.y = 200;
    buttons[LONG_BLITZ_BUTTON]->rect.w = 300;
    buttons[LONG_BLITZ_BUTTON]->rect.h = 200;

    buttons[SHORT_BUTTON]->rect.x = 50;
    buttons[SHORT_BUTTON]->rect.y = 400;
    buttons[SHORT_BUTTON]->rect.w = 300;
    buttons[SHORT_BUTTON]->rect.h = 200;

    buttons[MODERATE_BUTTON]->rect.x = WINDOW_WIDTH/2 - 150;
    buttons[MODERATE_BUTTON]->rect.y = 400;
    buttons[MODERATE_BUTTON]->rect.w = 300;
    buttons[MODERATE_BUTTON]->rect.h = 200;

    buttons[LONG_BUTTON]->rect.x = WINDOW_WIDTH - 50 - 300;
    buttons[LONG_BUTTON]->rect.y = 400;
    buttons[LONG_BUTTON]->rect.w = 300;
    buttons[LONG_BUTTON]->rect.h = 200;

    buttons[QUIT_BUTTON_TIME_CHOICE]->rect.x = 50;
    buttons[QUIT_BUTTON_TIME_CHOICE]->rect.y = 650;
    buttons[QUIT_BUTTON_TIME_CHOICE]->rect.w = 300;
    buttons[QUIT_BUTTON_TIME_CHOICE]->rect.h = 200;

    buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect.x = WINDOW_WIDTH/2 - 150;
    buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect.y = 650;
    buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect.w = 300;
    buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect.h = 200;

    buttons[BACK_BUTTON_TIME_CHOICE]->rect.x = WINDOW_WIDTH - 50 - 300;
    buttons[BACK_BUTTON_TIME_CHOICE]->rect.y = 650;
    buttons[BACK_BUTTON_TIME_CHOICE]->rect.w = 300;
    buttons[BACK_BUTTON_TIME_CHOICE]->rect.h = 200;

    buttons[LOAD_BUTTON]->rect.x = WINDOW_WIDTH/2 + 400 - 150;
    buttons[LOAD_BUTTON]->rect.y = 500;
    buttons[LOAD_BUTTON]->rect.w = 300;
    buttons[LOAD_BUTTON]->rect.h = 200;
    
    buttons[NOT_LOAD_BUTTON]->rect.x = WINDOW_WIDTH/2 - 400 - 150;
    buttons[NOT_LOAD_BUTTON]->rect.y = 500;
    buttons[NOT_LOAD_BUTTON]->rect.w = 300;
    buttons[NOT_LOAD_BUTTON]->rect.h = 200;


    // buttons for the chessboard
    buttons[START_BUTTON_IN_GAME]->rect.x = WINDOW_WIDTH-25-170;
    buttons[START_BUTTON_IN_GAME]->rect.y = 25;
    buttons[START_BUTTON_IN_GAME]->rect.w = 170;
    buttons[START_BUTTON_IN_GAME]->rect.h = 100;

    buttons[RESTART_BUTTON_IN_GAME]->rect.x = WINDOW_WIDTH-25-170;
    buttons[RESTART_BUTTON_IN_GAME]->rect.y = 175;
    buttons[RESTART_BUTTON_IN_GAME]->rect.w = 170;
    buttons[RESTART_BUTTON_IN_GAME]->rect.h = 100;

    buttons[NEW_GAME_BUTTON_IN_GAME]->rect.x = WINDOW_WIDTH-25-170;
    buttons[NEW_GAME_BUTTON_IN_GAME]->rect.y = 325;
    buttons[NEW_GAME_BUTTON_IN_GAME]->rect.w = 170;
    buttons[NEW_GAME_BUTTON_IN_GAME]->rect.h = 100;

    buttons[QUIT_BUTTON_IN_GAME]->rect.x = WINDOW_WIDTH-25-170;
    buttons[QUIT_BUTTON_IN_GAME]->rect.y = 475;
    buttons[QUIT_BUTTON_IN_GAME]->rect.w = 170;
    buttons[QUIT_BUTTON_IN_GAME]->rect.h = 100;

    buttons[UNDO_BUTTON_IN_GAME]->rect.x = WINDOW_WIDTH-25-170;
    buttons[UNDO_BUTTON_IN_GAME]->rect.y = 625;
    buttons[UNDO_BUTTON_IN_GAME]->rect.w = 170;
    buttons[UNDO_BUTTON_IN_GAME]->rect.h = 100;

    buttons[DL_LOG_IN_GAME_BUTTON]->rect.x = WINDOW_WIDTH-25-170;
    buttons[DL_LOG_IN_GAME_BUTTON]->rect.y = 775;
    buttons[DL_LOG_IN_GAME_BUTTON]->rect.w = 170;
    buttons[DL_LOG_IN_GAME_BUTTON]->rect.h = 100;

    buttons[PAUSE_BUTTON]->rect.x = 850+355/2-170/2;
    buttons[PAUSE_BUTTON]->rect.y = 775;
    buttons[PAUSE_BUTTON]->rect.w = 170;
    buttons[PAUSE_BUTTON]->rect.h = 100;

    buttons[PAWN_PROMOTION_BUTTON]->rect.x = 850+355/2-170/2;
    buttons[PAWN_PROMOTION_BUTTON]->rect.y = 50;
    buttons[PAWN_PROMOTION_BUTTON]->rect.w = 170;
    buttons[PAWN_PROMOTION_BUTTON]->rect.h = 100;

    buttons[QUEEN_BUTTON]->rect.x = 850+355/2-170/2;
    buttons[QUEEN_BUTTON]->rect.y = 175;
    buttons[QUEEN_BUTTON]->rect.w = 170;
    buttons[QUEEN_BUTTON]->rect.h = 100;

    buttons[ROOK_BUTTON]->rect.x = 850+355/2-170/2;
    buttons[ROOK_BUTTON]->rect.y = 325;
    buttons[ROOK_BUTTON]->rect.w = 170;
    buttons[ROOK_BUTTON]->rect.h = 100;

    buttons[BISHOP_BUTTON]->rect.x = 850+355/2-170/2;
    buttons[BISHOP_BUTTON]->rect.y = 475;
    buttons[BISHOP_BUTTON]->rect.w = 170;
    buttons[BISHOP_BUTTON]->rect.h = 100;

    buttons[KNIGHT_BUTTON]->rect.x = 850+355/2-170/2;
    buttons[KNIGHT_BUTTON]->rect.y = 625;
    buttons[KNIGHT_BUTTON]->rect.w = 170;
    buttons[KNIGHT_BUTTON]->rect.h = 100;

    buttons[NEXT_BUTTON_IN_GAME]->rect.x = WINDOW_WIDTH/2 + 400 - 150;
    buttons[NEXT_BUTTON_IN_GAME]->rect.y = 500;
    buttons[NEXT_BUTTON_IN_GAME]->rect.w = 300;
    buttons[NEXT_BUTTON_IN_GAME]->rect.h = 200;

    buttons[NOT_NEXT_BUTTON_IN_GAME]->rect.x = WINDOW_WIDTH/2 - 400 - 150;
    buttons[NOT_NEXT_BUTTON_IN_GAME]->rect.y = 500;
    buttons[NOT_NEXT_BUTTON_IN_GAME]->rect.w = 300;
    buttons[NOT_NEXT_BUTTON_IN_GAME]->rect.h = 200;


    // buttons for the victory menu
    buttons[DL_LOG_VICTORY_MENU_BUTTON]->rect.x = 150;
    buttons[DL_LOG_VICTORY_MENU_BUTTON]->rect.y = 100;
    buttons[DL_LOG_VICTORY_MENU_BUTTON]->rect.w = 300;
    buttons[DL_LOG_VICTORY_MENU_BUTTON]->rect.h = 200;

    buttons[PAUSE_BUTTON_VICTORY_MENU]->rect.x = WINDOW_WIDTH/2 - 150;
    buttons[PAUSE_BUTTON_VICTORY_MENU]->rect.y = 100;
    buttons[PAUSE_BUTTON_VICTORY_MENU]->rect.w = 300;
    buttons[PAUSE_BUTTON_VICTORY_MENU]->rect.h = 200;

    buttons[UNDO_ENDING_MOVE_BUTTON]->rect.x = WINDOW_WIDTH-150-300;
    buttons[UNDO_ENDING_MOVE_BUTTON]->rect.y = 100;
    buttons[UNDO_ENDING_MOVE_BUTTON]->rect.w = 300;
    buttons[UNDO_ENDING_MOVE_BUTTON]->rect.h = 200;

    buttons[QUIT_BUTTON_VICTORY_MENU]->rect.x = 50;
    buttons[QUIT_BUTTON_VICTORY_MENU]->rect.y = 700;
    buttons[QUIT_BUTTON_VICTORY_MENU]->rect.w = 300;
    buttons[QUIT_BUTTON_VICTORY_MENU]->rect.h = 200;

    buttons[NEW_GAME_BUTTON_VICTORY_MENU]->rect.x = WINDOW_WIDTH/2 - 150;
    buttons[NEW_GAME_BUTTON_VICTORY_MENU]->rect.y = 700;
    buttons[NEW_GAME_BUTTON_VICTORY_MENU]->rect.w = 300;
    buttons[NEW_GAME_BUTTON_VICTORY_MENU]->rect.h = 200;

    buttons[RESTART_BUTTON_VICTORY_MENU]->rect.x = WINDOW_WIDTH - 300 - 50;
    buttons[RESTART_BUTTON_VICTORY_MENU]->rect.y = 700;
    buttons[RESTART_BUTTON_VICTORY_MENU]->rect.w = 300;
    buttons[RESTART_BUTTON_VICTORY_MENU]->rect.h = 200;

    buttons[NEXT_BUTTON_VICTORY_MENU]->rect.x = WINDOW_WIDTH/2 + 400 - 150;
    buttons[NEXT_BUTTON_VICTORY_MENU]->rect.y = 500;
    buttons[NEXT_BUTTON_VICTORY_MENU]->rect.w = 300;
    buttons[NEXT_BUTTON_VICTORY_MENU]->rect.h = 200;

    buttons[NOT_NEXT_BUTTON_VICTORY_MENU]->rect.x = WINDOW_WIDTH/2 - 400 - 150;
    buttons[NOT_NEXT_BUTTON_VICTORY_MENU]->rect.y = 500;
    buttons[NOT_NEXT_BUTTON_VICTORY_MENU]->rect.w = 300;
    buttons[NOT_NEXT_BUTTON_VICTORY_MENU]->rect.h = 200;

}


void reset_buttons_state(){

    // for each button, we set the state to UNACTIVE
    for (int i = 0; i < NUMBER_OF_BUTTONS; i++){
        buttons[i]->state = UNACTIVE;
    }

}


void destroy_buttons(){

    // for each button, we free it
    for (int i = 0; i < NUMBER_OF_BUTTONS; i++){
        if (buttons[i] != NULL){
            free(buttons[i]);
        }
    }

    // free the array of buttons
    if (buttons != NULL){
        free(buttons);
    }

}


void show_load_menu(SDL_Renderer* renderer, int menu_type, bool is_clicked, SDL_Rect draw_red_boundary_move){

    // the blur level integer
    int blur_level_load_menu = 5;

    // add the background image
    SDL_Rect rect_full_screen;
    rect_full_screen.x = 0;
    rect_full_screen.y = 0;
    rect_full_screen.w = WINDOW_WIDTH;
    rect_full_screen.h = WINDOW_HEIGHT;
    add_image_to_render("../../Images/Buttons/wall_paper.jpg", renderer, rect_full_screen);
    // applying the blur to make the back end blurred
    if (is_clicked == false){
        applyBlur(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, blur_level_load_menu);
    }

    // the color of the text to display (white)
    SDL_Color color = {230, 230, 230, 255};

    // if we are in the game choice menu
    if (menu_type == GAMEPLAY_CHOICE){
        
        // buttons to choose a 1vs1 game
        add_font_to_render(renderer, "1vs1", 100, color, buttons[PLAYER_VS_PLAYER_BUTTON]->rect.x+divide_by_two(buttons[PLAYER_VS_PLAYER_BUTTON]->rect.w), buttons[PLAYER_VS_PLAYER_BUTTON]->rect.y+divide_by_two(buttons[PLAYER_VS_PLAYER_BUTTON]->rect.h));
        // buttons to choose a 1vsAI game
        add_font_to_render(renderer, "1vsAI", 100, color, buttons[PLAYER_VS_AI_BUTTON]->rect.x+divide_by_two(buttons[PLAYER_VS_AI_BUTTON]->rect.w), buttons[PLAYER_VS_AI_BUTTON]->rect.y+divide_by_two(buttons[PLAYER_VS_AI_BUTTON]->rect.h));
        // buttons to choose a AI vs AI game
        add_font_to_render(renderer, "AIvsAI", 100, color, buttons[AI_VS_AI_BUTTON]->rect.x+divide_by_two(buttons[AI_VS_AI_BUTTON]->rect.w), buttons[AI_VS_AI_BUTTON]->rect.y+divide_by_two(buttons[AI_VS_AI_BUTTON]->rect.h));
        // button to open the game log file
        add_font_to_render(renderer, "Open Game", 100, color, buttons[OPEN_GAME_LOG_BUTTON]->rect.x+divide_by_two(buttons[OPEN_GAME_LOG_BUTTON]->rect.w), buttons[OPEN_GAME_LOG_BUTTON]->rect.y+divide_by_two(buttons[OPEN_GAME_LOG_BUTTON]->rect.h));
        // button to quit the game
        add_font_to_render(renderer, "Quit", 100, color, buttons[QUIT_BUTTON_GAME_CHOICE]->rect.x+divide_by_two(buttons[QUIT_BUTTON_GAME_CHOICE]->rect.w), buttons[QUIT_BUTTON_GAME_CHOICE]->rect.y+divide_by_two(buttons[QUIT_BUTTON_GAME_CHOICE]->rect.h));
        // add text above the buttons to choose the game mode
        add_font_to_render(renderer, "Choose the game mode", 100, color, divide_by_two(WINDOW_WIDTH), 100);

        // if a click has been done, we are in the confirmation menu
        if (is_clicked == true){
            
            // showing the rectangle around the selected area 
            Draw_the_red_boundary_move_Rect(renderer, draw_red_boundary_move);
            // apply a blur for all precedent things before this screen
            applyBlur(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, 3*blur_level_load_menu);
            // button to validate the choice (next)
            add_font_to_render(renderer, "Yes", 100, color, buttons[NEXT_BUTTON_GAME_CHOICE]->rect.x+divide_by_two(buttons[NEXT_BUTTON_GAME_CHOICE]->rect.w), buttons[NEXT_BUTTON_GAME_CHOICE]->rect.y+divide_by_two(buttons[NEXT_BUTTON_GAME_CHOICE]->rect.h));
            // button to go not validate the choice (not next)
            add_font_to_render(renderer, "No", 100, color, buttons[NOT_NEXT_BUTTON_GAME_CHOICE]->rect.x+divide_by_two(buttons[NOT_NEXT_BUTTON_GAME_CHOICE]->rect.w), buttons[NOT_NEXT_BUTTON_GAME_CHOICE]->rect.y+divide_by_two(buttons[NOT_NEXT_BUTTON_GAME_CHOICE]->rect.h));
            // add text above the buttons to choose the game mode
            add_font_to_render(renderer, "Do you want to continue ?", 100, color, divide_by_two(WINDOW_WIDTH), 250);

        }

    }

    // if we are in the color choice menu
    else if (menu_type == COLOR_CHOICE){

        // buttons to choose the black color
        add_font_to_render(renderer, "Black", 100, color, buttons[BLACK_COLOR_BUTTON]->rect.x+divide_by_two(buttons[BLACK_COLOR_BUTTON]->rect.w), buttons[BLACK_COLOR_BUTTON]->rect.y+divide_by_two(buttons[BLACK_COLOR_BUTTON]->rect.h));
        // buttons to choose the white color
        add_font_to_render(renderer, "White", 100, color, buttons[WHITE_COLOR_BUTTON]->rect.x+divide_by_two(buttons[WHITE_COLOR_BUTTON]->rect.w), buttons[WHITE_COLOR_BUTTON]->rect.y+divide_by_two(buttons[WHITE_COLOR_BUTTON]->rect.h));
        // button to quit the game
        add_font_to_render(renderer, "Quit", 100, color, buttons[QUIT_BUTTON_COLOR_CHOICE]->rect.x+divide_by_two(buttons[QUIT_BUTTON_COLOR_CHOICE]->rect.w), buttons[QUIT_BUTTON_COLOR_CHOICE]->rect.y+divide_by_two(buttons[QUIT_BUTTON_COLOR_CHOICE]->rect.h));
        // button to go back to the main menu
        add_font_to_render(renderer, "Main_menu", 100, color, buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect.x+divide_by_two(buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect.w), buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect.y+divide_by_two(buttons[MAIN_MENU_BUTTON_COLOR_CHOICE]->rect.h));
        // button to go back to the previous menu
        add_font_to_render(renderer, "Back", 100, color, buttons[BACK_BUTTON_COLOR_CHOICE]->rect.x+divide_by_two(buttons[BACK_BUTTON_COLOR_CHOICE]->rect.w), buttons[BACK_BUTTON_COLOR_CHOICE]->rect.y+divide_by_two(buttons[BACK_BUTTON_COLOR_CHOICE]->rect.h));
        // add text above the buttons to choose the game mode
        add_font_to_render(renderer, "Choose the color of your pieces", 100, color, divide_by_two(WINDOW_WIDTH), 100);
        
        if (is_clicked == true){

            // showing the rectangle around the selected area
            Draw_the_red_boundary_move_Rect(renderer, draw_red_boundary_move);
            // apply a blur for all precedent things before this screen
            applyBlur(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, 3*blur_level_load_menu);
            // button to validate the choice (next)
            add_font_to_render(renderer, "Yes", 100, color, buttons[NEXT_BUTTON_COLOR_CHOICE]->rect.x+divide_by_two(buttons[NEXT_BUTTON_COLOR_CHOICE]->rect.w), buttons[NEXT_BUTTON_COLOR_CHOICE]->rect.y+divide_by_two(buttons[NEXT_BUTTON_COLOR_CHOICE]->rect.h));
            // button to go not validate the choice (not next)
            add_font_to_render(renderer, "No", 100, color, buttons[NOT_NEXT_BUTTON_COLOR_CHOICE]->rect.x+divide_by_two(buttons[NOT_NEXT_BUTTON_COLOR_CHOICE]->rect.w), buttons[NOT_NEXT_BUTTON_COLOR_CHOICE]->rect.y+divide_by_two(buttons[NOT_NEXT_BUTTON_COLOR_CHOICE]->rect.h));
            // add text above the buttons to choose the color of the player pieces
            add_font_to_render(renderer, "Do you want to continue ?", 100, color, divide_by_two(WINDOW_WIDTH), 250);

        }

    }

    // if the menu is the difficulty choice menu of the AI 
    else if (menu_type==DIFFICULTY_CHOICE || menu_type==DIFFICULTY_CHOICE_WHITE_AI || menu_type==DIFFICULTY_CHOICE_BLACK_AI){
        
        // buttons to choose the easy difficulty
        add_font_to_render(renderer, "Easy", 100, color, buttons[LVL1_DIFFICULTY_BUTTON]->rect.x+divide_by_two(buttons[LVL1_DIFFICULTY_BUTTON]->rect.w), buttons[LVL1_DIFFICULTY_BUTTON]->rect.y+divide_by_two(buttons[LVL1_DIFFICULTY_BUTTON]->rect.h));
        // buttons to choose the moderate difficulty
        add_font_to_render(renderer, "Moderate", 100, color, buttons[LVL2_DIFFICULTY_BUTTON]->rect.x+divide_by_two(buttons[LVL2_DIFFICULTY_BUTTON]->rect.w), buttons[LVL2_DIFFICULTY_BUTTON]->rect.y+divide_by_two(buttons[LVL2_DIFFICULTY_BUTTON]->rect.h));
        // buttons to choose the hard difficulty
        add_font_to_render(renderer, "Hard", 100, color, buttons[LVL4_DIFFICULTY_BUTTON]->rect.x+divide_by_two(buttons[LVL4_DIFFICULTY_BUTTON]->rect.w), buttons[LVL4_DIFFICULTY_BUTTON]->rect.y+divide_by_two(buttons[LVL4_DIFFICULTY_BUTTON]->rect.h));
        // buttons to choose the expert difficulty
        add_font_to_render(renderer, "Expert", 100, color, buttons[LVL7_DIFFICULTY_BUTTON]->rect.x+divide_by_two(buttons[LVL7_DIFFICULTY_BUTTON]->rect.w), buttons[LVL7_DIFFICULTY_BUTTON]->rect.y+divide_by_two(buttons[LVL7_DIFFICULTY_BUTTON]->rect.h));
        // button to quit the game
        add_font_to_render(renderer, "Quit", 100, color, buttons[QUIT_BUTTON_AI_CHOICE]->rect.x+divide_by_two(buttons[QUIT_BUTTON_AI_CHOICE]->rect.w), buttons[QUIT_BUTTON_AI_CHOICE]->rect.y+divide_by_two(buttons[QUIT_BUTTON_AI_CHOICE]->rect.h));
        // button to go back to the main menu
        add_font_to_render(renderer, "Main_menu", 100, color, buttons[MAIN_MENU_BUTTON_AI_CHOICE]->rect.x+divide_by_two(buttons[MAIN_MENU_BUTTON_AI_CHOICE]->rect.w), buttons[MAIN_MENU_BUTTON_AI_CHOICE]->rect.y+divide_by_two(buttons[MAIN_MENU_BUTTON_AI_CHOICE]->rect.h));
        // button to go back to the previous menu
        add_font_to_render(renderer, "Back", 100, color, buttons[BACK_BUTTON_AI_CHOICE]->rect.x+divide_by_two(buttons[BACK_BUTTON_AI_CHOICE]->rect.w), buttons[BACK_BUTTON_AI_CHOICE]->rect.y+divide_by_two(buttons[BACK_BUTTON_AI_CHOICE]->rect.h));
        // add text above the buttons to choose the diificulty of the AI
        if (menu_type==DIFFICULTY_CHOICE){
            add_font_to_render(renderer, "Choose the difficulty of the AI", 100, color, divide_by_two(WINDOW_WIDTH), 100);
        }
        else if (menu_type==DIFFICULTY_CHOICE_BLACK_AI){
            add_font_to_render(renderer, "Choose the black AI difficulty", 100, color, divide_by_two(WINDOW_WIDTH), 100);
        }
        else if (menu_type==DIFFICULTY_CHOICE_WHITE_AI){
            add_font_to_render(renderer, "Choose the white AI difficulty", 100, color, divide_by_two(WINDOW_WIDTH), 100);
        }

        if (is_clicked == true){

            // showing the rectangle around the selected area
            Draw_the_red_boundary_move_Rect(renderer, draw_red_boundary_move);
            // apply a blur for all precedent things before this screen
            applyBlur(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, 3*blur_level_load_menu);
            // button to validate the choice (next)
            add_font_to_render(renderer, "Yes", 100, color, buttons[NEXT_BUTTON_AI_CHOICE]->rect.x+divide_by_two(buttons[NEXT_BUTTON_AI_CHOICE]->rect.w), buttons[NEXT_BUTTON_AI_CHOICE]->rect.y+divide_by_two(buttons[NEXT_BUTTON_AI_CHOICE]->rect.h));
            // button to go not validate the choice (not next)
            add_font_to_render(renderer, "No", 100, color, buttons[NOT_NEXT_BUTTON_AI_CHOICE]->rect.x+divide_by_two(buttons[NOT_NEXT_BUTTON_AI_CHOICE]->rect.w), buttons[NOT_NEXT_BUTTON_AI_CHOICE]->rect.y+divide_by_two(buttons[NOT_NEXT_BUTTON_AI_CHOICE]->rect.h));
            // add text above the buttons to choose the game mode
            add_font_to_render(renderer, "Do you want to continue ?", 100, color, divide_by_two(WINDOW_WIDTH), 250);
        
        }

    }

    // if the menu is the time choice menu
    else if (menu_type == TIME_CHOICE){

        // buttons to choose the short blitz mode
        add_font_to_render(renderer, "Short Blitz", 100, color, buttons[SHORT_BLITZ_BUTTON]->rect.x+divide_by_two(buttons[SHORT_BLITZ_BUTTON]->rect.w), buttons[SHORT_BLITZ_BUTTON]->rect.y+divide_by_two(buttons[SHORT_BLITZ_BUTTON]->rect.h));
        // buttons to choose the long blitz mode
        add_font_to_render(renderer, "Long Blitz", 100, color, buttons[LONG_BLITZ_BUTTON]->rect.x+divide_by_two(buttons[LONG_BLITZ_BUTTON]->rect.w), buttons[LONG_BLITZ_BUTTON]->rect.y+divide_by_two(buttons[LONG_BLITZ_BUTTON]->rect.h));
        // buttons to choose the short mode
        add_font_to_render(renderer, "Short", 100, color, buttons[SHORT_BUTTON]->rect.x+divide_by_two(buttons[SHORT_BUTTON]->rect.w), buttons[SHORT_BUTTON]->rect.y+divide_by_two(buttons[SHORT_BUTTON]->rect.h));
        // buttons to choose the moderate mode
        add_font_to_render(renderer, "Moderate", 100, color, buttons[MODERATE_BUTTON]->rect.x+divide_by_two(buttons[MODERATE_BUTTON]->rect.w), buttons[MODERATE_BUTTON]->rect.y+divide_by_two(buttons[MODERATE_BUTTON]->rect.h));
        // buttons to choose the long mode
        add_font_to_render(renderer, "Long", 100, color, buttons[LONG_BUTTON]->rect.x+divide_by_two(buttons[LONG_BUTTON]->rect.w), buttons[LONG_BUTTON]->rect.y+divide_by_two(buttons[LONG_BUTTON]->rect.h));
        // button to quit the game
        add_font_to_render(renderer, "Quit", 100, color, buttons[QUIT_BUTTON_TIME_CHOICE]->rect.x+divide_by_two(buttons[QUIT_BUTTON_TIME_CHOICE]->rect.w), buttons[QUIT_BUTTON_TIME_CHOICE]->rect.y+divide_by_two(buttons[QUIT_BUTTON_TIME_CHOICE]->rect.h));
        // button to go back to the main menu
        add_font_to_render(renderer, "Main_menu", 100, color, buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect.x+divide_by_two(buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect.w), buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect.y+divide_by_two(buttons[MAIN_MENU_BUTTON_TIME_CHOICE]->rect.h));
        // button to go back to the previous menu
        add_font_to_render(renderer, "Back", 100, color, buttons[BACK_BUTTON_TIME_CHOICE]->rect.x+divide_by_two(buttons[BACK_BUTTON_TIME_CHOICE]->rect.w), buttons[BACK_BUTTON_TIME_CHOICE]->rect.y+divide_by_two(buttons[BACK_BUTTON_TIME_CHOICE]->rect.h));
        // add text above the buttons to choose the time mode
        add_font_to_render(renderer, "Choose the time mode", 100, color, divide_by_two(WINDOW_WIDTH), 100);

        if (is_clicked == true){

            // showing the rectangle around the selected area
            Draw_the_red_boundary_move_Rect(renderer, draw_red_boundary_move);
            // apply a blur for all precedent things before this screen
            applyBlur(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, 3*blur_level_load_menu);
            // button to validate the choice (next)
            add_font_to_render(renderer, "Yes", 100, color, buttons[LOAD_BUTTON]->rect.x+divide_by_two(buttons[LOAD_BUTTON]->rect.w), buttons[LOAD_BUTTON]->rect.y+divide_by_two(buttons[LOAD_BUTTON]->rect.h));
            // button to go not validate the choice (not next)
            add_font_to_render(renderer, "No", 100, color, buttons[NOT_LOAD_BUTTON]->rect.x+divide_by_two(buttons[NOT_LOAD_BUTTON]->rect.w), buttons[NOT_LOAD_BUTTON]->rect.y+divide_by_two(buttons[NOT_LOAD_BUTTON]->rect.h));
            // add text above the buttons to choose the game mode
            add_font_to_render(renderer, "Do you want to continue ?", 100, color, divide_by_two(WINDOW_WIDTH), 250);

        }

    }

}


void show_chess_board(SDL_Renderer *renderer, bool is_clicked, SDL_Rect draw_red_boundary_move, int selected_piece_index, SDL_Rect piece_movement_rect){

    // making the empty chessboard, coloring the background cases
    SDL_Rect rect;
    rect.w = SQUARE_SIZE;
    rect.h = SQUARE_SIZE;
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            rect.x = j * SQUARE_SIZE+WINDOW_LEFT_MARGIN;
            rect.y = i * SQUARE_SIZE+WINDOW_TOP_MARGIN;
            if (game_settings->is_board_reversed == false){
                if ((i + j) % 2 == 0) {
                    // case light square
                    SDL_SetRenderDrawColor(renderer, 238, 238, 210, 255); // light square color
                }
                else {
                    // case dark square
                    SDL_SetRenderDrawColor(renderer, 118, 150, 86, 255); // dark square color
                }
                SDL_RenderFillRect(renderer, &rect);
            }
            else if (game_settings->is_board_reversed == true){
                if ((7-i + 7-j) % 2 == 0) {
                    // case light square
                    SDL_SetRenderDrawColor(renderer, 238, 238, 210, 255); // light square color
                }
                else {
                    // case dark square
                    SDL_SetRenderDrawColor(renderer, 118, 150, 86, 255); // dark square color
                }
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    // if a move has been done, we show the movement of the piece by coloring the case in a different color
    if (chess_log->actual_size > 0){

        SDL_Rect from_index_rect;
        from_index_rect.x = get_file(get_from_square(chess_log->moves[chess_log->actual_size-1]->move_value)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN;
        from_index_rect.y = WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(get_from_square(chess_log->moves[chess_log->actual_size-1]->move_value)) * SQUARE_SIZE + WINDOW_TOP_MARGIN;
        // if the board is reversed, we need to change the coordinates
        if (game_settings->is_board_reversed == true){
            from_index_rect.x = (7 - get_file(get_from_square(chess_log->moves[chess_log->actual_size-1]->move_value))) * SQUARE_SIZE + WINDOW_LEFT_MARGIN;
            from_index_rect.y = WINDOW_BOARD_SIZE - SQUARE_SIZE - (7 - get_rank(get_from_square(chess_log->moves[chess_log->actual_size-1]->move_value))) * SQUARE_SIZE + WINDOW_TOP_MARGIN;
        }
        from_index_rect.w = SQUARE_SIZE;
        from_index_rect.h = SQUARE_SIZE;
        SDL_SetRenderDrawColor(renderer, 153, 204, 51, 100); // green color
        SDL_RenderFillRect(renderer, &from_index_rect);

        SDL_Rect to_index_rect;
        to_index_rect.x = get_file(get_to_square(chess_log->moves[chess_log->actual_size-1]->move_value)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN;
        to_index_rect.y = WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(get_to_square(chess_log->moves[chess_log->actual_size-1]->move_value)) * SQUARE_SIZE + WINDOW_TOP_MARGIN;
        // if the board is reversed, we need to change the coordinates
        if (game_settings->is_board_reversed == true){
            to_index_rect.x = (7 - get_file(get_to_square(chess_log->moves[chess_log->actual_size-1]->move_value))) * SQUARE_SIZE + WINDOW_LEFT_MARGIN;
            to_index_rect.y = WINDOW_BOARD_SIZE - SQUARE_SIZE - (7 - get_rank(get_to_square(chess_log->moves[chess_log->actual_size-1]->move_value))) * SQUARE_SIZE + WINDOW_TOP_MARGIN;
        }
        to_index_rect.w = SQUARE_SIZE;
        to_index_rect.h = SQUARE_SIZE;
        SDL_SetRenderDrawColor(renderer, 153, 204, 51, 100); // green color
        SDL_RenderFillRect(renderer, &to_index_rect);

    }

    // coloring the king case in red if a check is happening on it 
    if (chess_log->actual_size > 0){
        // if the white king is in check
        if (is_check(WHITE, bitboards, chess_log)){
            int white_king_index = get_king_index(bitboards, WHITE);
            SDL_Rect rect_white_king;
            rect_white_king.x = get_file(white_king_index) * SQUARE_SIZE + WINDOW_LEFT_MARGIN;
            rect_white_king.y =  WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(white_king_index) * SQUARE_SIZE + WINDOW_TOP_MARGIN;
            // if the board is reversed, we need to change the coordinates
            if (game_settings->is_board_reversed == true){
                rect_white_king.x = (7 - get_file(white_king_index)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN;
                rect_white_king.y =  WINDOW_BOARD_SIZE - SQUARE_SIZE - (7 - get_rank(white_king_index)) * SQUARE_SIZE + WINDOW_TOP_MARGIN;
            }
            rect_white_king.w = SQUARE_SIZE;
            rect_white_king.h = SQUARE_SIZE;
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red color
            SDL_RenderFillRect(renderer, &rect_white_king);
        }
        // if the black king is in check
        else if (is_check(BLACK, bitboards, chess_log)){
            int black_king_index = get_king_index(bitboards, BLACK);
            SDL_Rect rect_black_king;
            rect_black_king.x = get_file(black_king_index) * SQUARE_SIZE + WINDOW_LEFT_MARGIN;
            rect_black_king.y = WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(black_king_index) * SQUARE_SIZE + WINDOW_TOP_MARGIN;
            // if the board is reversed, we need to change the coordinates
            if (game_settings->is_board_reversed == true){
                rect_black_king.x = (7 - get_file(black_king_index)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN;
                rect_black_king.y = WINDOW_BOARD_SIZE - SQUARE_SIZE - (7 - get_rank(black_king_index)) * SQUARE_SIZE + WINDOW_TOP_MARGIN;
            }
            rect_black_king.w = SQUARE_SIZE;
            rect_black_king.h = SQUARE_SIZE;
            SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // red color
            SDL_RenderFillRect(renderer, &rect_black_king);
        }
    }

    // showing the letters and numbers on the side of the chessboard
    SDL_Color color = {0, 0, 0, 255}; // black
    int font_size = 20;
    int font_size_by_2 = 10;
    // if the board is not reversed
    if (game_settings->is_board_reversed == false){
        // adding the letters
        add_font_to_render(renderer, "a", font_size, color, WINDOW_LEFT_MARGIN + 1 * SQUARE_SIZE - font_size_by_2, WINDOW_TOP_MARGIN + 7 * SQUARE_SIZE + font_size_by_2);
        add_font_to_render(renderer, "b", font_size, color, WINDOW_LEFT_MARGIN + 2 * SQUARE_SIZE - font_size_by_2, WINDOW_TOP_MARGIN + 7 * SQUARE_SIZE + font_size_by_2);
        add_font_to_render(renderer, "c", font_size, color, WINDOW_LEFT_MARGIN + 3 * SQUARE_SIZE - font_size_by_2, WINDOW_TOP_MARGIN + 7 * SQUARE_SIZE + font_size_by_2);
        add_font_to_render(renderer, "d", font_size, color, WINDOW_LEFT_MARGIN + 4 * SQUARE_SIZE - font_size_by_2, WINDOW_TOP_MARGIN + 7 * SQUARE_SIZE + font_size_by_2);
        add_font_to_render(renderer, "e", font_size, color, WINDOW_LEFT_MARGIN + 5 * SQUARE_SIZE - font_size_by_2, WINDOW_TOP_MARGIN + 7 * SQUARE_SIZE + font_size_by_2);
        add_font_to_render(renderer, "f", font_size, color, WINDOW_LEFT_MARGIN + 6 * SQUARE_SIZE - font_size_by_2, WINDOW_TOP_MARGIN + 7 * SQUARE_SIZE + font_size_by_2);
        add_font_to_render(renderer, "g", font_size, color, WINDOW_LEFT_MARGIN + 7 * SQUARE_SIZE - font_size_by_2, WINDOW_TOP_MARGIN + 7 * SQUARE_SIZE + font_size_by_2);
        add_font_to_render(renderer, "h", font_size, color, WINDOW_LEFT_MARGIN + 8 * SQUARE_SIZE - font_size_by_2, WINDOW_TOP_MARGIN + 7 * SQUARE_SIZE + font_size_by_2);
        // adding the numbers
        add_font_to_render(renderer, "1", font_size, color, WINDOW_LEFT_MARGIN + font_size_by_2, WINDOW_TOP_MARGIN + 7 * SQUARE_SIZE + font_size_by_2);
        add_font_to_render(renderer, "2", font_size, color, WINDOW_LEFT_MARGIN + font_size_by_2, WINDOW_TOP_MARGIN + 6 * SQUARE_SIZE + font_size_by_2);
        add_font_to_render(renderer, "3", font_size, color, WINDOW_LEFT_MARGIN + font_size_by_2, WINDOW_TOP_MARGIN + 5 * SQUARE_SIZE + font_size_by_2);
        add_font_to_render(renderer, "4", font_size, color, WINDOW_LEFT_MARGIN + font_size_by_2, WINDOW_TOP_MARGIN + 4 * SQUARE_SIZE + font_size_by_2);
        add_font_to_render(renderer, "5", font_size, color, WINDOW_LEFT_MARGIN + font_size_by_2, WINDOW_TOP_MARGIN + 3 * SQUARE_SIZE + font_size_by_2);
        add_font_to_render(renderer, "6", font_size, color, WINDOW_LEFT_MARGIN + font_size_by_2, WINDOW_TOP_MARGIN + 2 * SQUARE_SIZE + font_size_by_2);
        add_font_to_render(renderer, "7", font_size, color, WINDOW_LEFT_MARGIN + font_size_by_2, WINDOW_TOP_MARGIN + 1 * SQUARE_SIZE + font_size_by_2);
        add_font_to_render(renderer, "8", font_size, color, WINDOW_LEFT_MARGIN + font_size_by_2, WINDOW_TOP_MARGIN + 0 * SQUARE_SIZE + font_size_by_2);
    }
    // if the board is reversed
    else if (game_settings->is_board_reversed == true){
        // adding the letters
        add_font_to_render(renderer, "h", font_size, color, WINDOW_LEFT_MARGIN + 1 * SQUARE_SIZE - font_size_by_2, WINDOW_TOP_MARGIN + 7 * SQUARE_SIZE + font_size_by_2);
        add_font_to_render(renderer, "g", font_size, color, WINDOW_LEFT_MARGIN + 2 * SQUARE_SIZE - font_size_by_2, WINDOW_TOP_MARGIN + 7 * SQUARE_SIZE + font_size_by_2);
        add_font_to_render(renderer, "f", font_size, color, WINDOW_LEFT_MARGIN + 3 * SQUARE_SIZE - font_size_by_2, WINDOW_TOP_MARGIN + 7 * SQUARE_SIZE + font_size_by_2);
        add_font_to_render(renderer, "e", font_size, color, WINDOW_LEFT_MARGIN + 4 * SQUARE_SIZE - font_size_by_2, WINDOW_TOP_MARGIN + 7 * SQUARE_SIZE + font_size_by_2);
        add_font_to_render(renderer, "d", font_size, color, WINDOW_LEFT_MARGIN + 5 * SQUARE_SIZE - font_size_by_2, WINDOW_TOP_MARGIN + 7 * SQUARE_SIZE + font_size_by_2);
        add_font_to_render(renderer, "c", font_size, color, WINDOW_LEFT_MARGIN + 6 * SQUARE_SIZE - font_size_by_2, WINDOW_TOP_MARGIN + 7 * SQUARE_SIZE + font_size_by_2);
        add_font_to_render(renderer, "b", font_size, color, WINDOW_LEFT_MARGIN + 7 * SQUARE_SIZE - font_size_by_2, WINDOW_TOP_MARGIN + 7 * SQUARE_SIZE + font_size_by_2);
        add_font_to_render(renderer, "a", font_size, color, WINDOW_LEFT_MARGIN + 8 * SQUARE_SIZE - font_size_by_2, WINDOW_TOP_MARGIN + 7 * SQUARE_SIZE + font_size_by_2);
        // adding the numbers
        add_font_to_render(renderer, "8", font_size, color, WINDOW_LEFT_MARGIN + font_size_by_2, WINDOW_TOP_MARGIN + 7 * SQUARE_SIZE + font_size_by_2);
        add_font_to_render(renderer, "7", font_size, color, WINDOW_LEFT_MARGIN + font_size_by_2, WINDOW_TOP_MARGIN + 6 * SQUARE_SIZE + font_size_by_2);
        add_font_to_render(renderer, "6", font_size, color, WINDOW_LEFT_MARGIN + font_size_by_2, WINDOW_TOP_MARGIN + 5 * SQUARE_SIZE + font_size_by_2);
        add_font_to_render(renderer, "5", font_size, color, WINDOW_LEFT_MARGIN + font_size_by_2, WINDOW_TOP_MARGIN + 4 * SQUARE_SIZE + font_size_by_2);
        add_font_to_render(renderer, "4", font_size, color, WINDOW_LEFT_MARGIN + font_size_by_2, WINDOW_TOP_MARGIN + 3 * SQUARE_SIZE + font_size_by_2);
        add_font_to_render(renderer, "3", font_size, color, WINDOW_LEFT_MARGIN + font_size_by_2, WINDOW_TOP_MARGIN + 2 * SQUARE_SIZE + font_size_by_2);
        add_font_to_render(renderer, "2", font_size, color, WINDOW_LEFT_MARGIN + font_size_by_2, WINDOW_TOP_MARGIN + 1 * SQUARE_SIZE + font_size_by_2);
        add_font_to_render(renderer, "1", font_size, color, WINDOW_LEFT_MARGIN + font_size_by_2, WINDOW_TOP_MARGIN + 0 * SQUARE_SIZE + font_size/2);
    }

    // going through the 64 squares of the chessboard
    for (int j = 0; j < 64; j++) {
        for (int i = 0; i < NUMBER_OF_BIBOARD; i++) {
            // Add white pieces if there is a white piece on the square
            if (bitboards[i] & (1ULL << j)) {
                char* name_piece;
                switch (i) {
                    case PAWN_WHITE:
                        name_piece = "../../Images/PNG_Chess_Game_Pieces/white_pawn.png";
                        break;
                    case KNIGHT_WHITE:
                        name_piece = "../../Images/PNG_Chess_Game_Pieces/white_knight.png";
                        break;
                    case BISHOP_WHITE:
                        name_piece = "../../Images/PNG_Chess_Game_Pieces/white_bishop.png";
                        break;
                    case ROOK_WHITE:
                        name_piece = "../../Images/PNG_Chess_Game_Pieces/white_rook.png";
                        break;
                    case QUEEN_WHITE:
                        name_piece = "../../Images/PNG_Chess_Game_Pieces/white_queen.png";
                        break;
                    case KING_WHITE:
                        name_piece = "../../Images/PNG_Chess_Game_Pieces/white_king.png";
                        break;
                    case PAWN_BLACK:
                        name_piece = "../../Images/PNG_Chess_Game_Pieces/black_pawn.png";
                        break;
                    case KNIGHT_BLACK:
                        name_piece = "../../Images/PNG_Chess_Game_Pieces/black_knight.png";
                        break;
                    case BISHOP_BLACK:
                        name_piece = "../../Images/PNG_Chess_Game_Pieces/black_bishop.png";
                        break;
                    case ROOK_BLACK:
                        name_piece = "../../Images/PNG_Chess_Game_Pieces/black_rook.png";
                        break;
                    case QUEEN_BLACK:
                        name_piece = "../../Images/PNG_Chess_Game_Pieces/black_queen.png";
                        break;
                    case KING_BLACK:
                        name_piece = "../../Images/PNG_Chess_Game_Pieces/black_king.png";
                        break;
                    case NOTHING:
                        name_piece = "Nothing";
                        break;
                }
                // Define destination rectangle
                SDL_Rect destRect = {get_file(j) * SQUARE_SIZE + WINDOW_LEFT_MARGIN,WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(j) * SQUARE_SIZE + WINDOW_TOP_MARGIN, SQUARE_SIZE, SQUARE_SIZE}; // Adjust the coordinates and size as needed
                // if the board is reversed (180° rotation)
                if (game_settings->is_board_reversed == true){
                    destRect.x = (7-get_file(j)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN;
                    destRect.y = WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(j)) * SQUARE_SIZE + WINDOW_TOP_MARGIN;
                }
                
                // if the piece j is selected, we draw it at the position of the mouse
                // for a non reversed board
                if (is_clicked == true && selected_piece_index == j){
                    destRect.x = piece_movement_rect.x-divide_by_two(SQUARE_SIZE);
                    destRect.y = piece_movement_rect.y-divide_by_two(SQUARE_SIZE);
                }
                if (strcmp(name_piece, "Nothing") != 0){
                    // Add image to renderer 
                    add_image_to_render(name_piece, renderer, destRect);
                }
            }
        }
    }

    // if a click has been done, we show the rectangle around the selected area 
    if (is_clicked == true && (((bitboards[WHITE_PIECES] & (1ULL << selected_piece_index)) && game_settings->color_of_player_that_is_playing == WHITE) || ((bitboards[BLACK_PIECES] & (1ULL << selected_piece_index)) && game_settings->color_of_player_that_is_playing == BLACK))){
        Draw_the_red_boundary_move_Rect(renderer, draw_red_boundary_move);
    }

}


void show_trajectory(SDL_Renderer* renderer, bool is_clicked, bool is_click_on_board, int selected_piece_index){

    // the click on board needs to be shown
    if (is_clicked && is_click_on_board){

        // getting the type of the piece selected
        int type_piece = get_type_of_piece(bitboards, selected_piece_index);

        // if the piece is a white pawn
        if (type_piece == PAWN_WHITE && game_settings->color_of_player_that_is_playing == WHITE){

            // looking if the pawn can move forward of 1 square (or 2 if it is on the starting line)
            if (!(bitboards[WHITE_PIECES] & (1ULL << (selected_piece_index+8))) && !(bitboards[BLACK_PIECES] & (1ULL << (selected_piece_index+8))) && selected_piece_index+8 < 64){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index+8) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index+8) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index+8)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index+8)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                // looking if the pawn can move forward of 2 squares (need to be on the starting line)
                if (!(bitboards[WHITE_PIECES] & (1ULL << (selected_piece_index+16))) && !(bitboards[BLACK_PIECES] & (1ULL << (selected_piece_index+16))) && selected_piece_index+16 < 64 && get_rank(selected_piece_index) == 1){
                    if (game_settings->is_board_reversed == false){
                        Draw_Filled_Circle(renderer, get_file(selected_piece_index+16) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index+16) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    else {
                        Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index+16)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index+16)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                }
            }
            // looking if the pawn can eat a piece on the left
            if ((bitboards[BLACK_PIECES] & (1ULL << (selected_piece_index+7))) && selected_piece_index+7 < 64 && get_file(selected_piece_index) != 0){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index+7) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index+7) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index+7)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index+7)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking if the pawn can eat a piece on the right
            if ((bitboards[BLACK_PIECES] & (1ULL << (selected_piece_index+9))) && selected_piece_index+9 < 64 && get_file(selected_piece_index) != 7){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index+9) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index+9)* SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index+9)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index+9)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking for an en passant move
            // left en passant
            if (is_en_passant_possible(WHITE, bitboards, selected_piece_index, selected_piece_index+7, chess_log) && get_file(selected_piece_index) != 0){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index+7) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index+7) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index+7)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index+7)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // right en passant
            if (is_en_passant_possible(WHITE, bitboards, selected_piece_index, selected_piece_index+9, chess_log) && get_file(selected_piece_index) != 7){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index+9) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index+9) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index+9)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index+9)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }

        }
        // if the piece is a black pawn
        else if (type_piece == PAWN_BLACK && game_settings->color_of_player_that_is_playing == BLACK){

            // looking if the pawn can move forward of 1 square (or 2 if it is on the starting line)
            if (!(bitboards[WHITE_PIECES] & (1ULL << (selected_piece_index-8))) && !(bitboards[BLACK_PIECES] & (1ULL << (selected_piece_index-8))) && selected_piece_index-8 >= 0){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index-8) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index-8) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index-8)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index-8)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                // looking if the pawn can move forward of 2 squares (need to be on the starting line)
                if (!(bitboards[WHITE_PIECES] & (1ULL << (selected_piece_index-16))) && !(bitboards[BLACK_PIECES] & (1ULL << (selected_piece_index-16))) && selected_piece_index-16 >= 0 && get_rank(selected_piece_index) == 6){
                    if (game_settings->is_board_reversed == false){
                        Draw_Filled_Circle(renderer, get_file(selected_piece_index-16) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index-16) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    else {
                        Draw_Filled_Circle(renderer, get_file(7-(selected_piece_index-16)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index-16)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                }
            }
            // looking if the pawn can eat a piece on the left
            if ((bitboards[WHITE_PIECES] & (1ULL << (selected_piece_index-9))) && selected_piece_index-9 >= 0 && get_file(selected_piece_index) != 0){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index-9) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index-9) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index-9)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index-9)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking if the pawn can eat a piece on the right
            if ((bitboards[WHITE_PIECES] & (1ULL << (selected_piece_index-7))) && selected_piece_index-7 >= 0 && get_file(selected_piece_index) != 7){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index-7) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index-7) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index-7)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index-7)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking for an en passant move
            // left en passant
            if (is_en_passant_possible(BLACK, bitboards, selected_piece_index, selected_piece_index-9, chess_log) && get_file(selected_piece_index) != 0){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index-9) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index-9) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index-9)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index-9)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // right en passant
            if (is_en_passant_possible(BLACK, bitboards, selected_piece_index, selected_piece_index-7, chess_log) && get_file(selected_piece_index) != 7){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index-7) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index-7) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index-7)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index-7)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }

        }
        // if the piece is a white knight
        else if (type_piece == KNIGHT_WHITE && game_settings->color_of_player_that_is_playing == WHITE){

            // we need to show the trajectory of the knight, we look around it in the possible directions, but the direction can't be of the same color
            // looking up and left left
            if (!(bitboards[WHITE_PIECES] & (1ULL << (selected_piece_index+6))) && selected_piece_index+6 < 64 && get_file(selected_piece_index+6) == get_file(selected_piece_index) - 2 && get_rank(selected_piece_index+6) == get_rank(selected_piece_index) + 1){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index+6) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index+6) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index+6)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index+6)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking up up and left
            if (!(bitboards[WHITE_PIECES] & (1ULL << (selected_piece_index+15))) && selected_piece_index+15 < 64 && get_file(selected_piece_index+15) == get_file(selected_piece_index) - 1 && get_rank(selected_piece_index+15) == get_rank(selected_piece_index) + 2){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index+15) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index+15) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index+15)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index+15)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking up up and right
            if (!(bitboards[WHITE_PIECES] & (1ULL << (selected_piece_index+17))) && selected_piece_index+17 < 64 && get_file(selected_piece_index+17) == get_file(selected_piece_index) + 1 && get_rank(selected_piece_index+17) == get_rank(selected_piece_index) + 2){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index+17) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index+17) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index+17)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index+17)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking up and right right
            if (!(bitboards[WHITE_PIECES] & (1ULL << (selected_piece_index+10))) && selected_piece_index+10 < 64 && get_file(selected_piece_index+10) == get_file(selected_piece_index) + 2 && get_rank(selected_piece_index+10) == get_rank(selected_piece_index) + 1){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index+10) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index+10) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index+10)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index+10)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking down and right right
            if (!(bitboards[WHITE_PIECES] & (1ULL << (selected_piece_index-6))) && selected_piece_index-6 >= 0 && get_file(selected_piece_index-6) == get_file(selected_piece_index) + 2 && get_rank(selected_piece_index-6) == get_rank(selected_piece_index) - 1){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index-6) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index-6) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index-6)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index-6)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking down down and right
            if (!(bitboards[WHITE_PIECES] & (1ULL << (selected_piece_index-15))) && selected_piece_index-15 >= 0 && get_file(selected_piece_index-15) == get_file(selected_piece_index) + 1 && get_rank(selected_piece_index-15) == get_rank(selected_piece_index) - 2){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index-15) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index-15) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index-15)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index-15)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking down down and left
            if (!(bitboards[WHITE_PIECES] & (1ULL << (selected_piece_index-17))) && selected_piece_index-17 >= 0 && get_file(selected_piece_index-17) == get_file(selected_piece_index) - 1 && get_rank(selected_piece_index-17) == get_rank(selected_piece_index) - 2){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index-17) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index-17) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index-17)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index-17)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking down and left left
            if (!(bitboards[WHITE_PIECES] & (1ULL << (selected_piece_index-10))) && selected_piece_index-10 >= 0 && get_file(selected_piece_index-10) == get_file(selected_piece_index) - 2 && get_rank(selected_piece_index-10) == get_rank(selected_piece_index) - 1){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index-10) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index-10) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index-10)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index-10)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }

        }
        // if the piece is a black knight
        else if (type_piece == KNIGHT_BLACK && game_settings->color_of_player_that_is_playing == BLACK){
            
            // we need to show the trajectory of the knight, we look around it in the possible directions, but the direction can't be of the same color
            // looking up and left left
            if (!(bitboards[BLACK_PIECES] & (1ULL << (selected_piece_index+6))) && selected_piece_index+6 < 64 && get_file(selected_piece_index+6) == get_file(selected_piece_index) - 2 && get_rank(selected_piece_index+6) == get_rank(selected_piece_index) + 1){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index+6) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index+6) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index+6)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index+6)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking up up and left
            if (!(bitboards[BLACK_PIECES] & (1ULL << (selected_piece_index+15))) && selected_piece_index+15 < 64 && get_file(selected_piece_index+15) == get_file(selected_piece_index) - 1 && get_rank(selected_piece_index+15) == get_rank(selected_piece_index) + 2){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index+15) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index+15) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index+15)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index+15)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking up up and right
            if (!(bitboards[BLACK_PIECES] & (1ULL << (selected_piece_index+17))) && selected_piece_index+17 < 64 && get_file(selected_piece_index+17) == get_file(selected_piece_index) + 1 && get_rank(selected_piece_index+17) == get_rank(selected_piece_index) + 2){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index+17) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index+17) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index+17)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index+17)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking up and right right
            if (!(bitboards[BLACK_PIECES] & (1ULL << (selected_piece_index+10))) && selected_piece_index+10 < 64 && get_file(selected_piece_index+10) == get_file(selected_piece_index) + 2 && get_rank(selected_piece_index+10) == get_rank(selected_piece_index) + 1){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index+10) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index+10) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index+10)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index+10)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking down and right right
            if (!(bitboards[BLACK_PIECES] & (1ULL << (selected_piece_index-6))) && selected_piece_index-6 >= 0 && get_file(selected_piece_index-6) == get_file(selected_piece_index) + 2 && get_rank(selected_piece_index-6) == get_rank(selected_piece_index) - 1){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index-6) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index-6) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index-6)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index-6)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking down down and right
            if (!(bitboards[BLACK_PIECES] & (1ULL << (selected_piece_index-15))) && selected_piece_index-15 >= 0 && get_file(selected_piece_index-15) == get_file(selected_piece_index) + 1 && get_rank(selected_piece_index-15) == get_rank(selected_piece_index) - 2){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index-15) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index-15) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index-15)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index-15)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking down down and left
            if (!(bitboards[BLACK_PIECES] & (1ULL << (selected_piece_index-17))) && selected_piece_index-17 >= 0 && get_file(selected_piece_index-17) == get_file(selected_piece_index) - 1 && get_rank(selected_piece_index-17) == get_rank(selected_piece_index) - 2){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index-17) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index-17) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index-17)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index-17)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking down and left left
            if (!(bitboards[BLACK_PIECES] & (1ULL << (selected_piece_index-10))) && selected_piece_index-10 >= 0 && get_file(selected_piece_index-10) == get_file(selected_piece_index) - 2 && get_rank(selected_piece_index-10) == get_rank(selected_piece_index) - 1){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index-10) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index-10) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index-10)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index-10)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }

        }
        // the queen is both a bishop and a rook (we need to make this separation so the queen has both trajectories)
        else if (type_piece == BISHOP_WHITE || type_piece == QUEEN_WHITE || type_piece == ROOK_WHITE){
            // if the piece is a white bishop or a white queen
            if ((type_piece == BISHOP_WHITE || type_piece == QUEEN_WHITE) && game_settings->color_of_player_that_is_playing == WHITE){
                
                // we need to show the trajectory of the bishop, we look around it in the possible directions (diagonals), but the direction can't be of the same color
                // looking up and left
                int i = selected_piece_index;
                while (!(bitboards[WHITE_PIECES] & (1ULL << (i+7))) && i+7 < 64 && get_file(i+7) != 7){ // we stop if there is a white piece on the way or if we are at the right edge of the board
                    if (game_settings->is_board_reversed == false){
                        Draw_Filled_Circle(renderer, get_file(i+7) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(i+7) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    else {
                        Draw_Filled_Circle(renderer, (7-get_file(i+7)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(i+7)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    i += 7;
                    // if there is a black piece on the way, we stop
                    if (bitboards[BLACK_PIECES] & (1ULL << i)){
                        break;
                    }
                }
                // looking up and right
                i = selected_piece_index;
                while (!(bitboards[WHITE_PIECES] & (1ULL << (i+9))) && i+9 < 64 && get_file(i+9) != 0){ // we stop if there is a white piece on the way or if we are at the left edge of the board
                    if (game_settings->is_board_reversed == false){
                        Draw_Filled_Circle(renderer, get_file(i+9) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(i+9) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    else {
                        Draw_Filled_Circle(renderer, (7-get_file(i+9)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(i+9)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    i += 9;
                    // if there is a black piece on the way, we stop
                    if (bitboards[BLACK_PIECES] & (1ULL << i)){
                        break;
                    }
                }
                // looking down and right
                i = selected_piece_index;
                while (!(bitboards[WHITE_PIECES] & (1ULL << (i-7))) && i-7 >= 0 && get_file(i-7) != 0){ // we stop if there is a white piece on the way or if we are at the left edge of the board
                    if (game_settings->is_board_reversed == false){
                        Draw_Filled_Circle(renderer, get_file(i-7) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(i-7) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    else {
                        Draw_Filled_Circle(renderer, (7-get_file(i-7)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(i-7)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    i -= 7;
                    // if there is a black piece on the way, we stop
                    if (bitboards[BLACK_PIECES] & (1ULL << i)){
                        break;
                    }
                }
                // looking down and left
                i = selected_piece_index;
                while (!(bitboards[WHITE_PIECES] & (1ULL << (i-9))) && i-9 >= 0 && get_file(i-9) != 7){ // we stop if there is a white piece on the way or if we are at the right edge of the board
                    if (game_settings->is_board_reversed == false){
                        Draw_Filled_Circle(renderer, get_file(i-9) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(i-9) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    else {
                        Draw_Filled_Circle(renderer, (7-get_file(i-9)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(i-9)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    i -= 9;
                    // if there is a black piece on the way, we stop
                    if (bitboards[BLACK_PIECES] & (1ULL << i)){
                        break;
                    }
                }
                
            }
            // if the piece is a white rook or a white queen
            if ((type_piece == ROOK_WHITE || type_piece == QUEEN_WHITE) && game_settings->color_of_player_that_is_playing == WHITE){

                // we need to show the trajectory of the rook, we look around it in the possible directions (horizontally and vertically), but the direction can't be of the same color
                // looking left
                int i = selected_piece_index;
                while (!(bitboards[WHITE_PIECES] & (1ULL << (i-1))) && i-1 >= 0 && get_file(i-1) != 7){ // we stop if there is a white piece on the way or if we are at the right edge of the board
                    if (game_settings->is_board_reversed == false){
                        Draw_Filled_Circle(renderer, get_file(i-1) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(i-1) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    else {
                        Draw_Filled_Circle(renderer, (7-get_file(i-1)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(i-1)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    i -= 1;
                    // if there is a black piece on the way, we stop
                    if (bitboards[BLACK_PIECES] & (1ULL << i)){
                        break;
                    }
                }
                // looking up
                i = selected_piece_index;
                while (!(bitboards[WHITE_PIECES] & (1ULL << (i+8))) && i+8 < 64){ // we stop if there is a white piece on the way
                    if (game_settings->is_board_reversed == false){
                        Draw_Filled_Circle(renderer, get_file(i+8) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(i+8) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    else {
                        Draw_Filled_Circle(renderer, (7-get_file(i+8)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(i+8)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    i += 8;
                    // if there is a black piece on the way, we stop
                    if (bitboards[BLACK_PIECES] & (1ULL << i)){
                        break;
                    }
                }
                // looking right
                i = selected_piece_index;
                while (!(bitboards[WHITE_PIECES] & (1ULL << (i+1))) && i+1 < 64 && get_file(i+1) != 0){ // we stop if there is a white piece on the way or if we are at the left edge of the board
                    if (game_settings->is_board_reversed == false){
                        Draw_Filled_Circle(renderer, get_file(i+1) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(i+1) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    else {
                        Draw_Filled_Circle(renderer, (7-get_file(i+1)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(i+1)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    i += 1;
                    // if there is a black piece on the way, we stop
                    if (bitboards[BLACK_PIECES] & (1ULL << i)){
                        break;
                    }
                }
                // looking down
                i = selected_piece_index;
                while (!(bitboards[WHITE_PIECES] & (1ULL << (i-8))) && i-8 >= 0){ // we stop if there is a white piece on the way
                    if (game_settings->is_board_reversed == false){
                        Draw_Filled_Circle(renderer, get_file(i-8) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(i-8) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    else {
                        Draw_Filled_Circle(renderer, (7-get_file(i-8)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(i-8)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    i -= 8;
                    // if there is a black piece on the way, we stop
                    if (bitboards[BLACK_PIECES] & (1ULL << i)){
                        break;
                    }
                }

            }
        }
        // the queen is both a bishop and a rook (we need to make this separation so the queen has both trajectories)
        else if (type_piece == BISHOP_BLACK || type_piece == QUEEN_BLACK || type_piece == ROOK_BLACK){
            // if the piece is a black bishop or a black queen
            if ((type_piece == BISHOP_BLACK || type_piece == QUEEN_BLACK) && game_settings->color_of_player_that_is_playing == BLACK){

                // we need to show the trajectory of the bishop, we look around it in the possible directions (diagonals), but the direction can't be of the same color
                // looking up and left
                int i = selected_piece_index;
                while (!(bitboards[BLACK_PIECES] & (1ULL << (i+7))) && i+7 < 64 && get_file(i+7) != 7){ // we stop if there is a black piece on the way or if we are at the right edge of the board
                    if (game_settings->is_board_reversed == false){
                        Draw_Filled_Circle(renderer, get_file(i+7) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(i+7) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    else {
                        Draw_Filled_Circle(renderer, (7-get_file(i+7)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(i+7)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    i += 7;
                    // if there is a white piece on the way, we stop
                    if (bitboards[WHITE_PIECES] & (1ULL << i)){
                        break;
                    }
                }
                // looking up and right
                i = selected_piece_index;
                while (!(bitboards[BLACK_PIECES] & (1ULL << (i+9))) && i+9 < 64 && get_file(i+9) != 0){ // we stop if there is a black piece on the way or if we are at the left edge of the board
                    if (game_settings->is_board_reversed == false){
                        Draw_Filled_Circle(renderer, get_file(i+9) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(i+9) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    else {
                        Draw_Filled_Circle(renderer, (7-get_file(i+9)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(i+9)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    i += 9;
                    // if there is a white piece on the way, we stop
                    if (bitboards[WHITE_PIECES] & (1ULL << i)){
                        break;
                    }
                }
                // looking down and right
                i = selected_piece_index;
                while (!(bitboards[BLACK_PIECES] & (1ULL << (i-7))) && i-7 >= 0 && get_file(i-7) != 0){ // we stop if there is a black piece on the way or if we are at the left edge of the board
                    if (game_settings->is_board_reversed == false){
                        Draw_Filled_Circle(renderer, get_file(i-7) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(i-7) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    else {
                        Draw_Filled_Circle(renderer, (7-get_file(i-7)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(i-7)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    i -= 7;
                    // if there is a white piece on the way, we stop
                    if (bitboards[WHITE_PIECES] & (1ULL << i)){
                        break;
                    }
                }
                // looking down and left
                i = selected_piece_index;
                while (!(bitboards[BLACK_PIECES] & (1ULL << (i-9))) && i-9 >= 0 && get_file(i-9) != 7){ // we stop if there is a black piece on the way or if we are at the right edge of the board
                    if (game_settings->is_board_reversed == false){
                        Draw_Filled_Circle(renderer, get_file(i-9) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(i-9) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    else {
                        Draw_Filled_Circle(renderer, (7-get_file(i-9)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(i-9)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    i -= 9;
                    // if there is a white piece on the way, we stop
                    if (bitboards[WHITE_PIECES] & (1ULL << i)){
                        break;
                    }
                }

            }
            // if the piece is a black rook or a black queen
            if ((type_piece == ROOK_BLACK || type_piece == QUEEN_BLACK) && game_settings->color_of_player_that_is_playing == BLACK){

                // we need to show the trajectory of the rook, we look around it in the possible directions (horizontally and vertically), but the direction can't be of the same color
                // looking left
                int i = selected_piece_index;
                while (!(bitboards[BLACK_PIECES] & (1ULL << (i-1))) && i-1 >= 0 && get_file(i-1) != 7){ // we stop if there is a black piece on the way or if we are at the right edge of the board
                    if (game_settings->is_board_reversed == false){
                        Draw_Filled_Circle(renderer, get_file(i-1) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(i-1) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    else {
                        Draw_Filled_Circle(renderer, (7-get_file(i-1)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(i-1)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    i -= 1;
                    // if there is a white piece on the way, we stop
                    if (bitboards[WHITE_PIECES] & (1ULL << i)){
                        break;
                    }
                }
                // looking up
                i = selected_piece_index;
                while (!(bitboards[BLACK_PIECES] & (1ULL << (i+8))) && i+8 < 64){ // we stop if there is a black piece on the way
                    if (game_settings->is_board_reversed == false){
                        Draw_Filled_Circle(renderer, get_file(i+8) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(i+8) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    else {
                        Draw_Filled_Circle(renderer, (7-get_file(i+8)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(i+8)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    i += 8;
                    // if there is a white piece on the way, we stop
                    if (bitboards[WHITE_PIECES] & (1ULL << i)){
                        break;
                    }
                }
                // looking right
                i = selected_piece_index;
                while (!(bitboards[BLACK_PIECES] & (1ULL << (i+1))) && i+1 < 64 && get_file(i+1) != 0){ // we stop if there is a black piece on the way or if we are at the left edge of the board
                    if (game_settings->is_board_reversed == false){
                        Draw_Filled_Circle(renderer, get_file(i+1) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(i+1) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    else {
                        Draw_Filled_Circle(renderer, (7-get_file(i+1)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(i+1)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    i += 1;
                    // if there is a white piece on the way, we stop
                    if (bitboards[WHITE_PIECES] & (1ULL << i)){
                        break;
                    }
                }
                // looking down
                i = selected_piece_index;
                while (!(bitboards[BLACK_PIECES] & (1ULL << (i-8))) && i-8 >= 0){ // we stop if there is a black piece on the way
                    if (game_settings->is_board_reversed == false){
                        Draw_Filled_Circle(renderer, get_file(i-8) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(i-8) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    else {
                        Draw_Filled_Circle(renderer, (7-get_file(i-8)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(i-8)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                    }
                    i -= 8;
                    // if there is a white piece on the way, we stop
                    if (bitboards[WHITE_PIECES] & (1ULL << i)){
                        break;
                    }
                }

            }
        }
        // if the piece is a white king
        else if (type_piece == KING_WHITE && game_settings->color_of_player_that_is_playing == WHITE){

            // we need to show the trajectory of the king, we look around it, but the direction can't be of the same color
            // looking left
            if (!(bitboards[WHITE_PIECES] & (1ULL << (selected_piece_index-1))) && selected_piece_index-1 >= 0 && get_file(selected_piece_index) != 0){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index-1) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index-1) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index-1)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index-1)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking up and left 
            if (!(bitboards[WHITE_PIECES] & (1ULL << (selected_piece_index+7))) && selected_piece_index+7 < 64 && get_file(selected_piece_index) != 0 && get_rank(selected_piece_index) != 7){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index+7) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index+7) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index+7)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index+7)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking up
            if (!(bitboards[WHITE_PIECES] & (1ULL << (selected_piece_index+8))) && selected_piece_index+8 < 64 && get_rank(selected_piece_index) != 7){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index+8) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index+8) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index+8)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index+8)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking up and right
            if (!(bitboards[WHITE_PIECES] & (1ULL << (selected_piece_index+9))) && selected_piece_index+9 < 64 && get_file(selected_piece_index) != 7 && get_rank(selected_piece_index) != 7){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index+9) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index+9) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index+9)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index+9)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking right
            if (!(bitboards[WHITE_PIECES] & (1ULL << (selected_piece_index+1))) && selected_piece_index+1 < 64 && get_file(selected_piece_index) != 7){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index+1) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index+1) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index+1)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index+1)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking down and right
            if (!(bitboards[WHITE_PIECES] & (1ULL << (selected_piece_index-7))) && selected_piece_index-7 >= 0 && get_file(selected_piece_index) != 7 && get_rank(selected_piece_index) != 0){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index-7) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index-7) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index-7)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index-7)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking down
            if (!(bitboards[WHITE_PIECES] & (1ULL << (selected_piece_index-8))) && selected_piece_index-8 >= 0 && get_rank(selected_piece_index) != 0){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index-8) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index-8) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index-8)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index-8)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking down and left
            if (!(bitboards[WHITE_PIECES] & (1ULL << (selected_piece_index-9))) && selected_piece_index-9 >= 0 && get_file(selected_piece_index) != 0 && get_rank(selected_piece_index) != 0){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index-9) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index-9) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index-9)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index-9)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // getting the type of castle that can be done
            // looking for the short castle
            if (is_castle_possible(WHITE, bitboards, selected_piece_index, selected_piece_index+2, chess_log)){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, 6 * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - 0 * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-6) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-0) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking for the long castle
            if (is_castle_possible(WHITE, bitboards, selected_piece_index, selected_piece_index-2, chess_log)){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, 2 * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - 0 * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-2) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-0) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }

        }
        // if the piece is a black king
        else if (type_piece == KING_BLACK && game_settings->color_of_player_that_is_playing == BLACK){

            // we need to show the trajectory of the king, we look around it, but the direction can't be of the same color
            // looking left
            if (!(bitboards[BLACK_PIECES] & (1ULL << (selected_piece_index-1))) && selected_piece_index-1 >= 0 && get_file(selected_piece_index) != 0){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index-1) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index-1) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index-1)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index-1)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking up and left
            if (!(bitboards[BLACK_PIECES] & (1ULL << (selected_piece_index+7))) && selected_piece_index+7 < 64 && get_file(selected_piece_index) != 0 && get_rank(selected_piece_index) != 7){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index+7) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index+7) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index+7)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index+7)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking up
            if (!(bitboards[BLACK_PIECES] & (1ULL << (selected_piece_index+8))) && selected_piece_index+8 < 64 && get_rank(selected_piece_index) != 7){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index+8) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index+8) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index+8)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index+8)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking up and right
            if (!(bitboards[BLACK_PIECES] & (1ULL << (selected_piece_index+9))) && selected_piece_index+9 < 64 && get_file(selected_piece_index) != 7 && get_rank(selected_piece_index) != 7){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index+9) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index+9) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index+9)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index+9)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking right
            if (!(bitboards[BLACK_PIECES] & (1ULL << (selected_piece_index+1))) && selected_piece_index+1 < 64 && get_file(selected_piece_index) != 7){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index+1) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index+1) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index+1)) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index+1)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking down and right
            if (!(bitboards[BLACK_PIECES] & (1ULL << (selected_piece_index-7))) && selected_piece_index-7 >= 0 && get_file(selected_piece_index) != 7 && get_rank(selected_piece_index) != 0){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index-7) % 8 * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index-7) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index-7) % 8) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index-7)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking down
            if (!(bitboards[BLACK_PIECES] & (1ULL << (selected_piece_index-8))) && selected_piece_index-8 >= 0 && get_rank(selected_piece_index) != 0){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index-8) % 8 * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index-8) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index-8) % 8) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index-8)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking down and left
            if (!(bitboards[BLACK_PIECES] & (1ULL << (selected_piece_index-9))) && selected_piece_index-9 >= 0 && get_file(selected_piece_index) != 0 && get_rank(selected_piece_index) != 0){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, get_file(selected_piece_index-9) % 8 * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - get_rank(selected_piece_index-9) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-get_file(selected_piece_index-9) % 8) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-get_rank(selected_piece_index-9)) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // getting the type of castle that can be done
            // looking for the short castle
            if (is_castle_possible(BLACK, bitboards, selected_piece_index, selected_piece_index+2, chess_log)){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, 6 * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - 7 * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-6) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-7) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }
            // looking for the long castle
            if (is_castle_possible(BLACK, bitboards, selected_piece_index, selected_piece_index-2, chess_log)){
                if (game_settings->is_board_reversed == false){
                    Draw_Filled_Circle(renderer, 2 * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - 7 * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
                else {
                    Draw_Filled_Circle(renderer, (7-2) * SQUARE_SIZE + WINDOW_LEFT_MARGIN + divide_by_two(SQUARE_SIZE), WINDOW_BOARD_SIZE - SQUARE_SIZE - (7-7) * SQUARE_SIZE + WINDOW_TOP_MARGIN + divide_by_two(SQUARE_SIZE), divide_by_two(divide_by_two(divide_by_two((SQUARE_SIZE)))));
                }
            }

        }

    }

}


void show_captured_pieces(SDL_Renderer* renderer){
    
    int size_piece = 20;
    SDL_Rect destRect;
    // we need to have a grey background for the captured pieces to be able to see them 
    destRect.x = WINDOW_LEFT_MARGIN-5;
    destRect.h = size_piece + 10;

    // the one for the white pieces 
    if (game_settings->is_board_reversed == false){
        destRect.y = 10;
    }
    else {
        destRect.y = WINDOW_HEIGHT - WINDOW_TOP_MARGIN + 10;
    }
    destRect.w = 5 + captured_pieces_and_score->number_of_white_captured_pieces * divide_by_two(size_piece) + 5;
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // grey
    SDL_RenderFillRect(renderer, &destRect);
    // the one for the black pieces
    if (game_settings->is_board_reversed == false){
        destRect.y = WINDOW_HEIGHT - WINDOW_TOP_MARGIN + 10;
    }
    else {
        destRect.y = 10;
    }
    destRect.w = 5 + captured_pieces_and_score->number_of_black_captured_pieces * divide_by_two(size_piece) + 5;
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // grey
    SDL_RenderFillRect(renderer, &destRect);

    destRect.w = size_piece;
    destRect.h = size_piece;
    if (game_settings->is_board_reversed == false){
            destRect.y = 15;
    }
    else {
        destRect.y = WINDOW_HEIGHT - WINDOW_TOP_MARGIN + 15;
    }
    // show the white captured pieces 
    for (int i=0; i<captured_pieces_and_score->number_of_white_captured_pieces; i++){
        destRect.x = WINDOW_LEFT_MARGIN + i * divide_by_two(size_piece) - 5;
        // printing the right image for the piece captured
        switch(captured_pieces_and_score->white_capture_pieces[i]){
            case PAWN_WHITE:
                add_image_to_render("../../Images/PNG_Chess_Game_Pieces/white_pawn.png", renderer, destRect);
                break;
            case KNIGHT_WHITE:
                add_image_to_render("../../Images/PNG_Chess_Game_Pieces/white_knight.png", renderer, destRect);
                break;
            case BISHOP_WHITE:
                add_image_to_render("../../Images/PNG_Chess_Game_Pieces/white_bishop.png", renderer, destRect);
                break;
            case ROOK_WHITE:
                add_image_to_render("../../Images/PNG_Chess_Game_Pieces/white_rook.png", renderer, destRect);
                break;
            case QUEEN_WHITE:
                add_image_to_render("../../Images/PNG_Chess_Game_Pieces/white_queen.png", renderer, destRect);
                break;
            case KING_WHITE:
                add_image_to_render("../../Images/PNG_Chess_Game_Pieces/white_king.png", renderer, destRect);
                break;
        }
    }
    if (game_settings->is_board_reversed == false){
        destRect.y = WINDOW_HEIGHT - WINDOW_TOP_MARGIN + 15;
    }
    else {
        destRect.y = 15;
    }
    // show the black captured pieces
    for (int i=0; i<captured_pieces_and_score->number_of_black_captured_pieces; i++){
        destRect.x = WINDOW_LEFT_MARGIN + i * divide_by_two(size_piece) -5;
        // printing the right image for the piece captured
        switch(captured_pieces_and_score->black_capture_pieces[i]){
            case PAWN_BLACK:
                add_image_to_render("../../Images/PNG_Chess_Game_Pieces/black_pawn.png", renderer, destRect);
                break;
            case KNIGHT_BLACK:
                add_image_to_render("../../Images/PNG_Chess_Game_Pieces/black_knight.png", renderer, destRect);
                break;
            case BISHOP_BLACK:
                add_image_to_render("../../Images/PNG_Chess_Game_Pieces/black_bishop.png", renderer, destRect);
                break;
            case ROOK_BLACK:
                add_image_to_render("../../Images/PNG_Chess_Game_Pieces/black_rook.png", renderer, destRect);
                break;
            case QUEEN_BLACK:
                add_image_to_render("../../Images/PNG_Chess_Game_Pieces/black_queen.png", renderer, destRect);
                break;
            case KING_BLACK:
                add_image_to_render("../../Images/PNG_Chess_Game_Pieces/black_king.png", renderer, destRect);
                break;
        }
    }

}


void show_score(SDL_Renderer* renderer){
    
    // if the score is different than zero 
    if (captured_pieces_and_score->score != 0){
        int x = 0;
        int y = 0;
        int size_score = 20;
        // if the player that is winning is white
        if (captured_pieces_and_score->players_that_is_winning == White_Player){
            if (game_settings->is_board_reversed == true){
                y = 15 + divide_by_two(size_score);
            }
            else {
                y = WINDOW_HEIGHT - WINDOW_TOP_MARGIN + 15 + divide_by_two(size_score);
            }
            x = WINDOW_LEFT_MARGIN + 5 + (captured_pieces_and_score->number_of_black_captured_pieces+1) * divide_by_two(size_score) + 5;
        }
        // if the player that is winning is black
        else if (captured_pieces_and_score->players_that_is_winning == Black_Player){
            if (game_settings->is_board_reversed == true){
                y = WINDOW_HEIGHT - WINDOW_TOP_MARGIN + 15 + divide_by_two(size_score);
            }
            else {
                y = 15 + divide_by_two(size_score);
            }
            x = WINDOW_LEFT_MARGIN + 5 + (captured_pieces_and_score->number_of_white_captured_pieces+1) * divide_by_two(size_score) + 5;
        }
        char* score = malloc(10*sizeof(char));
        sprintf(score, "%d", captured_pieces_and_score->score);
        SDL_Color color = {230, 230, 230, 255}; // white
        add_font_to_render(renderer, score, size_score, color, x, y);
        free(score);
    }
   
}


void show_updated_timer(SDL_Renderer* renderer){

    SDL_Rect destRect;
    destRect.w = SQUARE_SIZE + divide_by_two(SQUARE_SIZE);
    destRect.h = 50;
    destRect.x = WINDOW_LEFT_MARGIN + WINDOW_BOARD_SIZE - SQUARE_SIZE - divide_by_two(SQUARE_SIZE);
    // if the player playing is white
    if (game_settings->player_that_is_playing == White_Player){
        // if the board is not reversed
        if (game_settings->is_board_reversed == false){
            destRect.y = WINDOW_HEIGHT - 50;
            SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255); // white
            SDL_RenderFillRect(renderer, &destRect);
            destRect.y = 0;
            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255); // grey
            SDL_RenderFillRect(renderer, &destRect);
        }
        // if the board is reversed
        else if (game_settings->is_board_reversed == true){
            destRect.y = 0;
            SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255); // white
            SDL_RenderFillRect(renderer, &destRect);
            destRect.y = WINDOW_HEIGHT - 50;
            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255); // grey
            SDL_RenderFillRect(renderer, &destRect);
        }
    }
    // if the player playing is black
    if (game_settings->player_that_is_playing == Black_Player){
        // if the board is not reversed
        if (game_settings->is_board_reversed == false){
            destRect.y = 0;
            SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255); // white
            SDL_RenderFillRect(renderer, &destRect);
            destRect.y = WINDOW_HEIGHT - 50; 
            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255); // grey
            SDL_RenderFillRect(renderer, &destRect);
        }
        // if the board is reversed
        else if (game_settings->is_board_reversed == true){
            destRect.y = WINDOW_HEIGHT - 50;
            SDL_SetRenderDrawColor(renderer, 230, 230, 230, 255); // white
            SDL_RenderFillRect(renderer, &destRect);
            destRect.y = 0;
            SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255); // grey
            SDL_RenderFillRect(renderer, &destRect);
        }
        
    }

    SDL_Color color = {25, 25, 25, 255}; // black

    // getting the minutes and seconds for the white player
    int white_minutes_integer = (int) game_settings->white_time_remaining / 60;
    int white_seconds_integer = (int) game_settings->white_time_remaining % 60;
    char* white_minutes = malloc(10*sizeof(char));
    if (white_minutes_integer < 10){
        sprintf(white_minutes, "0%d", white_minutes_integer);
    } 
    else if (white_minutes_integer >= 10){
        sprintf(white_minutes, "%d", white_minutes_integer);
    }
    char* white_seconds = malloc(10*sizeof(char));
    if (white_seconds_integer < 10){
        sprintf(white_seconds, "0%d", white_seconds_integer);
    }
    else if (white_seconds_integer >= 10){
        sprintf(white_seconds, "%d", white_seconds_integer);
    }
    // making a string with the minutes and the seconds for the white player separated by a ":"
    char* white_time = malloc(10*sizeof(char));
    sprintf(white_time, "%s:%s", white_minutes, white_seconds);
    if (game_settings->is_board_reversed == false){
        add_font_to_render(renderer, white_time, 30, color, WINDOW_LEFT_MARGIN + WINDOW_BOARD_SIZE - divide_by_two(divide_by_two(SQUARE_SIZE*3)), WINDOW_HEIGHT - 50 + 25);
    }
    else if (game_settings->is_board_reversed == true){
        add_font_to_render(renderer, white_time, 30, color, WINDOW_LEFT_MARGIN + WINDOW_BOARD_SIZE - divide_by_two(divide_by_two(SQUARE_SIZE*3)), 25);
    }
    free(white_minutes);
    free(white_seconds);
    free(white_time);

    // getting the minutes and seconds for the black player
    int black_minutes_integer = (int) game_settings->black_time_remaining / 60;
    int black_seconds_integer = (int) game_settings->black_time_remaining % 60;
    char* black_minutes = malloc(10*sizeof(char));
    if (black_minutes_integer < 10){
        sprintf(black_minutes, "0%d", black_minutes_integer);
    }
    else if (black_minutes_integer >= 10){
        sprintf(black_minutes, "%d", black_minutes_integer);
    }
    char* black_seconds = malloc(10*sizeof(char));
    if (black_seconds_integer < 10){
        sprintf(black_seconds, "0%d", black_seconds_integer);
    }
    else if (black_seconds_integer >= 10){
        sprintf(black_seconds, "%d", black_seconds_integer);
    }
    // making a string with the minutes and the seconds for the black player separated by a ":"
    char* black_time = malloc(10*sizeof(char));
    sprintf(black_time, "%s:%s", black_minutes, black_seconds);
    if (game_settings->is_board_reversed == false){
        add_font_to_render(renderer, black_time, 30, color, WINDOW_LEFT_MARGIN + WINDOW_BOARD_SIZE - divide_by_two(divide_by_two(SQUARE_SIZE*3)), 25);
    }
    else if (game_settings->is_board_reversed == true){
        add_font_to_render(renderer, black_time, 30, color, WINDOW_LEFT_MARGIN + WINDOW_BOARD_SIZE - divide_by_two(divide_by_two(SQUARE_SIZE*3)), WINDOW_HEIGHT - 50 + 25);
    }
    free(black_minutes);
    free(black_seconds);
    free(black_time);

}


void add_move_in_log_render(SDL_Renderer* renderer, int log_index, int color_playing, int font_size, SDL_Color sdl_color, int middle_x, int middle_y){
    
    // getting the string we want to display
    char* move_str = malloc(10*sizeof(char));

    move move_played = chess_log->moves[log_index]->move_value;
    // first we need to treat special cases before : 
    if (get_flag(move_played) == Castle_Flag){
        // if the castle is a short castle
        if (get_to_square(move_played) == 6 || get_to_square(move_played) == 62){
            sprintf(move_str, "O-O");
        }
        // if the castle is a long castle
        else if (get_to_square(move_played) == 2 || get_to_square(move_played) == 58){
            sprintf(move_str, "O-O-O");
        }
    }
    else {
       
        // if there is a promotion we need to add the piece that the pawn is promoted to by adding "=Q" for a queen, "=R" for a rook, "=B" for a bishop and "=N" for a knight
        // others special rules needs to be applied if there is a capture 
        if (is_promotion_flag(get_flag(move_played))){
            // if there is a capture during the promotion
            if (chess_log->moves[log_index]->captured_piece_type != NOTHING){
                sprintf(move_str, "%s%c", move_str, get_file(get_from_square(move_played)) + 'a');
                sprintf(move_str, "%sx", move_str);
            }

            // adding the square where the piece has been going (the destination square) 
            sprintf(move_str, "%s%c%d", move_str, get_file(get_to_square(move_played)) + 'a', get_rank(get_to_square(move_played)) + 1);

            // adding the piece that the pawn has been promoted to
            int promoted_flag = get_flag(move_played);
            if (promoted_flag == Promote_To_Queen_Flag){
                sprintf(move_str, "%s=Q", move_str);
            }
            else if (promoted_flag == Promote_To_Rook_Flag){
                sprintf(move_str, "%s=R", move_str);
            }
            else if (promoted_flag == Promote_To_Bishop_Flag){
                sprintf(move_str, "%s=B", move_str);
            }
            else if (promoted_flag == Promote_To_Knight_Flag){
                sprintf(move_str, "%s=N", move_str);
            }
        }
        // no promotion, we do the normal thing
        else {
            //  for the different pieces : K=King, Q=Queen, R=Rook, B=Bishop, N=Knight, nothing for pawn
            // since we are adding this log info after a move was played, the piece that we move is the one that is at the destination square
            int piece_moved = get_type_of_piece(bitboards_log->bitboards[log_index], get_to_square(move_played));
            // adding the letter corresponding to the piece moved in the move_str
            switch(piece_moved){
                case PAWN_WHITE:
                    break;
                case KNIGHT_WHITE:
                    sprintf(move_str, "N");
                    break;
                case BISHOP_WHITE:
                    sprintf(move_str, "B");
                    break;
                case ROOK_WHITE:
                    sprintf(move_str, "R");
                    break;
                case QUEEN_WHITE:
                    sprintf(move_str, "Q");
                    break;
                case KING_WHITE:
                    sprintf(move_str, "K");
                    break;
                case PAWN_BLACK:
                    break;
                case KNIGHT_BLACK:
                    sprintf(move_str, "N");
                    break;
                case BISHOP_BLACK:
                    sprintf(move_str, "B");
                    break;
                case ROOK_BLACK:
                    sprintf(move_str, "R");
                    break;
                case QUEEN_BLACK:
                    sprintf(move_str, "Q");
                    break;
                case KING_BLACK:
                    sprintf(move_str, "K");
                    break;
            }

            // if this a capture, we need to add an "x" before, if it's a pawn that is taking, we need to indicate its column before the "x"
            if (chess_log->moves[log_index]->captured_piece_type != NOTHING){
                if (piece_moved == PAWN_WHITE || piece_moved == PAWN_BLACK){
                    sprintf(move_str, "%s%c", move_str, get_file(get_from_square(move_played)) + 'a');
                }
                sprintf(move_str, "%sx", move_str);
            }

            // adding the square where the piece has been going (the destination square) 
            sprintf(move_str, "%s%c%d", move_str, get_file(get_to_square(move_played)) + 'a', get_rank(get_to_square(move_played)) + 1);
        }

        // one parameter is the log (but the function always get the last element, no the one at the i-th move), we need to change the last element of the log to be the one at the i-th move and then putting it back
        move last_move = chess_log->moves[chess_log->actual_size-1]->move_value;
        chess_log->moves[chess_log->actual_size-1]->move_value = chess_log->moves[log_index]->move_value;
        int last_captured_piece_type = chess_log->moves[chess_log->actual_size-1]->captured_piece_type;
        chess_log->moves[chess_log->actual_size-1]->captured_piece_type = chess_log->moves[log_index]->captured_piece_type;
        castling_rights_flags last_castling_rights = chess_log->moves[chess_log->actual_size-1]->castling_rights;
        chess_log->moves[chess_log->actual_size-1]->castling_rights = chess_log->moves[log_index]->castling_rights;
        // same thing for the bitboards
        bit_board stored_bitboards[NUMBER_OF_BIBOARD]; 
        for (int i=0; i<NUMBER_OF_BIBOARD; i++){
            stored_bitboards[i] = bitboards[i];
        }
        for (int i=0; i<NUMBER_OF_BIBOARD; i++){
            bitboards[i] = bitboards_log->bitboards[log_index][i];
        }

        // at the end we add "+" if it's a check, "#" if it's a checkmate
        int check_state = get_check_state(1-color_playing);
        if (check_state == CHECK){
            sprintf(move_str, "%s+", move_str);
        }
        else if (check_state == CHECK_MATE){
            sprintf(move_str, "%s#", move_str);
        }

        // putting back the last move in the log with the right values
        chess_log->moves[chess_log->actual_size-1]->move_value = last_move;
        chess_log->moves[chess_log->actual_size-1]->captured_piece_type = last_captured_piece_type;
        chess_log->moves[chess_log->actual_size-1]->castling_rights = last_castling_rights;
        // same thing for the bitboards
        for (int i=0; i<NUMBER_OF_BIBOARD; i++){
            bitboards[i] = stored_bitboards[i];
        }

    }

    // adding the move
    add_font_to_render(renderer, move_str, font_size, sdl_color, middle_x, middle_y);
    free(move_str);

}


void show_log(SDL_Renderer* renderer){
    
    // if the pawn promotion is happening then we can't show the log since we need to show the promotion menu
    if (game_settings->is_pawn_promotion_happening == false){

        // the color of the text to display (white)
        SDL_Color color = {230, 230, 230, 255};

        // adding the log name to the board 
        add_font_to_render(renderer, "Log", 50, color, 850+355/2, 50);

        int starting_height = 100;
        // showing the last 20 moves (so 10 complete moves : one complete move is a move from white and a move from black)
        int max_move_shown = min(chess_log->actual_size, 20);
        for (int i=0; i<max_move_shown; i=i+2){
            
            // adding the number of the move on the left of the corresponding move for each player
            char* number_move = malloc(3*sizeof(char));
            if (chess_log->actual_size > 20){
                int delta = 0;
                if (chess_log->actual_size %2 == 1){
                    delta = 1;
                }
                sprintf(number_move, "%d", (chess_log->actual_size-20+i)/2 + 1 + delta);
            }
            else {
                sprintf(number_move, "%d", i/2 + 1);
            }
            add_font_to_render(renderer, number_move, 30, color, 875, starting_height + i*25);
            free(number_move);

            // in this case, we need only the move of the white player to be shown since there is no move from the black player yet
            if (chess_log->actual_size %2 == 1 && ((i == max_move_shown-1 && max_move_shown != 20) || (i == max_move_shown-2 && max_move_shown == 20))){
                // adding the move of the white player
                if (chess_log->actual_size > 20){
                    add_move_in_log_render(renderer, chess_log->actual_size-20+i+1, WHITE, 30, color, 975, starting_height + i*25);
                } 
                else {
                    add_move_in_log_render(renderer, i, WHITE, 30, color, 975, starting_height + i*25);
                }
            }
            else {
                if (chess_log->actual_size > 20){
                    int delta = 0;
                    if (chess_log->actual_size %2 == 1){
                        delta = 1;
                    }
                    // adding the move of the white player
                    add_move_in_log_render(renderer, chess_log->actual_size-20+i+delta, WHITE, 30, color, 975, starting_height + i*25);

                    // adding the move of the black player
                    add_move_in_log_render(renderer, chess_log->actual_size-20+i+1+delta, BLACK, 30, color, 1125, starting_height + i*25);
                }
                else {
                    // adding the move of the white player
                    add_move_in_log_render(renderer, i, WHITE, 30, color, 975, starting_height + i*25);

                    // adding the move of the black player
                    add_move_in_log_render(renderer, i+1, BLACK, 30, color, 1125, starting_height + i*25);
                }
            }

        }
    }

}


void add_move_AI_values(SDL_Renderer* renderer, int log_index, int font_size, SDL_Color sdl_color, int middle_x, int middle_y){
    
    // getting the string we want to display
    char* move_str = malloc(30*sizeof(char));
    sprintf(move_str, "Move : ");

    move move_played = chess_log->moves[log_index]->move_value;
    // first we need to treat special cases before : 
    if (get_flag(move_played) == Castle_Flag){
        // if the castle is a short castle
        if (get_to_square(move_played) == 6 || get_to_square(move_played) == 62){
            sprintf(move_str, "%sO-O", move_str);
        }
        // if the castle is a long castle
        else if (get_to_square(move_played) == 2 || get_to_square(move_played) == 58){
            sprintf(move_str, "%sO-O-O", move_str);
        }
    }
    else {
       
        // if there is a promotion we need to add the piece that the pawn is promoted to by adding "=Q" for a queen, "=R" for a rook, "=B" for a bishop and "=N" for a knight
        // others special rules needs to be applied if there is a capture 
        if (is_promotion_flag(get_flag(move_played))){
            // if there is a capture during the promotion
            if (chess_log->moves[log_index]->captured_piece_type != NOTHING){
                sprintf(move_str, "%s%c", move_str, get_file(get_from_square(move_played)) + 'a');
                sprintf(move_str, "%sx", move_str);
            }

            // adding the square where the piece has been going (the destination square) 
            sprintf(move_str, "%s%c%d", move_str, get_file(get_to_square(move_played)) + 'a', get_rank(get_to_square(move_played)) + 1);

            // adding the piece that the pawn has been promoted to
            int promoted_flag = get_flag(move_played);
            if (promoted_flag == Promote_To_Queen_Flag){
                sprintf(move_str, "%s=Q", move_str);
            }
            else if (promoted_flag == Promote_To_Rook_Flag){
                sprintf(move_str, "%s=R", move_str);
            }
            else if (promoted_flag == Promote_To_Bishop_Flag){
                sprintf(move_str, "%s=B", move_str);
            }
            else if (promoted_flag == Promote_To_Knight_Flag){
                sprintf(move_str, "%s=N", move_str);
            }
        }
        // no promotion, we do the normal thing
        else {
            //  for the different pieces : K=King, Q=Queen, R=Rook, B=Bishop, N=Knight, nothing for pawn
            // since we are adding this log info after a move was played, the piece that we move is the one that is at the destination square
            int piece_moved = get_type_of_piece(bitboards_log->bitboards[log_index], get_to_square(move_played));
            // adding the letter corresponding to the piece moved in the move_str
            switch(piece_moved){
                case PAWN_WHITE:
                    break;
                case KNIGHT_WHITE:
                    sprintf(move_str, "%sN", move_str);
                    break;
                case BISHOP_WHITE:
                    sprintf(move_str, "%sB", move_str);
                    break;
                case ROOK_WHITE:
                    sprintf(move_str, "%sR", move_str);
                    break;
                case QUEEN_WHITE:
                    sprintf(move_str, "%sQ", move_str);
                    break;
                case KING_WHITE:
                    sprintf(move_str, "%sK", move_str);
                    break;
                case PAWN_BLACK:
                    break;
                case KNIGHT_BLACK:
                    sprintf(move_str, "%sN", move_str);
                    break;
                case BISHOP_BLACK:
                    sprintf(move_str, "%sB", move_str);
                    break;
                case ROOK_BLACK:
                    sprintf(move_str, "%sR", move_str);
                    break;
                case QUEEN_BLACK:
                    sprintf(move_str, "%sQ", move_str);
                    break;
                case KING_BLACK:
                    sprintf(move_str, "%sK", move_str);
                    break;
            }

            // if this a capture, we need to add an "x" before, if it's a pawn that is taking, we need to indicate its column before the "x"
            if (chess_log->moves[log_index]->captured_piece_type != NOTHING){
                if (piece_moved == PAWN_WHITE || piece_moved == PAWN_BLACK){
                    sprintf(move_str, "%s%c", move_str, get_file(get_from_square(move_played)) + 'a');
                }
                sprintf(move_str, "%sx", move_str);
            }

            // adding the square where the piece has been going (the destination square) 
            sprintf(move_str, "%s%c%d", move_str, get_file(get_to_square(move_played)) + 'a', get_rank(get_to_square(move_played)) + 1);
        }

        // one parameter is the log (but the function always get the last element, no the one at the i-th move), we need to change the last element of the log to be the one at the i-th move and then putting it back
        move last_move = chess_log->moves[chess_log->actual_size-1]->move_value;
        chess_log->moves[chess_log->actual_size-1]->move_value = chess_log->moves[log_index]->move_value;
        int last_captured_piece_type = chess_log->moves[chess_log->actual_size-1]->captured_piece_type;
        chess_log->moves[chess_log->actual_size-1]->captured_piece_type = chess_log->moves[log_index]->captured_piece_type;
        castling_rights_flags last_castling_rights = chess_log->moves[chess_log->actual_size-1]->castling_rights;
        chess_log->moves[chess_log->actual_size-1]->castling_rights = chess_log->moves[log_index]->castling_rights;
        // same thing for the bitboards
        bit_board stored_bitboards[NUMBER_OF_BIBOARD]; 
        for (int i=0; i<NUMBER_OF_BIBOARD; i++){
            stored_bitboards[i] = bitboards[i];
        }
        for (int i=0; i<NUMBER_OF_BIBOARD; i++){
            bitboards[i] = bitboards_log->bitboards[log_index][i];
        }

        // at the end we add "+" if it's a check, "#" if it's a checkmate
        int color_to_check = WHITE;
        if (game_settings->white_AI_difficulty == LVL7){
            color_to_check = BLACK;
        }
        int check_state = get_check_state(color_to_check);
        if (check_state == CHECK){
            sprintf(move_str, "%s+", move_str);
        }
        else if (check_state == CHECK_MATE){
            sprintf(move_str, "%s#", move_str);
        }

        // putting back the last move in the log with the right values
        chess_log->moves[chess_log->actual_size-1]->move_value = last_move;
        chess_log->moves[chess_log->actual_size-1]->captured_piece_type = last_captured_piece_type;
        chess_log->moves[chess_log->actual_size-1]->castling_rights = last_castling_rights;
        // same thing for the bitboards
        for (int i=0; i<NUMBER_OF_BIBOARD; i++){
            bitboards[i] = stored_bitboards[i];
        }

    }

    // adding the move
    add_font_to_render(renderer, move_str, font_size, sdl_color, middle_x, middle_y);
    free(move_str);

}


void show_AI_values(SDL_Renderer* renderer, move selected_move_lvl7, int selected_score_lvl7, bool is_move_taken_from_book_lvl7, int depth_reached_lvl7){

    if (game_settings->white_AI_difficulty == LVL7 || game_settings->black_AI_difficulty == LVL7){
        // add the font for the AI values
        SDL_Color color = {230, 230, 230, 255};
        add_font_to_render(renderer, "AI Values", 50, color, 850+355/2, 600);

        // adding to what depth the AI has gone
        char* depth_reached = malloc(30*sizeof(char));
        sprintf(depth_reached, "Depth reached : %d", depth_reached_lvl7);
        add_font_to_render(renderer, depth_reached, 30, color, 850+355/2, 650);
        free(depth_reached);

        // adding the move 
        // finding the log index 
        int log_index = 0;
        if (chess_log->actual_size > 0){
            log_index = chess_log->actual_size-1;
        }
        if (((game_settings->color_of_player_that_is_playing == WHITE && game_settings->white_AI_difficulty == LVL7) || (game_settings->color_of_player_that_is_playing == BLACK && game_settings->black_AI_difficulty == LVL7)) && chess_log->actual_size > 1){
            log_index = chess_log->actual_size-2;
        }
        if (log_index > 0){
            add_move_AI_values(renderer, log_index, 30, color, 850+355/2, 700);
        }
        else {
            add_font_to_render(renderer, "Move :", 30, color, 850+355/2, 700);
        }

        if (is_move_taken_from_book_lvl7 == true){
            add_font_to_render(renderer, "Move taken from book", 30, color, 850+355/2, 750);
        }
        else {
            // adding the score
            char* score = malloc(30*sizeof(char));
            sprintf(score, "Eval : %d", selected_score_lvl7);
            add_font_to_render(renderer, score, 30, color, 850+355/2, 750);
            free(score);
        }
    }

}


void show_menu_button_in_game(SDL_Renderer* renderer){

    // display the start buttons
    add_image_to_render("../../Images/Buttons/Start_Button.bmp", renderer, buttons[START_BUTTON_IN_GAME]->rect);

    // display others buttons
    add_image_to_render("../../Images/Buttons/Restart_Button.bmp", renderer, buttons[RESTART_BUTTON_IN_GAME]->rect);
    add_image_to_render("../../Images/Buttons/New_Game_Button.bmp", renderer, buttons[NEW_GAME_BUTTON_IN_GAME]->rect);
    add_image_to_render("../../Images/Buttons/Quit_Button.bmp", renderer, buttons[QUIT_BUTTON_IN_GAME]->rect);

    // display the undo button 
    add_image_to_render("../../Images/Buttons/Undo_Button.bmp", renderer, buttons[UNDO_BUTTON_IN_GAME]->rect);
    
    // display the DL log button
    add_image_to_render("../../Images/Buttons/DL_Log_Button.bmp", renderer, buttons[DL_LOG_IN_GAME_BUTTON]->rect);

    // we then print at the place of the log on the render, the differents buttons concerning the pawn promotion
    if (game_settings->is_pawn_promotion_happening == true){

        // the back ground of the four pieces need to be gray so that we can see them
        SDL_Rect background_rect;
        background_rect.x = 850+divide_by_two(355)-divide_by_two(170)-25;
        background_rect.y = 150;
        background_rect.w = 220;
        background_rect.h = 600;
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255); // grey
        SDL_RenderFillRect(renderer, &background_rect);
        // adding the pawn promotion screen 
        add_image_to_render("../../Images/Buttons/Pawn_Promotion_Button.bmp", renderer, buttons[PAWN_PROMOTION_BUTTON]->rect);

        // if the color of the pawn that is promoted is white
        if (game_settings->color_of_pawn_promotion == WHITE){
            // we print the white pieces
            add_image_to_render("../../Images/PNG_Chess_Game_Pieces/white_queen.png", renderer, buttons[QUEEN_BUTTON]->rect);
            add_image_to_render("../../Images/PNG_Chess_Game_Pieces/white_rook.png", renderer, buttons[ROOK_BUTTON]->rect);
            add_image_to_render("../../Images/PNG_Chess_Game_Pieces/white_bishop.png", renderer, buttons[BISHOP_BUTTON]->rect);
            add_image_to_render("../../Images/PNG_Chess_Game_Pieces/white_knight.png", renderer, buttons[KNIGHT_BUTTON]->rect);
        }
        // if the color of the pawn that is promoted is black
        else if (game_settings->color_of_pawn_promotion == BLACK){
            // we print the black pieces
            add_image_to_render("../../Images/PNG_Chess_Game_Pieces/black_queen.png", renderer, buttons[QUEEN_BUTTON]->rect);
            add_image_to_render("../../Images/PNG_Chess_Game_Pieces/black_rook.png", renderer, buttons[ROOK_BUTTON]->rect);
            add_image_to_render("../../Images/PNG_Chess_Game_Pieces/black_bishop.png", renderer, buttons[BISHOP_BUTTON]->rect);
            add_image_to_render("../../Images/PNG_Chess_Game_Pieces/black_knight.png", renderer, buttons[KNIGHT_BUTTON]->rect);
        }
      
    }

    // concerning the pause button, only in AI vs AI mode
    if (game_settings->game_mode == AI_VS_AI || game_settings->game_mode == PLAYER_VS_AI){
        if (game_settings->is_game_on_pause == true){
            add_image_to_render("../../Images/Buttons/Active_Pause_Button.bmp", renderer, buttons[PAUSE_BUTTON]->rect);
            // showing the rectangle around the selected area
            Draw_the_red_boundary_move_Rect(renderer, buttons[PAUSE_BUTTON]->rect);
        }
        else if (game_settings->is_game_on_pause == false){
            add_image_to_render("../../Images/Buttons/Unactive_Pause_Button.bmp", renderer, buttons[PAUSE_BUTTON]->rect);
        }
    }

    // if a button is selected / active, we show a red boundary around it
    if (buttons[START_BUTTON_IN_GAME]->state == ACTIVE){
        Draw_the_red_boundary_move_Rect(renderer, buttons[START_BUTTON_IN_GAME]->rect);
    }
    else if (buttons[RESTART_BUTTON_IN_GAME]->state == ACTIVE){
        Draw_the_red_boundary_move_Rect(renderer, buttons[RESTART_BUTTON_IN_GAME]->rect);
    }
    else if (buttons[NEW_GAME_BUTTON_IN_GAME]->state == ACTIVE){
        Draw_the_red_boundary_move_Rect(renderer, buttons[NEW_GAME_BUTTON_IN_GAME]->rect);
    }
    else if (buttons[QUIT_BUTTON_IN_GAME]->state == ACTIVE){
        Draw_the_red_boundary_move_Rect(renderer, buttons[QUIT_BUTTON_IN_GAME]->rect);
    }
    else if (buttons[UNDO_BUTTON_IN_GAME]->state == ACTIVE){
        Draw_the_red_boundary_move_Rect(renderer, buttons[UNDO_BUTTON_IN_GAME]->rect);
    }
    else if (buttons[DL_LOG_IN_GAME_BUTTON]->state == ACTIVE){
        Draw_the_red_boundary_move_Rect(renderer, buttons[DL_LOG_IN_GAME_BUTTON]->rect);
    }
    else if (buttons[QUEEN_BUTTON]->state == ACTIVE){
        Draw_the_red_boundary_move_Rect(renderer, buttons[QUEEN_BUTTON]->rect);
    }
    else if (buttons[ROOK_BUTTON]->state == ACTIVE){
        Draw_the_red_boundary_move_Rect(renderer, buttons[ROOK_BUTTON]->rect);
    }
    else if (buttons[BISHOP_BUTTON]->state == ACTIVE){
        Draw_the_red_boundary_move_Rect(renderer, buttons[BISHOP_BUTTON]->rect);
    }
    else if (buttons[KNIGHT_BUTTON]->state == ACTIVE){
        Draw_the_red_boundary_move_Rect(renderer, buttons[KNIGHT_BUTTON]->rect);
    }
    else if (buttons[PAUSE_BUTTON]->state == ACTIVE){
        Draw_the_red_boundary_move_Rect(renderer, buttons[PAUSE_BUTTON]->rect);
    }

}


void show_confirmation_menu(SDL_Renderer* renderer){
    
    applyBlur(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, 15);
    // drawing what's behind the writing
    SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255); // black
    SDL_RenderFillRect(renderer, &buttons[NEXT_BUTTON_VICTORY_MENU]->rect);
    SDL_RenderFillRect(renderer, &buttons[NOT_NEXT_BUTTON_VICTORY_MENU]->rect);
    SDL_Rect updated_rect;
    updated_rect.x = 100;
    updated_rect.w = 1200;
    updated_rect.y = 350;
    updated_rect.h = 120;
    SDL_RenderFillRect(renderer, &updated_rect);
    
    // color of the font (white)
    SDL_Color color = {230, 230, 230, 255};
    // button to validate the choice (next)
    add_font_to_render(renderer, "Yes", 100, color, buttons[NEXT_BUTTON_VICTORY_MENU]->rect.x+divide_by_two(buttons[NEXT_BUTTON_VICTORY_MENU]->rect.w), buttons[NEXT_BUTTON_VICTORY_MENU]->rect.y+divide_by_two(buttons[NEXT_BUTTON_VICTORY_MENU]->rect.h));
    // button to go not validate the choice (not next)
    add_font_to_render(renderer, "No", 100, color, buttons[NOT_NEXT_BUTTON_VICTORY_MENU]->rect.x+divide_by_two(buttons[NOT_NEXT_BUTTON_VICTORY_MENU]->rect.w), buttons[NOT_NEXT_BUTTON_VICTORY_MENU]->rect.y+divide_by_two(buttons[NOT_NEXT_BUTTON_VICTORY_MENU]->rect.h));
    // add text above the buttons to choose the game mode
    add_font_to_render(renderer, "Do you want to continue ?", 100, color, divide_by_two(WINDOW_WIDTH), 400);

}


void show_victory_menu(SDL_Renderer* renderer, bool is_clicked, SDL_Rect draw_red_boundary_move){

    // the color of the text to display (black)
    SDL_Color color = {230, 230, 230, 255};

    // drawing what's behind the writing
    SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255); // black
    SDL_Rect updated_rect;
    updated_rect.x = buttons[QUIT_BUTTON_VICTORY_MENU]->rect.x-25;
    updated_rect.w = buttons[QUIT_BUTTON_VICTORY_MENU]->rect.w+50;
    updated_rect.y = buttons[QUIT_BUTTON_VICTORY_MENU]->rect.y;
    updated_rect.h = buttons[QUIT_BUTTON_VICTORY_MENU]->rect.h;
    SDL_RenderFillRect(renderer, &updated_rect);
    updated_rect.x = buttons[RESTART_BUTTON_VICTORY_MENU]->rect.x-25;
    updated_rect.w = buttons[RESTART_BUTTON_VICTORY_MENU]->rect.w+50;
    updated_rect.y = buttons[RESTART_BUTTON_VICTORY_MENU]->rect.y;
    updated_rect.h = buttons[RESTART_BUTTON_VICTORY_MENU]->rect.h;
    SDL_RenderFillRect(renderer, &updated_rect);
    updated_rect.x = buttons[NEW_GAME_BUTTON_VICTORY_MENU]->rect.x-125;
    updated_rect.w = buttons[NEW_GAME_BUTTON_VICTORY_MENU]->rect.w+250;
    updated_rect.y = buttons[NEW_GAME_BUTTON_VICTORY_MENU]->rect.y;
    updated_rect.h = buttons[NEW_GAME_BUTTON_VICTORY_MENU]->rect.h;
    SDL_RenderFillRect(renderer, &updated_rect);
    updated_rect.x = buttons[UNDO_ENDING_MOVE_BUTTON]->rect.x-25;
    updated_rect.w = buttons[UNDO_ENDING_MOVE_BUTTON]->rect.w+50;
    updated_rect.y = buttons[UNDO_ENDING_MOVE_BUTTON]->rect.y;
    updated_rect.h = buttons[UNDO_ENDING_MOVE_BUTTON]->rect.h;
    if (game_settings->game_mode == AI_VS_AI){
        SDL_RenderFillRect(renderer, &updated_rect);
        updated_rect.x = buttons[PAUSE_BUTTON_VICTORY_MENU]->rect.x-25;
        updated_rect.w = buttons[PAUSE_BUTTON_VICTORY_MENU]->rect.w+50;
        updated_rect.y = buttons[PAUSE_BUTTON_VICTORY_MENU]->rect.y;
        updated_rect.h = buttons[PAUSE_BUTTON_VICTORY_MENU]->rect.h;
    }
    SDL_RenderFillRect(renderer, &updated_rect);
    updated_rect.x = buttons[DL_LOG_VICTORY_MENU_BUTTON]->rect.x-25;
    updated_rect.w = buttons[DL_LOG_VICTORY_MENU_BUTTON]->rect.w+50;
    updated_rect.y = buttons[DL_LOG_VICTORY_MENU_BUTTON]->rect.y;
    updated_rect.h = buttons[DL_LOG_VICTORY_MENU_BUTTON]->rect.h;
    SDL_RenderFillRect(renderer, &updated_rect);

    // buttons to quit the game
    add_font_to_render(renderer, "Quit", 100, color, buttons[QUIT_BUTTON_VICTORY_MENU]->rect.x+divide_by_two(buttons[QUIT_BUTTON_VICTORY_MENU]->rect.w), buttons[QUIT_BUTTON_VICTORY_MENU]->rect.y+divide_by_two(buttons[QUIT_BUTTON_VICTORY_MENU]->rect.h));
    // buttons to restart the game
    add_font_to_render(renderer, "Restart", 100, color, buttons[RESTART_BUTTON_VICTORY_MENU]->rect.x+divide_by_two(buttons[RESTART_BUTTON_VICTORY_MENU]->rect.w), buttons[RESTART_BUTTON_VICTORY_MENU]->rect.y+divide_by_two(buttons[RESTART_BUTTON_VICTORY_MENU]->rect.h));
    // buttons to start a new game
    add_font_to_render(renderer, "New_Game", 100, color, buttons[NEW_GAME_BUTTON_VICTORY_MENU]->rect.x+divide_by_two(buttons[NEW_GAME_BUTTON_VICTORY_MENU]->rect.w), buttons[NEW_GAME_BUTTON_VICTORY_MENU]->rect.y+divide_by_two(buttons[NEW_GAME_BUTTON_VICTORY_MENU]->rect.h));
    // buttons to undo the last move
    add_font_to_render(renderer, "Undo", 100, color, buttons[UNDO_ENDING_MOVE_BUTTON]->rect.x+divide_by_two(buttons[UNDO_ENDING_MOVE_BUTTON]->rect.w), buttons[UNDO_ENDING_MOVE_BUTTON]->rect.y+divide_by_two(buttons[UNDO_ENDING_MOVE_BUTTON]->rect.h));
    if (game_settings->game_mode == AI_VS_AI){
        // buttons to pause the game
        add_font_to_render(renderer, "Pause", 100, color, buttons[PAUSE_BUTTON_VICTORY_MENU]->rect.x+divide_by_two(buttons[PAUSE_BUTTON_VICTORY_MENU]->rect.w), buttons[PAUSE_BUTTON_VICTORY_MENU]->rect.y+divide_by_two(buttons[PAUSE_BUTTON_VICTORY_MENU]->rect.h));
    }
    // buttons to download the game log
    add_font_to_render(renderer, "DL_Log", 100, color, buttons[DL_LOG_VICTORY_MENU_BUTTON]->rect.x+divide_by_two(buttons[DL_LOG_VICTORY_MENU_BUTTON]->rect.w), buttons[DL_LOG_VICTORY_MENU_BUTTON]->rect.y+divide_by_two(buttons[DL_LOG_VICTORY_MENU_BUTTON]->rect.h));
    // add text above the buttons to choose what to do next
    SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255); // black
    updated_rect.x = divide_by_two(WINDOW_WIDTH) - 350;
    updated_rect.w = 700;
    updated_rect.y = 0;
    updated_rect.h = 100;
    SDL_RenderFillRect(renderer, &updated_rect);
    add_font_to_render(renderer, "What's next ?", 100, color, divide_by_two(WINDOW_WIDTH), 50);

    // now showing different things depending on which player has lost the game in a certain game mode
    // first if there is a draw made by the 3 rules (3 boards were the same)
    if (game_settings->loosing_player == Draw_by_3_rules){
            
            SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255); // black
            updated_rect.x = 50;
            updated_rect.w = WINDOW_WIDTH - 100;
            updated_rect.y = divide_by_two(WINDOW_HEIGHT) - 50;
            updated_rect.h = 220;
            SDL_RenderFillRect(renderer, &updated_rect);
            add_font_to_render(renderer, "Draw", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT));
            add_font_to_render(renderer, "3 boards were the same", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT) + 100);
    
    }
    // then if there is a draw by the 50 rules (50 moves without any pawn move or capture)
    else if (game_settings->loosing_player == Draw_by_50_rules){
            
            SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255); // black
            updated_rect.x = 50;
            updated_rect.w = WINDOW_WIDTH - 100;
            updated_rect.y = divide_by_two(WINDOW_HEIGHT) - 50;
            updated_rect.h = 220;
            SDL_RenderFillRect(renderer, &updated_rect);
            add_font_to_render(renderer, "Draw", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT));
            add_font_to_render(renderer, "50 moves without any pawn move or capture", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT) + 100);
    
    }
    // and if there is a stalemate (no check but no moves possibles)
    else if (game_settings->loosing_player == Draw_by_stalemate){
            
            SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255); // black
            updated_rect.x = 200;
            updated_rect.w = 1000;
            updated_rect.y = divide_by_two(WINDOW_HEIGHT) - 50;
            updated_rect.h = 220;
            SDL_RenderFillRect(renderer, &updated_rect);
            add_font_to_render(renderer, "Draw", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT));
            add_font_to_render(renderer, "Stalemate", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT) + 100);

    }
    // and if there is a draw because of insuffisent material
    else if (game_settings->loosing_player == Draw_by_insufficient_material){
            
            SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255); // black
            updated_rect.x = 150;
            updated_rect.w = WINDOW_WIDTH - 300;
            updated_rect.y = divide_by_two(WINDOW_HEIGHT) - 50;
            updated_rect.h = 220;
            SDL_RenderFillRect(renderer, &updated_rect);
            add_font_to_render(renderer, "Draw", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT));
            add_font_to_render(renderer, "Insufficient material", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT) + 100);

    }
    // for a player vs player game
    else if (game_settings->game_mode == PLAYER_VS_PLAYER){
        // if the game is lost due to a time defeat 
        if (game_settings->is_game_lost_on_time){
            
            SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255); // black
            updated_rect.x = 200;
            updated_rect.w = 1000;
            updated_rect.y = divide_by_two(WINDOW_HEIGHT) - 50 - 110;
            updated_rect.h = 110;
            SDL_RenderFillRect(renderer, &updated_rect);
            add_font_to_render(renderer, "Time Defeat", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT) - 110);

        }
        // if the white player has lost
        if (game_settings->loosing_player == White_Player){
            
            SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255); // black
            updated_rect.x = 200;
            updated_rect.w = 1000;
            updated_rect.y = divide_by_two(WINDOW_HEIGHT) - 50;
            updated_rect.h = 220;
            SDL_RenderFillRect(renderer, &updated_rect);
            add_font_to_render(renderer, "White player has lost", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT));
            add_font_to_render(renderer, "Black player has won", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT) + 100);

        }
        // if the black player has lost
        else if (game_settings->loosing_player == Black_Player){
            
            SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255); // black
            updated_rect.x = 200;
            updated_rect.w = 1000;
            updated_rect.y = divide_by_two(WINDOW_HEIGHT) - 50;
            updated_rect.h = 220;
            SDL_RenderFillRect(renderer, &updated_rect);
            add_font_to_render(renderer, "Black player has lost", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT));
            add_font_to_render(renderer, "White player has won", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT) + 100);

        }
    }
    // for a player vs AI game
    else if (game_settings->game_mode == PLAYER_VS_AI){
        // if the game is lost due to a time defeat 
        if (game_settings->is_game_lost_on_time){
            
            SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255); // black
            updated_rect.x = 200;
            updated_rect.w = 1000;
            updated_rect.y = divide_by_two(WINDOW_HEIGHT) - 50 - 110;
            updated_rect.h = 110;
            SDL_RenderFillRect(renderer, &updated_rect);
            add_font_to_render(renderer, "Time Defeat", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT) - 110);

        }
        // if the human player has lost
        if ((game_settings->loosing_player == White_Player && game_settings->white_player_type == HUMAN) || (game_settings->loosing_player == Black_Player && game_settings->black_player_type == HUMAN)){
            // picture to say that you lose 
            SDL_Rect rectangle_for_the_image_to_go_to;
            rectangle_for_the_image_to_go_to.x = divide_by_two(WINDOW_WIDTH) - 300;
            rectangle_for_the_image_to_go_to.y = divide_by_two(WINDOW_HEIGHT) - 200 + 50;
            rectangle_for_the_image_to_go_to.w = 600;
            rectangle_for_the_image_to_go_to.h = 400;
            add_image_to_render("../../Images/Buttons/defeat.jpg", renderer, rectangle_for_the_image_to_go_to);
        }
        // if the AI player has lost
        else if ((game_settings->loosing_player == White_Player && game_settings->white_player_type == AI) || (game_settings->loosing_player == Black_Player && game_settings->black_player_type == AI)){
            // picture to say that you win
            SDL_Rect rectangle_for_the_image_to_go_to;
            rectangle_for_the_image_to_go_to.x = divide_by_two(WINDOW_WIDTH) - 300;
            rectangle_for_the_image_to_go_to.y = divide_by_two(WINDOW_HEIGHT) - 200 + 50;
            rectangle_for_the_image_to_go_to.w = 600;
            rectangle_for_the_image_to_go_to.h = 400;
            add_image_to_render("../../Images/Buttons/victory.jpg", renderer, rectangle_for_the_image_to_go_to);
        }
    }
    // for an AI vs AI game
    else if (game_settings->game_mode == AI_VS_AI){
        // if the game is lost due to a time defeat 
        if (game_settings->is_game_lost_on_time){
            
            SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255); // black
            updated_rect.x = 200;
            updated_rect.w = 1000;
            updated_rect.y = divide_by_two(WINDOW_HEIGHT) - 50 - 110;
            updated_rect.h = 110;
            SDL_RenderFillRect(renderer, &updated_rect);
            add_font_to_render(renderer, "Time Defeat", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT) - 110);

        }
        // if the white AI has lost
        if (game_settings->loosing_player == White_Player){
            
            SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255); // black
            updated_rect.x = 100;
            updated_rect.w = 1200;
            updated_rect.y = divide_by_two(WINDOW_HEIGHT) - 50;
            updated_rect.h = 220;
            SDL_RenderFillRect(renderer, &updated_rect);
            if (game_settings->white_AI_difficulty == LVL1){
                add_font_to_render(renderer, "LVL1 White AI has lost", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT));
            }
            else if (game_settings->white_AI_difficulty == LVL2){
                add_font_to_render(renderer, "LVL2 White AI has lost", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT));
            }
            else if (game_settings->white_AI_difficulty == LVL3){
                add_font_to_render(renderer, "LVL3 White AI has lost", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT));
            }
            else if (game_settings->white_AI_difficulty == LVL4){
                add_font_to_render(renderer, "LVL4 White AI has lost", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT));
            }
            else if (game_settings->white_AI_difficulty == LVL5){
                add_font_to_render(renderer, "LVL5 White AI has lost", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT));
            }
            else if (game_settings->white_AI_difficulty == LVL6){
                add_font_to_render(renderer, "LVL6 White AI has lost", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT));
            }
            else if (game_settings->white_AI_difficulty == LVL7){
                add_font_to_render(renderer, "LVL7 White AI has lost", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT));
            }
            if (game_settings->black_AI_difficulty == LVL1){
                add_font_to_render(renderer, "LVL1 Black AI has won", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT) + 100);
            }
            else if (game_settings->black_AI_difficulty == LVL2){
                add_font_to_render(renderer, "LVL2 Black AI has won", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT) + 100);
            }
            else if (game_settings->black_AI_difficulty == LVL3){
                add_font_to_render(renderer, "LVL3 Black AI has won", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT) + 100);
            }
            else if (game_settings->black_AI_difficulty == LVL4){
                add_font_to_render(renderer, "LVL4 Black AI has won", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT) + 100);
            }
            else if (game_settings->black_AI_difficulty == LVL5){
                add_font_to_render(renderer, "LVL5 Black AI has won", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT) + 100);
            }
            else if (game_settings->black_AI_difficulty == LVL6){
                add_font_to_render(renderer, "LVL6 Black AI has won", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT) + 100);
            }
            else if (game_settings->black_AI_difficulty == LVL7){
                add_font_to_render(renderer, "LVL7 Black AI has won", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT) + 100);
            }

        }
        // if the black AI has lost
        else if (game_settings->loosing_player == Black_Player){

            SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255); // black
            updated_rect.x = 200;
            updated_rect.w = 1000;
            updated_rect.y = divide_by_two(WINDOW_HEIGHT) - 50;
            updated_rect.h = 220;
            SDL_RenderFillRect(renderer, &updated_rect);
            if (game_settings->black_AI_difficulty == LVL1){
                add_font_to_render(renderer, "LVL1 Black AI has lost", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT));
            }
            else if (game_settings->black_AI_difficulty == LVL2){
                add_font_to_render(renderer, "LVL2 Black AI has lost", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT));
            }
            else if (game_settings->black_AI_difficulty == LVL3){
                add_font_to_render(renderer, "LVL3 Black AI has lost", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT));
            }
            else if (game_settings->black_AI_difficulty == LVL4){
                add_font_to_render(renderer, "LVL4 Black AI has lost", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT));
            }
            else if (game_settings->black_AI_difficulty == LVL5){
                add_font_to_render(renderer, "LVL5 Black AI has lost", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT));
            }
            else if (game_settings->black_AI_difficulty == LVL6){
                add_font_to_render(renderer, "LVL6 Black AI has lost", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT));
            }
            else if (game_settings->black_AI_difficulty == LVL7){
                add_font_to_render(renderer, "LVL7 Black AI has lost", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT));
            }
            if (game_settings->white_AI_difficulty == LVL1){
                add_font_to_render(renderer, "LVL1 White AI has won", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT) + 100);
            }
            else if (game_settings->white_AI_difficulty == LVL2){
                add_font_to_render(renderer, "LVL2 White AI has won", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT) + 100);
            }
            else if (game_settings->white_AI_difficulty == LVL3){
                add_font_to_render(renderer, "LVL3 White AI has won", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT) + 100);
            }
            else if (game_settings->white_AI_difficulty == LVL4){
                add_font_to_render(renderer, "LVL4 White AI has won", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT) + 100);
            }
            else if (game_settings->white_AI_difficulty == LVL5){
                add_font_to_render(renderer, "LVL5 White AI has won", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT) + 100);
            }
            else if (game_settings->white_AI_difficulty == LVL6){
                add_font_to_render(renderer, "LVL6 White AI has won", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT) + 100);
            }
            else if (game_settings->white_AI_difficulty == LVL7){
                add_font_to_render(renderer, "LVL7 White AI has won", 100, color, divide_by_two(WINDOW_WIDTH), divide_by_two(WINDOW_HEIGHT) + 100);
            }

        }
    }

    if (is_clicked == true){

        // showing the rectangle around the selected area
        Draw_the_red_boundary_move_Rect(renderer, draw_red_boundary_move);
        // apply a blur for all precedent things before this screen
        int blur_level_victory_menu = 15;
        applyBlur(renderer, WINDOW_WIDTH, WINDOW_HEIGHT, blur_level_victory_menu);

        // drawing what's behind the writing
        SDL_SetRenderDrawColor(renderer, 25, 25, 25, 255); // black
        SDL_RenderFillRect(renderer, &buttons[NEXT_BUTTON_VICTORY_MENU]->rect);
        SDL_RenderFillRect(renderer, &buttons[NOT_NEXT_BUTTON_VICTORY_MENU]->rect);
        updated_rect.x = 100;
        updated_rect.w = 1200;
        updated_rect.y = 350;
        updated_rect.h = 120;
        SDL_RenderFillRect(renderer, &updated_rect);
        
        // button to validate the choice (next)
        add_font_to_render(renderer, "Yes", 100, color, buttons[NEXT_BUTTON_VICTORY_MENU]->rect.x+divide_by_two(buttons[NEXT_BUTTON_VICTORY_MENU]->rect.w), buttons[NEXT_BUTTON_VICTORY_MENU]->rect.y+divide_by_two(buttons[NEXT_BUTTON_VICTORY_MENU]->rect.h));
        // button to go not validate the choice (not next)
        add_font_to_render(renderer, "No", 100, color, buttons[NOT_NEXT_BUTTON_VICTORY_MENU]->rect.x+divide_by_two(buttons[NOT_NEXT_BUTTON_VICTORY_MENU]->rect.w), buttons[NOT_NEXT_BUTTON_VICTORY_MENU]->rect.y+divide_by_two(buttons[NOT_NEXT_BUTTON_VICTORY_MENU]->rect.h));
        // add text above the buttons to choose the game mode
        add_font_to_render(renderer, "Do you want to continue ?", 100, color, divide_by_two(WINDOW_WIDTH), 400);

    }

}
