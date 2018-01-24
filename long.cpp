#include <iostream>

using namespace std;

int main() {
  int c = 0, i = 0;
  while (i < 500000000) {

    if (i & 1) ++c;
  }

  cout << "long process DONE";
  // system();
  return 0;
}


