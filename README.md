# AED2

*Repo para salvar algumas anotações e códigos úteis da disciplina de AED II*

### Guia de instalação do compilador:

#### Para utilização com PowerShell:

- Siga este tutorial: https://edisciplinas.usp.br/pluginfile.php/4251304/mod_resource/content/1/Instala%C3%A7%C3%A3o%20do%20compilador%20gcc%20no%20Windows.pdf

#### Para utilização com GitBash:

1. Acesse para obter instalador: https://www.msys2.org/
2. `pacman -Syu`
3. `$ pacman -S mingw-w64-ucrt-x86_64-gcc`
4. `gcc --version` confere se o compilador está instalado
5. `gcc seu_arquivo.c -o nome_do_executavel`
6. `gcc seu_arquivo.c -o nome_do_executavel -lm` serve para **incorporar a lib math em sua compilação**, mas é preciso adicionar ainda assim a **#include<math.h>** nas libs do código

### Guia de setup do ambiente

1. Clonar o repo: `git clone https://github.com/skyzismo/aed2-codes.git`
2. Receber as atualizações remotas: `git fetch`
3. Listar branches remotas: `git branch -r`
4. Mudar para develop: `git checkout develop`
5. Receber atualizações da branch: `git pull`

#### Quando arquivos forem adicionados ou modificados:

1. Configurar credenciais de email: `git config --global user.email "you@example.com"`
2. Configurar credenciais de username: `git config --global user.name "Your Name"`

#### Keywords para mensagens de commit:

- **feat:** Add user authentication

- **fix:** Resolve issue with user login

- **chore:** Update dependencies

- **docs:** Update README with installation instructions

- **style**: Format code using Prettier

- **refactor**: Simplify user authentication logic

- **test**: Add unit tests for login endpoint

- **build**: Update webpack configuration

- Use for performance improvements.

```plaintext
perf: Optimize database query for faster response time
```

- Use when reverting a previous commit.

```plaintext
revert: Revert changes from commit abc123
```

- Use when merging branches.

```plaintext
merge: Merge feature-branch into main
```

- Use for commits related to version releases.

```plaintext
release: Version 1.2.0
```
###### **Links Úteis:**
###### 1. Link para tutorial de markdown: [Markdown](https://commonmark.org/help/tutorial/)

###### 2. Contribuidor: [Lucas Gadelha](https://www.linkedin.com/in/lucas-gadelha-me/)
