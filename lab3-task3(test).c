#include <stdio.h>         // Include the standard input/output library
#include <string.h>        // Include string manipulation functions
#include <ctype.h>         // Include character handling functions
#include <stdbool.h>       // Include boolean type (true/false)
#include <time.h>          // Include time library for dynamic date handling

// Constants for squad size, number of teams, and max lengths for names, clubs, and positions
#define SQUAD_SIZE 20
#define NUM_TEAMS 10
#define MAX_NAME_LENGTH 25
#define MAX_CLUB_LENGTH 20
#define MAX_POSITION_LENGTH 15

// Struct definition for a player
typedef struct {
    char name[MAX_NAME_LENGTH];      // Player's name
    int kit_number;                  // Player's kit number
    char club[MAX_CLUB_LENGTH];      // Club the player belongs to
    int day, month, year;            // Date of birth (DD MM YYYY)
    char position[MAX_POSITION_LENGTH]; // Position of the player (e.g., Forward, Defender)
} player_t;

// Struct definition for a team
typedef struct {
    char name[MAX_CLUB_LENGTH];      // Team's name
    player_t players[SQUAD_SIZE];    // Array of players in the team
    int activeSize;                  // Number of players currently in the team
} team_t;

// Global array to store teams and track the number of enrolled teams
team_t teams[NUM_TEAMS];
int enrolled_teams = 0;             // Counter for the number of enrolled teams

// Function prototypes for various operations
void display_menu();
void enroll_club();
void add_player();
void search_update();
void display_club_statistics();
void handle_error(const char *message);
bool duplicate_kit_or_name(team_t *team, int kit_number, const char *name);
int calculate_age(int day, int month, int year);

int main() {
    int choice;

    // Main loop to continuously display the menu and process user inputs
    while (1) {
        display_menu();  // Display the main menu
        printf("Enter your choice: ");
        scanf("%d", &choice);  // Read user's menu choice

        // Switch statement to handle different menu options
        switch (choice) {
            case 1: enroll_club(); break;       // Option 1: Enroll a new club
            case 2: add_player(); break;        // Option 2: Add a new player
            case 3: search_update(); break;     // Option 3: Search and update player details
            case 4: display_club_statistics(); break; // Option 4: Display club statistics
            default:                           // Any other choice: Exit the program
                printf("Exiting program. Goodbye!\n");
                return 0;
        }
    }
    return 0;
}

// Function to display the main menu
void display_menu() {
    printf("\n--- League Team Application ---\n");
    printf("1. Enroll Club\n");
    printf("2. Add Player\n");
    printf("3. Search and Update Player\n");
    printf("4. Display Club Statistics\n");
    printf("Any other number to exit\n");
}

// Function to enroll a new club
void enroll_club() {
    // Check if the maximum number of teams has been reached
    if (enrolled_teams >= NUM_TEAMS) {
        handle_error("Maximum number of teams reached.");
        return;
    }

    // Prompt user to enter club name
    printf("Enter club name: ");
    scanf(" %[^\n]%*c", teams[enrolled_teams].name);  // Read club name with spaces

    // Initialize the new club's player list
    teams[enrolled_teams].activeSize = 0;
    enrolled_teams++;  // Increment the enrolled teams counter
    printf("Club enrolled successfully.\n");
}

// Function to add a player to a club
void add_player() {
    // Check if any clubs have been enrolled yet
    if (enrolled_teams == 0) {
        handle_error("No clubs enrolled yet.");
        return;
    }

    // Display the list of enrolled clubs
    printf("Select a club to add a player:\n");
    for (int i = 0; i < enrolled_teams; i++) {
        printf("%d. %s\n", i + 1, teams[i].name);  // Display club index and name
    }

    int club_choice;
    printf("Enter club number: ");
    scanf("%d", &club_choice);  // Read club choice (1-based index)
    club_choice--;  // Convert to 0-based index

    // Validate club selection
    if (club_choice < 0 || club_choice >= enrolled_teams) {
        handle_error("Invalid club selection.");
        return;
    }

    team_t *team = &teams[club_choice];  // Pointer to the selected team

    // Check if the team has reached the maximum squad size
    if (team->activeSize >= SQUAD_SIZE) {
        handle_error("Squad is full.");
        return;
    }

    player_t new_player;  // Declare a new player

    // Input player details
    printf("Enter player name: ");
    scanf(" %[^\n]%*c", new_player.name);  // Read player name with spaces

    printf("Enter kit number (1-99): ");
    scanf("%d", &new_player.kit_number);  // Read player's kit number

    printf("Enter date of birth (DD MM YYYY): ");
    scanf("%d %d %d", &new_player.day, &new_player.month, &new_player.year);  // Read birthdate

    printf("Enter position: ");
    scanf(" %[^\n]%*c", new_player.position);  // Read player position (e.g., Forward)

    // Check for duplicate player name or kit number in the team
    if (duplicate_kit_or_name(team, new_player.kit_number, new_player.name)) {
        handle_error("Duplicate player name or kit number.");
        return;
    }

    // Add the new player to the team's roster
    team->players[team->activeSize++] = new_player;
    printf("Player added successfully.\n");
}

