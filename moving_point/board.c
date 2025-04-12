#include <stdio.h>
#include <stdlib.h>
#include "board.h"

void set(char **ptr, int h, int w, char value) {
    *(*(ptr+h)+w) = value;
}

int create_board(struct board_t **board, int width,int height) {
    if(board == NULL || width <= 0 || height <= 0) {
        return 1;
    }
    *board = malloc(sizeof(struct board_t));
    if(*board == NULL) {
        return 2;
    }

    (*board)->board = (char **)malloc(sizeof(char *) * height);
    if((*board)->board == NULL) {
        free(*board);
        return 2;
    }
    for(int i=0; i<height; i++) {
        *((*board)->board+i) = (char *)malloc(sizeof(char) * (width+1));
        if(*((*board)->board+i) == NULL) {
            for(int j=0; j<i; j++) {
                free(*((*board)->board+j));
            }
            free((*board)->board);
            free(*board);
            return 2;
        }
    }

    for(int i=0; i<height; i++) {
        for(int j=0; j<width; j++) {
            set((*board)->board,i,j,'.');
        }
    }
    for(int i=0; i<height; i++) {
        set((*board)->board,i,width,'\0');
    }
    (*board)->width = width;
    (*board)->height = height;
    (*board)->move_player_up = move_player_up;
    (*board)->move_player_down = move_player_down;
    (*board)->move_player_right = move_player_right;
    (*board)->move_player_left = move_player_left;
    (*board)->is_init = 0;
    return 0;
}

void display_board(const struct board_t *board) {
    if(board == NULL || board->height <= 0 || board->width <= 0 || board->board == NULL) {
        return;
    }
    for(int i=0; i<board->height; i++) {
        printf("%s\n",*(board->board+i));
    }
}

void free_board(struct board_t *board) {
    if(board == NULL || board->height <= 0 || board->board == NULL) {
        return;
    }
    for(int i=0; i<board->height; i++) {
        free(*(board->board + i));
    }
    free(board->board);
    free(board);
}

int set_player(struct board_t *board, int x, int y) {
    if(board == NULL || board->board == NULL || y >= board->height || x >= board->width || y < 0 || x < 0 || board->is_init) {
        return 1;
    }
    board->player.x = x;
    board->player.y = y;
    board->is_init = 1;
    set(board->board,y,x,'@');
    return 0;
}

struct board_t* move_player_up(struct board_t* board) {
    if(board == NULL || board->board == NULL || board->height <= 0 || board->width <= 0 || !board->is_init || board->player.x >= board->width || board->player.y >= board->height || board->player.x < 0 || board->player.y < 0) {
        return NULL;
    }
    int x = board->player.x;
    int y = board->player.y;
    if(board->player.y-1 < 0) {
        set(board->board,y,x,'.');
        set(board->board,board->height-1,x,'@');
        board->player.y = board->height-1;
        return board;
    }

    set(board->board,y,x,'.');
    set(board->board,y-1,x,'@');
    board->player.y -= 1;
    return board;
}

struct board_t* move_player_down(struct board_t* board) {
    if(board == NULL || board->board == NULL || board->height <= 0 || board->width <= 0 || !board->is_init || board->player.x >= board->width || board->player.y >= board->height || board->player.x < 0 || board->player.y < 0) {
        return NULL;
    }
    int x = board->player.x;
    int y = board->player.y;
    if(board->player.y+1 >= board->height) {
        set(board->board,y,x,'.');
        set(board->board,0,x,'@');
        board->player.y = 0;
        return board;
    }
    set(board->board,y,x,'.');
    set(board->board,y+1,x,'@');
    board->player.y += 1;
    return board;
}

struct board_t* move_player_left(struct board_t* board) {
    if(board == NULL || board->board == NULL || board->height <= 0 || board->width <= 0 || !board->is_init || board->player.x >= board->width || board->player.y >= board->height || board->player.x < 0 || board->player.y < 0) {
        return NULL;
    }
    int x = board->player.x;
    int y = board->player.y;
    if(board->player.x-1 < 0) {
        set(board->board,y,x,'.');
        set(board->board,y,board->width-1,'@');
        board->player.x = board->width-1;
        return board;
    }
    set(board->board,y,x,'.');
    set(board->board,y,x-1,'@');
    board->player.x -= 1;
    return board;
}

struct board_t* move_player_right(struct board_t* board) {
    if(board == NULL || board->board == NULL || board->height <= 0 || board->width <= 0 || !board->is_init || board->player.x >= board->width || board->player.y >= board->height || board->player.x < 0 || board->player.y < 0) {
        return NULL;
    }
    int x = board->player.x;
    int y = board->player.y;
    if(board->player.x+1 >= board->width) {
        set(board->board,y,x,'.');
        set(board->board,y,0,'@');
        board->player.x = 0;
        return board;
    }
    set(board->board,y,x,'.');
    set(board->board,y,x+1,'@');
    board->player.x += 1;
    return board;
}

