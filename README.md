# Trabalho Final de Programção Concorrente

Trabalho final da disciplina de programação concorrente Universidade de Brasília.

## 📃 Resumo 

Utilizando dos conhecimentos difundidos na disciplina de programação concorrente, foi elaborado um projeto que une o reality show de maquiagem da Netflix ”Glow Up” com a sincronizacção de threads através de semáforos.
No projeto, os MUAs (abreviação para a expressão Make Up Artist, que em português significa artistas de maquiagem), competem entre si para a execução e apresentação de sua maquiagem em cada uma das 3 etapas do episódio. Além disso, é estabelecida uma sincronia entre as threads dos artistas e a do jurado para que durante o episódio as apresentações das maquiagens e os julgamentos tenham uma ordem.

## 🚀 Execução 

```gcc -pthread -o glowup glowup.c
```
```./glowup   
```