// Function to search and update a player's details by name or kit number
void search_update() {
    // Check if any clubs have been enrolled yet
    if (enrolled_teams == 0) {
        handle_error("No clubs enrolled yet.");
        return;
    }

    char search_name[MAX_NAME_LENGTH];  // Variable to store the name of the player being searched
    int search_kit;                     // Variable to store the kit number of the player being searched

    // Prompt user for search parameters
    printf("Enter player name to search: ");
    scanf(" %[^\n]%*c", search_name);  // Read search name with spaces

    printf("Enter kit number to search: ");
    scanf("%d", &search_kit);  // Read search kit number

    // Search for the player in all enrolled teams
    for (int i = 0; i < enrolled_teams; i++) {
        team_t *team = &teams[i];
        for (int j = 0; j < team->activeSize; j++) {
            player_t *player = &team->players[j];

            // If player is found by name or kit number, display their details
            if (strcasecmp(player->name, search_name) == 0 || player->kit_number == search_kit) {
                printf("Player found in club %s:\n", team->name);
                printf("Name: %s, Kit: %d, DOB: %02d/%02d/%04d, Position: %s\n",
                       player->name, player->kit_number, player->day, player->month, player->year, player->position);

                // Allow user to update the player's position
                printf("Enter new position: ");
                scanf(" %[^\n]%*c", player->position);  // Update player position
                printf("Player details updated.\n");
                return;
            }
        }
    }

    // If player is not found, display an error
    handle_error("Player not found.");
}

// Function to display statistics for all enrolled clubs
void display_club_statistics() {
    // Check if any clubs have been enrolled yet
    if (enrolled_teams == 0) {
        handle_error("No clubs enrolled yet.");
        return;
    }

    // Display statistics for each club
    for (int i = 0; i < enrolled_teams; i++) {
        team_t *team = &teams[i];
        printf("Club: %s\n", team->name);
        printf("Total players: %d\n", team->activeSize);

        int total_age = 0;  // Variable to accumulate total age of players
        // Loop through all players in the team
        for (int j = 0; j < team->activeSize; j++) {
            player_t *player = &team->players[j];
            int age = calculate_age(player->day, player->month, player->year);  // Calculate player's age
            total_age += age;  // Add player's age to the total
            printf("Name: %s, Kit: %d, Age: %d, Position: %s\n",
                   player->name, player->kit_number, age, player->position);
        }

        // If the team has players, display the average age
        if (team->activeSize > 0) {
            printf("Average age: %.2f\n", (float)total_age / team->activeSize);
        }
        printf("\n");
    }
}

// Function to handle error messages
void handle_error(const char *message) {
    printf("Error: %s\n", message);
}

// Function to check for duplicate kit number or player name in a team
bool duplicate_kit_or_name(team_t *team, int kit_number, const char *name) {
    for (int i = 0; i < team->activeSize; i++) {
        // Check if the kit number or player name already exists
        if (team->players[i].kit_number == kit_number || strcasecmp(team->players[i].name, name) == 0) {
            return true;  // Duplicate found
        }
    }
    return false;  // No duplicates
}

// Function to calculate the age of a player based on their date of birth
int calculate_age(int day, int month, int year) {
    // Get the current date
    time_t t = time(NULL);
    struct tm current_time = *localtime(&t);
    int current_year = current_time.tm_year + 1900;  // Get the current year
    int current_month = current_time.tm_mon + 1;    // Get the current month
    int current_day = current_time.tm_mday;          // Get the current day

    // Calculate age
    int age = current_year - year;
    if (month > current_month || (month == current_month && day > current_day)) {
        age--;  // Decrease age if birthday hasn't occurred yet this year
    }
    return age;  // Return the calculated age
}
