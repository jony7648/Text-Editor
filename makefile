normal_args=main.c draw.c file.c state.c command_line.c -o program -lncurses

default:
	gcc $(normal_args)
