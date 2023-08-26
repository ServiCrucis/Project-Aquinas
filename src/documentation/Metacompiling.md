# Metacompiling

# Metaphysical Design:

## Input:

1. A token string operand
2. A token string dictionary

## Output:

1. A token string output

## Objective Purpose:

The converting of token string operands as-by a whatness to radical token strings; or vice versa.

## Physical Design:

### Token Strings:

The operands are directed, potentially cyclic graphs representing a genus of possible token string inputs where:

1. each node represents a single possible token at a given time according to a unique token string.
2. there is either a single edge leading to this node; no edges leading to this node (a property unique to the origin node, or an error in the graph’s implementation); or at most two edges leading back to this node in which case one of these is a mode of representing repeating token strings, while the other edge is connected to the origin of the directed graph.
3. each unique path from origin to terminal node is a unique token string and vice versa.

### Converting:

The `convert` procedure is very simple and consists of merely traversing the dictionary using the operand: the current token taken from the operand denotes which edge should be taken relative to the current node in the dictionary.

Traversal of the dictionary continues until we’ve either reached a terminal node in the dictionary, or a terminal node in the operand: if either a terminal node in the operand but not in the dictionary, or if the converse of this predicate, then signal an illegal converting state with general cause `premature_terminal_node` and either the dictionary or the operand itself as the specific cause as-by the respective condition, then halt the procedure.

It is up to the implementation to determine whether any output is determined from the current non-terminal node, or strictly from terminal nodes. With such an implementation, it becomes possible to implement converting resumption, and incomplete results.

The implementation, as may be guessed, is capable of having arbitrarily great complexity, or great simplicity, depending on the perfection of the implementation with respect to the particular objective or subjective purpose to be implemented.

## Implementation:

The graphs can be partially or wholly represented implicitly as a procedure, or explicitly as a graph implementation; or a combination of both of these.