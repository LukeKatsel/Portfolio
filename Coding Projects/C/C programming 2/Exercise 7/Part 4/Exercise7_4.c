/* tree.h -- binary search tree                          */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAXITEMS 300
#define SLEN 100

/* redefine Item as appropriate */
typedef struct item
{
    char word[SLEN];                    
    int occurs;                                               // changed to int to hold the number of it occurs
} Item;



typedef struct trnode
{
    Item item;
    struct trnode * left;  /* pointer to right branch  */
    struct trnode * right; /* pointer to left branch   */
} Trnode;

typedef struct tree
{
    Trnode * root;         /* pointer to root of tree  */
    int size;              /* number of items in tree  */
} Tree;

typedef struct pair {
    Trnode * parent;
    Trnode * child;
} Pair;


/* function prototypes */

/* operation:      initialize a tree to empty          */
/* preconditions:  ptree points to a tree              */
/* postconditions: the tree is initialized to empty    */
void InitializeTree(Tree * ptree);

/* operation:      determine if tree is empty          */
/* preconditions:  ptree points to a tree              */
/* postconditions: function returns true if tree is    */
/*                 empty and returns false otherwise   */
bool TreeIsEmpty(const Tree * ptree);

/* operation:      determine if tree is full           */
/* preconditions:  ptree points to a tree              */
/* postconditions: function returns true if tree is    */
/*                 full and returns false otherwise    */
bool TreeIsFull(const Tree * ptree);

/* operation:      determine number of items in tree   */
/* preconditions:  ptree points to a tree              */
/* postconditions: function returns number of items in */
/*                 tree                                */
int TreeItemCount(const Tree * ptree);

/* operation:      add an item to a tree               */
/* preconditions:  pi is address of item to be added   */
/*                 ptree points to an initialized tree */
/* postconditions: if possible, function adds item to  */
/*                 tree and returns true; otherwise,   */
/*                 the function returns false          */
bool AddItem(const Item * pi, Tree * ptree);

/* operation: find an item in a tree                   */
/* preconditions:  pi points to an item                */
/*                 ptree points to an initialized tree */
/* postconditions: function returns true if item is in */
/*                 tree and returns false otherwise    */
bool InTree(const Item * pi, const Tree * ptree);

/* operation:      delete an item from a tree          */
/* preconditions:  pi is address of item to be deleted */
/*                 ptree points to an initialized tree */
/* postconditions: if possible, function deletes item  */
/*                 from tree and returns true;         */
/*                 otherwise the function returns false*/
bool DeleteItem(const Item * pi, Tree * ptree);

/* operation:      apply a function to each item in    */
/*                 the tree                            */
/* preconditions:  ptree points to a tree              */
/*                 pfun points to a function that takes*/
/*                 an Item argument and has no return  */
/*                 value                               */
/* postcondition:  the function pointed to by pfun is  */
/*                 executed once for each item in tree */
void Traverse (const Tree * ptree, void (* pfun)(Item item));

void DeleteAll(Tree * ptree);

static Pair SeekItem(const Item * pi, const Tree * ptree);


/* petclub.c -- use a binary search tree *//////////////////////////////////////////////////////////////////////////////////////////////////////

char menu(void);
void addpet(Tree * pt, char word[SLEN]);
void showpets(const Tree * pt);
void findpet(const Tree * pt);
void printitem(Item item);
void uppercase(char * str);
char * s_gets(char * st, int n);

