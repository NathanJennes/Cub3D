MAKE_DIR		:=		$(PWD)

MASTER_MAKE		:=		$(MAKE_DIR)/Makefile

SRCS_DIR		:=		$(MAKE_DIR)/src
OBJS_DIR		:=		$(MAKE_DIR)/obj

LIBFT_DIR		:=		$(MAKE_DIR)/Libft
LEAKY_DIR		:=		$(LIBFT_DIR)/Leaky
MLX_DIR			:=		$(MAKE_DIR)/minilibx

INC_PATH		:=		-I$(LIBFT_DIR) -I$(LEAKY_DIR) -I$(MAKE_DIR)/include -I$(MLX_DIR)

LIB_PATH		:=		-L$(LIBFT_DIR) -L$(MLX_DIR) -L$(LEAKY_DIR)

OS				=	$(shell uname -s)
ifeq ($(OS), Linux)
	MLXFLAGS	=		-L /usr/local/lib -lmlx_Linux -L/usr/X11/lib -I/usr/local/include -lXext -lX11 -lz
else
	MLXFLAGS	=		-lmlx -framework OpenGL -framework AppKit
endif

LIBS			:=		$(MLXFLAGS) $(LIB_PATH) -lftd -lleaky -lm

BIN_CC			:=		gcc

BIN_CFLAGS		:=
BIN_CFLAGS		+=		-MD
BIN_CFLAGS		+=		-Wall -Wextra -Werror
BIN_CFLAGS		+=		-g3 -fsanitize=address
BIN_CFLAGS		+=		$(INC_PATH)

BIN_LDFLAGS		:=
BIN_LDFLAGS		+=		-fsanitize=address

LIBFT_LIB		:=		$(LIBFT_DIR)/libftd.a

export MAKE_DIR
export OBJS_DIR
export MASTER_MAKE
export SRCS_DIR
export OBJS_DIR
export INC_PATH
export LIB_PATH
export LIBS
export BIN_CC
export BIN_CFLAGS
export BIN_LDFLAGS
export LIBFT_LIB
export LIB_PATH

.PHONY: all
all: header
	@$(MAKE) -j4 -C $(LIBFT_DIR)
ifeq ($(OS), Darwin)
	@$(MAKE) -j4 -C $(MLX_DIR)
endif
	@$(MAKE) -j4 -C $(SRCS_DIR) -r -R --warn-undefined-variables

debug: header
	@$(MAKE) -j4 -C $(LIBFT_DIR) debug
ifeq ($(OS), Darwin)
	@$(MAKE) -j4 -C $(MLX_DIR)
endif
	@$(MAKE) -j4 -C $(SRCS_DIR) -r -R --warn-undefined-variables

.PHONY: bonus
bonus: all

.PHONY: clean
clean: header
	@$(MAKE) -C $(LIBFT_DIR) clean
ifeq ($(OS), Darwin)
	@$(MAKE) -C $(MLX_DIR) clean
endif
	@$(MAKE) -C $(SRCS_DIR) clean

.PHONY: fclean
fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(SRCS_DIR) fclean

.PHONY: re
re: fclean all

# Misc
# =====================

print-%:	; @echo $* = $($*)

.PHONY: header
header:
	@printf "\n"
	@printf "$(_ORANGE)\t  ______  __    __ _______   ______  _______  \n$(_END)"
	@printf "$(_ORANGE)\t /      \|  \  |  \       \ /      \|       \ \n$(_END)"
	@printf "$(_ORANGE)\t|  ▓▓▓▓▓▓\ ▓▓  | ▓▓ ▓▓▓▓▓▓▓\  ▓▓▓▓▓▓\ ▓▓▓▓▓▓▓\\n$(_END)"
	@printf "$(_ORANGE)\t| ▓▓   \▓▓ ▓▓  | ▓▓ ▓▓__/ ▓▓\▓▓__| ▓▓ ▓▓  |  ▓▓\n$(_END)"
	@printf "$(_ORANGE)\t| ▓▓     | ▓▓  | ▓▓ ▓▓    ▓▓ |     ▓▓ ▓▓  |  ▓▓\n$(_END)"
	@printf "$(_ORANGE)\t| ▓▓   __| ▓▓  | ▓▓ ▓▓▓▓▓▓▓\__\▓▓▓▓▓\ ▓▓  |  ▓▓\n$(_END)"
	@printf "$(_ORANGE)\t| ▓▓__/  \ ▓▓__/ ▓▓ ▓▓__/ ▓▓  \__| ▓▓ ▓▓__/  ▓▓\n$(_END)"
	@printf "$(_ORANGE)\t \▓▓    ▓▓\▓▓    ▓▓ ▓▓    ▓▓\▓▓    ▓▓ ▓▓     ▓▓\n$(_END)"
	@printf "$(_ORANGE)\t  \▓▓▓▓▓▓  \▓▓▓▓▓▓ \▓▓▓▓▓▓▓  \▓▓▓▓▓▓ \▓▓▓▓▓▓▓ \n$(_END)"
	@printf "\n"

# Colors
# ****************************************************************************

_GREY	= \033[30m
_RED	= \033[31m
_ORANGE	= \033[38;5;209m
_GREEN	= \033[32m
_YELLOW	= \033[33m
_BLUE	= \033[34m
_PURPLE	= \033[35m
_CYAN	= \033[36m
_WHITE	= \033[37m
_END	= \033[0m

export _GREY
export _RED
export _ORANGE
export _GREEN
export _YELLOW
export _BLUE
export _PURPLE
export _CYAN
export _WHITE
export _END

# ****************************************************************************
