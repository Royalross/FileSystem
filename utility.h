

void add_child(Node *parent, Node *child) ;
Node* back_track(Node *node, int levels) ;
Node* copy_node(Node *current, const char *name, Node *parent) ;
Node* create_node(const char name[MAX_NAME_LENGTH], int is_file, Node *parent) ;
Node* find_child(Node *root, const char *name) ;
void print_tree(Node *node, int level) ;
void remove_child(Node *parent, const char *name) ;