int main(int argc, char *argv[])
{
    Tree words;
    char choice;
    FILE *file;
    char string[100];
    char *tok;
    char delim[] = " \t\r\n\v\f.,!?()";

    if (argc != 2){                                             // error checking command args
        puts("Wrong number of command-line arguments!\n");
        return 1;
    }

    file = fopen(argv[1], "r");

    if (file == NULL){                                          // error checking file
        puts("Error opening file");
        return 1;
    }
    
    InitializeTree(&words);

    while (fgets(string, SLEN, file) != NULL){

        tok = strtok(string, delim);                            // using strtok to only get valid words

        while (tok != NULL){
            addpet(&words, tok);
            tok = strtok(NULL, delim);
        }
    }
    fclose(file);
    while ((choice = menu()) != 'q')
    {
        switch (choice)
        {
            case 'l' :  showpets(&words);                       // shows the entire list 
                break;
            case 's' :  findpet(&words);                        // modified this function to be able to print the actual item in tree
                break;
            default  :  puts("Switching error");
        }
    }
    DeleteAll(&words);
    puts("Bye.");
    return 0;
}

char menu(void)
{
    int ch;

    //puts("Nerfville Pet Club Membership Program");
    puts("\nEnter the letter corresponding to your choice:");
    puts("l) List all the words along with the number of occurrences");
    puts("s) Enter a word to get the number of occuances");
    puts("q) quit");
    while ((ch = getchar()) != EOF)
    {
        while (getchar() != '\n')  /* discard rest of line */
            continue;
        ch = tolower(ch);
        if (strchr("lsq",ch) == NULL)
            puts("Please enter an l, s, or q:");
        else
            break;
    }
    if (ch == EOF)       /* make EOF cause program to quit */
        ch = 'q';

    return ch;
}

void addpet(Tree * pt, char word[SLEN])
{
    Item temp;

    if (TreeIsFull(pt))
        puts("No room in the List!");
    else
    {
        strncpy(temp.word, word, SLEN);
        //uppercase(temp.word);
        temp.occurs = 1;
        AddItem(&temp, pt);
    }
}

void showpets(const Tree * pt)
{
    if (TreeIsEmpty(pt))
        puts("No entries!");
    else
        Traverse(pt, printitem);
}

void printitem(Item item)
{
    printf("Word: %-19s  occurs: %d\n", item.word, item.occurs);
}

void findpet(const Tree * pt)
{
    Item temp;
    Pair temp2;

    if (TreeIsEmpty(pt))
    {
        puts("No entries!");
        return;     
    }

    puts("Please enter word you wish to find:");
    s_gets(temp.word, SLEN);
    
    temp2 = SeekItem(&temp, pt);
    //uppercase(temp.word);
     if (temp2.child != NULL){
        //printitem(temp);
        printitem(temp2.child->item);                   // this is how it prints the actual item in the tree
    }
    else
        printf("Word does not occur.\n");
}

void uppercase(char * str)
{
    while (*str)
    {
        *str = toupper(*str);
        str++;
    }
}

char * s_gets(char * st, int n)
{
    char * ret_val;
    char * find;

    ret_val = fgets(st, n, stdin);
    if (ret_val)
    {
        find = strchr(st, '\n');   // look for newline
        if (find)                  // if the address is not NULL,
            *find = '\0';          // place a null character there
        else
            while (getchar() != '\n')
                continue;          // dispose of rest of line
    }
    return ret_val;
}

/* tree.c -- tree support functions *////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* local data type */

/* protototypes for local functions */
static Trnode * MakeNode(const Item * pi);
static bool ToLeft(const Item * i1, const Item * i2);
static bool ToRight(const Item * i1, const Item * i2);
static void AddNode (Trnode * new_node, Trnode * root);
static void InOrder(const Trnode * root, void (* pfun)(Item item));
static void DeleteAllNodes(Trnode * ptr);

/* function definitions */
void InitializeTree(Tree * ptree)
{
    ptree->root = NULL;
    ptree->size = 0;
}

bool TreeIsEmpty(const Tree * ptree)
{
    if (ptree->root == NULL)
        return true;
    else
        return false;
}

bool TreeIsFull(const Tree * ptree)
{
    if (ptree->size == MAXITEMS)
        return true;
    else
        return false;
}

int TreeItemCount(const Tree * ptree)
{
    return ptree->size;
}

