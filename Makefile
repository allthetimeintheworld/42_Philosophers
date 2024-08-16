# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jadyar <jadyar@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/15 10:11:50 by jadyar            #+#    #+#              #
#    Updated: 2024/08/16 17:04:45 by jadyar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Variables
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude #-fsanitize=thread
LDFLAGS = -lpthread

# Source files
SRCS = src/main.c src/init.c src/thread_routine.c src/utils.c src/parse_arg.c src/monitor.c src/error_handle.c src/simulate.c
# Header files
HEADERS = include/philosopher.h
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