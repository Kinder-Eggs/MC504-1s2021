# Projeto 5

### A solução do projeto consiste em duas novas chamadas de sistema para o kernel linux

Nosso problema consiste na implementação de duas chamadas de sistema que auxiliariam um User Weighted Round Robin Scheduler.

Para isso é necessário que sejam criadas um par de chamadas de sistema, um get e um set, que iram controlar o parâmetro de peso.

Para garantir seu funcionamento tiveram de ser alterado alguns arquivos presentes no kernel do linux:
* arch/x86/entry/syscalls/syscall_64.tbl - Adicionado as duas novas chamadas de sistema à tabela
* kernel/Makefile - Alterado configuração para a compilação da nova chamada de sistema
* include/linux/syscalls.h - Extendido a header das chamadas de sistema para incluir as duas novas chamadas de sistema

Além disso também foi criado um novo arquivo contendo as chamadas de sistema e um arquivo para testes:
* kernel/getsetuserweight.c - Arquivo .c contendo as duas chamadas de sistema
* testes/teste.c - Arquivo que utiliza as novas chamadas de sistema para mostrar seu funcionamento

[Vídeo explicativo]()
