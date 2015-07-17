#include "../../TREE/tree.h"

int main()
{
    graph_t *graph;
    GVC_t *gvc;
    gvc = gvContext();
    /* parse command line args - minimally argv[0] sets layout engine */
    /* Create a simple digraph */
    graph = agopen("graph", Agdirected, NULL);

    int ls[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 };
    node *root = tree_build(ls, 31);
    node *newtree = tree_mirror(root);
    tree_print(graph, NULL, newtree);
    tree_free(root);
    tree_free(newtree);

    /* Compute a layout using layout engine from command line args */
    gvLayout(gvc, graph, "dot");
    /* Write the graph according to -T and -o options */
    gvRenderFilename(gvc, graph, "png", "demo1.png");
    /* Free layout data */
    gvFreeLayout(gvc, graph);
    /* Free graph structures */
    agclose(graph);
    /* close output file, free context, and return number of errors */
    return (gvFreeContext(gvc));
}
