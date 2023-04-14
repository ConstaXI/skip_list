#include <stdio.h>
#include "./src/skip_list.h"

int main() {
    set_max_height(6);

    node_t *head = create_nodes();

    insert(10, rand() % 100, head);
    insert(9, rand() % 100, head);
    insert(8, rand() % 100, head);
    insert(7, rand() % 100, head);
    insert(6, rand() % 100, head);
    insert(5, rand() % 100, head);
    insert(4, rand() % 100, head);
    insert(3, rand() % 100, head);
    insert(2, rand() % 100, head);
    insert(1, rand() % 100, head);

    delete(5, head);

    print_skip_list(head);

    free_nodes(head);

    return 0;
}
