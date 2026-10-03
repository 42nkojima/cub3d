NAME        = cub3D
CC          = cc
CFLAGS      = -Wall -Wextra -Werror

SRCS        = main.c \
			  render/render.c
OBJ_DIR     = obj
OBJS        = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

LIBFT_DIR   = libft
LIBFT       = $(LIBFT_DIR)/libft.a

MLX_DIR     = minilibx-linux
MLX_LIB     = $(MLX_DIR)/libmlx.a

UNAME_S     := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
X11_INC     = -I/opt/X11/include
X11_FLAGS   = -L/opt/X11/lib
endif
INCLUDES    = -I. -Irender -I$(LIBFT_DIR) -I$(MLX_DIR) $(X11_INC)
MLX_FLAGS   = -L$(MLX_DIR) -lmlx $(X11_FLAGS) -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(MLX_LIB) $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -L$(LIBFT_DIR) -lft -o $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX_LIB):
	@if [ ! -d $(MLX_DIR) ]; then \
		echo "$(MLX_DIR) not found: extract minilibx-linux.tgz at the repository root" >&2; \
		exit 1; \
	fi
	@$(MAKE) -C $(MLX_DIR)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@if [ -f $(MLX_DIR)/Makefile.gen ]; then $(MAKE) -C $(MLX_DIR) clean; fi

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

norm:
	@norminette $$(git ls-files '*.c' '*.h' ':!:minilibx-linux/**')

.PHONY: all clean fclean re norm
