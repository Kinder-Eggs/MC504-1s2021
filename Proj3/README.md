# Projeto 3

### A solução do projeto consiste em uma animação do problema "Building H2O" e sua respectiva solução

O problema e sua solução são descritos no capítulo 5.6 do livro [The Little Book of Semaphores](https://greenteapress.com/semaphores/LittleBookOfSemaphores.pdf)

O problema se baseia na existência de dois tipos de threads, oxigênio e hidrogênio, estas somente podem terminar sua execução quando estiverem presentes junto com elas um número suficiente de threads para formar uma molécula de água (Duas threads de hidrogênio e uma de oxigênio).

Sua solucão e animação consiste no uso de mutex locks, barreiras e semáforos para sincronizar que as threads representativas do oxigênio e hidrogênio somente terminem suua execução quando um número suficiente de threads estiverem prontas para continuar.

[Vídeo explicativo](https://drive.google.com/file/d/1oVYSTDSa2RT7PK_jFyB5HywXypTfScmy/view?usp=sharing)
