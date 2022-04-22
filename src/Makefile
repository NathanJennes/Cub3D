NAME 			=	cub3d

# Source files
# ****************************************************************************

SRCS_FILE		=	main.c core.c hooks.c error_utils.c colors_utils.c draw.c

SRCS			=	$(addprefix $(SRCS_DIR)/, $(SRCS_FILE))
OBJS			=	$(addprefix $(OBJS_DIR)/, $(notdir $(SRCS:.c=.o)))

DEPENDS			=	$(OBJS:.o=.d)

# Recipe
# ****************************************************************************

all: $(NAME)

$(OBJS_DIR)/%.o:	$(SRCS_DIR)/%.c | $(OBJS_DIR)
	@$(BIN_CC) $(BIN_CFLAGS) -c $< -o $@
	@printf "$(_GREEN)█$(_END)"

$(NAME): $(OBJS) $(LIBFT_LIB)
	@printf "$(_BLUE)\nCompiled source files\n"
	@$(BIN_CC) $(BIN_CFLAGS) $(OBJS) $(LIBS) $(MLXFLAGS) -o ../$@
	@printf "$(_GREEN)Finish compiling $(NAME)!$(_END)\n"

bonus: all

debug:
	@$(MAKE) $(NAME_DBG) -C .

clean:
	@printf "$(_YELLOW)Removing object files ...$(_END)\n"
	@rm -rf $(OBJS_DIR)
	@rm -fr *.dSYM

fclean:	clean
	@printf "$(_RED)Removing Executable ...$(_END)\n"
	@rm -rf ../$(NAME)

re:		fclean all

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
