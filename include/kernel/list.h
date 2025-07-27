typedef struct list_node {
    struct list_node *next;
    struct list_node *prev;
} list_node_t;

static inline void list_init(list_node_t *head)
{
    head->next = head;
    head->prev = head;
}

static inline void list_push(list_node_t *head, list_node_t *node)
{
    node->next = head->next;
    head->next->prev = node;
    node->prev = head;
    head->next = node;
}

static inline void list_push_back(list_node_t *head, list_node_t *node)
{
    list_push(head->prev, node);
}

static inline void list_remove(list_node_t *node)
{
    node->next->prev = node->prev;
    node->prev->next = node->next;
}
