# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/12 14:05:22 by ivalimak          #+#    #+#              #
#    Updated: 2023/12/05 16:31:45 by ivalimak         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	pipex

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -g
#CFLAGS	=	-Wall -Wextra -Werror -g -fsanitize=address -static-libsan

SRCDIR	=	src
OBJDIR	=	obj
LIBDIR	=	libft

LIBFT	=	$(LIBDIR)/libft.a

SRCS	=	$(SRCDIR)/main.c \
			$(SRCDIR)/exec.c \
			$(SRCDIR)/cmd.c \
			$(SRCDIR)/utils.c

OBJS	=	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJDIR) $(OBJS)
	@echo Compiling $(NAME)...
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBDIR) -lft -o $(NAME)

$(LIBFT):
	@make -C $(LIBDIR) --no-print-directory

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@echo Compiling $@
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -C $(LIBDIR) clean --no-print-directory
	@rm -rf $(OBJDIR)

fclean: clean
	@make -C $(LIBDIR) fclean --no-print-directory
	@rm -f $(NAME)

re: fclean all
