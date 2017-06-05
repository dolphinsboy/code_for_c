#include "trace.h"

int foo() {
  return 2;
}

int bar() {
  return 1;
}

int main(int argc, char** argv) {

  printf("foo=%d bar=%d\n", foo(), bar());

}
