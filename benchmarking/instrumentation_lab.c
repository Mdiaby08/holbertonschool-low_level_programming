#include <stdio.h>
#include <time.h>

#define DATASET_SIZE 50000
#define SEED_VALUE 42u

static int dataset[DATASET_SIZE];

static unsigned int next_value(unsigned int *state)
{
    *state = (*state * 1103515245u) + 12345u;
    return *state;
}

static void build_dataset(void)
{
    unsigned int state;
    int i;

    state = SEED_VALUE;

    for (i = 0; i < DATASET_SIZE; i++)
        dataset[i] = (int)(next_value(&state) % 100000);
}

static void process_dataset(void)
{
    int i;
    int v;

for (i = 0; i < DATASET_SIZE; i++)
{
v = dataset[i];
v = (v * 3) + (v / 7) - (v % 11);
if (v < 0)
v = -v;
dataset[i] = v;
}
}

static unsigned long reduce_checksum(void)
{
unsigned long sum;
int i;

sum = 0;
for (i = 0; i < DATASET_SIZE; i++)
sum = (sum * 131ul) + (unsigned long)dataset[i];

return sum;
}

int main(void)
{
unsigned long checksum;
clock_t t_start, t_end;
clock_t t_build_start, t_build_end;
clock_t t_process_start, t_process_end;
clock_t t_reduce_start, t_reduce_end;

/* TOTAL start */
t_start = clock();

/* BUILD_DATA timing */
t_build_start = clock();
build_dataset();
t_build_end = clock();

/* PROCESS timing */
t_process_start = clock();
process_dataset();
t_process_end = clock();

/* REDUCE timing */
t_reduce_start = clock();
checksum = reduce_checksum();
t_reduce_end = clock();

/* TOTAL end */
t_end = clock();

if (checksum == 0ul)
printf("impossible\n");

/* Required output */
printf("TOTAL seconds: %.6f\n",
(double)(t_end - t_start) / CLOCKS_PER_SEC);
printf("BUILD_DATA seconds: %.6f\n",
(double)(t_build_end - t_build_start) / CLOCKS_PER_SEC);
printf("PROCESS seconds: %.6f\n",
(double)(t_process_end - t_process_start) / CLOCKS_PER_SEC);
printf("REDUCE seconds: %.6f\n",
(double)(t_reduce_end - t_reduce_start) / CLOCKS_PER_SEC);

return 0;
}
