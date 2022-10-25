shellnado> path_cmd = (null)
path_cmd = (null)
cmd[0] = [path_cmd]	cmd[1] = [=]	cmd[2] = [(null)]	
infile = (null)
outfile = (null)
fds = 0x1e83a48
envp = 0x1e83a50
builtin = 0
in_file = 0
in_pipe = 0
out_append = 0
out_trunc = 0
out_pipe = 0
next = (nil)

shellnado> cmd[0] = [minimal.supp]
path_cmd = (null)
cmd[0] = [cmd[0]]	cmd[1] = [=]	cmd[2] = [[minimal.supp]]	
infile = (null)
outfile = (null)
fds = 0x1e83a48
envp = 0x1e83a50
builtin = 0
in_file = 0
in_pipe = 0
out_append = 0
out_trunc = 0
out_pipe = 0
next = (nil)

Command 'cmd[0]' not found.
shellnado> infile = (null)
path_cmd = (null)
cmd[0] = [infile]	cmd[1] = [=]	cmd[2] = [(null)]	
infile = (null)
outfile = (null)
fds = 0x1e83a48
envp = 0x1e83a50
builtin = 0
in_file = 0
in_pipe = 0
out_append = 0
out_trunc = 0
out_pipe = 0
next = (nil)

Command 'infile' not found.
shellnado> outfile = (null)
path_cmd = (null)
cmd[0] = [outfile]	cmd[1] = [=]	cmd[2] = [(null)]	
infile = (null)
outfile = (null)
fds = 0x1e83a48
envp = 0x1e83a50
builtin = 0
in_file = 0
in_pipe = 0
out_append = 0
out_trunc = 0
out_pipe = 0
next = (nil)

shellnado> fds = 0x1e83a48
path_cmd = (null)
cmd[0] = [fds]	cmd[1] = [=]	cmd[2] = [0x1e83a48]	
infile = (null)
outfile = (null)
fds = 0x1e83a48
envp = 0x1e83a50
builtin = 0
in_file = 0
in_pipe = 0
out_append = 0
out_trunc = 0
out_pipe = 0
next = (nil)

Command 'fds' not found.
shellnado> envp = 0x1e83a50
path_cmd = (null)
cmd[0] = [envp]	cmd[1] = [=]	cmd[2] = [0x1e83a50]	
infile = (null)
outfile = (null)
fds = 0x1e83a48
envp = 0x1e83a50
builtin = 0
in_file = 0
in_pipe = 0
out_append = 0
out_trunc = 0
out_pipe = 0
next = (nil)

Command 'envp' not found.
shellnado> builtin = 0
path_cmd = (null)
cmd[0] = [builtin]	cmd[1] = [=]	cmd[2] = [0]	
infile = (null)
outfile = (null)
fds = 0x1e83a48
envp = 0x1e83a50
builtin = 0
in_file = 0
in_pipe = 0
out_append = 0
out_trunc = 0
out_pipe = 0
next = (nil)

shellnado> in_file = 0
path_cmd = (null)
cmd[0] = [in_file]	cmd[1] = [=]	cmd[2] = [0]	
infile = (null)
outfile = (null)
fds = 0x1e83a48
envp = 0x1e83a50
builtin = 0
in_file = 0
in_pipe = 0
out_append = 0
out_trunc = 0
out_pipe = 0
next = (nil)

shellnado> in_pipe = 0
path_cmd = (null)
cmd[0] = [in_pipe]	cmd[1] = [=]	cmd[2] = [0]	
infile = (null)
outfile = (null)
fds = 0x1e83a48
envp = 0x1e83a50
builtin = 0
in_file = 0
in_pipe = 0
out_append = 0
out_trunc = 0
out_pipe = 0
next = (nil)

shellnado> out_append = 0
path_cmd = (null)
cmd[0] = [out_append]	cmd[1] = [=]	cmd[2] = [0]	
infile = (null)
outfile = (null)
fds = 0x1e83a48
envp = 0x1e83a50
builtin = 0
in_file = 0
in_pipe = 0
out_append = 0
out_trunc = 0
out_pipe = 0
next = (nil)

shellnado> out_trunc = 0
path_cmd = (null)
cmd[0] = [out_trunc]	cmd[1] = [=]	cmd[2] = [0]	
infile = (null)
outfile = (null)
fds = 0x1e83a48
envp = 0x1e83a50
builtin = 0
in_file = 0
in_pipe = 0
out_append = 0
out_trunc = 0
out_pipe = 0
next = (nil)

shellnado> out_pipe = 0
path_cmd = (null)
cmd[0] = [out_pipe]	cmd[1] = [=]	cmd[2] = [0]	
infile = (null)
outfile = (null)
fds = 0x1e83a48
envp = 0x1e83a50
builtin = 0
in_file = 0
in_pipe = 0
out_append = 0
out_trunc = 0
out_pipe = 0
next = (nil)

shellnado> next = (nil)
path_cmd = (null)
cmd[0] = [next]	cmd[1] = [=]	cmd[2] = [(nil)]	
infile = (null)
outfile = (null)
fds = 0x1e83a48
envp = 0x1e83a50
builtin = 0
in_file = 0
in_pipe = 0
out_append = 0
out_trunc = 0
out_pipe = 0
next = (nil)

Command 'next' not found.
shellnado> 
shellnado> shellnado> minishell
path_cmd = (null)
cmd[0] = [shellnado]	
infile = (null)
outfile = minishell
fds = 0x1e83a48
envp = 0x1e83a50
builtin = 0
in_file = 0
in_pipe = 0
out_append = 0
out_trunc = 1
out_pipe = 0
next = (nil)

ize=undefined
check:	CFLAGS		+=  -g3
check:	LFLAGS		+=  -pedantic -ansi
check:	LFLAGS		+=  -fsanitize=address
check:	LFLAGS		+=  -fsanitize=leak
check:	LFLAGS		+=  -fsanitize=undefined
check:	LFLAGS		+=  -g3
check:	${NAME}

# ################################## #
#                CLEAN               #
# ################################## #

clean:
			$(RM) $(O_DIR)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

-include	$(OBJS:.o=.d)
-include ./objs/*.d
-include ./objs/bi/*.d
-include ./objs/ev/*.d
-include ./objs/exe/*.d
-include ./objs/pa/*.d
-include ./objs/ut/*.d

.PHONY: all check clean fclean re
