#include <stdio.h>
#include "./src/skip_list.h"
#include "src/generator.h"

int main() {
    u_int32_t   seed,
                universe_size,
                burn_in,
                number_of_simulations,
                find_frequency,
                insert_frequency,
                delete_frequency,
                print_frequency;

    seed = 76;
    universe_size = 90;
    burn_in = 100;
    number_of_simulations = 30;
    find_frequency = 10;
    insert_frequency = 10;
    delete_frequency = 10;
    print_frequency = 10;

    node_t* head = create_node(-1, 0);

    set_seed(seed);

    int option;
    for (int i = 0; i < number_of_simulations; i++) {
        u_int32_t next = get_next() % (find_frequency + insert_frequency + delete_frequency);

        if (next < find_frequency) {
            option = 0;
        } else if (next <= find_frequency < find_frequency + insert_frequency ) {
            option = 1;
        } else {
            option = 2;
        }

        switch (option) {
            case 0: {
                u_int32_t to_find = get_next() % universe_size;

                node_t* found = find((int32_t) to_find, head);

                if (found) {
                    printf("Found %d\n", found->key);
                    break;
                }

                printf("Not found %d\n", to_find);

                break;
            }
            case 1: {
                u_int32_t to_insert = get_next() % universe_size;

                insert((int32_t) to_insert, &head);

                printf("Inserted %d\n", to_insert);

                break;
            }
            case 2: {
                u_int32_t to_delete = get_next() % universe_size;

                delete((int32_t) to_delete, head);

                printf("Deleted %d\n", to_delete);

                break;
            }
            default: {
                printf("Invalid option: %d", option);
                break;
            }
        }
    }

    print_skip_list(head);
}
