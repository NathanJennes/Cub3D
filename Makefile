MAKE_DIR		:=		$(PWD)

MASTER_MAKE		:=		$(MAKE_DIR)/Makefile

SRCS_DIR		:=		$(MAKE_DIR)/src

RELEASE_OBJS_DIR	:=		$(MAKE_DIR)/obj
DEBUG_OBJS_DIR		:=		$(MAKE_DIR)/objd
PROFILE_OBJS_DIR	:=		$(MAKE_DIR)/objp

LIBFT_DIR		:=		$(MAKE_DIR)/Libft
LEAKY_DIR		:=		$(LIBFT_DIR)/Leaky
MLX_DIR			:=		$(MAKE_DIR)/minilibx

INC_PATH		:=		-I$(LIBFT_DIR) -I$(LEAKY_DIR) -I$(MAKE_DIR)/include

LIB_PATH		:=		-L$(LIBFT_DIR) -L$(LEAKY_DIR)

OS				=	$(shell uname -s)
ifeq ($(OS), Linux)
	MLXFLAGS	=		-L /usr/local/lib -lmlx_Linux -L/usr/X11/lib -I/usr/local/include -lXext -lX11 -lz
else
	LIB_PATH	+=		-L $(MLX_DIR)
	INC_PATH	+=		-I $(MLX_DIR)
	MLXFLAGS	=		-lmlx -framework OpenGL -framework AppKit -lz
endif

RELEASE_LIBS		:=		$(MLXFLAGS) $(LIB_PATH) -lft -lleaky -lm
DEBUG_LIBS			:=		$(MLXFLAGS) $(LIB_PATH) -lftd -lleakyd -lm

BIN_CC				:=		gcc

RELEASE_BIN_CFLAGS		:=
RELEASE_BIN_CFLAGS		+=		-MD
RELEASE_BIN_CFLAGS		+=		-Wall -Wextra -Werror -O3
RELEASE_BIN_CFLAGS		+=		-mllvm -inline-threshold=100000000
RELEASE_BIN_CFLAGS		+=		$(INC_PATH)

DEBUG_BIN_CFLAGS		:=
DEBUG_BIN_CFLAGS		+=		-MD
DEBUG_BIN_CFLAGS		+=		-Wall -Wextra -Werror
DEBUG_BIN_CFLAGS		+=		-g3 -DDEBUG
DEBUG_BIN_CFLAGS		+=		$(INC_PATH)

PROFILE_BIN_CFLAGS		:=
PROFILE_BIN_CFLAGS		+=		-MD -DDEBUG_PROFILE
PROFILE_BIN_CFLAGS		+=		-Wall -Wextra
PROFILE_BIN_CFLAGS		+=		-g3 -fsanitize=address -finstrument-functions
PROFILE_BIN_CFLAGS		+=		$(INC_PATH)

RELEASE_BIN_LDFLAGS		:=

DEBUG_BIN_LDFLAGS		:=
DEBUG_BIN_LDFLAGS		+=		-fsanitize=address

PROFILE_BIN_LDFLAGS		:=		-fsanitize=address

RELEASE_LIBFT_LIB	:=		$(LIBFT_DIR)/libft.a
DEBUG_LIBFT_LIB		:=		$(LIBFT_DIR)/libftd.a

RELEASE_LEAKY_LIB	:=		$(LEAKY_DIR)/libleaky.a
DEBUG_LEAKY_LIB		:=		$(LEAKY_DIR)/libleakyd.a

export MAKE_DIR
export RELEASE_OBJS_DIR
export DEBUG_OBJS_DIR
export PROFILE_OBJS_DIR
export MASTER_MAKE
export SRCS_DIR
export OBJS_DIR
export INC_PATH
export LIB_PATH
export RELEASE_LIBS
export DEBUG_LIBS
export BIN_CC
export RELEASE_BIN_CFLAGS
export DEBUG_BIN_CFLAGS
export PROFILE_BIN_CFLAGS
export RELEASE_BIN_LDFLAGS
export DEBUG_BIN_LDFLAGS
export PROFILE_BIN_LDFLAGS
export DEBUG_LIBFT_LIB
export RELEASE_LIBFT_LIB
export DEBUG_LEAKY_LIB
export RELEASE_LEAKY_LIB
export LIB_PATH
export LIBFT_DIR
export LEAKY_DIR

.PHONY: all
all: header
	@$(MAKE) -j4 -C $(LIBFT_DIR)
ifeq ($(OS), Darwin)
	@$(MAKE) -j4 -C $(MLX_DIR)
endif
	@$(MAKE) -j4 -C $(SRCS_DIR) -r -R --warn-undefined-variables

.PHONY: perf
perf: header
	@$(MAKE) -j4 -C $(LIBFT_DIR)
ifeq ($(OS), Darwin)
	@$(MAKE) -j4 -C $(MLX_DIR)
endif
	@$(MAKE) -j4 -C $(SRCS_DIR) -r -R --warn-undefined-variables perf

.PHONY: debug
debug: header
	@$(MAKE) -j4 -C $(LIBFT_DIR) debug
ifeq ($(OS), Darwin)
	@$(MAKE) -j4 -C $(MLX_DIR)
endif
	@$(MAKE) -j4 -C $(SRCS_DIR) -r -R --warn-undefined-variables debug

.PHONY: profile
profile: header
	@$(MAKE) -j4 -C $(LIBFT_DIR)
ifeq ($(OS), Darwin)
	@$(MAKE) -j4 -C $(MLX_DIR)
endif
	@$(MAKE) -j4 -C $(SRCS_DIR) -r -R --warn-undefined-variables profile
	./cub3dp 2> output.txt
	./profily cub3dp > profile_log.txt

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

.PHONY: cub_profile_re
cub_profile_re:
	@$(MAKE) -C $(SRCS_DIR) fclean
	@$(MAKE) -C $(SRCS_DIR) profile

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
