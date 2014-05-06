#ifndef UTILITY_H
#define UTILITY_H 1

#include <exception>
#include <cassert>

// #define NDEBUG

class Error : public std::exception {
public:
  Error(const char* msg_) : msg(msg_) {}
  const char* what() const noexcept override
    {return msg;}
private:
  const char* msg;
};


#endif /*UTILITY_H*/