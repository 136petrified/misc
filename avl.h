typedef struct Node {
    int data;
    Node *next; // default: NULL
} Node;

typedef struct TreeNode {
    int data;
    TreeNode *left; // default: NULL
    TreeNode *right; // default: NULL
} TreeNode;

/* NODE FUNCTIONS */
int size();
void insert(const int *data, const int *pos);
void remove(const int *pos);
void push_first(const int *data);
void push_last(const int *data);
int pop_first();
int pop_last();
void _free();

Node* find(const int *pos);

/* NODE VARIABLES */
Node *head = 0, 
     *tail = 0;


/* TREE FUNCTIONS */
void t_size();
void t_balance();
void t_insert(const int *data, const int *pos);
void t_remove(const int *pos);
void t_free();
void height();
