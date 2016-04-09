#ifndef __STDBOOL_H__
#define __STDBOOL_H__

#ifndef __cplusplus

#define bool    _Bool
#define true    1
#define false   0

#else /* __cplusplus */

/* Supporting _Bool in C++ is a GCC extension.  */
#define _Bool   bool

#if __cplusplus < 201103L
/* Defining these macros in C++98 is a GCC extension.  */
#define bool    bool
#define false   false
#define true    true
#endif

#endif /* __cplusplus */

/* Signal that all the definitions are present.  */
#define __bool_true_false_are_defined   1

#endif /* __STDBOOL_H__ */