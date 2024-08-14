# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jadyar <jadyar@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/13 19:30:53 by jadyar            #+#    #+#              #
#    Updated: 2024/08/14 14:55:07 by jadyar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Variables
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude #-fsanitize=thread
LDFLAGS = -lpthread

# Source files
SRCS = main.c init.c philo_routine.c utils.c parse_args.c monitor.c
# Header files
HEADERS = philosopher.h
# Object files
OBJS = $(SRCS:.c=.o)
# Executable name
EXEC = philosophers

# Default target
all: $(EXEC)

# Rule to build the executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Rule to build object files
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up build files
clean:
	$(RM) $(OBJS) $(EXEC)

fclean: clean
	$(RM) $(EXEC)

re: fclean all

# Phony targets
.PHONY: all