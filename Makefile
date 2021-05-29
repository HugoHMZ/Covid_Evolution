##
## EPITECH PROJECT, 2021
## B-NWP-400-LIL-4-1-myftp-hugo.humez
## File description:
## Makefile
##

ECHO            =       /bin/echo -e
DEFAULT         =       "\033[00m"
GREEN           =       "\033[0;32m"
TEAL            =       "\033[1;36m"
RED             =       "\033[1;31m"
YELLOW		=	"\033[1;33m"
BLUE		=	"\033[1;34m"

CC              =       g++

RM              =       rm -f

NAME            =       covidEvolution

CXXFLAGS	+=	-I./core/includes -I./include -ggdb3
CXXFLAGS	+=	-Wextra -Wall -W -lsfml-graphics -lsfml-window -lsfml-system

S_SRC             =       src/main.cpp \
						  src/CovidEvolution.cpp \
						  src/SFML.cpp

OBJ             =       $(S_SRC:.cpp=.o)

all             :	sources_files $(NAME)

sources_files		:
			@$(ECHO) $(TEAL) "SOURCES FILES" $(DEFAULT)

$(NAME)         :	$(OBJ)
			@$(CC) -o $(NAME) $(OBJ) $(CXXFLAGS) && \
			 $(ECHO) $(YELLOW) "[OK]" $(BLUE) $(NAME) $(DEFAULT)  || \
			 $(ECHO) $(RED) "[XX]" $(TEAL) $(NAME) $(DEFAULT)

clean           :
			@rm -f $(OBJ)

fclean          :       clean
			@$(RM) $(NAME)

re              :       fclean all

.PHONY         :       all clean fclean re

.cpp.o		:
			@$(CC) $(CXXFLAGS) -c $< -o $@  && \
			 $(ECHO) $(YELLOW) "[OK]" $(BLUE) $< $(DEFAULT) || \
			 $(ECHO) $(RED) "[XX]" $(TEAL) $< $(DEFAULT)