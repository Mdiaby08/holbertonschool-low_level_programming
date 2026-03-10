#include <stdio.h>

int row_sum(int row, int cols)
{
int c;
int sum = 0;

for (c = 1; c <= cols; c++)
sum += row * c;

return sum;
}

int total_sum(int rows, int cols)
{
int sum_rows = (rows * (rows + 1)) / 2;
int sum_cols = (cols * (cols + 1)) / 2;

return sum_rows * sum_cols;
}

int main(void)
{
printf("%d\n", total_sum(3, 3));
return 0;
}
