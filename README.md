# simple-market-manager
Uma implementação CRUD simples com SQLite3 C API.

### Passos para compilação
- Fiz os passos utilizando compilador MSVC. Procure comandos similares no seu compilador:
1. Baixe o código do SQLite Amalgamation
2. Você vai precisar somente dos arquivos 'sqlite3.c' e 'sqlite3.h'
3. Utilize o comando 'cl sqlite3.c -link -dll -out:sqlite3.dll'
4. Quando for compilar utilize 'cl /MD main.c -link sqlite3.obj'