#ifndef STDINT_H
#define STDINT_H


#ifndef __UINT64_TYPE__
typedef unsigned long uint64_t; // 64 bit unsigned
#endif

#ifndef __INT64_TYPE__
typedef signed long int64_t; // 64 bit signed
#endif

typedef unsigned char uint8_t;  // 8 bit unsigned
typedef signed char int8_t;     // 8 bit signed
typedef unsigned short uint16_t; // 16 bit unsigned
typedef signed short int16_t;    // 16 bit signed
typedef unsigned int uint32_t;   // 32 bit unsigned
typedef signed int int32_t;      // 32 bit signed

#endif // STDINT_H
