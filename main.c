#include "flags.c"
#include "pokemons.c"

int main(int argc, char * argv[])
{
    unsigned int width = 5;
    unsigned int height = 5;
    unsigned int seed = 0;
    int n = 1;
    unsigned int turns = 1;
    unsigned int counter = 0;
    int name_iter = 0;
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
            char filename[20];
            sprintf(filename, "%i.ppm", name_iter);
            create_ppm(matrix, height, width, filename);
            ++name_iter;
        }
        play_turn(matrix, height, width);
        ++counter;
    }
    if (n <= 0 || turns == 0) // If the user only wants to print the last image OR there are no simulated turns.
    {
        char * filename;
        sprintf(filename, "pokemons%u.ppm", name_iter);
        create_ppm(matrix, height, width, filename);
    }
    printf("\n");
    free_matrix(matrix, height);
    return 1;
}