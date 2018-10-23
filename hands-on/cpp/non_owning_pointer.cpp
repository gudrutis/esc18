#include <memory>
#include <iostream>

char* some_api();

int main()
{
  auto* p = some_api();
  std::cout << p << '\n';
  // free(p);
  // delete p;
   delete [] p;
}


#include <cstring>

char* some_api() {
  static char s[] = "Hello, world!";
  return strstr(s, "orl");
}
