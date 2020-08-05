#include <iostream>
//#include <cstdint>
#include <cstring>
#include <byteswap.h>
#include <arpa/inet.h>
#include <string>
float s1(const uint16_t *src)
{
  uint32_t uValue(( ( (uint32_t) src[0] ) << 16 ) + src[1]);
  return *(float*) &uValue;
}
 
float s2(const uint16_t *src)
{
  union U
  {
      uint16_t n[2];     // occupies 8 bytes
      float f; // occupies 4 bytes
  };
  U u;
  u.n[0] = src[1];
  u.n[1] = src[0];
  return u.f;
}
float s3(const uint16_t *src)
{
    float f;
    uint32_t uValue(( ( (uint32_t) src[0] ) << 16 ) + src[1]);
    memcpy(&f,&uValue,sizeof(f));
    return f;
}
float s4(const uint16_t *src)
{
   float f;
   memcpy(&f, &src[1], sizeof(uint16_t));
   memcpy(&f+sizeof(uint16_t), &src[0], sizeof(uint16_t));
   return f;
}
float s5(const uint16_t *src)
{
   float f;
   uint32_t i;
   i = ntohl(bswap_32((((uint32_t)src[0]) << 16) + src[1]));
   memcpy(&f, &i, sizeof(float));
   return f;
}
int main()
{
    union S
    {
      float f;
      uint16_t src[2];
    };
    S s;
    s.src[1]=0x28f6;
    s.src[0]=0x4178;
    std::cout << std::hex << "s1 = " << s1(s.src) << '\n';
    std::cout << std::hex << "s2 = " << s2(s.src) << '\n';
    std::cout << std::hex << "s3 = " << s3(s.src) << '\n';
   // std::cout << std::hex << "s4 = " << s4(s.src) << '\n';
    std::cout << std::hex << "s5 = " << s5(s.src) << '\n';
    std::cout << std::hex << "f = " <<  s.f  << '\n';
    std::string str3;
    str3 = "test";
    std::cout << str3;
    return 0;
}
