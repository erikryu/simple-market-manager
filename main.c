#include <stdio.h>
#include <stdlib.h>

#define MAXPRODUCTS 10
#define MAXNAMELENGHT 50

char*
getProductName(char *name, int lim)
{
    int c, i;

    for (i=0; i<lim-1 && (c=getchar())!=EOF && c!='\n'; ++i)
        name[i] = c;

    if (c=='\n') ++i;
    name[i] = '\0';

    return name;
}

int
main(void)
{
    struct Produto {
        int id;
        double price;
        char name[MAXNAMELENGHT];
    } pd[MAXPRODUCTS] = {
        1, 2.00, "Tomate",
        2, 5.00, "Abacate",
        3, 3.50, "Refrigerante Lata",
        4, 4.30, "Chocolate",
        5, 2.75, "Café"
    };

    for (int i=0; i<MAXPRODUCTS; ++i)
    {
        if (pd[i].id == 0)
        {
            pd[i].id = i + 1;

            printf("Digite o nome do produto de ID=%d: ", pd[i].id);
            getProductName(pd[i].name, MAXNAMELENGHT);
        }
    }

    for (int i=0; i<MAXPRODUCTS; ++i)
        printf("%d %.2lf %s\n", pd[i].id, pd[i].price, pd[i].name);

    return 0;
}
