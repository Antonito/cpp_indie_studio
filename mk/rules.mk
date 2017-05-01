MAIN_OBJ_DIR=	$(ROOT_DIR)/obj/
EMPTY=
OBJ_DIR=	$(MAIN_OBJ_DIR)$(shell basename $(CURDIR))/
PRECOMPILED_OBJ=$(PRECOMPILED_HEADER:%.hpp=%.hpp.gch)
OBJ=		$(PRECOMPILED_OBJ)		\
		$(SRC:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)
OBJ_DIR_LIST=	$(DIR_LIST:$(SRC_DIR)%=$(OBJ_DIR)%)

NAME_EXTENSION=	$(suffix $(NAME))

$(NAME):	$(MAIN_OBJ_DIR) $(OBJ_DIR_LIST) $(OBJ)
ifeq ($(NAME_EXTENSION),.a)
		@$(RANLIB) $(NAME) $(OBJ) && \
		$(ECHO) "$(WHITE)[$(GREEN)OK$(WHITE)] Generated $(CYAN)"$(NAME)"\n$(CLEAR)" || \
		$(ECHO) "$(WHITE)[$(RED)KO$(WHITE)] Generated $(CYAN)"$(NAME)"\n$(CLEAR)"
else
		@$(CXX) $(OBJ) -o $(NAME) $(LDFLAGS) && \
		$(ECHO) "$(WHITE)[$(GREEN)OK$(WHITE)] Linked $(CYAN)"$(NAME)"\n$(CLEAR)" || \
		$(ECHO) "$(WHITE)[$(RED)KO$(WHITE)] Linked $(CYAN)"$(NAME)"\n$(CLEAR)"
endif

$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp
ifeq ($(CXX),clang++)
		@$(CXX) $(CXXFLAGS) -c -o $@ $< $(addprefix -include-pch ,$(PRECOMPILED_OBJ)) && \
		$(ECHO) "$(WHITE)[$(GREEN)OK$(WHITE)] Compiled "$<"\n$(CLEAR)" || \
		$(ECHO) "$(WHITE)[$(RED)KO$(WHITE)] Compiled "$<"\n$(CLEAR)"
else
		@$(CXX) $(CXXFLAGS) -c -o $@ $< && \
		$(ECHO) "$(WHITE)[$(GREEN)OK$(WHITE)] Compiled "$<"\n$(CLEAR)" || \
		$(ECHO) "$(WHITE)[$(RED)KO$(WHITE)] Compiled "$<"\n$(CLEAR)"
endif

%.hpp.gch:		%.hpp
		@$(CXX) -x c++-header $(CXXFLAGS) -c -o $@ $(SRC_DIR)stdafx.cpp && \
		$(ECHO) "$(WHITE)[$(GREEN)OK$(WHITE)] Precompiled "$<"\n$(CLEAR)" || \
		$(ECHO) "$(WHITE)[$(RED)KO$(WHITE)] Precompiled "$<"\n$(CLEAR)"

$(MAIN_OBJ_DIR) $(OBJ_DIR_LIST):
		@$(MKDIR) $@ && \
		$(ECHO) "$(WHITE)[$(PURPLE)MKDIR$(WHITE)] Created obj directory $(CYAN)"$@"\n$(CLEAR)" || \
		$(ECHO) "$(WHITE)[$(PURPLE)MKDIR$(WHITE)] Cannot create obj directory $(CYAN)"$@"\n$(CLEAR)"

all:		$(NAME)

infos:
		@$(ECHO) "$(CYAN)Compiler:\t\t$(CXX)\n"
		@$(ECHO) "Compilation Flags:\t$(CXXFLAGS)\n"
ifeq ($(NAME_EXTENSION),.a)
		@$(ECHO) "Library Generation:\t$(RANLIB)\n$(CLEAR)"
else
		@$(ECHO) "Link Flags:\t\t$(LDFLAGS)\n$(CLEAR)"
endif

clean:
		@$(RM) $(OBJ)
		@$(RM_DIR) $(OBJ_DIR)
		@find $(MAIN_OBJ_DIR) -maxdepth 0 -empty -exec $(RM_DIR) $(MAIN_OBJ_DIR) {} \;
		@$(ECHO) "$(WHITE)[$(YELLOW)RM$(WHITE)] Removed OBJs files and directory\n$(CLEAR)"


fclean:		clean
		@$(RM) $(NAME)
		@$(ECHO) "$(WHITE)[$(YELLOW)RM$(WHITE)] Removed $(CYAN)"$(NAME)"\n$(CLEAR)"

re:		fclean all

run:
		./$(NAME)

.PHONY: all clean fclean re infos run
