#ifndef Std
#define Std
typedef unsigned char 			u8;
typedef signed char 			s8;
typedef unsigned short int	    u16;
typedef signed short int 		s16;
typedef unsigned long int 		u32;
typedef signed long int 		s32;
typedef float 					f32;
typedef double 					f64;
typedef long double 			f128;

#define STD_TYPES_OK            1 
#define STD_TYPES_NOK           0

#define NULL			    ((void*)0) // address of 0 , duo to common of complilers will not write in this address

#endif
