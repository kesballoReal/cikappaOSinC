
// stdint.h
// Author: kesballoReal

#ifndef STDINT_H
#define STDINT_H

#define NULL ((void *)0)

#ifndef __UINT64_TYPE__
typedef unsigned long uint64_t; 
#endif

#ifndef __INT64_TYPE__
typedef signed long int64_t; 
#endif

typedef unsigned char uint8_t; 
typedef signed char int8_t;     
typedef unsigned short uint16_t; 
typedef signed short int16_t;    
typedef unsigned int uint32_t;   
typedef signed int int32_t;      

typedef unsigned long uintptr_t;

#endif // STDINT_H
