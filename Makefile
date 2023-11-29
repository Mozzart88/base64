SRC_DIR := src
TEST_DIR := test
SS := $(SRC_DIR)/decode.c $(SRC_DIR)/encode.c
TEST_SS := $(wildcard $(TEST_DIR)/*.test.c) $(TEST_DIR)/test.c
NAME := libbase64.a
TEST := sandbox/test
SANDBOX := sandbox
OBJD := obj
OBJS := $(SS:.c=.o)
OBJSD := $(OBJS:src/%=obj/%)
TEST_OBJS := $(TEST_SS:.c=.o)
TEST_OBJSD := $(TEST_OBJS:test/%=obj/%)
H := -L . -lbase64
CC := clang
CF := -Wall -Wextra -Werror -I include/
ifdef debug
CF += -g
else
CF += -O3
endif

TITLE_NAME := print_title_name
TITLE_TEST := print_title_test
TITLE_RUN_TEST := print_title_run_test

all: $(OBJD) $(NAME)

$(NAME): $(TITLE_NAME) $(OBJSD)
	@ar rc $(NAME) $(OBJSD)
	@echo "\033[34m done\033[0m"

print_title_name:
	@echo "\033[32mCompiling\033[0m \033[1;32m$(NAME)s\033[1;0m: \c"

$(TEST): $(TITLE_TEST) $(TEST_OBJSD)
	@$(CC) $(CF) $(INC) $(H) -o $(TEST) $(TEST_OBJSD)
	@echo "\033[34m done\033[0m"

print_title_test:
	@echo "\033[32mCompiling\033[0m \033[1;32m$(TEST_DIR)s\033[1;0m: \c"

print_title_run_test:
	@echo "\n\033[1;32mRun $(TEST_DIR)s\033[1;0m:"

obj/%.o: src/%.c
	@$(CC) $(CF) -c $< -o $@
	@echo "\033[34m.\033[0m\c"

obj/%.o: test/%.c
	@$(CC) $(CF) -c $< -o $@
	@echo "\033[34m.\033[0m\c"

$(OBJD):
	$(shell mkdir -p $(OBJD))

$(SANDBOX):
	$(shell mkdir -p $(SANDBOX))

clean:
	/bin/rm -fr $(OBJD) $(SANDBOX)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all



test: $(OBJD) $(NAME) $(SANDBOX) $(TEST) $(TITLE_RUN_TEST)
	./sandbox/test
	

.SILENT: clean fclean re test

.PHONY: clean fclean all test