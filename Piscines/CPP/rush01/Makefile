GCC= clang++ -Wall -Wextra -Werror
RM= rm -f
SRC=main.cpp \
	SdlWin.cpp \
	NcWin.cpp 

OBJ=$(SRC:.cpp=.o)
NAME=Yolo
INC_PATH=~/library/frameworks/SDL2.framework/Headers 
TTF_PATH=~/library/frameworks/SDL2_ttf.framework/Headers
FRAMEWORK=-F ~/library/frameworks -framework SDL2 -framework SDL2_ttf

all:$(NAME)

%.o:%.cpp
	@$(GCC) -c $^ -I $(INC_PATH) -I $(TTF_PATH)

$(NAME):$(OBJ)
	@$(GCC) -o $(NAME) $(OBJ)  $(FRAMEWORK)  -lncurses
	@echo "\033[0;33m$@ was created\033[0m"

clean:
	@$(RM) $(OBJ)

fclean:	clean
	@$(RM) $(NAME)

re: fclean all

here:
	@$(RM) $(OBJ)
