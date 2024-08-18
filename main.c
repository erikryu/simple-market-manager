#include <stdio.h>
#include <stdlib.h>

#define MAXPRODUCTS 5
#define MAXNAMELENGTH 50

typedef struct Produto {
    int id;
    float price;
    char productName[MAXNAMELENGTH];
} pd;

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

void
addPd(int id, float *price, char name[MAXNAMELENGTH])
{
    printf("Digite o nome do produto: ");
    getText(name, MAXNAMELENGTH);

    printf("Digite o preço: ");
    while(scanf("%f", price) != 1)
    {
        printf("Entrada inválida. Digite novamente: ");
        while(getchar() != '\n');
    }

    while(getchar() != '\n');
}

int
main(void)
{
    int i, option;
    pd products[MAXPRODUCTS];

    do
    {
        printf("Menu: ");
        printf("\n1. Adicione alguns produtos");
        printf("\n2. Liste os produtos já registrados");
        printf("\n3. Saia do programa");
        printf("\nDigite a sua escolha: ");

        scanf("%d", &option);
        printf("\n");
        while(getchar()!='\n' && getchar()!=EOF);

        if (option == 1)
        {
            for (i=0; i<MAXPRODUCTS; ++i)
            {
                products[i].id = i + 1;
                products[i].price = 0.0;

                addPd(products[i].id, &products[i].price, products[i].productName);
            }
        } else if (option == 2)
        {
            for (int i=0; i<MAXPRODUCTS; ++i)
                printf("%d %.2lf %s\n", products[i].id, products[i].price, products[i].productName);

        } else if (option == 3)
            printf("OK! Saindo");

        else
            while(getchar()!='\n' && getchar()!=EOF);

    } while (option != 3);

    return 0;
}
