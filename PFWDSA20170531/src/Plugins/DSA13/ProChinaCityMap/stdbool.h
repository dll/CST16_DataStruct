/*

* ISO C Standard: 7.16 Boolean type and values

*/

#ifndef _STDBOOL_H

#define _STDBOOL_H

#ifndef __cplusplus

#define bool _Bool

#define true 1

#define false 0

#else 
	/*__cplusplus */
	/*Supporting in C++ is a GCC extension. */

#define _Bool bool

#define bool bool

#define false false

#define true true

#endif 
	/*__cplusplus */
	/*Signal that all the definitions are present. */

#define __bool_true_false_are_defined 1

#endif
/*stdbool.h */
