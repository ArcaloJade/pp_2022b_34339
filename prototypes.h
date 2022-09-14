// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <unistd.h>

// Defines
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_RESET   "\x1b[0m"

// Base values
float MAX_HP = 10.0;
float BASE_DMG = 1.0;
const int TYPE_QUANTITY = 3;
char * red = "255 0 0";
char * green = "0 255 0";
char * blue = "0 0 255";
char * white = "255 255 255";

// Extras
struct Pokemon
{
    int type;
    float hp;
    float dmg;
};

enum pokemon_type
{
    FIRE,
    WATER,
    GRASS,
};

// Prototypes
void help(void);
struct Pokemon ** initialize_matrix(unsigned int, unsigned int);
void free_matrix(struct Pokemon **, unsigned int);
unsigned int get_width(void);
unsigned int get_height(void);
unsigned int get_seed(void);
int get_interval(void);
unsigned int get_turns(void);
enum pokemon_type random_type(void);
void attack(struct Pokemon *, struct Pokemon *);
void play_turn(struct Pokemon **, unsigned int, unsigned int);
void print_ppm(struct Pokemon **, unsigned int, unsigned int);