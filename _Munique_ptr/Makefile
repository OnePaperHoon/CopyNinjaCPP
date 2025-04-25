NAME			=		run

CXX				=		c++
CXXFLAGS		=		-Wall -Wextra -Werror -std=c++11

SRCS_DIR	= ./srcs/
SRCS		=	main.cpp
OBJS_SRCS	=	$(addprefix $(SRCS_DIR), $(SRCS:.cpp=.o))
OBJS		=	$(OBJS_SRCS)

all : $(NAME)

$(NAME) : $(OBJS)
	@echo $(CURSIVE)$(YELLOW) "      - Making $(NAME) -" $(NONE)
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $@
	@echo $(CURSIVE)$(YELLOW) "        - Compiling $(NAME) -" $(NONE)

%.o : %.cpp
	@echo $(CURSIVE)$(YELLOW) "      - Making object files -" $(NONE)
	@$(CXX) $(CXXFLAGS) -c $< -g -o $@

clean :
	@rm -fr $(OBJS)
	@echo $(CURSIVE)$(BLUE) "     - clean OBJ files -" $(NONE)

fclean : clean
	@rm -fr $(NAME)
	@echo $(CURSIVE)$(PURPLE)"      - clean $(NAME) file -"$(NONE)

re	:
	@make fclean
	@make all

.PHONY: all make clean fclean bonus re

NONE='\033[0m'
GREEN='\033[32m'
YELLOW='\033[33m'
GRAY='\033[2;37m'
CURSIVE='\033[3m'
PURPLE='\033[35m'
BLUE='\033[34m'
DELETELINE='\033[K;
