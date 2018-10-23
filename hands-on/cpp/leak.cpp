
int* factory();

// "still reachable"
auto g = factory();

int main()
{
  // "definitely lost"
  auto t = factory();
  delete t;
  delete g;
}

int* factory()
{
  return new int;
}
