/*
RTTI (Run-Time Type Information)
RTTI allows you to query the type of an object at runtime. It provides mechanisms like dynamic_cast and typeid to determine the actual type of an object and perform type-safe conversions.


Type Casting (static_cast, dynamic_cast, const_cast, reinterpret_cast)
Type casting is the process of converting one type of data to another. C++ provides several casting operators:
• static_cast: Used for implicit conversions that are considered safe by the compiler.
• dynamic_cast: Used for safe downcasting in polymorphic class hierarchies, with runtime type checking.
• const_cast: Used to add or remove const or volatile qualifiers.
• reinterpret_cast: Used for low-level casting between unrelated types, often
considered unsafe.
*/