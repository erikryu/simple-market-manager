#include <stdio.h>
#include <string.h>
#include <time.h>
#include "sqlite3.h"

#define MAXPRODUCTS 5
#define MAXNAMELENGTH 50

typedef struct Produto {
    int id;
    double price;
    char productName[MAXNAMELENGTH];
} pd;

sqlite3 *db;
int att;

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
addPd(int id, double price, char name[MAXNAMELENGTH])
{
    printf("Digite o nome do produto: ");
    getText(name, MAXNAMELENGTH);

    printf("Digite o preço: ");
    scanf("%lf", &price);
    while(getchar() != '\n');
    
    sqlite3_stmt *stmt;
    const char *prepstmt = "INSERT INTO produtos (price, name) VALUES (?, ?);";

    att = sqlite3_prepare_v2(db, prepstmt, -1, &stmt, NULL);
    if (att==SQLITE_OK)
    {
        sqlite3_bind_double(stmt, 1, price);
        sqlite3_bind_text(stmt, 2, name, -1, NULL);
    } else
    {
        fprintf(stderr, "Erro em: %s\n", sqlite3_errmsg(db));
    }

    if (sqlite3_step(stmt)==SQLITE_ROW)
    {
        printf("%lf: ", sqlite3_column_double(stmt, 1));
        printf("%s\n", sqlite3_column_text(stmt, 2));
    }

    sqlite3_finalize(stmt);
    return 0;
}

void
menu(pd products)
{
    int option, i;
    
    option = 0;

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
            addPd(products.id, products.price, products.productName);

        } else if (option == 2)
        {
            for (int i=0; i<MAXPRODUCTS; ++i)
                ;
        } else if (option == 3)
            printf("OK! Saindo");

        else
            while(getchar()!='\n' && getchar()!=EOF);

    } while (option != 3);
}

int
main(void)
{
    int i, option;
    pd products;

    att = sqlite3_open("products.db", &db);

    const char *mkIndex = "CREATE TABLE IF NOT EXISTS produtos(id INTEGER PRIMARY KEY AUTOINCREMENT, price FLOAT, name VARCHAR(50));";
    char *errmsg = 0;
    att = sqlite3_exec(db, mkIndex, NULL, NULL, &errmsg);
    if (att != SQLITE_OK)
    {
        fprintf(stderr,"Erro ao abrir banco de dados: %s\n", errmsg);
        sqlite3_free(errmsg);
        sqlite3_close(db);
        return att; 
    }

    menu(products);

    sqlite3_close(db);

    return 0;
}
