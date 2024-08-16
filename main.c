#include <stdio.h>
#include <stdlib.h>

#define MAXPRODUCTS 10
#define MAXNAMELENGHT 50

int
getText(char *text, int lim)
{
    int c = 0;

    if (!fgets(text, lim, stdin))
        return -1;

    size_t len = strlen(text);
    if (len > 0 && text[len - 1] == '\n')
        text[len - 1] = '\0';

    if (len==lim - 1 && text[len - 1] != '\0')
        while((c = getchar()) != EOF && c!='\n');

    return len;
}

int
main(void)
{
    int i, j;

    struct Produto {
        int id;
        double price;
        char name[MAXNAMELENGHT];
    } pd[MAXPRODUCTS];

    for (i=0; i<MAXPRODUCTS; ++i)
    {
        pd[i].id = i + 1;

        printf("Digite o nome do produto: ");
        getText(pd[i].name, MAXNAMELENGHT);

        printf("Digite o preço: ");
        while(scanf("%lf", &pd[i].price) != 1)
        {
            printf("Entrada inválida. Digite novamente: ");
            while(getchar() != '\n');
        }

        while(getchar() != '\n');
    }

    for (int i=0; i<MAXPRODUCTS; ++i)
        printf("%d %.2lf %s\n", pd[i].id, pd[i].price, pd[i].name);

    return 0;
}
