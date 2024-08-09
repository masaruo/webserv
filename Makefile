# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mogawa <masaruo@gmail.com>                 +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/04 14:12:23 by mogawa            #+#    #+#              #
#    Updated: 2024/07/26 16:39:33 by mogawa           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

TARGET		:=	webserv
CXX			:=	c++
CXXFLAGS	=	-Wall -Wextra -Werror -std=c++98 -MMD -MP
LDFLAGS		=	
SRCDIR		:=	./src
INC			:=	-I./include -I./include/request -I./include/response -I./include/socket -I./include/utility
SRC			:=	$(wildcard $(SRCDIR)/*.cpp) \
				$(wildcard $(SRCDIR)/socket/*.cpp) \
				$(wildcard $(SRCDIR)/utility/*.cpp) \
				$(wildcard $(SRCDIR)/request/*.cpp) \
				$(wildcard $(SRCDIR)/response/*.cpp)
OBJDIR		:=	obj
OBJ			:=	$(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRC))
DEP			:=	$(OBJ:.o=.d)

ifdef WITH_ASAN
CXXFLAGS	:=	$(filter-out -Werror, $(CXXFLAGS))
CXXFLAGS	+=	-ggdb3 -O0 -fsanitize=address,undefined,leak
LDFLAGS		+=	-fsanitize=address,undefined,leak
endif

all: $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INC) -c $< -o $@

$(TARGET):	$(OBJ)
	$(CXX) $(LDFLAGS) $^ -o $@

debug: fclean
	$(MAKE) all WITH_ASAN=1

clean:
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(TARGET)

re: fclean
	$(MAKE) all

-include $(DEP)

.PHONY: clean fclean re
