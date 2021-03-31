# Custom-Shell-in-Ubuntu
C program which runs customised command prompt

Use `gcc Shell.c -lreadline` to compile the program.

Example commands:
  1. `ls`
  2. `touch new_file.txt && ls`  -> executes both commands sequentially
  3. `touch new_file.txt &&& ls`  -> executes both commands parallely
  4. `ls>outpu.txt` -> stores result of the command into the file

Any command can be executed in this custom shell.
Use `exit` to exit the shell program.
