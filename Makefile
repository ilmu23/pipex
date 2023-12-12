# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ivalimak <ivalimak@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/12 14:05:22 by ivalimak          #+#    #+#              #
#    Updated: 2023/12/12 14:40:57 by ivalimak         ###   ########.fr        #
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

SRCS	=	$(SRCDIR)/main.c

BSRCS	=	$(SRCDIR)/main_bonus.c

CSRCS	=	$(SRCDIR)/cmd.c \
			$(SRCDIR)/pipe.c \
			$(SRCDIR)/exec.c \
			$(SRCDIR)/error.c \
			$(SRCDIR)/utils.c \

OBJS	=	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(SRCS))
BOBJS	=	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(BSRCS))
COBJS	=	$(patsubst $(SRCDIR)/%.c, $(OBJDIR)/%.o, $(CSRCS))

all: $(NAME)

$(NAME): $(LIBFT) $(OBJDIR) $(OBJS) $(COBJS)
	@echo Compiling $(NAME)...
	@$(CC) $(CFLAGS) $(OBJS) $(COBJS) -L$(LIBDIR) -lft -o $(NAME)

bonus: .bonus

.bonus: $(LIBFT) $(OBJDIR) $(BOBJS) $(COBJS)
	@echo Compiling $(NAME) bonus...
	@$(CC) $(CFLAGS) $(BOBJS) $(COBJS) -L$(LIBDIR) -lft -o $(NAME)
	@touch .bonus

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
	@rm -f .bonus

fclean: clean
	@make -C $(LIBDIR) fclean --no-print-directory
	@rm -f $(NAME)

re: fclean all
