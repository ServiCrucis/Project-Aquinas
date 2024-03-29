# Universal Polymorphic Proceduralism

## Practical Principles
1. Every procedure must fulfill one objective purpose: if it fulfills multiple purposes, the procedure is evil and must be continuously bifurcated until we are left with a set of procedures that have a single purpose. For example: a procedure that adds two numbers of any kind (real, complex, IEEE754 float, etc.) is single-purpose, but a procedure that adds and subtracts is multi-purpose because subtraction has a different end than addition.

2. The data model is thoroughly and fundamentally symbolic: everything is a symbol, and a symbol contains one or more symbols. A symbol contains state, action, or both, but not neither; and these symbols are constructed via base symbols provided by the language itself. All state is symbolic in nature, as are the actions which can be applied to state. For implementation in numerical contexts, the following rules shall apply:
   1. The memory model shall consist of memory contexts with numerical addressing in [0, N) (N is determined by the objective purpose) and a unique numerical identifier relative to another memory context except for the global memory context which refers to itself as its parent.
   2. Numerical values shall be representable in any numerical base or user-defined format.

3. Everything must be readable:
   1. Everything must be sufficiently documented such that one could, from the documentation alone, reproduce the procedure. This includes the interface's documentation which usually immediately precedes a procedure's header `<return-type> <procedure-name>(<arguments>)`, as well as the comments within the body of the procedure. A line or set of lines requires a comment to explain it if the line(s) do not directly model in themselves some particular action at that point in execution, for example: `i  = 0x5f3759df - ( i >> 1 ); // apply numerically computed constant that finishes the crude invsqrt approximation`.
   2. Extending the documentation rules, everything must be well-named: a procedure should be named according to its purpose; state symbol definitions should be named according to their essences rather than purpose; and state symbol uses in general should be defined according to the purpose defined by the context. In order to be readable to anyone who understands English sufficiently, it must be free grammatical errors; free of abbrvs., I.N.I.T.I.A.L.I.S.M.s, and A[cr]O[ny]M[s]; it must be succinct; should be in the imperative mood; free of articles like 'the', 'a', or 'an'; and have no conjunctions. This ensures that anyone who has proficiency of English (especially a non-native speaker) is capable of reading the code while minimizing the time spent figuring out what some term means.
   3. A single standard must be universally adopted amongst all programmers over permitting varied conventions regardless of historical significance:
      1. State symbol names shall use UpperCamelCase.
      2. State symbol members and uses shall use lowerCamelCase.
      3. Behavior symbol definitions and pointers shall use snake_case.
      4. A symbol is to be named in the singular unless the symbol's essence is plural in nature.
      5. An array of symbols of the same type is to be named in the plural regardless of element count.

## Justifications
_All three rules guarantee optimal productivity by reducing, where possible, all possibilities for human mistakes to occur while facilitating their identification and removal when they occur._

Rule 1 minimizes debugging time by ensuring that every problem can be isolated as to its cause and then solved accordingly, and therefore quickly finding manifestations of human mistakes when they occur.

Rule 2 minimizes the opportunities for human error to cause security-critical bugs and bugs in general while directly modeling reality: all programs necessarily operate on computers, and computers operate on numbers, therefore our programming languages must model this directly, or at minimum, our software implementations within these languages when this is not possible with the language.

Rules 3.1 and 3.2 ensure that every programmer reading the code understands it without looking elsewhere (except where directed to by the documentation as needed).

Rule 3.3 guarantees that each kind of base language symbol according to its respective purpose is easily recognizable when scanning while still looking sufficiently beautiful for morale's sake.
