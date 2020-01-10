#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <time.h>

void showing(char  (*array)[9]);
void fill_the_char_table(char (*array)[9], char ch);
void fill_the_int_table(int (*array)[9], int num);
int taking(char (*array)[9], int (*set)[9]);
int solving(char (*array)[9], int (*set)[9]);
int checking(char (*array)[9], int row, int column, char value);
int check_square(char (*array)[9], int row_square, int column_square, int row, int column, char value);
void fill_the_set_table(char (*array)[9], int (*set)[9]);

int main()
{
    char array[9][9] = {{'-','-','-',  '-','-','-',  '-','-','-',},
                        {'-','-','-',  '-','-','-',  '-','-','-',},
                        {'-','-','-',  '-','-','-',  '-','-','-',},

                        {'-','-','-',  '-','-','-',  '-','-','-',},
                        {'-','-','-',  '-','-','-',  '-','-','-',},
                        {'-','-','-',  '-','-','-',  '-','-','-',},

                        {'-','-','-',  '-','-','-',  '-','-','-',},
                        {'-','-','-',  '-','-','-',  '-','-','-',},
                        {'-','-','-',  '-','-','-',  '-','-','-',}};
    int set[9][9];
    //fill_the_int_table(set, 0);
    fill_the_set_table(array, set);
    showing(array);
    getchar();
    //while (taking(array, set)) showing(array);
    time_t start = time(NULL);
    if (!solving(array, set)) printf("Sudoku nie mozliwe do rozwiazania.\n");
    else showing(array);
    printf("\nCzas rozwiazania: %.0fs", difftime(time(NULL), start));
    return 0;
}

void showing(char (*array)[9])
{
    system("cls");
    printf("-------------\n");
    for (int i = 0; i < 9; i++)
    {
        putchar('|');
        for (int j = 0; j < 9; j++)
        {
            putchar(array[i][j]);
            if (j % 3 == 2) putchar('|');
        }
        putchar('\n');
        if (i % 3 == 2) printf("-------------\n");
    }
}

void fill_the_char_table(char (*array)[9], char ch)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            array[i][j] = ch;
        }
    }
}

void fill_the_int_table(int (*array)[9], int num)
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            array[i][j] = num;
        }
    }
}

int taking(char (*array)[9], int (*set)[9])
{
    int row, column;
    char value;
    int status;
    while (1)
    {
        printf("Prosze wprowadzic dane w formacie \"Wiersz kolumna wartosc\" (Wprowadz \'q\' aby zakonczyc): ");
        if ((status = scanf("%d%d %c", &row, &column, &value)) == 3 && row <= 9 && row >= 0 && column <= 9 && column >= 0 && isdigit(value))
        {
            set[row-1][column-1]++;
            if (value == '-') set[row-1][column-1] = 0;
            array[row-1][column-1] = value;
            while (getchar() != '\n');
            return 1;
        }
        else if (status == 0)
        {
            while (getchar() != '\n');
            return 0;
        }
        else
        {
            printf("Wprowadzono bledne dane.\n");
            while (getchar() != '\n');
        }
    }
}

int solving(char (*array)[9], int (*set)[9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (array[i][j] == '-') continue;
            if (!checking(array, i, j, array[i][j])) return 0;
        }
    }
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (set[i][j]) continue;
            if (array[i][j] == '-') array[i][j] = '1';
            else if (array[i][j] != '9') array[i][j]++;
            else if (array[i][j] == '9')
            {
                array[i][j] = '-';
                if (j == 0)
                {
                    if (i == 0) return 0;
                    else
                    {
                        i--;
                        j = 7;
                        if (set[i][j+1]) j--;
                        continue;
                    }
                }
                else
                {
                    j--;
                    while (set[i][j])
                    {
                        if (j == 0)
                        {
                            i--;
                            j = 8;
                        }
                        else j--;
                    }
                    j--;
                    continue;
                }
            }
            if (!checking(array, i, j, array[i][j])) j--;
        }
    }
    return 1;
}

int checking(char (*array)[9],int row, int column, char value)
{
    for (int i = 0; i < 9; i++)
    {
        if (i == column) continue;
        if (array[row][i] == value) return 0;
    }
    for (int i = 0; i < 9; i++)
    {
        if (i == row) continue;
        if (array[i][column] == value) return 0;
    }
    if (!check_square(array, row/3, column/3, row, column, value)) return 0;
    return 1;
}

int check_square(char (*array)[9], int row_square, int column_square, int row, int column, char value)
{
    row_square *= 3;
    column_square *= 3;
    for (int i = row_square; i < (row_square + 3); i++)
    {
        for (int j = column_square; j < (column_square + 3); j++)
        {
            if (i == row && j == column) continue;
            if (array[i][j] == value) return 0;
        }
    }
    return 1;
}

void fill_the_set_table(char (*array)[9], int (*set)[9])
{
    for (int i = 0; i < 9; i++)
    {
        for (int j = 0; j < 9; j++)
        {
            if (array[i][j] == '-') set[i][j] = 0;
            else set[i][j] = 1;
        }
    }
}
