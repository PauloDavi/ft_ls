VPATH := src

NAME := ft_ls
CFLAGS := -Wextra -Wall -Werror -O3 -g3
CC := cc
RM := rm -rf

LIBFT_DIR := lib/libft
LIBFT := $(LIBFT_DIR)/libft.a
LIBS := -L$(LIBFT_DIR) -lft

OBJ_DIR := build
INCLUDE_DIR := include
INCLUDES := -I$(INCLUDE_DIR) -I$(LIBFT_DIR)

SRCS := ft_ls.c list_directories.c file_entry.c tabulation.c print_utils.c
SRCS += parse_args.c order_files.c parse_flags.c list_files.c
OBJS := $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

all: $(LIBFT) $(NAME)

$(LIBFT_DIR):
	git submodule update --init --recursive

$(LIBFT): | $(LIBFT_DIR)
	@$(MAKE) -C $(LIBFT_DIR)

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	$(RM) $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	$(RM) $(NAME)

re: fclean all

run: all
	./$(NAME)

val: all
	@valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) $(ARGS)

.PHONY: all clean fclean re run val
