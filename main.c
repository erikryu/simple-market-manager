#include <stdio.h>
#include <string.h>
#include "sqlite3.h"

#define MAXPRODUCTS 5
#define MAXNAMELENGTH 50

typedef struct Produto {
    int id;
    double price;
    char productName[MAXNAMELENGTH];
} pd;

sqlite3 *db;
sqlite3_stmt *stmt;

int rc;
char *errmsg = 0;

int
callback(void *Ununsed, int argc, char **argv, char **azColumName)
{
    Ununsed = 0;

    for(int i=0; i<argc; i++)
    {
        printf("%s = %s\n", azColumName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");

    return 0;
}

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
    
    const char *prepstmt = "INSERT INTO produtos (price, name) VALUES (?, ?);";

    rc = sqlite3_prepare_v2(db, prepstmt, -1, &stmt, NULL);
    if (rc==SQLITE_OK)
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
listProducts()
{
    const char *sqlist = "SELECT * FROM produtos";
    rc = sqlite3_exec(db, sqlist, callback, 0, &errmsg);
}

int
delPd()
{
    int gid = 0;
    char *delsql = "DELETE FROM produtos WHERE id = ?;";

    printf("Digite o nome do produto a ser removido: ");
    scanf("%d", &gid);
    while (getchar()!='\n');

    rc = sqlite3_prepare_v2(db, delsql, -1, &stmt, NULL);
    if (rc==SQLITE_OK)
    {
        sqlite3_bind_int(stmt, 1, gid);
    } else fprintf(stderr, "Erro em: %s\n", sqlite3_errmsg(db));

    rc = sqlite3_step(stmt);
    if (rc!=SQLITE_DONE)
    {
        fprintf(stderr, "Erro em: %s\n", sqlite3_errmsg(db));
    } else {
        printf("Linha deletada");
        sqlite3_finalize(stmt);
    }

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
        printf("\n3. Remove um produto por ID");
        printf("\n4. Sair");
        printf("\nDigite a sua escolha: ");

        scanf("%d", &option);
        printf("\n");
        while(getchar()!='\n' && getchar()!=EOF);

        if (option == 1)
        {
            addPd(products.id, products.price, products.productName);

        } else if (option == 2)
        {
            listProducts();
        } else if (option == 3)
        {
            delPd();
        } else if(option == 4)
            printf("OK! SAINDO");

        else
            while(getchar()!='\n' && getchar()!=EOF);

    } while (option != 4);
}

int
main(void)
{
    int i, option;
    pd products;

    rc = sqlite3_open("products.db", &db);

    const char *mkIndex = "CREATE TABLE IF NOT EXISTS produtos(id INTEGER PRIMARY KEY AUTOINCREMENT, price FLOAT, name VARCHAR(50));";
    rc = sqlite3_exec(db, mkIndex, NULL, NULL, &errmsg);
    if (rc != SQLITE_OK)
    {
        fprintf(stderr,"Erro ao abrir banco de dados: %s\n", errmsg);
        sqlite3_free(errmsg);
        sqlite3_close(db);
        return rc; 
    }

    menu(products);

    sqlite3_close(db);

    return 0;
}
