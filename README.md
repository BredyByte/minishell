# 🤯 Minishell

## 📄 Abstract
This project involves the creation of a simple shell, called Minishell, which can interpret and execute commands. The goal is to implement various shell functionalities, including prompt display, command execution, history management, and handling of special characters.

## 🧾 Project Overview
Minishell is a command-line interpreter that aims to replicate basic shell functionalities. The project requirements include handling quotes, interpreting metacharacters, implementing redirections, pipes, and managing environment variables. The shell should also handle signals, built-in commands, and provide a user-friendly interface.

## 📝 Task Description

<span style="font-size: 1.2em; font-weight: bold; color: #3498db;">Your Awesome Shell Should:</span>


- Display a prompt when waiting for a new command.
- Have a working history.
- Search and launch the right executable based on the PATH variable or using a relative or absolute path.
- Avoid using more than one global variable to indicate a received signal.
- Not interpret unclosed quotes or special characters that are not required by the subject.
- Handle single and double quotes, preventing the interpretation of metacharacters in the quoted sequence.
- Handle ctrl-C, ctrl-D, and ctrl-\ as specified.
- <details>
  <summary>Implement redirections : </summary>

  - `<` for input,
  - `>` for output,
  - `<<` with a delimiter, and
  - `>>` for output in append mode.
</details>

- Handle ctrl-C, ctrl-D, and ctrl-\ as specified.

- <details>
  <summary>Implement built-ins :</summary>

  - **echo** with the `-n` option,

  - **cd** with only a relative or absolute path,

  - **pwd**,

  - **export**,

  - **unset**,

  - **env**,

  - **exit**.
</details>

- Implement pipes (`|`) for connecting the output of one command to the input of the next.
- Handle environment variables (`$`) that should expand to their values.
- Handle `$?` which should expand to the exit status of the most recently executed foreground pipeline.

##  🗂️ Directory Hierarchy
```
|—— assets
|    |—— libft
|        |—— Makefile
|        |—— include
|            |—— libft.h
|        |—— src
|—— include
|    |—— defines.h
|    |—— minishell.h
|—— src
|    |—— built-ins
|        |—— cd.c
|        |—— cd_utils.c
|        |—— echo.c
|        |—— env.c
|        |—— env_array_utils.c
|        |—— exit.c
|        |—— export.c
|        |—— export_utils.c
|        |—— export_utils2.c
|        |—— pwd.c
|        |—— refill_envp_lst.c
|        |—— tuple_utils.c
|        |—— tuple_utils2.c
|        |—— unset.c
|    |—— free
|        |—— free_all.c
|    |—— init.c
|    |—— init_utils.c
|    |—— parser
|        |—— expan_core.c
|        |—— expan_utils.c
|        |—— group_cmd_lst.c
|        |—— group_core.c
|        |—— group_here_doc.c
|        |—— group_redir.c
|        |—— group_utils.c
|        |—— token_concat_token_word.c
|        |—— token_core.c
|        |—— token_delete_token_sep.c
|        |—— token_handlers.c
|    |—— pipex
|        |—— pipex.c
|        |—— pipex_utils.c
|        |—— pipex_utils2.c
|    |—— signals
|        |—— signals.c
|—— Makefile
```

## 💖 **Appreciation Corner**
   This fantastic work was completed and brought to perfection with the help of my friend and colleague, the genius [🚀 regea-go](https://github.com/xEgea11).

## 📝 P.S.
   If you have any questions about the project, feel free to contact me via [Telegram](https://t.me/Davyd_y_punto) or [LinkedIn](https://www.linkedin.com/in/davyd-bredykhin-1u961/).
