# Binary Trees

# Physical Design:

2-ary tree or *bi*nary tree where each node has exactly two edges and one parent except: the origin node which has a logical parent of itself for computational purposes; and terminal nodes which have no child nodes.

# Implementation:

*********************************************************************************************************************************************************************************************DISCLAIMER: THE FOLLOWING NEEDS REVISION BUT CAN BE USED AS-IS:*********************************************************************************************************************************************************************************************

```c
struct binary_tree_node {
	// type is implicit: just have explicit terminal nodes. 
	// The rest are non-terminal.
	// enum binary_tree_node_type type;

	// depth info is superfluous: stored on binary_tree.
	// uint8_t depth;
	union {
		void *data;
		struct binary_tree_node *nodes;
	};
};

struct binary_tree {
	uint8_t depth;
	// either a single leaf array, or many branches
	union {
		void *data;
		struct binary_tree_node *nodes;
	};
	// unary encoding of tree collocations
	// the digit place is a unique level
	// a 1 denotes a level having collocated levels on the node.
	// a 0 denotes a level that has been collocated.
	// all 0 levels are located on the next level marked with a 1.
	//
	// since we can support [1, 256]-bit identifiers to map, we need a variable
	// number of bits.
	uint8_t tree_collocations[];
};
```

## Memory Management:

(some old implementation notes I left for myself:)

1. Nodes separate from metadata.
2. Memory context for each node size for which nodes are allocated to.
3. When collocating nodes, promote to next size memory context