MAKE_DIR		:=		$(PWD)

MASTER_MAKE		:=		$(MAKE_DIR)/Makefile

SRCS_DIR		:=		$(MAKE_DIR)/src
BONUS_DIR		:=		$(MAKE_DIR)/bonus

RELEASE_OBJS_DIR		:=		$(MAKE_DIR)/obj
RELEASE_BONUS_OBJS_DIR	:=		$(MAKE_DIR)/bonus_obj
DEBUG_OBJS_DIR			:=		$(MAKE_DIR)/objd
DEBUG_BONUS_OBJS_DIR	:=		$(MAKE_DIR)/bonus_objd

LIBFT_DIR		:=		$(MAKE_DIR)/Libft
MLX_DIR			:=		$(MAKE_DIR)/minilibx

INCLUDE_DIR			:=	-I$(MAKE_DIR)/include
INCLUDE_BONUS_DIR	:=	-I$(MAKE_DIR)/include_bonus

INC_PATH		:=		-I$(LIBFT_DIR)

LIB_PATH		:=		-L$(LIBFT_DIR)

OS				=	$(shell uname -s)
ifeq ($(OS), Linux)
	MLXFLAGS	=		-L /usr/local/lib -lmlx_Linux -L/usr/X11/lib -I/usr/local/include -lXext -lX11 -lz
else
	LIB_PATH	+=		-L $(MLX_DIR)
	INC_PATH	+=		-I $(MLX_DIR)
	MLXFLAGS	=		-lmlx -framework OpenGL -framework AppKit -lz
endif

RELEASE_LIBS		:=		$(MLXFLAGS) $(LIB_PATH) -lft -lm
DEBUG_LIBS			:=		$(MLXFLAGS) $(LIB_PATH) -lftd -lm

BIN_CC				:=		gcc

RELEASE_BIN_CFLAGS		:=
RELEASE_BIN_CFLAGS		+=		-MD
RELEASE_BIN_CFLAGS		+=		-Wall -Wextra -Werror -O3
RELEASE_BIN_CFLAGS		+=		-mllvm -inline-threshold=100000000
RELEASE_BIN_CFLAGS		+=		$(INC_PATH)

DEBUG_BIN_CFLAGS		:=
DEBUG_BIN_CFLAGS		+=		-MD
DEBUG_BIN_CFLAGS		+=		-Wall -Wextra -Werror
DEBUG_BIN_CFLAGS		+=		-fsanitize=address -g3 -DDEBUG
DEBUG_BIN_CFLAGS		+=		$(INC_PATH)

RELEASE_BIN_LDFLAGS		:=

DEBUG_BIN_LDFLAGS		:=
DEBUG_BIN_LDFLAGS		+=		-fsanitize=address

RELEASE_LIBFT_LIB	:=		$(LIBFT_DIR)/libft.a
DEBUG_LIBFT_LIB		:=		$(LIBFT_DIR)/libftd.a

export MAKE_DIR
export RELEASE_BONUS_OBJS_DIR
export RELEASE_OBJS_DIR
export DEBUG_OBJS_DIR
export DEBUG_BONUS_OBJS_DIR
export MASTER_MAKE
export SRCS_DIR
export BONUS_DIR
export OBJS_DIR
export INC_PATH
export LIB_PATH
export RELEASE_LIBS
export DEBUG_LIBS
export BIN_CC
export RELEASE_BIN_CFLAGS
export DEBUG_BIN_CFLAGS
export RELEASE_BIN_LDFLAGS
export DEBUG_BIN_LDFLAGS
export DEBUG_LIBFT_LIB
export RELEASE_LIBFT_LIB
export LIB_PATH
export LIBFT_DIR
export INCLUDE_DIR
export INCLUDE_BONUS_DIR

.PHONY: all
all: header
	@$(MAKE) -j4 -C $(LIBFT_DIR)
ifeq ($(OS), Darwin)
	@$(MAKE) -j4 -C $(MLX_DIR)
endif
	@$(MAKE) -j4 -C $(SRCS_DIR) -r -R --warn-undefined-variables

.PHONY: debug
debug: header
	@$(MAKE) -j4 -C $(LIBFT_DIR) debug
ifeq ($(OS), Darwin)
	@$(MAKE) -j4 -C $(MLX_DIR)
endif
	@$(MAKE) -j4 -C $(SRCS_DIR) -r -R --warn-undefined-variables debug

.PHONY: bonus
bonus: header
	@$(MAKE) -j4 -C $(LIBFT_DIR)
ifeq ($(OS), Darwin)
	@$(MAKE) -j4 -C $(MLX_DIR)
endif
	@$(MAKE) -j4 -C $(BONUS_DIR) -r -R --warn-undefined-variables

.PHONY: debug_bonus
debug_bonus: header
	@$(MAKE) -j4 -C $(LIBFT_DIR) debug
ifeq ($(OS), Darwin)
	@$(MAKE) -j4 -C $(MLX_DIR)
endif
	@$(MAKE) -j4 -C $(BONUS_DIR) -r -R --warn-undefined-variables debug

.PHONY: clean
clean: header
	@$(MAKE) -C $(LIBFT_DIR) clean
ifeq ($(OS), Darwin)
	@$(MAKE) -C $(MLX_DIR) clean
endif
	@$(MAKE) -C $(SRCS_DIR) clean
	@$(MAKE) -C $(BONUS_DIR) clean

.PHONY: fclean
fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(SRCS_DIR) fclean
	@$(MAKE) -C $(BONUS_DIR) fclean

.PHONY: re
re: fclean all

.PHONY: debug_re
debug_re: fclean debug

.PHONY: cub_re
cub_re:
	@$(MAKE) -C $(SRCS_DIR) fclean
	@$(MAKE) -C $(SRCS_DIR)

.PHONY: cub_debug_re
cub_debug_re:
	@$(MAKE) -C $(SRCS_DIR) fclean
	@$(MAKE) -C $(SRCS_DIR) debug

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
