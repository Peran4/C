#include <stdio.h>
#include <stdlib.h>
#include "board.h"

int main() {
    int w,h;
    printf("Enter width and height of the board: ");
    if(scanf("%d %d",&w,&h) != 2) {
        printf("Incorrect input");
        return 1;
    }
    if(h <= 0 || w <= 0) {
        printf("Incorrect input data");
        return 2;
    }
    struct board_t *board;
    int ret = create_board(&board,w,h);
    if(ret) {
        printf("Failed to allocate memory");
        return 8;
    }
    int x,y;
    printf("Enter player's initial coordinates (x, y):");
    if(scanf("%d %d",&x,&y) != 2) {
        free_board(board);
        printf("Incorrect input");
        return 1;
    }
    while(getchar()!='\n');
    if(x < 0 || y < 0 || x >= board->width || y >= board->height) {
        free_board(board);
        printf("Incorrect input data");
        return 2;
    }
    if(set_player(board,x,y)) {
        free_board(board);
        printf("Incorrect input data");
        return 2;
    }
    display_board(board);
    char choice;
    while(1) {
        printf("Choose your action: ");
        if(!scanf("%c",&choice)) {
            free_board(board);
            printf("Incorrect input");
            return 1;
        }
        if(choice == 'w') {
            board = board->move_player_up(board);
            display_board(board);
        }
        else if(choice == 's') {
            board = board->move_player_down(board);
            display_board(board);
        }
        else if(choice == 'a') {
            board = board->move_player_left(board);
            display_board(board);
        }
        else if(choice == 'd') {
            board = board->move_player_right(board);
            display_board(board);
        }
        else if(choice == 'q') {
            free_board(board);
            return 0;
        }
        else {
            printf("Incorrect choice\n");
        }
        while(getchar() != '\n');
    }
    return 0;
}
