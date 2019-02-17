//
// Created by bob on 19-1-14.
//

#ifndef HASHTREE_HCONFIG_H
#define HASHTREE_HCONFIG_H

#define DEBUG

#define FIX_DEPTH 9

#define ARCH 64

#define KEYSIZE 8

#if (ARCH==64)
    #if(KEYSIZE==8)
    typedef long HashMem;
    #elif (KEYSIZE==16)
    typedef struct s{long a[2];} HashMem;
    #endif
#endif


//prime conf
#define PRIMENUM 9
#define PRIMELIST {2,3,5,7,11,13,17,19,23}
#define BITLENLIST {2,2,3,3,4,4,5,5,5}
#define BITMASK { 0x00,};
#define CAPLIST {2,6,30,210,2310,30030,510510,9699690,223092870}
#endif //HASHTREE_HCONFIG_H
