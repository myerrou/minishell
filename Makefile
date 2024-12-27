NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address,undefined
RM = rm -rf

SRCS = src/lexer/lexer_utilis.c\
	src/lexer/lexer.c\
	src/lexer/lexer_error.c\
	src/lexer/lexer_utilis2.c\
	src/parsing/parsing_utilis.c\
	src/parsing/parsing_utilis2.c\
	src/parsing/parsing.c\
	src/expand/expand_utilis.c\
	src/expand/expand.c\
	src/expand_herdoc/expand_herdoc.c\
	src/main.c\
	execution/builtins/echo.c\
	execution/builtins/env.c\
	execution/builtins/pwd.c\
	execution/builtins/cd.c\
	execution/builtins/export.c\
	execution/builtins/export_utils.c\
	execution/builtins/exit.c\
	execution/builtins/unset.c\
	execution/envirement/bring_envirement.c\
	execution/envirement/envirement.c\
	execution/envirement/envirement_utils.c\
	execution/envirement/shellvl.c\
	execution/envirement/sort_envirement.c\
	execution/execute/bin.c\
	execution/execute/builtins.c\
	execution/execute/execute.c\
	execution/execute/extra_exec.c\
	execution/redir_pipe_sig_herd/pipe.c\
	execution/redir_pipe_sig_herd/redir_signals.c\
	execution/redir_pipe_sig_herd/herdoc.c\
	libf/ft_malloc.c\
	libf/ft_lstclear.c\
	libf/ft_skipallspace.c\
	libf/ft_strisnum.c\
	libf/ft_isprint.c\
	libf/ft_free_ptr.c\
	libf/ft_isalpha.c\
	libf/ft_strcmp.c\
	libf/ft_isalnum.c\
	libf/ft_isdigit.c\
	libf/ft_isascii.c\
	libf/ft_atoi.c\
	libf/ft_memcmp.c\
	libf/ft_strncmp.c\
	libf/ft_toupper.c\
	libf/ft_tolower.c\
	libf/ft_strlen.c\
	libf/ft_strlcpy.c\
	libf/ft_strlcat.c\
	libf/ft_putstr_fd.c\
	libf/ft_putnbr_fd.c\
	libf/ft_putendl_fd.c\
	libf/ft_putchar_fd.c\
	libf/ft_memcpy.c\
	libf/ft_memmove.c\
	libf/ft_memchr.c\
	libf/ft_memset.c\
	libf/ft_calloc.c\
	libf/ft_bzero.c\
	libf/ft_striteri.c\
	libf/ft_strchr.c\
	libf/ft_strrchr.c\
	libf/ft_strdup.c\
	libf/ft_strnstr.c\
	libf/ft_strtrim.c\
	libf/ft_substr.c\
	libf/ft_strjoin.c\
	libf/ft_itoa.c\
	libf/ft_strmapi.c\
	libf/ft_split.c

OBJS = ${SRCS:.c=.o}

all : $(NAME)

$(NAME) : $(OBJS)
	${CC} ${CFLAGS} ${OBJS} -o ${NAME} -lreadline

clean : 
	${RM} ${OBJS}

fclean : clean
	${RM} ${NAME}

re : fclean all

.PHONY: all clean fclean re
