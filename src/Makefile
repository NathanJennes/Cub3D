RELEASE_NAME 			:=	cub3d
DEBUG_NAME				:=	cub3dd

# Source files
# ****************************************************************************

CORE_DIR		:=	core
CORE_FILE		:=	main.c exit.c main_loop.c error_utils.c init.c gc.c			\
					getters.c getters_2.c window.c input_device.c key_manager.c	\
					key_listeners.c mouse_manager.c mouse_listeners.c
CORE_SRCS		:=	$(addprefix $(CORE_DIR)/, $(CORE_FILE))

RENDER_DIR		:=	render
RENDER_FILE		:=	render_primitives.c render_primitives_img.c	\
					colors.c colors_utils.c	\
					screen_rendering.c texture_rendering.c	\
					render_ui_texture.c render_text.c	\
					render_walls.c
RENDER_SRCS		:=	$(addprefix $(RENDER_DIR)/, $(RENDER_FILE))

UI_DIR			:=	ui
UI_FILE			:=	fps_counter.c ui_helper.c ui_manager.c						\
					render_minimap.c ui_init.c ui_component.c					\
					ui_button.c ui_img_box.c ui_label.c ui_slider.c	\
					ui_slider_update.c ui_button_update.c main_menu.c	\
					main_menu_buttons.c main_menu_buttons2.c	\
					ui_centering.c ui_padding.c ui_relative_pos.c main_menu_init.c
UI_SRCS			:=	$(addprefix $(UI_DIR)/, $(UI_FILE))

TEXTURES_DIR	:=	textures
TEXTURES_FILE	:=	xpm_loader.c texture_generation.c ambiant_occlusion.c		\
					texture_deletion.c texture_manager.c	\
					texture_manager_helper.c	\
					texture_utils.c		\
					texture_grayscale.c texture_inversed.c
TEXTURE_SRCS	:=	$(addprefix $(TEXTURES_DIR)/, $(TEXTURES_FILE))

IO_DIR			:=	io
IO_FILE			:=	savegame.c		\
					saves_manager.c
IO_SRCS			:=	$(addprefix $(IO_DIR)/, $(IO_FILE))

SAVE_DIR		:=	$(IO_DIR)/save
SAVE_FILE		:=	save_deserialization.c	\
					save_deserialization_mandatory.c save_deserialization_mandatory_utils.c	\
					save_deserialization_map.c save_deserialization_map_content.c	\
					save_deserialization_map_specs.c save_deserialization_map_textures.c	\
					save_deserialization_player.c	\
					save_serialization.c	\
					map_construction.c
SAVE_SRCS		:=	$(addprefix $(SAVE_DIR)/, $(SAVE_FILE))

SRCS			:=	$(addprefix $(SRCS_DIR)/, $(CORE_SRCS))						\
					$(addprefix $(SRCS_DIR)/, $(UI_SRCS))						\
					$(addprefix $(SRCS_DIR)/, $(RENDER_SRCS))					\
					$(addprefix $(SRCS_DIR)/, $(TEXTURE_SRCS))					\
					$(addprefix $(SRCS_DIR)/, $(IO_SRCS))						\
					$(addprefix $(SRCS_DIR)/, $(SAVE_SRCS))

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

$(RELEASE_OBJS_DIR)/%.o:	$(SRCS_DIR)/$(SAVE_DIR)/%.c | $(RELEASE_OBJS_DIR)
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

$(DEBUG_OBJS_DIR)/%d.o:	$(SRCS_DIR)/$(SAVE_DIR)/%.c | $(DEBUG_OBJS_DIR)
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

info:
	@echo $(RELEASE_OBJS)
	@echo $(DEBUG_OBJS)

-include $(DEPENDS)
