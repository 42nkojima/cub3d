NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

SRCS        = main.c
OBJ_DIR     = obj
OBJS        = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

MLX_DIR     = minilibx-linux
MLX_LIB     = $(MLX_DIR)/libmlx.a
INCLUDES    = -I. -I$(LIBFT_DIR) -I$(MLX_DIR)

UNAME_S     := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
X11_FLAGS   = -L/opt/X11/lib
endif
MLX_FLAGS   = -L$(MLX_DIR) -lmlx $(X11_FLAGS) -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT) $(MLX_LIB)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	@$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@if [ -d $(MLX_DIR) ]; then $(MAKE) -C $(MLX_DIR) clean; fi

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re