bool AddItem(const Item * pi, Tree * ptree)
{
    Trnode * new_node;

    if  (TreeIsFull(ptree))
    {
        fprintf(stderr,"Tree is full\n");
        return false;             /* early return           */
    }
    if (SeekItem(pi, ptree).child != NULL)
    {
        
    }
    new_node = MakeNode(pi);      /* points to new node     */
    if (new_node == NULL)
    {
        fprintf(stderr, "Couldn't create node\n");
        return false;             /* early return           */
    }
    /* succeeded in creating a new node */
    ptree->size++;

    if (ptree->root == NULL){  /* case 1: tree is empty  */
        ptree->root = new_node;   /* new node is tree root  */
    }
    else{                          /* case 2: not empty      */
        AddNode(new_node,ptree->root); /* add node to tree  */
    }
    return true;                  /* successful return      */
}

bool InTree(const Item * pi, const Tree * ptree)
{
    return (SeekItem(pi, ptree).child == NULL) ? false : true;
}

void Traverse (const Tree * ptree, void (* pfun)(Item item))
{

    if (ptree != NULL)
        InOrder(ptree->root, pfun);
}

void DeleteAll(Tree * ptree)
{
    if (ptree != NULL)
        DeleteAllNodes(ptree->root);
    ptree->root = NULL;
    ptree->size = 0;
}


/* local functions */
static void InOrder(const Trnode * root, void (* pfun)(Item item))
{
    if (root != NULL)
    {
        InOrder(root->left, pfun);
        (*pfun)(root->item);
        InOrder(root->right, pfun);
    }
}

static void DeleteAllNodes(Trnode * root)
{
    Trnode * pright;

    if (root != NULL)
    {
        pright = root->right;
        DeleteAllNodes(root->left);
        free(root);
        DeleteAllNodes(pright);
    }
}

static void AddNode (Trnode * new_node, Trnode * root)
{
    if (ToLeft(&new_node->item, &root->item))
    {
        if (root->left == NULL)      /* empty subtree       */
            root->left = new_node;   /* so add node here    */
        else
            AddNode(new_node, root->left);/* else process subtree*/
    }
    else if (ToRight(&new_node->item, &root->item))
    {
        if (root->right == NULL)
            root->right = new_node;
        else
            AddNode(new_node, root->right);
    }
    else                         /* should be no duplicates */
    {
        root->item.occurs++;
    }
}

static bool ToLeft(const Item * i1, const Item * i2)
{
    int comp1;

    if ((comp1 = strcmp(i1->word, i2->word)) < 0)
        return true;
    else if (comp1 == 0 &&
             strcmp(i1->word, i2->word) < 0 )
        return true;
    else
        return false;
}

static bool ToRight(const Item * i1, const Item * i2)
{
    int comp1;

    if ((comp1 = strcmp(i1->word, i2->word)) > 0)
        return true;
    else if (comp1 == 0 &&
             strcmp(i1->word, i2->word) > 0 )
        return true;
    else
        return false;
}

static Trnode * MakeNode(const Item * pi)
{
    Trnode * new_node;

    new_node = (Trnode *) malloc(sizeof(Trnode));
    if (new_node != NULL)
    {
        new_node->item = *pi;
        new_node->left = NULL;
        new_node->right = NULL;
    }

    return new_node;
}

static Pair SeekItem(const Item * pi, const Tree * ptree)
{
    Pair look;
    look.parent = NULL;
    look.child = ptree->root;

    if (look.child == NULL)
        return look;                        /* early return   */

    while (look.child != NULL)
    {
        if (ToLeft(pi, &(look.child->item)))
        {
            look.parent = look.child;
            look.child = look.child->left;
        }
        else if (ToRight(pi, &(look.child->item)))
        {
            look.parent = look.child;
            look.child = look.child->right;
        }
        else       /* must be same if not to left or right    */
            break; /* look.child is address of node with item */
    }

    return look;                       /* successful return   */
}

