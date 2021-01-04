								Relatório


## BombRoad


### Descrição da solução 

- Numa fase inicial do projeto planeamos dividir o projeto por funções para melhor organização e reutilização do código;
- A função `main` vai chamar 2 funções uma delas para imprimir o menu sempre que o programa é inicializado e outra que trata do resto do programa. Sempre que o programa é inicializado isto garante que o menu é imprimido no inicio;
- A função `menu` possui como conteúdo uma série de comandos `puts` de modo a imprimir o menu conforme o enunciado. Deste modo basta chamar a função para imprimir o menu.
- A função `choices` é responsável pelo input do jogador e o manuseamento do mapa. A função possui um loop infinito de modo que o jogo apenas acabe quando o jogador comandar. Um mapa vazio é gerado automaticamente no inicio do programa e caso outro mapa seja importado este é apagado. Esta função chama as funções `readFile` e `writeFile` caso sejam selecionadas as opções para ler ou gravar ficheiros.


-   Uma função imprime o menu e não retorna nenhuma valor de modo a que esta possa ser reutilizada. tinha os "prints" do menu. Noutra função lia os "inputs" do utilizador e por ai adiante mas decidimo verificava se os inputs estavam certos. Se estivessem o programa continua, passando para a função seguinte. Caso contrário mostra uma mensagem de erro.


### Fluxograma 

![Fluxograma](Fluxograma.png)
</b>

### Descrição do método para teste e debug

- Para teste de ficheiros inputs, usamos o ficheiro que o professor disponibilizou no moodle, e criamos outro ficheiro com várias coordenadas. Nesse mesmo ficheiro possuía letras minúsculas e maiúsculas, números juntos, coordenadas fora do intervalo de valores.
- Para debug do projeto faziamos _printf("This part is working");_, por exemplo, em um determinado sitio do programa para verificar se funcionava ou os possíveis erros do programa. 

### Conclusões e matéria aprendida 

- Manipulação de ficheiros na linguagem C.
- Vetores e Matrizes.
- Leitura de ficheiros em carateres.
- Condições.


### Referências 

- Linguagem C, Damas,L.M.D


