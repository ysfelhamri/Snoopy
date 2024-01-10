#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

void delay(float ms)
{
    clock_t start_time = clock();
    while (clock() < start_time + ms)
        ;
}
int mat_is_null(int **mat, int n)
{
    if(!mat)return 1;
    int i;
    for (i = 0; i < n; i++)
        if (!mat[i])
            return 1;
    return 0;
}
void goto_print(int x, int y, char *c)
{
    COORD mycoord;
    mycoord.X = y;
    mycoord.Y = x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mycoord);
    printf("%s", c);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){0, 0});
}
void goto_print_int(int x, int y, int d)
{

    COORD mycoord;
    mycoord.X = y;
    mycoord.Y = x;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), mycoord);
    printf("%d", d);
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), (COORD){0, 0});
}
void print_mat(int **mat, int n)
{
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
            mat[i][j] ? printf(" %d ", mat[i][j]) : printf("   ");
        printf("\n");
    }
}
void init_mat(int **mat, int n)
{
    if(mat_is_null(mat, n)){
        printf("NULL ptr!");
        exit(33);
    }
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (i == 0 || i == n - 1 || j == 0 || j == n - 1)
                mat[i][j] = 2;
            else
                mat[i][j] = 0;
        }
        mat[0][i] = 2;
    }
}
void print_grid(int **mat, int n)
{
    if(mat_is_null(mat, n)){
        printf("NULL ptr!");
        exit(33);
    }
    int i, j;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            switch (mat[i][j])
            {
            case 1:

                printf(" ☻ ");

                break;
            case 2:

                if (i == 0)
                {
                    if (j == 0)
                        printf(" ▓ ▄▄");
                    else if (j == n - 1)
                        printf("▄▄ ▓");
                    else
                        printf("▄▄▄");
                }
                else if (i == n - 1)
                {
                    if (j == 0)
                        printf(" ▓ ▀▀");
                    else if (j == n - 1)
                        printf("▀▀ ▓");
                    else
                        printf("▀▀▀");
                }

                else if (j == 0)
                    printf(" ▓ █ ");
                else if (j == n - 1)
                    printf(" █ ▓");

                else
                    printf("###");

                break;
            case 3:

                printf(" ♂ ");

                break;
            case 4:

                printf(" ♫ ");

                break;
            case 8:

                printf(" ◙ ");

                break;
            case 9:
                printf(" ◙ ");
                break;
            default:

                printf("   ");

                break;
            }
        }
        printf("\n");
    }
}
void moving_ball(int **mat, int n, int *x, int *y, int *flag, int player_x, int player_y, int *state)
{
    if(mat_is_null(mat, n)){
        printf("NULL ptr!");
        exit(33);
    }
    if (!*flag && !*state)
    {
        if (*x + 1 == player_x && *y + 1 == player_y)
            *state = 1;
        if (*y != n - 1 && mat[*x + 1][*y + 1] == 0 && *x != n - 1)
        {
            mat[*x][*y] = 0;
            goto_print(*x, *y * 3 + 3, " ");
            mat[++*x][++*y] = 3;
            goto_print(*x, *y * 3 + 3, "♂");
        }
        else if (*y == n - 1 || mat[*x][*y + 1] != 0)
        {
            if (*x == player_x && *y + 1 == player_y)
                *state = 1;
            *flag = 2;
        }
        else if (*x == n - 1 || mat[*x + 1][*y] != 0)
        {
            if (*x + 1 == player_x && *y == player_y)
                *state = 1;
            *flag = 3;
        }
        else if (mat[*x + 1][*y + 1] != 0 && mat[*x][*y + 1] == 0)
            *flag = 1;
    }
    if (*flag == 1 && !*state)
    {
        if (*x - 1 == player_x && *y - 1 == player_y)
            *state = 1;
        if (*y != 0 && mat[*x - 1][*y - 1] == 0 && *x != 0)
        {
            mat[*x][*y] = 0;
            goto_print(*x, *y * 3 + 3, " ");
            mat[--*x][--*y] = 3;
            goto_print(*x, *y * 3 + 3, "♂");
        }
        else if (*y == 0 || mat[*x][*y - 1] != 0)
        {
            if (*x == player_x && *y - 1 == player_y)
                *state = 1;
            *flag = 3;
        }
        else if (*x == 0 || mat[*x - 1][*y] != 0)
        {
            if (*x - 1 == player_x && *y == player_y)
                *state = 1;
            *flag = 2;
        }
        else if (mat[*x - 1][*y - 1] != 0 && mat[*x][*y - 1] == 0)
            *flag = 0;
    }
    if (*flag == 2 && !*state)
    {
        if (*x + 1 == player_x && *y - 1 == player_y)
            *state = 1;
        if (*y != 0 && mat[*x + 1][*y - 1] == 0 && *x != n - 1)
        {
            mat[*x][*y] = 0;
            goto_print(*x, *y * 3 + 3, " ");
            mat[++*x][--*y] = 3;
            goto_print(*x, *y * 3 + 3, "♂");
        }
        else if (*y == 0 || mat[*x][*y - 1] != 0)
        {
            if (*x == player_x && *y - 1 == player_y)
                *state = 1;
            *flag = 0;
        }
        else if (*x == n - 1 || mat[*x + 1][*y] != 0)
        {
            if (*x + 1 == player_x && *y == player_y)
                *state = 1;
            *flag = 1;
        }
        else if (mat[*x + 1][*y - 1] != 0 && mat[*x + 1][*y] == 0)
            *flag = 3;
    }
    if (*flag == 3 && !*state)
    {
        if (*x - 1 == player_x && *y + 1 == player_y)
            *state = 1;
        if (*y != n - 1 && mat[*x - 1][*y + 1] == 0 && *x != 0)
        {
            mat[*x][*y] = 0;
            goto_print(*x, *y * 3 + 3, " ");
            mat[--*x][++*y] = 3;
            goto_print(*x, *y * 3 + 3, "♂");
        }
        else if (*y == n - 1 || mat[*x][*y + 1] != 0)
        {
            if (*x == player_x && *y + 1 == player_y)
                *state = 1;
            *flag = 1;
        }
        else if (*x == 0 || mat[*x - 1][*y] != 0)
        {
            if (*x - 1 == player_x && *y == player_y)
                *state = 1;
            *flag = 0;
        }
        else if (mat[*x - 1][*y + 1] != 0 && mat[*x - 1][*y] == 0)
            *flag = 2;
    }
}
void mov_char(int **mat, int n, int *x, int *y, int *out, int *bird_flag, int *tp_flag)
{
    if(mat_is_null(mat, n)){
        printf("NULL ptr!");
        exit(33);
    }
    if (kbhit())
    {
        int direction;
        direction = getch();

        switch (direction)
        {
        case 75:
            if (mat[*x][*y - 1] == 4)
                *bird_flag = 1;
            if (mat[*x][*y - 1] == 8)
                *tp_flag = 1;
            if (mat[*x][*y - 1] == 9)
                *tp_flag = 2;
            if (*y != 0 && mat[*x][*y - 1] == 0 || mat[*x][*y - 1] == 4)
            {
                mat[*x][*y] = 0;
                goto_print(*x, *y * 3 + 3, " ");
                mat[*x][--*y] = 1;
                goto_print(*x, *y * 3 + 3, "☻");
            }
            break;
        case 77:
            if (mat[*x][*y + 1] == 4)
                *bird_flag = 1;
            if (mat[*x][*y + 1] == 8)
                *tp_flag = 1;
            if (mat[*x][*y + 1] == 9)
                *tp_flag = 2;
            if (*y != n - 1 && mat[*x][*y + 1] == 0 || mat[*x][*y + 1] == 4)
            {
                mat[*x][*y] = 0;
                goto_print(*x, *y * 3 + 3, " ");
                mat[*x][++*y] = 1;
                goto_print(*x, *y * 3 + 3, "☻");
            }
            break;
        case 72:
            if (mat[*x - 1][*y] == 4)
                *bird_flag = 1;
            if (mat[*x - 1][*y] == 8)
                *tp_flag = 1;
            if (mat[*x - 1][*y] == 9)
                *tp_flag = 2;
            if (*x != 0 && mat[*x - 1][*y] == 0 || mat[*x - 1][*y] == 4)
            {
                mat[*x][*y] = 0;
                goto_print(*x, *y * 3 + 3, " ");
                mat[--*x][*y] = 1;
                goto_print(*x, *y * 3 + 3, "☻");
            }

            break;
        case 80:
            if (mat[*x + 1][*y] == 4)
                *bird_flag = 1;
            if (mat[*x + 1][*y] == 8)
                *tp_flag = 1;
            if (mat[*x + 1][*y] == 9)
                *tp_flag = 2;
            if (*x != n - 1 && mat[*x + 1][*y] == 0 || mat[*x + 1][*y] == 4)
            {
                mat[*x][*y] = 0;
                goto_print(*x, *y * 3 + 3, " ");
                mat[++*x][*y] = 1;
                goto_print(*x, *y * 3 + 3, "☻");
            }
            break;

        case 13:
            *out = 1;
            break;
        }
    }
}
void game_timer(int **mat, int n, int *time, int *timer_pos, int *dec_flag)
{
    if(mat_is_null(mat, n)){
        printf("NULL ptr!");
        exit(33);
    }
    if (*time <= 0)
        return;
    --*time;
    if (*dec_flag)
    {
        goto_print(*timer_pos, 1, "░");
        goto_print(*timer_pos, (n - 1) * 3 + 5, "░");
        ++*timer_pos;
        *dec_flag = 0;
    }
    goto_print(n + 2, 12, "    ");
    goto_print_int(n + 2, 12, *time);
}
void bird(int *bird_flag, int *score, int *level_bird_count, int n)
{
    if (!*bird_flag || level_bird_count == 0)
        return;
    ++*score;
    *bird_flag = 0;
    --*level_bird_count;
    goto_print(n + 1, 9, "    ");
    goto_print_int(n + 1, 9, *score);
}
int bird_count(int **mat, int n)
{
    int res = 0;
    int i, j;
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (mat[i][j] == 4)
                res++;
    return res;
}
void level_one(int **mat, int n, int *player_x, int *player_y, int *ball_x, int *ball_y)
{
    if(mat_is_null(mat, n)){
        printf("NULL ptr!");
        exit(33);
    }
    init_mat(mat, n);
    *ball_x = 1;
    *player_x = n / 2 - 1;
    *ball_y = n - 5;
    *player_y = n / 2;
    mat[*player_x][*player_y] = 1;
    mat[1][1] = 4;
    mat[2][n - 3] = 4;
    mat[n - 3][n - 4] = 4;
    mat[n - 3][3] = 4;

    mat[1][2] = 2;
    mat[2][2] = 2;

    mat[n / 2][n / 2] = 2;
    mat[n / 2][n / 2 - 1] = 2;
    mat[n / 2 - 1][n / 2 - 1] = 2;
    mat[1][n - 6] = 2;
    mat[2][n - 6] = 2;
    mat[7][n - 2] = 2;
    mat[7][n - 3] = 2;
    mat[n - 2][n - 7] = 2;
    mat[n - 3][n - 7] = 2;
    mat[n - 4][n - 7] = 2;
    mat[n - 5][n - 7] = 2;
    mat[n - 6][1] = 2;
    mat[n - 6][2] = 2;
    mat[n - 2][5] = 2;
    mat[n - 3][5] = 2;
}
void level_two(int **mat, int n, int *player_x, int *player_y, int *ball_x, int *ball_y)
{
    if(mat_is_null(mat, n)){
        printf("NULL ptr!");
        exit(33);
    }
    init_mat(mat, n);
    *ball_x = n - 3;
    *player_x = n / 2 - 1;
    *ball_y = n - 3;
    *player_y = n / 2;
    mat[*player_x][*player_y] = 1;

    mat[1][1] = 4;
    mat[2][n - 3] = 4;
    mat[n - 3][n - 4] = 4;
    mat[n - 3][3] = 4;

    mat[1][3] = 2;
    mat[2][3] = 2;
    mat[3][3] = 2;
    mat[3][1] = 2;
    mat[3][2] = 2;

    mat[1][n - 6] = 2;
    mat[2][n - 6] = 2;
    mat[7][n - 2] = 2;
    mat[7][n - 3] = 2;
    mat[n - 2][n - 7] = 2;
    mat[n - 3][n - 7] = 2;
    mat[n - 4][n - 7] = 2;
    mat[n - 5][n - 7] = 2;
    mat[n - 6][1] = 2;
    mat[n - 6][2] = 2;
    mat[n - 2][5] = 2;
    mat[n - 3][5] = 2;

    mat[n / 2][n / 2 + 1] = 2;
    mat[n / 2][n / 2] = 2;

    mat[n / 2][n / 2 - 1] = 2;
    mat[n / 2 - 1][n / 2 - 2] = 2;
    mat[n / 2 - 2][n / 2 - 2] = 2;
    mat[n / 2 - 3][n / 2 - 2] = 2;
}
void health(int *hearts, int *state, int n, int *out)
{
    if (*hearts <= 0)
    {
        float pause_ms = 500;
        float pause_delay = clock() + pause_ms;
        int flash = 0;
        int level_wait = clock() + 2000;
        goto_print(n / 2, (n / 2) * 3 - 1, "You Lost!");
        while (1)
        {
            if (clock() >= pause_delay)
            {
                if (!flash)
                {
                    goto_print(n / 2, (n / 2) * 3 - 1, "         ");
                    flash = 1;
                }
                else
                {
                    goto_print(n / 2, (n / 2) * 3 - 1, "You Lost!");
                    flash = 0;
                }
                pause_delay = clock() + pause_ms;
            }
            if (clock() >= level_wait)
            {
                *out = 1;
                return;
            }
        }
    }
    goto_print(n, *hearts * 2 - 1, " ");
    --*hearts;
    *state = 0;
}
void teleport(int *player_x, int *player_y, int p1_x, int p1_y, int p2_x, int p2_y, int **mat)
{
    if (mat[p2_x][p2_y + 1] == 0)
    {
        goto_print(*player_x, *player_y * 3 + 3, " ");
        mat[*player_x][*player_y] = 0;
        *player_x = p2_x;
        *player_y = p2_y + 1;
        goto_print(*player_x, *player_y * 3 + 3, "☻");
    }
    else if (mat[p2_x][p2_y - 1] == 0)
    {
        goto_print(*player_x, *player_y * 3 + 3, " ");
        mat[*player_x][*player_y] = 0;
        *player_x = p2_x;
        *player_y = p2_y - 1;
        goto_print(*player_x, *player_y * 3 + 3, "☻");
    }
    else if (mat[p2_x + 1][p2_y] == 0)
    {
        goto_print(*player_x, *player_y * 3 + 3, " ");
        mat[*player_x][*player_y] = 0;
        *player_x = p2_x + 1;
        *player_y = p2_y;
        goto_print(*player_x, *player_y * 3 + 3, "☻");
    }
    else if (mat[p2_x - 1][p2_y] == 0)
    {
        goto_print(*player_x, *player_y * 3 + 3, " ");
        mat[*player_x][*player_y] = 0;
        *player_x = p2_x - 1;
        *player_y = p2_y;
        goto_print(*player_x, *player_y * 3 + 3, "☻");
    }
    else
        return;
}
void print_menu()
{
    system("cls");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    printf(" ▓ ▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄ ▓\n"
           " ▓ █                     , ----.__                 █ ▓\n"
           " ▓ █               __.,'           \\               █ ▓\n"
           " ▓ █            .'                 *\\              █ ▓\n"
           " ▓ █           /       |   |     / **\\             █ ▓\n"
           " ▓ █          .   mm            / ****.            █ ▓\n"
           " ▓ █           \\                | ****|            █ ▓\n"
           " ▓ █            ` ._______      \\ ****/            █ ▓\n"
           " ▓ █                     \\______/`---'             █ ▓\n"
           " ▓ █       xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx       █ ▓\n"
           " ▓ █      x                                 x      █ ▓\n"
           " ▓ █	 x                                   x     █ ▓\n"
           " ▓ █    x                                     x    █ ▓\n"
           " ▓ █   x                                       x   █ ▓\n"
           " ▓ █  x                                         x  █ ▓\n"
           " ▓ █ xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx █ ▓\n"
           " ▓ ▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀ ▓\n");
}
void pause_reprint(int **mat, int n)
{
    if(mat_is_null(mat, n)){
        printf("NULL ptr!");
        exit(33);
    }
    goto_print(n / 2, (n / 2) * 3 - 1, "       ");
    int i;
    for (i = (n / 2) - 1; i < (n / 2) + 7; i++)
        switch (mat[n / 2][i])
        {
        case 1:

            goto_print(n / 2, i * 3 + 3, "☻");

            break;
        case 2:

            goto_print(n / 2, i * 3 + 2, "###");

            break;
        case 3:

            goto_print(n / 2, i * 3 + 3, "♂");

            break;
        case 4:

            goto_print(n / 2, i * 3 + 3, "♫");

            break;
        case 8:

            goto_print(n / 2, i * 3 + 3, "◙");

            break;
        case 9:
            goto_print(n / 2, i * 3 + 3, "◙");

            break;
        default:

            goto_print(n / 2, i * 3 + 3, "");

            break;
        }
}
void score_save(int score_reg)
{
    FILE *score;
    int error;
    score = fopen("scores.sp", "r+b");
    if (!score)
    {
        score = fopen("scores.sp", "w+b");
        if(!score) return;
        error = fwrite(&score_reg, sizeof(int), 1, score);
        if(!error) return;
        error = fseek(score, sizeof(int), SEEK_SET);
        if(error) return;
        error = fwrite(&score_reg, sizeof(int), 1, score);
        if(!error) return;
        error = fclose(score);
        if(!error) return;
        return;
    }
    if (!score)
        return;
    int high_score;
    error = fseek(score, sizeof(int), SEEK_SET);
    if(error) return;
    error = fread(&high_score, sizeof(int), 1, score);
    if(!error) return;
    if (score_reg > high_score)
    {
        error = fseek(score, sizeof(int), SEEK_SET);
        if(error) return;
        error = fwrite(&score_reg, sizeof(int), 1, score);
        if(!error) return;
    }
    error = fseek(score, 0, SEEK_SET);
    if(error) return;
    error = fwrite(&score_reg, sizeof(int), 1, score);
    if(!error) return;

    error= fclose(score);
    if(!error) return;
}
void read_save(int *last_score, int *high_score)
{
    FILE *score;
    int error;
    score = fopen("scores.sp", "rb");
    if (!score)
    {
        *last_score = 0;
        *high_score = 0;
        return;
    }
    error = fread(last_score, sizeof(int), 1, score);
    if(!error) return;
    error =fseek(score, sizeof(int), SEEK_SET);
    if(error) return;
    error = fread(high_score, sizeof(int), 1, score);
    if(!error) return;
    error= fclose(score);
    if(!error) return;
}
void print_options();
void stats_menu()
{
    int last_score, high_score, key;
    system("cls");
    print_menu();
    read_save(&last_score, &high_score);
    goto_print(11, 16, "Last Attempt Score :");
    goto_print_int(11, 37, last_score);
    goto_print(12, 16, "High Score :");
    goto_print_int(12, 29, high_score);
    goto_print(13, 13, "->");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
    goto_print(13, 16, "Back");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    while (1)
    {
        key = getch();
        if (key == 13)
        {
            print_options();
            return;
        }
    }
}
void print_options()
{
    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    system("cls");
    print_menu();
    goto_print(11, 19, "->");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
    goto_print(11, 22, "Start Game");
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    goto_print(13, 22, "Quit");
    goto_print(12, 22, "           ");
    goto_print(12, 22, "Stats");
    int opt = 0;
    int out_opt = 0;
    while (1)
    {
        switch (getch())
        {
        case 80:

            if (opt == 0)
            {
                opt++;
                goto_print(11, 19, "  ");
                goto_print(11, 22, "Start Game");
                goto_print(12, 19, "->");

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
                goto_print(12, 22, "Stats");

                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            }
            else if (opt == 1)
            {
                opt++;
                goto_print(12, 19, "  ");
                goto_print(12, 22, "Stats");
                goto_print(13, 19, "->");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
                goto_print(13, 22, "Quit");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            }

            break;
        case 72:

            if (opt == 2)
            {
                opt--;
                goto_print(13, 19, "  ");
                goto_print(13, 22, "Quit");
                goto_print(12, 19, "->");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
                goto_print(12, 22, "Stats");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            }
            else if (opt == 1)
            {
                opt--;
                goto_print(12, 19, "  ");
                goto_print(12, 22, "Stats");
                goto_print(11, 19, "->");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BACKGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
                goto_print(11, 22, "Start Game");
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            }
            break;
        case 13:
            if (opt == 2)
            {
                system("cls");
                exit(0);
            }
            else if (opt == 1)
            {
                stats_menu();
            }
            out_opt = 1;
            break;
        }
        if (out_opt)
            break;
    }
}

