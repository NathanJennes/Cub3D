RELEASE_NAME 			:=	cub3d
DEBUG_NAME				:=	cub3dd

# Source files
# ****************************************************************************

CORE_DIR		:=	core
CORE_FILE		:=	main.c exit.c main_loop.c init.c gc.c collision.c			\
					getters.c getters_2.c window.c cub_error.c player.c			\
					player_update.c getters_3.c
CORE_SRCS		:=	$(addprefix $(CORE_DIR)/, $(CORE_FILE))

INPUT_DIR		:=	$(CORE_DIR)/input
INPUT_FILE		:=	input_device.c key_listeners.c key_manager.c	\
					mouse_listeners.c mouse_manager.c
INPUT_SRCS		:=	$(addprefix $(INPUT_DIR)/, $(INPUT_FILE))

RENDER_DIR		:=	render
RENDER_FILE		:=	render_primitives.c render_primitives_img.c	\
					render_primitives_unsafe.c render_primitives_img_unsafe.c	\
					colors.c colors_utils.c	utils.c texture_wall_utils.c	\
					screen_rendering.c texture_rendering.c	\
					render_walls.c raycasting.c	\
					texture_wall.c	\
					init_renderer.c
RENDER_SRCS		:=	$(addprefix $(RENDER_DIR)/, $(RENDER_FILE))

TEXTURES_DIR	:=	textures
TEXTURES_FILE	:=	xpm_loader.c texture_generation.c	\
					texture_deletion.c texture_utils.c	\
					texture_manager.c texture_manager_helper.c	\
					texture_grayscale.c texture_inversed.c texture_flip.c	\
					texture_walls_generation.c
TEXTURE_SRCS	:=	$(addprefix $(TEXTURES_DIR)/, $(TEXTURES_FILE))

IO_DIR			:=	io
IO_FILE			:=	loaded_map.c map_error.c
IO_SRCS			:=	$(addprefix $(IO_DIR)/, $(IO_FILE))

SAVE_DIR		:=	$(IO_DIR)/save
SAVE_FILE		:=	save_deserialization.c\
					save_deserialization_mandatory.c save_deserialization_mandatory_utils.c	\
					map_construction.c map_checking.c player_checking.c map_checking_utils.c
SAVE_SRCS		:=	$(addprefix $(SAVE_DIR)/, $(SAVE_FILE))

SETTINGS_DIR		:=	$(IO_DIR)/settings
SETTINGS_FILE		:=	load_settings.c
SETTINGS_SRCS		:=	$(addprefix $(SETTINGS_DIR)/, $(SETTINGS_FILE))

SRCS			:=	$(addprefix $(SRCS_DIR)/, $(CORE_SRCS))						\
					$(addprefix $(SRCS_DIR)/, $(SAVE_SRCS))						\
					$(addprefix $(SRCS_DIR)/, $(RENDER_SRCS))					\
					$(addprefix $(SRCS_DIR)/, $(TEXTURE_SRCS))					\
					$(addprefix $(SRCS_DIR)/, $(IO_SRCS))						\
					$(addprefix $(SRCS_DIR)/, $(INPUT_SRCS))					\
					$(addprefix $(SRCS_DIR)/, $(SETTINGS_SRCS))					\

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

$(RELEASE_OBJS_DIR)/%.o:	$(SRCS_DIR)/$(TEXTURES_DIR)/%.c | $(RELEASE_OBJS_DIR)
	@$(BIN_CC) $(RELEASE_BIN_CFLAGS) -c $< -o $@
	@printf "$(_GREEN)█$(_END)"

$(RELEASE_OBJS_DIR)/%.o:	$(SRCS_DIR)/$(IO_DIR)/%.c | $(RELEASE_OBJS_DIR)
	@$(BIN_CC) $(RELEASE_BIN_CFLAGS) -c $< -o $@
	@printf "$(_GREEN)█$(_END)"

