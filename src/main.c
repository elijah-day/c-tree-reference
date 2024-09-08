#include "stdio.h"
#include "stdlib.h"
#include "string.h"

typedef struct node_t
{
	char *name;
	int subnode_count;
	struct node_t *subnode;
}
node_t;

void init_node(node_t *node, const char *name)
{
	node->name = calloc(1, sizeof(name));
	strcpy(node->name, name);
	node->subnode = NULL;
	node->subnode_count = 0;
}

void terminate_node(node_t *node)
{
	free(node->name);
	free(node->subnode);
}

void add_subnode(node_t *node, const char *name)
{
	/*
	 * Allocate new memory if there are no existing subnodes under the node.
	 * Otherwise, reallocate existing memory and reassign the subnode pointer.
	 */

	if(node->subnode_count == 0)
	{
		node->subnode = calloc(1, sizeof(node_t));
	}
	else
	{
		node_t *tmp_mem = realloc
		(
			node->subnode,
			(node->subnode_count + 1) * sizeof(node_t)
		);

		/* Realloc appears to handle the freeing of node->subnode. */

		node->subnode = tmp_mem;
		tmp_mem = NULL;
	}

	node->subnode_count += 1;
	init_node(&node->subnode[node->subnode_count - 1], name);
}

void remove_subnodes_recursive(node_t *node)
{
	for(int i = 0; i < node->subnode_count; i++)
	{
		remove_subnodes_recursive(&node->subnode[i]);
	}

	terminate_node(node);
}

void list_subnodes_recursive(node_t *node)
{
	static int depth = 0;

	for(int i = 0; i < depth; i++)
	{
		printf("    ");
	}

	printf("* %s\n", node->name);

	/* Iterate through this node's subnodes, if any, and call this function. */

	for(int i = 0; i < node->subnode_count; i++)
	{
		depth += 1;
		list_subnodes_recursive(&node->subnode[i]);
	}

	depth -= 1;
}

int main(void)
{
	node_t root;
	init_node(&root, "Root");

	add_subnode(&root, "0");
		add_subnode(&root.subnode[0], "0.0");
			add_subnode(&root.subnode[0].subnode[0], "0.0.0");
		add_subnode(&root.subnode[0], "0.1");
			add_subnode(&root.subnode[0].subnode[1], "0.1.0");
			add_subnode(&root.subnode[0].subnode[1], "0.1.1");
	add_subnode(&root, "1");
		add_subnode(&root.subnode[1], "1.0");
		add_subnode(&root.subnode[1], "1.1");

	list_subnodes_recursive(&root);
	remove_subnodes_recursive(&root);

	return 0;
}
