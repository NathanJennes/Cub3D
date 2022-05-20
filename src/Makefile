RELEASE_NAME 			:=	cub3d
DEBUG_NAME				:=	cub3dd

# Source files
# ****************************************************************************

CORE_DIR		:=	core
CORE_FILE		:=	main.c exit.c main_loop.c error_utils.c hooks.c init.c gc.c	\
					getters.c getters_2.c window.c input_device.c player.c
CORE_SRCS		:=	$(addprefix $(CORE_DIR)/, $(CORE_FILE))

RENDER_DIR		:=	render
RENDER_FILE		:=	draw.c rendering_primitives.c colors_utils.c				\
					render_ui_texture.c render_ui.c	\
					render_walls.c render_debug.c
RENDER_SRCS		:=	$(addprefix $(RENDER_DIR)/, $(RENDER_FILE))

UI_DIR			:=	ui
UI_FILE			:=	fps_counter.c ui_helper.c ui_manager.c						\
					render_minimap.c ui_init.c ui_component.c ui_button.c		\
					print_debug.c
UI_SRCS			:=	$(addprefix $(UI_DIR)/, $(UI_FILE))

TEXTURES_DIR	:=	textures
TEXTURES_FILE	:=	xpm_loader.c texture_generation.c ambiant_occlusion.c		\
					texture_deletion.c texture_manager.c texture_utils.c		\
					texture_grayscale.c texture_inversed.c
TEXTURE_SRCS	:=	$(addprefix $(TEXTURES_DIR)/, $(TEXTURES_FILE))

IO_DIR			:=	io
IO_FILE			:=	savegame.c													\
					serialization.c												\
					deserialization.c deserialization_player.c					\
					deserialization_map.c deserialization_map_specs.c			\
					deserialization_map_textures.c deserialization_map_content.c\
					saves_manager.c	\
					map_construction.c	\
					parsing.c parsing_utils.c deserialization_settings.c
IO_SRCS			:=	$(addprefix $(IO_DIR)/, $(IO_FILE))

SRCS			:=	$(addprefix $(SRCS_DIR)/, $(CORE_SRCS))						\
					$(addprefix $(SRCS_DIR)/, $(UI_SRCS))						\
					$(addprefix $(SRCS_DIR)/, $(RENDER_SRCS))					\
					$(addprefix $(SRCS_DIR)/, $(TEXTURE_SRCS))					\
					$(addprefix $(SRCS_DIR)/, $(IO_SRCS))

RELEASE_OBJS	:=	$(addprefix $(RELEASE_OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))
DEBUG_OBJS		:=	$(addprefix $(DEBUG_OBJS_DIR)/, $(notdir $(SRCS:.c=d.o)))

DEPENDS			:=	$(RELEASE_OBJS:.o=.d) $(DEBUG_OBJS:.o=.d)

# Recipe
# ****************************************************************************

.PHONY: all
all: $(RELEASE_NAME)

.PHONY: debug
debug: $(DEBUG_NAME)

.PHONY: bonus
bonus: all

# --------------------------- #
#           Release           #
# --------------------------- #

$(RELEASE_OBJS_DIR)/%.o:	$(SRCS_DIR)/$(CORE_DIR)/%.c | $(RELEASE_OBJS_DIR)
	@$(BIN_CC) $(RELEASE_BIN_CFLAGS) -c $< -o $@
	@printf "$(_GREEN)█$(_END)"

$(RELEASE_OBJS_DIR)/%.o:	$(SRCS_DIR)/$(RENDER_DIR)/%.c | $(RELEASE_OBJS_DIR)
	@$(BIN_CC) $(RELEASE_BIN_CFLAGS) -c $< -o $@
	@printf "$(_GREEN)█$(_END)"

$(RELEASE_OBJS_DIR)/%.o:	$(SRCS_DIR)/$(UI_DIR)/%.c | $(RELEASE_OBJS_DIR)
	@$(BIN_CC) $(RELEASE_BIN_CFLAGS) -c $< -o $@
	@printf "$(_GREEN)█$(_END)"

