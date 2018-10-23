#include <memory>
using SomeType = int;

SomeType* factory();
void do_something(SomeType*);

int main()
{
  std::unique_ptr<int> t { factory() };

   try {

  do_something(t.get());

  // delete t;

   } catch (...) {
   }
}

SomeType* factory()
{
  return new SomeType{};
}

void do_something(SomeType*)
{
  throw 1;
}
