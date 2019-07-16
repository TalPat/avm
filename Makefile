NAME			=	avm
SRCDIR		=	./src/
SRC				= 	main.cpp\
					Lexer.cpp\
					Operand.cpp\
					OperandFactory.cpp\
					Parser.cpp\
					Vm.cpp

SRCPATH		:=	$(addprefix $(SRCDIR), $(SRC))
OBJDIR		=	obj/
OBJ				=	$(SRC:%.cpp=%.o)
OBJPATH		:=	$(addprefix $(OBJDIR), $(OBJ))

HEADER		=	./include/
CFLAGS		= -std=c++11#-Wall -Werror -Wextra
CC				=	clang++
INCLUDES	=	-I $(HEADER)

all: $(NAME)

$(NAME): $(OBJPATH)
	$(CC) -o $(NAME) $(SRCPATH) $(INCLUDES) $(CFLAGS)

$(OBJDIR)%.o: $(SRCDIR)%.cpp
	mkdir -p $(OBJDIR)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCLUDES)

clean:
	rm -rf $(OBJPATH)

fclean:	clean
	rm -rf $(NAME)

re: fclean all