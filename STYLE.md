# Zylix Coding Style
To make development between authors sane and to easily identify different parts of code, the following coding style has been developed. Having a consistent coding style makes the project easier to read and maintain. Code may be rejected for not following this style. All code will be in American English and no other language, except in comments. If you do make comments in other languages, translate it to English as best you can. Exceptions can be made for use in internationalizing strings and such.

This style guide is in development, style guidelines will be added, but ones already present are set in stone.

## Files
Don't capitalize file names, and separate words in the name with underscores. Please submit files with ```LF``` line endings. Non-Unix line endings will be rejected. Please be aware of this if you are using Cygwin, it defaults to ```CRLF``` endings.

Don't put editor mode lines or other editor specific code in files, some people have their own code formatting preferences, and yours shouldn't supersede them. Configure your editor globally or just deal with it.

## C Coding Style
The Zylix coding style is quite different from the normal C style you'll find in the standard library. As a quick reference:
* Use spaces instead of tabs.
* Code is formatted to appear correct at tab size 4.
* Always put a return statement, even if the function is ```void```.
* Use Pascal Case for function naming (similar to Camel Case but with the first letter also capitalized).
* Variable names are delimited by underscores and never capitalized.
* Opening brackets are on the same line and closing brackets on their own line.

### Brackets
For function definitions opening curly brackets are to be placed on the same line as their associated function or statement. Closing brackets are to be on their own line.
```
int SomeFunction(int some_argument) {
    return some_argument + 2;
}
```
For if statements, only use curly brackets if there is only one statement. If that if statement also includes an else statements, use brackets. Else statements are to be placed on the same line as the closing bracket of the if statement.
```
if(condition_flag == 2)
    DoSomethingElse();

if(condition_flag == 1) {
    DoSomething();
} else {
    DoSomethingElse();
}
```

Initializer lists are defined as follows:
```
unsigned int some_array[] = {
    some,
    thing,
    etc,
};
```

### Function Naming
Please make function names as descriptive as possible. Since the kernel has it's own minimal implementation of the standard library, it keeps the function names there the same. All original functions are to be declared in "Pascal Case", with any acronyms capitalized.
```
void PrintGNU() {
    printf("GNU's not Unix!");
}
```
Do not abbreviate function names, if your function deals with a string, name it ```DoThisToString```, not ```DoThisToStr```. Make them clear.
```
/* Do this. */
char* StringTokenize(char* string, const char* deliminator) {
    Good();
}

/* Don't do this. */
char *strtok(char *str, const char *delim) {
    Bad();
}
```

### Variable Naming
Please make variable names as descriptive as possible. Variable names are always under-cased, and words are separated by underscores.

```
int good_name;
int badname;
int VeryBadName;
int Whatareyoudoing;
int pleaseDontDoThis;
```

Structures that are typedefed must be suffixed with ```_s``` and their typedef must be suffixed with ```_t```.

### Spacing
All source code is to be spaced with spaces, not tabs and be 4 spaces. Any source code submitted with tabs will be rejected. Most competent editors have the option to either convert tabs to spaces on save or treat 4 spaces as a tab. Code should be fit within 127 characters, with an exception to comments. The examples in this section are what not to do.

Function names will not have a space between the name and argument parentheses.
```
void SomeFunction ();
```
Don't leave spaces around expressions in parentheses.
```
size = sizeof( struct file );
```
Functions that return a pointer or variables and data involving pointers, the ```*``` character is preferred to be next to the type of the definition. For example:
```
char* string_pointer;
void* GetAVoidPointer();
```
Use one space around each side of the binary and ternary operators:
```
=  +  -  <  >  *  /  %  |  &  ^  <=  >=  ==  !=  ?  : +  -
```
No space around unary operators:
```
&  *  ~  !  sizeof  typeof  alignof  __attribute__  defined
```
No space around unary increment and decrement operators:
```
variable++;
variable--;
--variable;
--variable;
```
No space around the ```.``` and ```->``` structure member operators.

