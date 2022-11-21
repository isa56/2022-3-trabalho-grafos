# Trabalho de Grafos - 2022/3 - A

## Sumário

| Tópico                                                |
| ----------------------------------------------------- |
| [Integrantes do Grupo](#integrantes-do-grupo-id-21)    |
| [Descrição do Projeto](#descrição-do-projeto)         |
| [Instruções de Compilação e Execução](#instruções-de-compilação-e-execução)         |
| [Documentação e Referências Utilizadas](#documentação-e-referências-utilizadas) |
| [Observações para o Grupo](#observações-para-o-grupo) |

---

## Integrantes do Grupo (ID 21)
- [Eduardo Araujo](https://github.com/eduardonascimentojf);
- [Isadora Ferreira](https://github.com/isa56);
- [Miguel Sales](https://github.com/salesmiguelz).

[↑ Sumário](#sumário)

---

## Descrição do Projeto

Projeto de Teoria dos Grafos (DCC059), desenvolvido em C++, com uso de CMake e Google Test.
O objetivo inicial é desenvolver um TAD que represente grafos simples, orientados e não orientados, ponderados e não ponderados (nos vértices e arestas).


[↑ Sumário](#sumário)

---

## Instruções de Compilação e Execução

Para conseguir rodar o programa, é necessário ter instalados o [Git](https://git-scm.com/) e o [CMake](https://cmake.org/) em seu computador.

1. Clone ou baixe o repositório da maneira como preferir. Para usar a linha de comando:
  ```bash
  git clone https://github.com/isa56/2022-3-trabalho-grafos
  ```

2. Acesse a pasta recém clonada e execute os comandos do `CMake` no terminal:
  ```bash
  cmake -B build
  cmake --build build
  ```

3. Execute o arquivo que quiser:

    i. O programa principal `main`:
      ```bash
      ./build/main
      ```


    ii. Os testes unitários `test`:
      ```bash
      ./build/test/nomeDoTeste
      ```
3. Ou execute com o g++:

    i. Gerar o arquivo executável  `.exe`:
      ```bash
     g++ -o execGrupo21.exe  src/*.cpp
      ```


    ii. executar o arquivo `main`:
      ```bash
      ./execGrupo21.exe teste.txt testeS.txt 0 1 0
      ```
[↑ Sumário](#sumário)

---

## Documentação e Referências Utilizadas
- [DevDocs para C++](https://devdocs.io/cpp/);
- [Tutorial Graphviz](http://www.inf.ufes.br/~pdcosta/ensino/2018-2-estruturas-de-dados/material/Tutorial%20Graphviz.pdf);


[↑ Sumário](#sumário)

---

## Observações para o Grupo

### Rotina de Push:
1. Puxar o que está no repositório: `git pull`
2. Adicionar arquivos: `git add nome/e/caminho/do/arquivo.cpp`
3. Fazer commit: `git commit -m "TipoDeCommit: Mensagem de Commit"`
4. Empurra para o repositório remoto: `git push origin nome-da-branch`

#### Tipos de Commit:
Para saber mais, recomendo a leitura: [Conventional Commits](https://conventionalcommits.org/en/v1.0.0/). Boa prática, impressione recrutadores!

- `Feat`: (feature), adiciona funcionalidade nova
- `Fix`: correção de bugs
- `Docs`: Alterações apenas na Documentação
- `Refactor`: Mudança de código que não adiciona ou altera algo, mudança na forma como o código é escrito (refatoração)
- `Revert`: reversão para um commit anterior
- `Test`: Adiciona ou altera testes

#### Exemplo de rotina de commit:
1. `git pull`
2. `git add src/main.cpp src/Sort.cpp`
3. `git commit -m "Refactor: Muda código de Sort para arquivo próprio."`
4. `git push origin feat/sort`

[↑ Sumário](#sumário)
