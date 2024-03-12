

#ifndef E03_TITLE_H
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #define E03_TITLE_H
    #define MAXLEN 21
    typedef struct titolo_s *pTitle;
    void title_print(pTitle x);
    pTitle title_init();
    pTitle title_cpy(char* name);
    pTitle leggi_titolo(FILE *fp);
    void title_free(pTitle x);
    int title_cmp(pTitle t1, pTitle t2);


#endif //E03_TITLE_H
