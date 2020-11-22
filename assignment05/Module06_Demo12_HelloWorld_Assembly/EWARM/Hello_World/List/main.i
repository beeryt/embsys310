






 

 
 

 

















 

  #pragma system_include

 
 

 

  #pragma system_include














 


 
 


  #pragma system_include

 



 

 

 

 
#pragma rtmodel = "__dlib_version", "6"

 


 



























 


  #pragma system_include

 
 
 


  #pragma system_include

 

 

 

 

   

 
 


   #pragma system_include






 




 


 


 


 

 


 

 

 

 

 

 

 

 

 















 



















 











 























 





 



 










 














 













 








 













 













 















 











 








 








 






 





 












 





 













 






 


   


  







 







 




 






 




 




 













 

   




 







 







 







 










 





 

















 


 


 













 

   


 


 



 

 

 
  typedef unsigned int _Wchart;
  typedef unsigned int _Wintt;

 

 
typedef unsigned int     _Sizet;

 
typedef signed char   __int8_t;
typedef unsigned char  __uint8_t;
typedef signed short int   __int16_t;
typedef unsigned short int  __uint16_t;
typedef signed int   __int32_t;
typedef unsigned int  __uint32_t;
   typedef signed long long int   __int64_t;
   typedef unsigned long long int  __uint64_t;
typedef signed int   __intptr_t;
typedef unsigned int  __uintptr_t;

 
typedef struct _Mbstatet
{  
    unsigned int _Wchar;   
    unsigned int _State;   

} _Mbstatet;

 

 
  typedef struct __va_list __Va_list;


    typedef struct __FILE _Filet;

 
typedef struct
{
    long long _Off;     
  _Mbstatet _Wstate;
} _Fpost;


 

 
  
   
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Locksyslock_Malloc(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Locksyslock_Stream(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Locksyslock_Debug(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Locksyslock_StaticGuard(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlocksyslock_Malloc(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlocksyslock_Stream(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlocksyslock_Debug(void);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlocksyslock_StaticGuard(void);

      _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Lockfilelock(_Filet *);
      _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlockfilelock(_Filet *);

  typedef void *__iar_Rmtx;

  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Initdynamiclock(__iar_Rmtx *);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Dstdynamiclock(__iar_Rmtx *);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Lockdynamiclock(__iar_Rmtx *);
  _Pragma("object_attribute = __weak") __intrinsic __nounwind void __iar_Unlockdynamiclock(__iar_Rmtx *);

  






 





    #pragma no_bounds
    __intrinsic __nounwind void __aeabi_assert(char const *, char const *, int);
  #pragma no_bounds
  __intrinsic __nounwind int  __iar_ReportAssert(const char *, const char *,
                                       const char *, const char *);
  _Pragma("object_attribute = __weak")
  __intrinsic __nounwind void __iar_EmptyStepPoint(void);


    
 







 


void swap_pointers(void** ptrA, void** ptrB);       
int divAsm(int a);                                  
void swapCharsAsm(char a, char b);                  
void swapPointersAsm(void** ptrA, void** ptrB);     


int problem1_main();
int hello_world(); 
int problem3_main();
int problem4_main();



int main() {
    return hello_world(); 
}

void swap_pointers(void** ptrA, void** ptrB) {
    void* tmp = *ptrA;
    *ptrA = *ptrB;
    *ptrB = tmp;
}

int problem1_main() {
    int A = 1;
    int B = 2;
    int *ptrA = &A;
    int *ptrB = &B;

    int *originalA = ptrA;
    int *originalB = ptrB;

    swap_pointers((void*)&ptrA, (void*)&ptrB);

    ((ptrA != ptrB) ? (void) 0 : (__aeabi_assert("ptrA != ptrB", "C:\\Users\\Carl\\Desktop\\UW_Workspace\\embsys310\\assignment05\\main.c", 57), (__iar_EmptyStepPoint())));
    ((A == *ptrB) ? (void) 0 : (__aeabi_assert("A == *ptrB", "C:\\Users\\Carl\\Desktop\\UW_Workspace\\embsys310\\assignment05\\main.c", 58), (__iar_EmptyStepPoint())));
    ((B == *ptrA) ? (void) 0 : (__aeabi_assert("B == *ptrA", "C:\\Users\\Carl\\Desktop\\UW_Workspace\\embsys310\\assignment05\\main.c", 59), (__iar_EmptyStepPoint())));
    ((originalA == ptrB) ? (void) 0 : (__aeabi_assert("originalA == ptrB", "C:\\Users\\Carl\\Desktop\\UW_Workspace\\embsys310\\assignment05\\main.c", 60), (__iar_EmptyStepPoint())));
    ((originalB == ptrA) ? (void) 0 : (__aeabi_assert("originalB == ptrA", "C:\\Users\\Carl\\Desktop\\UW_Workspace\\embsys310\\assignment05\\main.c", 61), (__iar_EmptyStepPoint())));
    return 0;
}

int problem2_main() {
    int original = 54321;
    int expected = original / 2;

    int actual = divAsm(original);

    ((54321 == original) ? (void) 0 : (__aeabi_assert("54321 == original", "C:\\Users\\Carl\\Desktop\\UW_Workspace\\embsys310\\assignment05\\main.c", 71), (__iar_EmptyStepPoint())));
    ((actual == expected) ? (void) 0 : (__aeabi_assert("actual == expected", "C:\\Users\\Carl\\Desktop\\UW_Workspace\\embsys310\\assignment05\\main.c", 72), (__iar_EmptyStepPoint())));
    return 0;
}

int problem3_main() {
    return 0;
}

int problem4_main() {
    return 0;
}
