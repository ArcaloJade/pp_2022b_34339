#include "prototypes.h"

void help(void)
{
    // Displays the flags and what they do, as well as an explanation about how the game works.
    printf(COLOR_GREEN "\nFLAGS:\n");
    printf(COLOR_YELLOW "   -h " COLOR_RESET ">> Displays a list with all flags and instructions on how the program works. Terminates the program after being called.\n");
    printf(COLOR_YELLOW "   -w " COLOR_RESET ">> Asks the user to indicate the width of the desired matrix. Must be an unsigned int higher than 0. DEFAULT: 5.\n");
    printf(COLOR_YELLOW "   -H " COLOR_RESET ">> Asks the user to indicate the height of the desired matrix. Must be an unsigned int higher than 0. DEFAULT: 5.\n");
    printf(COLOR_YELLOW "   -s " COLOR_RESET ">> Asks the user to indicate the seed of the randomly generated matrix. Must be an unsigned int equal to or higher than 0. DEFAULT: 0.\n");
    printf(COLOR_YELLOW "   -n " COLOR_RESET ">> Indicates the printing interval the user wants for the PPM image. Must be an int. If this value is <= 0, only the last generated image will be printed. DEFAULT: 1.\n");
    printf(COLOR_YELLOW "   -t " COLOR_RESET ">> Asks the user to indicate the amount of turns that will be played. Must be equal to or higher than 0, as well as >= n. DEFAULT: 1.\n");
    printf(COLOR_GREEN "\nGAME INSTRUCTIONS:\n" COLOR_RESET);
    printf("    -   Each square in the PPM image represents a " COLOR_YELLOW "Pokemon.\n" COLOR_RESET);
    printf("    -   There are three types of Pokemon: " COLOR_RED "FIRE" COLOR_RESET ", " COLOR_BLUE "WATER" COLOR_RESET " and " COLOR_GREEN "GRASS" COLOR_RESET ".\n");
    printf("    -   Each element has a " COLOR_YELLOW "weakness" COLOR_RESET ": FIRE deals higher damage to GRASS, GRASS to WATER, and WATER to FIRE.\n");
    printf("    -   If a Pokemon is attacking one which isn't weak to the attacker's element, the attack is weakened.\n");
    printf("    -   When a Pokemon is " COLOR_YELLOW "defeated" COLOR_RESET ", it revives as one of the same element of the attacker.\n\n");
}

unsigned int get_width(void)
{
    // Gets a specified width value (unsigned int) from the user, and returns it.
    unsigned int w;
    printf("Insert matrix width: ");
    scanf("%u", &w);
    while (w == 0)
    {
        w = get_width();
    }
    return w;
}

unsigned int get_height(void)
{
    // Gets a specified height value (unsigned int) from the user, and returns it.
    unsigned int h;
    printf("Insert matrix height: ");
    scanf("%u", &h);
    while (h == 0)
    {
        h = get_height();
    }
    return h;
}

unsigned int get_seed(void)
{
    // Gets a specified seed value (unsigned int) from the user, and returns it.
    unsigned int s;
    printf("Insert matrix seed: ");
    scanf("%u", &s);
    while (s < 0)
    {
        s = get_seed();
    }
    return s;
}

int get_interval(void)
{
    // Gets a specified frequency value (int) from the user, and returns it.
    int n;
    printf("Insert image printing frequency (Enter a non-positive value to print only the last one): ");
    scanf("%i", &n);
    return n;
}

unsigned int get_turns(void)
{
    // Gets a specified turn value (unsigned int) from the user, and returns it.
    unsigned int t;
    printf("Insert quantity of turns: ");
    scanf("%u", &t);
    return t;
}