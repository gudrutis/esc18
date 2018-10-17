#include<random>
#include<vector>
#include<cstdint>
#include<algorithm>
#include<iostream>
#include<cassert>

#include<chrono>

#include "memory_usage.h"

auto start = std::chrono::high_resolution_clock::now();

uint64_t maxLive=0;

void stop(const char * m) {
  auto delta = std::chrono::high_resolution_clock::now()-start;
  maxLive= std::max( maxLive, memory_usage::totlive() );
  std::cout << m;
  std::cout << " elapsted time (ms) " << std::chrono::duration_cast<std::chrono::milliseconds>(delta).count() << std::endl;
  std::cout << "allocated so far " << memory_usage::allocated();
  std::cout << " deallocated so far " << memory_usage::deallocated() << std::endl;
  std::cout << "total / max live " << memory_usage::totlive() << ' ' << maxLive << std::endl;

  start = std::chrono::high_resolution_clock::now();
}

constexpr int NG=100000;
constexpr int ME=80;

std::mt19937 reng;
std::poisson_distribution<int> aGen(NG);
std::poisson_distribution<int> bGen(ME);


class Generator {
public:

  void generate() {
    // generate ng groups
    ng = aGen(reng);

    // for each group generate elements
    int ne[ng];
    totElements=0;
    for(int i=0;i<ng;++i) totElements += (ne[i]=bGen(reng));
  }


  int group(uint32_t i) const {
    i = i%totElements;
    i = i%ng + (i/7)%ng; 
    return i%ng;
    
  }

  // return in which subgroup of "g" "i" belongs
  int split(uint32_t g, uint32_t i) const {
    return  (g%1014) ? (i%3)/2 : 0;  
      
  }

  int nElements() const {
    return totElements;
  }
  
 private:
  int ng;
  int totElements;
  
  
};



Generator generator;

#include<unordered_map>
void one(bool doprint) {
 if (doprint) stop("before generation");

 generator.generate();

 auto ntot = generator.nElements();

  if (doprint) stop("aftert generation");

  // here find the groups
  std::unordered_map<int,int> count;
  for (int i=0;i<ntot;++i) ++count[generator.group(i)];

  
  // and then split them
  

 if (doprint) stop("end of algo");
 
}


int main() {

  one(true);
  stop("\nafter call: ");

  for (int i=0; i<20; ++i) {
    one(false);
    // stop("after call");
  }
  stop("\nafter loop in main: ");

  one(true);

  stop("\nat the end: ");

  
  return 0;

}





