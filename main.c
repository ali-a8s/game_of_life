#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

void draw(void *u, int w, int h, int time_s, int percentage, int generation, int live_cells)
{
    char (*world)[w] = u;

    system("cls");
    printf("*** GAME OF LIFE ***\n\n");
    printf("generation: %d | live cells: %d \nspeed: %d sec | init: %d %%",
           generation, live_cells,time_s, percentage);
    printf("\n\n");

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            printf(world[y][x] ? "X" : "-");
        }
        printf("\n");
    }
}

void evolution(void *u, int h, int w)
{
    char (*world)[w] = u;
    char new[h][w];

    for (int x = 0; x < w; x++) {
        for (int y = 0; y < h; y++) {
            int lives = 0;
            for (int xd = x - 1; xd <= x + 1; xd++) {
                for (int yd = y - 1; yd <= y + 1; yd++) {
                    if (world[((yd + h) % h)][(xd + w) % w]) {
                        lives++;
                    }
                }
            }

            if (world[y][x]) lives--;

            if (lives == 3) {
                new[y][x] = 1;
            } else if (lives == 2 && world[y][x] == 1) {
                new[y][x] = 1;
            } else {
                new[y][x] = 0;
            }
        }
    }

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            world[y][x] = new[y][x];
        }
    }
}

int count_live_cells(void *u, int w, int h)
{
    char (*world)[w] = u;
    int count = 0;

    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            if (world[y][x]) {   
                count++;
            }
        }
    }

    return count;
}

int main()
{
    srand(time(0));

    int w = 0, h = 0, time_s = 0, percentage = 0;
    int generation = 1;

    printf("Enter width: ");
    scanf("%d", &w);
    printf("Enter height: ");
    scanf("%d", &h);
    printf("Enter evolution speed (seconds): ");
    scanf("%d", &time_s);

    printf("Enter initial percentage of live cells (0-100): ");
	scanf("%d", &percentage); 

    int time_ms = time_s * 1000000;

    char world[h][w];

    
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            world[y][x] = (rand() % 100 < percentage) ? 1 : 0;
        }
    }

    while (1) {
        int live = count_live_cells(world, w, h);  
        draw(world, w, h, time_s, percentage, generation, live);
        evolution(world, h, w);
        usleep(time_ms);
        generation++;
    }

    return 0;
}