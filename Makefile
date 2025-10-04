NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBMLX = ./MLX42
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
LIBFT_DIR = libft

# Source files
SRCS = main.c init.c \
		player.c game.c init_data.c cub_file.c free_functions.c \
		texture_color.c init_texture.c init_color.c init_map.c \
		map_utils.c map_gamebility.c minimap.c \
		ray.c error.c \
		
# Add src/ prefix to source files  
SRCS := $(addprefix $(SRC_DIR)/,$(SRCS))

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libft library
LIBFT = $(LIBFT_DIR)/libft.a

HEADERS = -I $(INC_DIR) -I$(LIBFT_DIR)  -I $(LIBMLX)/include
LIBS = $(LIBFT) $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

all: $(OBJ_DIR) $(LIBFT) libmlx $(NAME)

# Create obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Rule to build libft by calling its Makefile
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

# Rule to compile .c files into .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(LIBMLX)/build
	$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re libmlx