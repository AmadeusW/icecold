# Development Log

## Forward declarations
If I need to declare a pointer to an object, I don't need to include its header into my header.
I can just declare `class ClassName;` and compiler will know which size to allocate for pointers to `ClassName`
Specifically, the compiler needs to know that `ClassName` is a class and not a struct.

I need to include object's header only when I actually need to know the implementation,
e.g. in the implementation file or when declaring a descendant class.