$(RELEASE_OBJS_DIR)/%.o:	$(SRCS_DIR)/$(SAVE_DIR)/%.c | $(RELEASE_OBJS_DIR)
	@$(BIN_CC) $(RELEASE_BIN_CFLAGS) -c $< -o $@
	@printf "$(_GREEN)█$(_END)"

$(RELEASE_OBJS_DIR)/%.o:	$(SRCS_DIR)/$(INPUT_DIR)/%.c | $(RELEASE_OBJS_DIR)
	@$(BIN_CC) $(RELEASE_BIN_CFLAGS) -c $< -o $@
	@printf "$(_GREEN)█$(_END)"

$(RELEASE_OBJS_DIR)/%.o:	$(SRCS_DIR)/$(SETTINGS_DIR)/%.c | $(RELEASE_OBJS_DIR)
	@$(BIN_CC) $(RELEASE_BIN_CFLAGS) -c $< -o $@
	@printf "$(_GREEN)█$(_END)"

$(RELEASE_NAME): $(RELEASE_OBJS) $(RELEASE_LIBFT_LIB) $(RELEASE_LEAKY_LIB)
	@printf "$(_BLUE)\nCompiled source files\n"
	@$(BIN_CC) $(RELEASE_BIN_LDFLAGS) $(RELEASE_OBJS) $(RELEASE_LIBS) -o ../$@
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

$(DEBUG_OBJS_DIR)/%d.o:	$(SRCS_DIR)/$(TEXTURES_DIR)/%.c | $(DEBUG_OBJS_DIR)
	@$(BIN_CC) $(DEBUG_BIN_CFLAGS) -c $< -o $@
	@printf "$(_GREEN)█$(_END)"

$(DEBUG_OBJS_DIR)/%d.o:	$(SRCS_DIR)/$(IO_DIR)/%.c | $(DEBUG_OBJS_DIR)
	@$(BIN_CC) $(DEBUG_BIN_CFLAGS) -c $< -o $@
	@printf "$(_GREEN)█$(_END)"

$(DEBUG_OBJS_DIR)/%d.o:	$(SRCS_DIR)/$(SAVE_DIR)/%.c | $(DEBUG_OBJS_DIR)
	@$(BIN_CC) $(DEBUG_BIN_CFLAGS) -c $< -o $@
	@printf "$(_GREEN)█$(_END)"

$(DEBUG_OBJS_DIR)/%d.o:	$(SRCS_DIR)/$(INPUT_DIR)/%.c | $(DEBUG_OBJS_DIR)
	@$(BIN_CC) $(DEBUG_BIN_CFLAGS) -c $< -o $@
	@printf "$(_GREEN)█$(_END)"

$(DEBUG_OBJS_DIR)/%d.o:	$(SRCS_DIR)/$(SETTINGS_DIR)/%.c | $(DEBUG_OBJS_DIR)
	@$(BIN_CC) $(DEBUG_BIN_CFLAGS) -c $< -o $@
	@printf "$(_GREEN)█$(_END)"

$(DEBUG_NAME): $(DEBUG_OBJS) $(DEBUG_LIBFT_LIB) $(DEBUG_LEAKY_LIB)
	@printf "$(_BLUE)\nCompiled source files\n"
	@$(BIN_CC) $(DEBUG_BIN_LDFLAGS) $(DEBUG_OBJS) $(DEBUG_LIBS) -o ../$@
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

$(RELEASE_LEAKY_LIB):
	@$(MAKE) -j4 -C $(LEAKY_DIR) -r -R

$(DEBUG_LEAKY_LIB):
	@$(MAKE) -j4 -C $(LEAKY_DIR) -r -R

$(RELEASE_LIBFT_LIB):
	@$(MAKE) -j4 -C $(LIBFT_DIR) -r -R

$(DEBUG_LIBFT_LIB):
	@$(MAKE) -j4 -C $(LIBFT_DIR) -r -R

info:
	@echo $(RELEASE_OBJS)
	@echo $(DEBUG_OBJS)

-include $(DEPENDS)
