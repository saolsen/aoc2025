#include "aoc.c"

int main(void) {
  Input input = read_input("inputs/day01.txt");

  int dial = 50;
  int num_zeros = 0;

  for (size_t i = 0; i < input.lines_count; i++) {
    char *line = input.lines[i];

    char direction = line[0];
    int distance = atoi(&line[1]);

    switch (direction) {
    case 'R': {
      dial = (dial + distance) % 100;
    } break;
    case 'L': {
      dial = (dial - distance);
      while (dial < 0) {
        dial += 100;
      }
      dial = dial % 100;
    } break;
    default:
      exit(1);
    }
    if (dial == 0) {
      num_zeros++;
    }
  }

  printf("Num zeros: %d\n", num_zeros);

  free_input(&input);
  return 0;
}