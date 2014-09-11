#include <stdio.h>
#include <stdlib.h>


/* a shade under 128 MB */
#define LOTS_O_RAM 120011084

void *squeal() {
  perror("squee! ");
  exit(-1);
}

#ifdef EMSCRIPTEN
int memhog_main(const int argc, char * const argv[])
#else
int main(int argc, char **argv)
#endif
{
  void *piggy = (void*)(malloc(LOTS_O_RAM) || squeal());
  fprintf(stderr, "oink oink %d @ %p oink", LOTS_O_RAM, piggy);
  free(piggy);
  return 0;
}
