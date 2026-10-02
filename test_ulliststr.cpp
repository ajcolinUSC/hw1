#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "ulliststr.h"

// Use this file to test your ulliststr implementation before running the test
// suite

using namespace std;

void printit(ULListStr &d) {
  cout << "size=" << d.size() << " [ ";
  for (size_t i = 0; i < d.size(); i++) {
    cout << d.get(i) << " ";
  }
  cout << "]" << endl;
}

int main(int argc, char *argv[]) {
  ULListStr dat;

  cout << "empty? " << dat.empty() << " (want 1)" << endl;
  cout << "size? " << dat.size() << " (want 0)" << endl;

  dat.pop_back();
  dat.pop_front();
  cout << "still empty? " << dat.empty() << " (want 1)" << endl;

  dat.push_back("7");
  dat.push_front("8");
  dat.push_back("9");
  printit(dat);
  cout << "front=" << dat.front() << " (want 8)" << endl;
  cout << "back=" << dat.back() << " (want 9)" << endl;

  dat.set(1, "seven");
  cout << "get(1)=" << dat.get(1) << " (want seven)" << endl;

  try {
    dat.get(99);
    cout << "BAD: no throw" << endl;
  } catch (std::invalid_argument &e) {
    cout << "good, threw on get(99)" << endl;
  }

  dat.clear();
  cout << "after clear size=" << dat.size() << " (want 0)" << endl;

  for (int i = 0; i < 25; i++) {
    stringstream ss;
    ss << i;
    dat.push_back(ss.str());
  }
  cout << "size=" << dat.size() << " (want 25)" << endl;
  cout << "front=" << dat.front() << " (want 0)" << endl;
  cout << "back=" << dat.back() << " (want 24)" << endl;
  cout << dat.get(0) << " " << dat.get(9) << " " << dat.get(10) << " "
       << dat.get(19) << " " << dat.get(20) << " " << dat.get(24)
       << " (want 0 9 10 19 20 24)" << endl;

  // pop back
  while (!dat.empty()) {
    dat.pop_back();
  }
  cout << "size=" << dat.size() << " (want 0) empty=" << dat.empty() << endl;

  for (int i = 0; i < 25; i++) {
    stringstream ss;
    ss << i;
    dat.push_front(ss.str());
  }
  cout << "size=" << dat.size() << " (want 25)" << endl;
  cout << "front=" << dat.front() << " (want 24)" << endl;
  cout << "back=" << dat.back() << " (want 0)" << endl;

  // pop front
  while (!dat.empty()) {
    dat.pop_front();
  }
  cout << "size=" << dat.size() << " (want 0)" << endl;

  // front and back
  for (int i = 0; i < 15; i++) {
    stringstream ss;
    ss << "b" << i;
    dat.push_back(ss.str());
    stringstream ss2;
    ss2 << "f" << i;
    dat.push_front(ss2.str());
  }
  cout << "size=" << dat.size() << " (want 30)" << endl;
  cout << "front=" << dat.front() << " (want f14)" << endl;
  cout << "back=" << dat.back() << " (want b14)" << endl;
  printit(dat);

  for (int i = 0; i < 10; i++) {
    dat.pop_front();
    dat.pop_back();
  }
  cout << "size=" << dat.size() << " (want 10)" << endl;
  printit(dat);

  dat.push_back("tail");
  dat.push_front("head");
  cout << "front=" << dat.front() << " back=" << dat.back()
       << " (want head tail)" << endl;
  printit(dat);

  return 0;
}
