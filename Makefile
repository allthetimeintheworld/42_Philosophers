# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jadyar <jadyar@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/08 12:21:25 by jadyar            #+#    #+#              #
#    Updated: 2024/08/09 11:58:03 by jadyar           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Variables
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=thread -g -Iinclude
LDFLAGS = -lpthread

# Source files
SRCS = src/main.c src/init.c src/utils.c src/monitor.c
# Header files
HEADERS = include/philo.h
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
	rm -f $(OBJS) $(EXEC)

fclean: clean
	$(RM) $(EXEC)

re: fclean all

# Phony targets
.PHONY: all clean