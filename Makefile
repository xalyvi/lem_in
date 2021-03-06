SRC = utils/get_line.c \
	utils/numbers.c \
	utils/string.c \
	utils/string_more.c \
	utls.c \
	get_rooms.c \
	get_links.c \
	get_rooms_support.c \
	get_links_support.c \
	bfs.c \
	queue.c \
	mapset.c \
	output_forks.c \
	solve_sup.c \
	paths.c \
	ants.c \
	free.c \
	main.c \

OBJ = $(SRC:.c=.o)

SRCDIR = ./src
OBJDIR = ./obj

SRCS = $(addprefix $(SRCDIR)/, $(SRC))
OBJS = $(addprefix $(OBJDIR)/, $(OBJ))

INCLUDES = -I ./includes

CC = gcc
CFLAGS = -Wall -Werror -Wextra

NAME = lem-in

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
