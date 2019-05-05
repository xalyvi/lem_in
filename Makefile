SRC = utils/get_line.c \
	utils/numbers.c \
	utils/string.c \
	utils/string_more.c \
	get_nodes.c \
	get_links.c \
	get_nodes_support.c \
	solve_support.c \
	lem_in.c \
	queue.c \
	main.c \

OBJ = $(SRC:.c=.o)

SRCDIR = ./src
OBJDIR = ./obj

SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(OBJ))

INCLUDES = -I ./includes

CC = gcc
CFLAGS = -Wall -Werror -Wextra

NAME = lem_in

all: $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)/utils

$(OBJDIR)/%.o:$(SRCDIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

$(NAME): $(OBJDIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	@/bin/rm -rf $(OBJDIR)

fclean: clean
	@/bin/rm -rf $(NAME)

re: fclean all
