# Universal Polymorphic Proceduralism

## Practical Principles
1. Every procedure has one purpose: if it fulfills multiple purposes, the procedure is evil and must be continuously bifurcated until we are left with a set of procedures that have a single purpose. For example: a procedure that adds two numbers of any kind (real, complex, IEEE754 float, etc.) is single-purpose, but a procedure that adds and subtracts is multi-purpose because subtraction has a different end than addition.

2. The data model is thoroughly and fundamentally numerical: everything is a construct, and a construct contains one or more constructs. A construct contains state, behavior, or both, but not neither; and these constructs are constructed via atomic constructs provided by the language itself. All state is numerical in nature, as are the behaviors which can be applied to state.
   2.1.1. The memory model shall consist of memory contexts with numerical addressing in [0, +\infty) and a unique numerical identifier relative to another memory context except for the global memory context which refers to itself as its parent.
   2.1.2. Numerical values shall be representable in any user-defined format.

3. Everything must be readable:
   1. Everything must be sufficiently documented such that one could, from the documentation alone, reproduce the procedure. This includes the interface's documentation which usually immediately precedes a procedure's header `<return-type> <procedure-name>(<arguments>)`, as well as the comments within the body of the function. A line or set of lines requires a comment to explain it if the line(s) do not directly model in themselves some particular behavior at that point in execution, for example: `return x << n; // multiply by power of two`.
   2. Extending the documentation rules, everything must be well-named: a procedure should be named according to its purpose; state construct definitions should be named according to their essences rather than purpose; and state construct utilizations should be defined according to their purpose according to the context. In order to be readable to anyone who understands English sufficiently, it must be free grammatical errors; free of abbrvs. and a.c.r.o.n.y.m.s.; it must be succinct; should be in the imperative mood; free of articles like 'the', 'a', or 'an'; and have no conjunctions. This ensures that anyone who has proficiency of English is capable of reading the code while minimizing the time spent figuring out what the meaning of the name is.
   3. A single standard must be universally adopted amongst all programmers over permitting varied conventions regardless of historical significance:
      1. State construct names shall use UpperCamelCase.
      2. State construct members and utilizations shall use lowerCamelCase.
      3. Behavior construct definitions and pointers shall use snake_case.

## Justifications
_All three rules guarantee optimal productivity by reducing, where possible, all possibilities for human mistakes to occur while facilitating their identification and removal when they occur._

Rule 1 minimizes debugging time by ensuring that every problem can be isolated as to its cause and then solved accordingly, and therefore quickly finding manifestations of human mistakes when they occur.

Rule 2 minimizes the opportunities for human error to cause security-critical bugs and bugs in general while directly modeling reality: all programs necessarily operate on computers, and computers operate on numbers, therefore our programming languages must model this directly, or at minimum, our software implementations within these languages when this is not possible with the language.

Rules 3.1 and 3.2 ensure that every programmer reading the code understands it without looking elsewhere (except where directed to by the documentation as needed).

Rule 3.3 guarantees that each kind of atomic language construct according to its respective purpose is easily recognizable when scanning while still looking sufficiently beautiful for morale's sake.