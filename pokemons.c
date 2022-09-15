#include "prototypes.h"

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