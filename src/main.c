#include "bpt.h"

int main(){

    int64_t input;
    char instruction;
    char buf[120];
    char *result;
    open_table("DB2021083681.db");

    FILE *log;
 
    log = fopen("log.txt", "w");

    // instructions

    for(int i=0; i<4000; i++) {
        db_insert(i, "test");
    }

    pr();
    printf("# of Keys in Children: %d %d\n", load_page(rt->next_offset)->num_of_keys, load_page(rt->b_f[0].p_offset)->num_of_keys);

    // Deletes two leaf nodes of rt->next_offset completely (125->123)
    // So rt->next offset does not have enough children
    // Sibling has 127 nodes -> internal redistribution
    for(int i=2000; i<2017; i++) {
        db_delete(i);
    }   

    pr();
    printf("# of Keys in Children: %d %d\n", load_page(rt->next_offset)->num_of_keys, load_page(rt->b_f[0].p_offset)->num_of_keys);


    // fflush();

    //
    printf("Running...\n");
    //

    while(scanf("%c", &instruction) != EOF){
        switch(instruction){
            case 'i':
                scanf("%ld %s", &input, buf);
                db_insert(input, buf);
                break;
            case 'f':
                scanf("%ld", &input);
                result = db_find(input);
                if (result) {
                    printf("Key: %ld, Value: %s\n", input, result);
                }
                else
                    printf("Not Exists\n");

                fflush(stdout);
                break;
            case 'd':
                scanf("%ld", &input);
                db_delete(input);
                break;
            case 'p':
                pt();
                break;
            case 'q':
                while (getchar() != (int)'\n');
                return EXIT_SUCCESS;
                break;   

        }
        while (getchar() != (int)'\n');
    }
    printf("\n");
    return 0;
}