$(RELEASE_OBJS_DIR)/%.o:	$(SRCS_DIR)/$(TEXTURES_DIR)/%.c | $(RELEASE_OBJS_DIR)
	@$(BIN_CC) $(RELEASE_BIN_CFLAGS) -c $< -o $@
	@printf "$(_GREEN)█$(_END)"

$(RELEASE_OBJS_DIR)/%.o:	$(SRCS_DIR)/$(IO_DIR)/%.c | $(RELEASE_OBJS_DIR)
	@$(BIN_CC) $(RELEASE_BIN_CFLAGS) -c $< -o $@
	@printf "$(_GREEN)█$(_END)"

$(RELEASE_NAME): $(RELEASE_OBJS) $(RELEASE_LIBFT_LIB) $(RELEASE_LEAKY_LIB)
	@printf "$(_BLUE)\nCompiled source files\n"
	@$(BIN_CC) $(RELEASE_BIN_CFLAGS) $(RELEASE_OBJS) $(RELEASE_LIBS) -o ../$@
	@printf "$(_GREEN)Finish compiling $(RELEASE_NAME)!$(_END)\n"

# --------------------------- #
#           Debug             #
# --------------------------- #

$(DEBUG_OBJS_DIR)/%d.o:	$(SRCS_DIR)/$(CORE_DIR)/%.c | $(DEBUG_OBJS_DIR)
	@$(BIN_CC) $(DEBUG_BIN_CFLAGS) -c $< -o $@
	@printf "$(_GREEN)█$(_END)"

$(DEBUG_OBJS_DIR)/%d.o:	$(SRCS_DIR)/$(RENDER_DIR)/%.c | $(DEBUG_OBJS_DIR)
	@$(BIN_CC) $(DEBUG_BIN_CFLAGS) -c $< -o $@
	@printf "$(_GREEN)█$(_END)"

$(DEBUG_OBJS_DIR)/%d.o:	$(SRCS_DIR)/$(UI_DIR)/%.c | $(DEBUG_OBJS_DIR)
	@$(BIN_CC) $(DEBUG_BIN_CFLAGS) -c $< -o $@
	@printf "$(_GREEN)█$(_END)"

$(DEBUG_OBJS_DIR)/%d.o:	$(SRCS_DIR)/$(TEXTURES_DIR)/%.c | $(DEBUG_OBJS_DIR)
	@$(BIN_CC) $(DEBUG_BIN_CFLAGS) -c $< -o $@
	@printf "$(_GREEN)█$(_END)"

$(DEBUG_OBJS_DIR)/%d.o:	$(SRCS_DIR)/$(IO_DIR)/%.c | $(DEBUG_OBJS_DIR)
	@$(BIN_CC) $(DEBUG_BIN_CFLAGS) -c $< -o $@
	@printf "$(_GREEN)█$(_END)"

$(DEBUG_NAME): $(DEBUG_OBJS) $(DEBUG_LIBFT_LIB) $(DEBUG_LEAKY_LIB)
	@printf "$(_BLUE)\nCompiled source files\n"
	@$(BIN_CC) $(DEBUG_BIN_CFLAGS) $(DEBUG_OBJS) $(DEBUG_LIBS) -o ../$@
	@printf "$(_GREEN)Finish compiling $(DEBUG_NAME)!$(_END)\n"

clean:
	@printf "$(_YELLOW)Removing object files ...$(_END)\n"
	@rm -rf $(RELEASE_OBJS_DIR)
	@rm -rf $(DEBUG_OBJS_DIR)
	@rm -fr *.dSYM

fclean:	clean
	@printf "$(_RED)Removing Executable ...$(_END)\n"
	@rm -rf ../$(RELEASE_NAME)
	@rm -rf ../$(DEBUG_NAME)

re:		fclean all

$(RELEASE_OBJS_DIR):
	@mkdir -p $(RELEASE_OBJS_DIR)

$(DEBUG_OBJS_DIR):
	@mkdir -p $(DEBUG_OBJS_DIR)

-include $(DEPENDS)
