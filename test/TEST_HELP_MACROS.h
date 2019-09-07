#ifndef TEST_HELPER_MACROS
#define TEST_HELPER_MACROS

#define ZERO_MEM(ARG)\
for(int i = 0; i<sizeof(ARG)/sizeof(ARG[0]); i++){\
  ARG[i] = 0;\
}

#endif
