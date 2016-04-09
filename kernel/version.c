#include <stdint.h>

char* _kernel_version_format = "%d.%d.%d-%s";

char* __kernel_name          = "zykernel";
char* __kernel_code_name     = "development";

int   __kernel_version_major = 0;
int   __kernel_version_minor = 0;
int   __kernel_version_lower = 0;

char* __kernel_build_date = __DATE__;
char* __kernel_build_time = __TIME__;

#if (defined(__GNUC__) || defined(__GNUG__)) && !(defined(__clang__) || defined(__INTEL_COMPILER))
# define COMPILER_VERSION "gcc " __VERSION__
#elif (defined(__clang__))
# define COMPILER_VERSION "clang " __clang_version__
#else
# define COMPILER_VERSION "unsupported compiler"
#endif

char* __kernel_compiler_version = COMPILER_VERSION;
