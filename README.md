# Project Aquinas

The only tools a programmer will ever need:
1. a way to run software
2. a way to make software
3. a way to define software

To run software, you need an execution environment.<br/>
To make software, you need a compiler.<br/>
To define software, you need a programming language.<br/>

What about debugging you ask? 
Well that would be correcting your software's definition;
and that, for the most part, is on you! It'll be facilitated
by the project of course&mdash;don't worry.

Demo you ask? Well it's coming out when it's coming out 
I'm afraid. My life is too insane right now for any
consistent schedules and time estimates. In other words:
it's coming out on God's time.

# Demo Progress as of October 19th, 2023:

## What remains before a demo can be released:

### Allocators (foundation of all state):

1. [x] ~~ImperfectStackUnitAllocator~~
2. [ ] ImperfectUnitAllocator (uses ImperfectStackUnitAllocator, ExistenceTree)
3. [ ] ImperfectCompositeAllocator (uses ImperfectUnitAllocator, ExistenceTree)
4. [ ] PerfectCompositeAllocator (uses ImperfectCompositeAllocator, PerfectMap)

### State Constructs:

1. [ ] BinaryTree
2. [ ] ExistenceTree (uses BinaryTree)
3. [ ] DifferenceTree (uses BinaryTree)
4. [ ] Map, PerfectMap (uses DifferenceTree)
5. [ ] ConversionTree (uses Map)
6. [ ] Idea (a definition entry in a Dictionary)
7. [ ] Object (an instance of a being extending an Idea)
8. [ ] essential ideas (foundation of the Master Dictionary)
9. [ ] MasterDictionary and Dictionary
10. [ ] Language (Idea)
11. [ ] Metalanguage (Idea, species of Language)
12. [ ] ProgrammingLanguage (Idea, species of Language)

### Executors:

1. [ ] Metacompiler (uses everything above)



# Discussion & Hangouts! 
(Complete degenerates will not be tolerated 
and promptly banned!): https://discord.gg/9HzjW85
