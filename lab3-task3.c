#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define SQUAD_SIZE 20
#define NUM_TEAMS 10
#define MAX_NAME_LENGTH 25
#define MAX_CLUB_LENGTH 20
#define MAX_POSITION_LENGTH 15

typedef struct {
    char name[MAX_NAME_LENGTH];
    int kit_number;
    char club[MAX_CLUB_LENGTH];
    int day, month, year;
    char position[MAX_POSITION_LENGTH];
} player_t;

typedef struct {
    char name[MAX_CLUB_LENGTH];
    player_t players[SQUAD_SIZE];
    int activeSize;
} team_t;
