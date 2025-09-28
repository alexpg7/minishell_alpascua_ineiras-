# 🖥️ minishell ![Static Badge](https://img.shields.io/badge/Barcelona-black?style=for-the-badge&logo=42&logoColor=%23FFFFFF)
![Static Badge](https://img.shields.io/badge/c-grey?style=flat&logo=c)
![Static Badge](https://img.shields.io/badge/Makefile-green?style=flat&logo=AnkerMake)
![Static Badge](https://img.shields.io/badge/status-completed-green?style=flat)

The first challenging 42 project: a bash terminal.

## :hammer: Compilation
Firstly, clone the repository into you computer directory:

```bash
git clone https://github.com/alexpg7/minishell.git minishell && cd minishell
```

Once cloned, just execute the `make` command:

```bash
make
```

The `make`command should notify when ``libft.a`` and ``minishell`` are compiled.

## 🖱️ Usage

### 1️⃣ 1 command mode

``minishell`` can be executed with a command, just like with bash. For example:

```bash
./minishell echo "Hello, world!"
```

should output:
```output
Hello, world!
```

### 🐚 Shell mode

To execute the usual mode, execute ``minishell`` without any other argument:

```bash
./minishell
```

The program should open up a prompt with your pwd and should allow you to start writing commands:

```output
Welcome to minishell
/...(your pwd).../minishell->
```

From now on, you can use ```minishell``` as if it was bash, with some limitations...

## ⚠️ Limitations

``minishell`` works as a functional shell, but some features have not been implemented (and will never be):

* Double pipe ``||`` operator works as a double pipe with no command in between
* ``&``, ``&&`` operators do not work
* Unclosed quotes will not be asked to be completed, they will just fail
* Pipes with no commmand (example: ``echo hola | | grep h``) will just fail
* Wildcards ``*`` are not implemented
* Parentheses ``()`` are interpreted as regular characters, they do not stablish any priority
* Environment variables (``$VAR``) are interpreted after splitting arguments (this means that spaces and quotes inside ``VAR`` do not influence the command, they are not key characters)
* ``+=`` operator from ``export`` command is not implemented
* ``;`` and ``\`` are interpreted as regular characters