int main()
{
    srand(time(NULL));
    int i, player_x, player_y, out = 0, ball_x, ball_y, flag = 0, ball_ms = 100, collision_state = 0;
    int n = 17;
    int ratio = 3, wait = 0;
    int timer = n * ratio, dec_flag = 0, timer_pos = 0;
    int level_bird_count;
    int bird_flag = 0, score = 0;
    int init_hearts = 3, hearts = init_hearts;
    int tp_flag = 0, p1_x, p2_x, p1_y, p2_y;
    SetConsoleOutputCP(CP_UTF8);
    int **grid = (int **)malloc(n * sizeof(int *));
    if(!grid){
        printf("Mem alloc error!");
        exit(33);
    }
    for (i = 0; i < n; i++){
        grid[i] = (int *)malloc(n * sizeof(int));
        if(!grid[i]){
            printf("Mem alloc error!");
            exit(33);
        }
    }
    float ball_delay = clock() + ball_ms;
    float timer_ms = 1000;
    float timer_delay = clock() + timer_ms;
    float pause_ms = 500;
    float pause_delay = clock() + pause_ms;
    float ball_direction_ms = 1000;
    float ball_direction_delay = clock() + ball_direction_ms;
    float level_wait;
    int pause = 0;
    int flash = 0;
    int end = 0;
    int next_level = 0;
    int level_count = 0;
    int levels_size = 2;
    int ch;
    void (*levels[2])(int **, int, int *, int *, int *, int *) = {level_one, level_two};
    print_menu();
    goto_print(12, 22, "Press Enter");
    while (1)
    {
        if (clock() >= pause_delay)
        {
            if (!flash)
            {
                goto_print(12, 22, "           ");
                flash = 1;
            }
            else
            {
                goto_print(12, 22, "Press Enter");
                flash = 0;
            }
            pause_delay = clock() + pause_ms;
        }
        if (kbhit())
            if (getch() == 13)
                break;
    }
    print_options();
    system("cls");
    print_menu();
    goto_print(12, 23, "Level 1");
    delay(2000);
    flash = 0;
    pause_delay = clock() + pause_ms;
    levels[0](grid, n, &player_x, &player_y, &ball_x, &ball_y);
    level_bird_count = bird_count(grid, n);
    system("cls");
    print_grid(grid, n);
    for (i = 0; i < hearts; i++)
        goto_print(n, 1 + i * 2, "♥");
    goto_print(n + 1, 1, "Score : 0");
    goto_print(n + 2, 1, "Time Left: ");
    goto_print_int(n + 2, 12, timer);

    while (1)
    {

        if (!timer)
        {
            pause = 1;
            goto_print(n / 2, (n / 2) * 3 - 1, "Time's Up!");
            level_wait = clock() + 2000;
            while (1)
            {
                if (clock() >= pause_delay)
                {
                    if (!flash)
                    {
                        goto_print(n / 2, (n / 2) * 3 - 1, "          ");
                        flash = 1;
                    }
                    else
                    {
                        goto_print(n / 2, (n / 2) * 3 - 1, "Time's Up!");
                        flash = 0;
                    }
                    pause_delay = clock() + pause_ms;
                }

                if (clock() >= level_wait)
                    break;
            }
            pause = 0;
            end = 1;
        }
        if (!level_bird_count)
        {
            pause = 1;
            goto_print(n / 2, (n / 2) * 3 - 1, "You Win!");
            level_wait = clock() + 2000;
            while (1)
            {
                if (clock() >= pause_delay)
                {
                    if (!flash)
                    {
                        goto_print(n / 2, (n / 2) * 3 - 1, "        ");
                        flash = 1;
                    }
                    else
                    {
                        goto_print(n / 2, (n / 2) * 3 - 1, "You Win!");
                        flash = 0;
                    }
                    pause_delay = clock() + pause_ms;
                }
                if (clock() >= level_wait)
                    break;
            }
            pause = 0;
            next_level = 1;
        }
        if (next_level)
        {
            if (level_count + 1 >= levels_size)
                end = 1;
            else
            {
                score_save(score);
                print_menu();
                goto_print(12, 23, "Level ");
                goto_print_int(12, 30, level_count + 2);
                delay(2000);
                if (ball_ms - 50 > 0)
                    ball_ms -= 50;
                out = 0;
                flag = 0;
                collision_state = 0;
                wait = 0;
                timer = n * ratio;
                dec_flag = 0;
                timer_pos = 0;
                bird_flag = 0;

                ball_delay = clock() + ball_ms;
                timer_delay = clock() + timer_ms;
                pause_delay = clock() + pause_ms;
                pause = 0;
                flash = 0;
                end = 0;
                level_count++;
                levels[level_count](grid, n, &player_x, &player_y, &ball_x, &ball_y);
                if (level_count == 1)
                {
                    p1_x = n - 2;
                    p1_y = 7;
                    p2_x = 2;
                    p2_y = 2;
                    grid[p1_x][p1_y] = 8;
                    grid[p2_x][p2_y] = 9;
                }
                level_bird_count = bird_count(grid, n);
                system("cls");
                print_grid(grid, n);
                for (i = 0; i < hearts; i++)
                    goto_print(n, 1 + i * 2, "♥");
                goto_print(n + 1, 1, "Score : ");
                goto_print(n + 1, 9, "    ");
                goto_print_int(n + 1, 9, score);
                goto_print(n + 2, 1, "Time Left: ");
                goto_print_int(n + 2, 12, timer);
                next_level = 0;
                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
            }
        }

        if (!pause)
        {

            if (collision_state || !hearts)
            {
                health(&hearts, &collision_state, n, &end);
            }
            if (end)
            {
                score_save(score);
                level_count = 0;
                score = 0;
                ball_ms = 100;
                out = 0;
                flag = 0;
                collision_state = 0;
                wait = 0;
                timer = n * ratio;
                dec_flag = 0;
                timer_pos = 0;
                bird_flag = 0;
                hearts = init_hearts;
                ball_delay = clock() + ball_ms;
                timer_delay = clock() + timer_ms;
                pause_delay = clock() + pause_ms;
                pause = 0;
                flash = 0;
                end = 0;
                levels[0](grid, n, &player_x, &player_y, &ball_x, &ball_y);
                level_bird_count = bird_count(grid, n);
                print_options();
                system("cls");
                print_menu();
                goto_print(12, 23, "Level ");
                goto_print_int(12, 30, level_count + 1);
                delay(2000);
                system("cls");
                print_grid(grid, n);
                for (i = 0; i < hearts; i++)
                    goto_print(n, 1 + i * 2, "♥");
                goto_print(n + 1, 1, "Score : ");
                goto_print(n + 1, 9, "    ");
                goto_print_int(n + 1, 9, score);
                goto_print(n + 2, 1, "Time Left: ");
                goto_print_int(n + 2, 12, timer);
                next_level = 0;
                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
            }
            mov_char(grid, n, &player_x, &player_y, &out, &bird_flag, &tp_flag);
            if (out)
            {
                goto_print(n / 2, (n / 2) * 3 - 1, "Paused!");
                while (1)
                {
                    if (clock() >= pause_delay)
                    {
                        if (!flash)
                        {
                            goto_print(n / 2, (n / 2) * 3 - 1, "       ");
                            flash = 1;
                        }
                        else
                        {
                            goto_print(n / 2, (n / 2) * 3 - 1, "Paused!");
                            flash = 0;
                        }
                        pause_delay = clock() + pause_ms;
                    }
                    if (kbhit())
                    {
                        ch = getch();
                        if (ch == 13)
                            break;
                        if (ch == 27)
                        {
                            score_save(score);
                            end = 1;
                            break;
                        }
                    }
                }
                if (end)
                    continue;
                out = 0;
                pause_reprint(grid, n);
            }
            if (tp_flag == 1)
            {
                teleport(&player_x, &player_y, p1_x, p1_y, p2_x, p2_y, grid);
                tp_flag = 0;
            }
            if (tp_flag == 2)
            {
                teleport(&player_x, &player_y, p2_x, p2_y, p1_x, p1_y, grid);
                tp_flag = 0;
            }
            if (clock() >= ball_direction_delay)
            {
                switch (flag)
                {
                case 0:
                    flag = (rand() % 2) ? 3 : 1;
                    break;
                case 1:
                    flag = (rand() % 2) ? 2 : 3;
                    break;
                case 2:
                    flag = (rand() % 2) ? 0 : 1;

                    break;
                case 3:
                    flag = (rand() % 2) ? 1 : 2;
                    break;
                }

                ball_direction_delay = clock() + ball_direction_delay;
            }
            if (clock() >= ball_delay)
            {

                moving_ball(grid, n, &ball_x, &ball_y, &flag, player_x, player_y, &collision_state);
                ball_delay = clock() + ball_ms;
            }
            if (bird_flag)
                bird(&bird_flag, &score, &level_bird_count, n);
            if (timer > 0)
                if (clock() >= timer_delay)
                {
                    if (wait + 1 == ratio)
                    {
                        dec_flag = 1;
                        wait = 0;
                    }
                    else
                        wait++;
                    game_timer(grid, n, &timer, &timer_pos, &dec_flag);
                    timer_delay = clock() + timer_ms;
                }
        }
    }
    for (i = 0; i < n; i++)
        free(grid[i]);
    free(grid);
    return 0;
}