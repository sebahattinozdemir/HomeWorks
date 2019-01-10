#include <stdio.h>

/* 
binary trees are represented as arrays of positive integers
0 means empty node
if a node has an index i, its children are found at indices 
2i+1 for the left child and 2i+2 for the right, 
while its parent (if any) is found at index floor((i-1)/2)
assuming the root has index zero.
*/

/** these are the functions we are asked to implement for the binary tree class **/
/* 
we pass the array (int *tree) and its size (int size) to all functions to make thing easier
we also pass the value that we are looking for (int a)
*/
/*
assume binary search tree
left child values is less than the parent
right child is greater than the parent
*/
int search(int *tree, int size, int a);
/*
same as above but limit your search to 'limit' number of steps
*/
int search_limit(int *tree, int size, int a, int limit);
/* 
this time the array is not sorted, we need to search both children for each node in the tree
find the path from the root to the node with the given value 
save the path in array p, which is allocated with necessary space
return 0 if no path is found, 
something else (maybe the path length) if found
*/
int path(int *tree, int size, int a, int *path);


/** these return child/parent indices **/
int left(int i) {
    return 2*i + 1;
}
int right(int i) {
    return 2*i + 2;
}
int parent(int i) {
    return (i-1)/2;
}


/** search **/

/* 
at each step we search a subtree (left or right)
while checking for the boundaries of the tree
thus we pass the size in each call
*/
int search_help(int *tree, int size, int a, int root){

    if (root >= size || tree[root] == 0){
        printf("root:%d out of boundary\n", root);
        return -1;
    }
    /* check before print, if out of boundaries, tree[root] may cause segfault */
    printf("root:%d value:%d\n", root, tree[root]);

    if (tree[root] == a)
        return root;
    else if (tree[root] > a)
        return search_help(tree, size, a, left(root));
    else
        return search_help(tree, size, a, right(root));
}

int search(int *tree, int size, int a){
    return search_help(tree, size, a, 0);
}

/* without the prints:
int search_help(int *tree, int size, int a, int root){

    if (root >= size)
        return -1;
    else if (tree[root] == a)
        return root;
    else if (tree[root] > a)
        return search_help(tree, size, a, left(root));
    else
        return search_help(tree, size, a, right(root));
}
*/

/** search with limit **/

int search_limit_help(int *tree, int size, int a, int root, int limit){

    if (root >= size || tree[root] == 0){
        printf("root:%d out of boundary\n", root);
        return -1;
    }
    else if (limit == 0){
        printf("reached search limit\n");
        return -1;
    }
    /* check before print, if out of boundaries, tree[root] may cause segfault */
    printf("root:%d value:%d at iter:%d\n", root, tree[root], limit);

    if (tree[root] == a)
        return root;
    else if (tree[root] > a)
        return search_limit_help(tree, size, a, left(root), limit-1);
    else
        return search_limit_help(tree, size, a, right(root), limit-1);

}

int search_limit(int *tree, int size, int a, int limit){
    return search_limit_help(tree, size, a, 0, limit);
}


/** path **/

/* 
this function returns the length of the path (evaluates to true) if it can find a path, 
0 (evaluates to false) otherwise */
int path_help(int *tree, int size, int a, int *p, int root, int level){

    int len = 0;

    /* if we are out of the array without finding the node */
    if (root >= size || tree[root] == 0){
        printf("%*sp:%d out of bounds -> return 0\n", 2*level, "", root);
        return 0;
    }

    printf("%*sp:%d tree[p]:%d at call\n", 2*level, "", root, tree[root]);   
    /* here we use function return value as a condition, we could write as:
    (len = path_help(tree, size, a, p, left(root)) != 0
    */
    if (    /* if we reached the node we are looking for */
            tree[root] == a ||
             /* maybe we can find the node in the left subtree */
            (len = path_help(tree, size, a, p, left(root), level+1)) ||
            /* maybe we can find the node in the right subtree */
            (len = path_help(tree, size, a, p, right(root), level+1)) 
            ){

        int i;
        /* add the current node, increase len and return*/
        p[len++] = root;

        /* just to trace the calls */
        printf("%*sfound node at this path -> return %d\n", 2*level, "", len);
        printf("%*scurrent path\n%*s", 2*level, "", 2*level, "");
        for (i=0; i<len; i++)
            printf("(i:%d v:%d) ", p[i], tree[p[i]]);
        printf("\n");
        /* trace end */

        return len;
    }
    else{
        printf("%*scould not find %d at this branch -> return 0\n", 2*level, "",  a);
        return 0;
    }
}

/* 
after you learn about pointers and memory allocation modify this function
so that it returns the array that contains the path
    instead of getting p as an argument,
    allocate the array in this function then pass it to the helper
    then return p at the end, so that we can use the path in other parts of the program 
*/
int path(int *tree, int size, int a, int *p){
    return path_help(tree, size, a, p, 0, 0);
}


/** main for tests **/

int main(){

    int i, j, v;
    int vs[] = {3, 4, 12, 21};
    /*
            10               
            / \       
           /   \      
          /     \     
         /       \    
        4        16       
       / \       / \   
      /   \     /   \  
     2    6    14   18   
    / \  / \  / \   / \
   0  0  0 8 12 0   0 20
    */
    int bst[] = {10, 4, 16, 2, 6, 14, 18, 0, 0, 0, 8, 12, 0, 0, 20};
    int bst_size = 15;
    
    printf("\n\n*** Search ***\n\n");

    for (j=0; j<4; j++){
        v = vs[j];
        i = search(bst, bst_size, v);
        if (i != -1){
            printf("# Found %d at %d\n\n", v, i);
        }
        else{
            printf("# Could not find %d\n\n", v);
        }
    }

    printf("\n\n*** Search with Limit ***\n\n");

    for (j=0; j<4; j++){
        v = vs[j];
        i = search_limit(bst, bst_size, v, 2);
        if (i != -1){
            printf("# Found %d at %d\n\n", v, i);
        }
        else{
            printf("# Could not find %d\n\n", v);
        }
    }

    printf("\n\n*** Path ***\n\n");

    for (j=0; j<4; j++){
        int p[5] = {0};
        int len;
        v = vs[j];
        printf("### Searching a path to %d\n", v);
        len = path(bst, bst_size, v, p);
        if (len){
            int i;
            printf("### Found a path to %d\n", v);
            for (i=len-1; i>=0; i--)
                printf("i:%d v:%d\n", p[i], bst[p[i]]);
            printf("\n");
        }
        else{
            printf("### No path found to %d\n\n", v);
        }
    }


    return 0;
}
