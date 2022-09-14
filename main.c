#include "prototypes.h"

int main(int argc, char * argv[])
{
    unsigned int width = 5;
    unsigned int height = 5;
    unsigned int seed = 0;
    int n = 1;
    unsigned int turns = 1;
    unsigned int counter = 0;
    if (argc > 6)
    {
        puts("Too many arguments were inserted.");
        return 0;
    }
    int opt;
    while ((opt = getopt(argc, argv, "hwHsnt")) != -1)
    {
        switch (opt)
        {
            case 'h':
                help();
                return 1;
            case 'w':
                width = get_width();
                break;
            case 'H':
                height = get_height();
                break;
            case 's':
                seed = get_seed();
                break;
            case 'n':
                n = get_interval();
                break;
            case 't':
                turns = get_turns();
                break;
            default:
                puts("Invalid flag.");
        }
    }
    if (n > turns)
    {
        puts("Your printing frequency is higher than the given turns.");
        return 0;
    }
    srand(seed);
    struct Pokemon ** matrix = initialize_matrix(height, width);
    while (counter < turns)
    {
        if ((n > 0) && (counter % n == 0))
        {
            print_ppm(matrix, height, width);
        }
        play_turn(matrix, height, width);
        ++counter;
    }
    if (n <= 0 || turns == 0) // If the user only wants to print the last image OR there are no simulated turns.
    {
        print_ppm(matrix, height, width);
    }
    printf("\n");
    free_matrix(matrix, height);
    return 1;
}

// Functions
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

struct Pokemon ** initialize_matrix(unsigned int row, unsigned int col)
{
    // Initializes a matrix full of Pokemon structs and allocates it within a specific space of memory for future modifications. Returns a pointer to that memory.
    struct Pokemon ** matrix = (struct Pokemon **)malloc(row * sizeof(struct Pokemon));
    for (int k = 0; k < row; ++k)
    {
        matrix[k] = (struct Pokemon *)malloc(col * sizeof(struct Pokemon));
    }
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            matrix[i][j].hp = MAX_HP;
            matrix[i][j].dmg = BASE_DMG;
            matrix[i][j].type = random_type();
        }
    }
    return matrix;
}

