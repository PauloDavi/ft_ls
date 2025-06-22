<h1 align="center">
	ft_ls
</h1>

<p align="center">
  <img src="https://i.imgur.com/U7aswVo.png" width="140" alt="grade" />
  <img src="https://game.42sp.org.br/static/assets/achievements/ft_lse.png" width="120" alt="m" />
</p>

---

<p align="center">
	<b><i>Your Best Project</i></b><br>
</p>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/PauloDavi/42sp-ft-ls?color=lightblue" />
	<img alt="Code language count" src="https://img.shields.io/github/languages/count/PauloDavi/42sp-ft-ls?color=yellow" />
	<img alt="GitHub top language" src="https://img.shields.io/github/languages/top/PauloDavi/42sp-ft-ls?color=blue" />
	<img alt="GitHub last commit" src="https://img.shields.io/github/last-commit/PauloDavi/42sp-ft-ls?color=green" />
</p>

<h3 align="center">
	<a href="#-about-the-project">About</a>
	<span> • </span>
	<a href="#%EF%B8%8F-compile">Compile</a>
	<span> • </span>
	<a href="#-usage">Usage</a>
	<span> • </span>
	<a href="#-options">Options</a>
	<span> • </span>
	<a href="#-examples">Examples</a>
	<span> • </span>
	<a href="#-credits">Credits</a>
	<span> • </span>
	<a href="#-license">License</a>
</h3>

---

## 💡 About the project

`ft_ls` is a C implementation of the classic Unix `ls` command, designed for educational purposes at 42SP. It lists directory contents with support for various flags and options, mimicking the behavior of the original command, including recursive listing, color output, and more.

---

## 🛠️ Compile

> This project is written in C and requires the **`gcc` compiler** and standard C libraries.

To compile, simply run:

```sh
make
```

The executable `ft_ls` will be generated in the project root.

---

## 📋 Usage

Basic usage:

```sh
./ft_ls [OPTIONS] [FILES...]
```

If no files or directories are specified, `ft_ls` lists the contents of the current directory.

---

## ⚙️ Options

Below is a table of all supported flags and options, with detailed explanations:

| Short | Long           | Description                                                                                 |
|:-----:|:--------------|:--------------------------------------------------------------------------------------------|
|   -l  |               | Use a long listing format.                                                                  |
|   -a  | --all         | Include directory entries whose names begin with a dot (`.`).                               |
|   -A  | --almost-all  | Like `-a`, but exclude `.` and `..`.                                                        |
|   -r  | --reverse     | Reverse the order while sorting.                                                            |
|   -t  |               | Sort by modification time, newest first.                                                    |
|   -R  | --recursive   | List subdirectories recursively.                                                            |
|   -u  |               | Use time of last access instead of modification for sorting (`-t`) or printing (`-l`).      |
|   -f  |               | Do not sort; enable `-a` and disable almost all other options.                              |
|   -g  |               | Like `-l`, but do not list owner.                                                           |
|   -G  |               | Inhibit display of group information.                                                       |
|   -d  | --directory   | List directories themselves, not their contents.                                             |
|   -Q  | --quote-name  | Enclose entry names in double quotes.                                                        |
|   -N  | --literal     | Do not quote entry names.                                                                    |
|   -m  |               | Fill width with a comma-separated list of entries.                                           |
|       | --color       | Enable colorized output. (default: enabled)                                                  |
|       | --help        | Display help and exit.                                                                       |

### Option Details

- **-l**: Shows detailed information (permissions, links, owner, group, size, date, name).
- **-a / --all**: Shows all files, including hidden ones (starting with `.`).
- **-A / --almost-all**: Shows all except `.` and `..`.
- **-r / --reverse**: Reverses the sort order.
- **-t**: Sorts by modification time instead of name.
- **-R / --recursive**: Recursively lists subdirectories.
- **-u**: Uses last access time for sorting/printing with `-t`/`-l`.
- **-f**: Disables sorting, enables `-a`, disables color, disables `-l`, disables owner/group/time/reverse.
- **-g**: Like `-l`, but omits owner.
- **-G**: Omits group information in long format.
- **-d / --directory**: Lists directory names, not their contents.
- **-Q / --quote-name**: Encloses names in double quotes.
- **-N / --literal**: Disables quoting of names.
- **-m**: Outputs as a comma-separated list.
- **--color**: Enables color output (default: enabled).
- **--help**: Shows help message and exits.

---

## 🧑‍💻 Examples

### List current directory
```sh
./ft_ls
```

### List all files, including hidden
```sh
./ft_ls -a
```

### Long format, sorted by time, reversed
```sh
./ft_ls -ltr
```

### List directories recursively
```sh
./ft_ls -R /etc /usr
```

### List only directories themselves
```sh
./ft_ls -d /tmp /var
```

### Comma-separated output, quoted names
```sh
./ft_ls -mQ
```

### Show help
```sh
./ft_ls --help
```

---

## 📝 Return Codes

- `0`: Success
- `1`: Error (invalid option, permission denied, file not found, etc.)

---

## 🏗️ Project Structure

```
ft_ls/
├── Makefile
├── README.md
├── include/         # Header files
├── lib/             # Libft library
├── src/             # Source files
└── build/           # Object files
```

---

## 🙏 Credits

- Developed by [Paulo Davi](https://github.com/PauloDavi).
- Inspired by the original Unix `ls` command.
- Part of the 42SP curriculum.

---

## 📄 License

This project is for educational purposes only.

---

## 🔧 Proposed Improvements

Abaixo estão sugestões para aprimorar a qualidade do projeto, focando em clareza, documentação e performance:

### 1. Clareza do Código
- Padronizar nomes de variáveis e funções para maior legibilidade.
- Modularizar funções muito longas ou com múltiplas responsabilidades.
- Remover código morto ou redundante.
- Adicionar comentários explicativos em trechos complexos.

### 2. Documentação das Funções
- Adicionar comentários do tipo Doxygen ou similar em todas as funções públicas e principais funções internas.
- Explicar parâmetros, valores de retorno e efeitos colaterais das funções.
- Incluir exemplos de uso para funções utilitárias.
- Documentar estruturas de dados e enums utilizados no projeto.

### 3. Performance de Execução
- Revisar loops aninhados e otimizar onde possível.
- Minimizar alocações e liberações de memória desnecessárias.
- Utilizar buffers e operações em lote para reduzir chamadas de sistema.
- Avaliar o uso de algoritmos de ordenação mais eficientes para grandes volumes de arquivos.
- Medir e analisar gargalos com ferramentas de profiling.

Essas melhorias visam tornar o projeto mais sustentável, fácil de entender e eficiente para futuros desenvolvedores e usuários.
