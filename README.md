# Jaime Adventures

Um projeto feito para disciplina de Ténicas de Programação em linguagem de programação c++, utilizando a biblioteca gráfica [sfml](https://en.sfml-dev.org/).

# Compilar e rodar
Para rodar o projeto, além de algum compilador c++, você precisa ter o gerenciador de compilação [Cmake](https://cmake.org/) e a biblioteca [sfml](https://en.sfml-dev.org/).

```
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -S . -B ./build # se precisar do compile_commands.json
cmake -S . -B ./build # para gerar a configuração cmake normalmente
cmake --build ./build/  # para gerar o binário

./build/game
```

# Sobre

Disciplina: Técnicas de Programação – CSE20 / S73  – Prof. Dr. Jean M. Simão

Departamento Acadêmico de Informática – DAINF - Campus de Curitiba

Curso Bacharelado em: Engenharia da Computação / Sistemas de Informação

Universidade Tecnológica Federal do Paraná - UTFPR

# Autores

Fabio Henrique Kleis Ribas Correa e Francisco Luis Dunaiski Bruginski

fabiohenrique@utfpr.edu.br, fbruginski@utfpr.edu.br
