# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 14:12:23 by mogawa            #+#    #+#              #
#    Updated: 2024/12/17 07:04:46 by mogawa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET		:=	webserv
CXX			:=	clang++
CXXFLAGS	:=	-Wall -Wextra -Werror -std=c++98 -MMD -MP 
LDFLAGS		:=	
INCDIRS		:=	$(shell find include -type d)
INC			:=	$(addprefix -I, $(INCDIRS))

SRC			:=	$(filter-out %/test/%, \
				$(wildcard src/*.cpp) \
				$(wildcard src/*/*.cpp) \
				$(wildcard src/*/*/*.cpp))
SRCDIR		:=	$(sort $(dir $(SRC)))
VPATH		:=	$(SRCDIR)
OBJDIR		:=	obj
OBJ			:=	$(addprefix $(OBJDIR)/, $(addsuffix .o, $(notdir $(basename $(SRC)))))
DEP			:=	$(OBJ:.o=.d)

ifdef WITH_DEBUG
CXXFLAGS	:=	$(filter-out -Werror, $(CXXFLAGS))
CXXFLAGS	+=	-ggdb -O0 -fsanitize=address,undefined -fno-limit-debug-info -fno-omit-frame-pointer
LDFLAGS		:=	-fsanitize=address,undefined
endif

ifdef WITH_GDB
CXXFLAGS	:=	$(filter-out -Werror, $(CXXFLAGS))
CXXFLAGS	+=	-ggdb -O0 -fsanitize=address,undefined -fno-limit-debug-info -fno-omit-frame-pointer -DDEBUG
LDFLAGS		:=	-fsanitize=address,undefined
endif



all: $(TARGET)

$(OBJDIR)/%.o: %.cpp
	@mkdir -p $(OBJDIR)
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

$(TARGET):	$(OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

debug: fclean
	$(MAKE) all WITH_DEBUG=1

gdb: fclean
	$(MAKE) all WITH_GDB=1

clean:
	$(RM) -r $(OBJDIR)
	$(down)

fclean: clean
	$(RM) $(TARGET)

re: fclean
	$(MAKE) all

docker:
	docker container exec -it webserv bash

down:
	docker compose -f .devcontainer/docker-compose.yml down

valgrind:
	valgrind --leak-check=full --track-fds=yes -s ./$(TARGET)

-include $(DEP)

.PHONY: clean fclean gdb debug re docker val up down

# $(info SRC=$(SRC))