void free_matrix(struct Pokemon ** matrix, unsigned int row)
{
    // Frees the reserved space of memory occupied by the Pokemon matrix from the initialize_matrix() functions.
    for (int i = 0; i < row; ++i)
    {
        free(matrix[i]);
    }
    free(matrix);
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

enum pokemon_type random_type(void)
{
    // Picks a random Pokemon type from the ones enumerated in pokemon_type.
    enum pokemon_type type;
    type = rand()%TYPE_QUANTITY;
    return type;
}

void attack(struct Pokemon * attacker, struct Pokemon * defender)
{
    // Lowers a Pokemon's HP based on its own type, as well as the attacker's.
    if ((attacker->type == 0 && defender->type == 2) || (attacker->type == 1 && defender->type == 0) || (attacker->type == 2 && defender->type == 1))
    {
        defender->hp -= (attacker->dmg * 2.0); // Attack to weaker element
    }
    else
    {
        defender->hp -= (attacker->dmg / 2.0);
    }
    if (defender->hp <= 0)
    {
        defender->hp = MAX_HP;
        defender->type = attacker->type;
    }
}

void play_turn(struct Pokemon ** matrix, unsigned int row, unsigned int col)
{
    // The selected Pokemon attacks all neighboring Pokemons.
    for (int i = 0; i < row; ++i)
        {
            for (int j = 0; j < col; ++j)
            {
                if (i > 0 && i < (row - 1) && j > 0 && j < (col - 1)) // Inner-edge
                {
                    attack(&matrix[i][j], &matrix[i - 1][j]);
                    attack(&matrix[i][j], &matrix[i + 1][j]);
                    attack(&matrix[i][j], &matrix[i][j - 1]);
                    attack(&matrix[i][j], &matrix[i][j + 1]);
                    attack(&matrix[i][j], &matrix[i - 1][j - 1]);
                    attack(&matrix[i][j], &matrix[i - 1][j + 1]);
                    attack(&matrix[i][j], &matrix[i + 1][j - 1]);
                    attack(&matrix[i][j], &matrix[i + 1][j + 1]);
                }
                else if (i == 0 && j > 0 && j < (col - 1)) // First row (no corners)
                {
                    attack(&matrix[i][j], &matrix[i][j - 1]);
                    attack(&matrix[i][j], &matrix[i][j + 1]);
                    attack(&matrix[i][j], &matrix[i + 1][j]);
                    attack(&matrix[i][j], &matrix[i + 1][j - 1]);
                    attack(&matrix[i][j], &matrix[i + 1][j + 1]);
                }
                else if (i == (row - 1) && j > 0 && j < (col - 1)) // Last row (no corners)
                {
                    attack(&matrix[i][j], &matrix[i][j - 1]);
                    attack(&matrix[i][j], &matrix[i][j + 1]);
                    attack(&matrix[i][j], &matrix[i - 1][j]);
                    attack(&matrix[i][j], &matrix[i - 1][j - 1]);
                    attack(&matrix[i][j], &matrix[i - 1][j + 1]);
                }
                else if (j == 0 && i > 0 && i < (row - 1)) // First collumn (no corners)
                {
                    attack(&matrix[i][j], &matrix[i - 1][j]);
                    attack(&matrix[i][j], &matrix[i + 1][j]);
                    attack(&matrix[i][j], &matrix[i][j + 1]);
                    attack(&matrix[i][j], &matrix[i - 1][j + 1]);
                    attack(&matrix[i][j], &matrix[i + 1][j + 1]);
                }
                else if (j == (col - 1) && i > 0 && i < (row - 1)) // Last collumn (no corners)
                {
                    attack(&matrix[i][j], &matrix[i - 1][j]);
                    attack(&matrix[i][j], &matrix[i + 1][j]);
                    attack(&matrix[i][j], &matrix[i][j - 1]);
                    attack(&matrix[i][j], &matrix[i - 1][j - 1]);
                    attack(&matrix[i][j], &matrix[i + 1][j - 1]);
                }
                else if (i == 0 && j == 0) // Left-superior corner
                {
                    attack(&matrix[i][j], &matrix[i][j + 1]);
                    attack(&matrix[i][j], &matrix[i + 1][j]);
                    attack(&matrix[i][j], &matrix[i + 1][j + 1]);
                }
                else if (i == 0 && j == (col - 1)) // Right-superior corner
                {
                    attack(&matrix[i][j], &matrix[i][j - 1]);
                    attack(&matrix[i][j], &matrix[i + 1][j]);
                    attack(&matrix[i][j], &matrix[i + 1][j - 1]);
                }
                else if (i == (row - 1) && j == 0) // Left-inferior corner
                {
                    attack(&matrix[i][j], &matrix[i][j + 1]);
                    attack(&matrix[i][j], &matrix[i - 1][j]);
                    attack(&matrix[i][j], &matrix[i - 1][j + 1]);
                }
                else if (i == (row - 1) && j == (col - 1)) // Right-inferior corner
                {
                    attack(&matrix[i][j], &matrix[i][j - 1]);
                    attack(&matrix[i][j], &matrix[i - 1][j]);
                    attack(&matrix[i][j], &matrix[i - 1][j - 1]);
                }
                else
                {
                    puts("ATTACK ERROR!");
                }
            }
        }
}

void print_ppm(struct Pokemon ** matrix, unsigned int row, unsigned int col)
{
    // Prints all values needed to create the PPM image.
    printf("\nP3 %u %u 255 ", col, row);
    for (int i = 0; i < row; ++i)
    {
        for (int j = 0; j < col; ++j)
        {
            int type = matrix[i][j].type;
            if (type == 0)
            {
                printf("%s ", red);
            }
            else if (type == 1)
            {
                printf("%s ", blue);
            }
            else if (type == 2)
            {
                printf("%s ", green);
            }
            else
            {
                printf("%s ", white); // If any pixels are printed with the color white, there is an error.
            }
        }
    }
    printf("\n");
}