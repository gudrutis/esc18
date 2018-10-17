#ifndef Data_h
#define Data_h

#include<cstdint>
#include<vector>
#include<memory>



using Float=float;

enum Quality: uint8_t { bad, loose, strict, tight };

struct Data {

  Data(){}
  // virtual ~Data(){}
  
  Float x,y,z;
  Float vx,vy,vz;
  bool isValid;
  Quality quality;

};

using AOS = std::vector<Data>;
using AOP = std::vector<std::unique_ptr<Data>>;


struct SOA {
  Float *x, *y, *z;
  Float *vx, *vy, *vz;
  bool *isValid;
  Quality *quality;  
};

#endif 
