#include <stdlib.h>
#include "ia.h"

int playerIA() {
  return (rand() % NB_COLUMN) + 1;
}
