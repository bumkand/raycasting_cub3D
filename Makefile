NAME = cub3d
CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBMLX = ./MLX42
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj

# Source files
SRCS = main.c get_next_line.c get_next_line_utils.c init.c \
		player.c game.c init_data.c cub_file.c free_functions.c \
		ray.c
		
# Add src/ prefix to source files  
SRCS := $(addprefix $(SRC_DIR)/,$(SRCS))

# Object files
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

HEADERS = -I $(INC_DIR) -I $(LIBMLX)/include
LIBS = $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm

all: $(OBJ_DIR) libmlx $(NAME)

# Create obj directory if it doesn't exist
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

# Rule to compile .c files into .o files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(NAME)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(LIBMLX)/build

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re