Don't be stingy about breaking up sections of code so they are easier to understand.
```
int MultiplyTwoValues(int a, int b) {
    if(a == 0) {
        return 0;
    }

    if(b == 0) {
        return 0;
    }

    return a * b;
}
```

### Comments
Comments use the ```/* */``` style.

If commentating what a specific line of code does, put it on the line above.
```
void SomeFunction() {
    /* Define an integer with the value of 0. */
    int test_number = 0;
    /* Add 1 + 2 and set test_number to that value. */
    test_number = AddTheseNumbers(1, 2);
    /* Check for presence of aliens with our magic number 5. */
    if(test_number == 5) {
        /* Do something. */
        DoSomething();
    }
}
```
Multi-line comments use this style.
```
/**
 * This function adds two numbers together.
 */
 void SomeFunction() {
     int test_number = 0;
     test_number = AddTheseNumbers(1, 2);
     if(test_number == 5) {
         DoSomething();
     }
 }
```

### Macros
Macros should be defined in All-Caps always.
```
#define GOOD_MACRO
#define Bad_Macro
#define EvenWorse
#define please_dont_do_this
```

Try to avoid multi-statement macros, they are much better as an actual function. Should you find their use necessary, multi-statement macros should be surrounded in a ```do { } while(0)``` loop.
```
#define GOOD_MACRO(x)    \
        do {
            x = x + 8;
        } while(0)
```

Don't use macros that break control flow. This is very bad. While it looks like this macro is a function call, the ```return``` statement actually returns the "calling" function. This can cause very hard to find bugs.
```
#define I_AM_AN_EVIL_PERSON(x)    \
        do {
            x = x + 8;
            return;
        } while(0)
```

Multi-level macros will have a space between the ```#``` and the operation of the macro. Put one space for each level you are in the macro. If the macro is an ```#ifndef``` or ```#ifdef``` put a comment at the end of the associated ```#endif``` of the name of the macro.
```
#ifndef HAVE_SOME_FUNC
# ifdef __CLANG__
#  define SomeFunc ClangSomeFunc
# else
#  define SomeFunc GCCSomeFunc
# endif /* __CLANG__ */
#endif /* HAVE_SOME_FUNC */
```

All header files will have ```#include``` guards. The ```#include``` guards will have the name of the header file prefixed and suffixed with a double underscore. Also make sure to put a comment at the ```#endif``` of the file name. This is included for compatibility reasons, even if most modern compilers are not affected by this.
```
#ifndef __EXAMPLE_HEADER_H__
#define __EXAMPLE_HEADER_H__

void SomeFunction();

#endif /* __EXAMPLE_HEADER_H__ */
```

### Inline Functions
Use the ```inline``` keyword sparingly. Unless you know what you're doing, it just increases compile size while doing nothing for speed. If it has more than one use, it shouldn't be inline.

### Inline Assembly
In architecture specific code, it may be necessary to use inline assembly to interact with and access the hardware. However, for code that is platform independent do not use assembly. Consider adding a new function prototype to the headers in the ```include/arch``` directory and interfacing with hardware specific code in ```/arch/your_arch_here```. When writing inline assembly functions, put each instruction in a separate quote on a newline, and end each string with ```\n\t``` to properly format it in the assembly output. Large, complex pieces of assembly should go in their own separate assembly ```name.s``` file, with corresponding functions defined in C header files.

```
___asm___ ___volatile___(
    "mov $0x10, %eax\n\t"
    "mov %eax, %edx"
    : /* Outputs */ : /* Inputs */ : /* Clobbers */
);
```

As we are using the C99 standard, all inline assembly is defined with the ```___asm___``` keyword, and must be followed by the ```___volatile___``` keyword. The GNU compiler may try to optimize away inline assembly if it believes it can do so without any side effects. So always put the ```___volatile___``` even if you know the compiler will not optimize it away.

## Assembly Coding Style
Assembler is in GNU syntax style.

### Function Naming
Function names in Assembler are Pascal Case (similar to Camel Case but with the first letter also capitalized).
