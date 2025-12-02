#include "aoc.c"

int main(void) {
  Input input = read_input("inputs/day01.txt");

  int dial = 50;
  int num_zeros = 0;

  for (size_t i = 0; i < input.lines_count; i++) {
    char *line = input.lines[i];

    char direction = line[0];
    int distance = atoi(&line[1]);

    // printf("%i [%c%i] %i\n", dial, direction, distance, num_zeros);

    bool started_at_zero = dial == 0;

    switch (direction) {
    case 'R': {
      dial = (dial + distance);
      num_zeros += dial / 100;
      dial = dial % 100;
    } break;
    case 'L': {
      dial = (dial - distance);
      if (dial == 0) {
        num_zeros++;
      } else if (dial < 0) {
        while (dial < 0) {
          dial += 100;
          if (started_at_zero) {
            // Don't count the zero we started at
            // printf(" no pass through zero\n");
            started_at_zero = false;
          } else {
            // printf(" pass through zero\n");
            num_zeros++;
          }
        }
      }
    } break;
    default:
      exit(1);
    }
  }

  printf("Num zeros: %d\n", num_zeros);

  free_input(&input);
  return 0;
}