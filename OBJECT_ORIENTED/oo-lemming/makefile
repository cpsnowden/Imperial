OBJ_F=main.o Lemming.o direction.o
EXE_F=main
COMP=g++
CPP_FLG= -Wall -g -MMD

$(EXE_F): $(OBJ_F)
	$(COMP) $(CPP_FLG) $(OBJ_F) -o $(EXE_F)

Lemming.o: Lemming.h Lemming.cpp Direction.h Room.h
	$(COMP) $(CPP_FLG) -c Lemming.cpp

main.o: main.cpp Lemming.h Direction.h Room.h 
	$(COMP) $(CPP_FLG) -c main.cpp

direction.o: direction.cpp direction.h
	$(COMP) $(CPP_FLG) -c direction.cpp

-include $(OBJ_F:.o=.d) 

.PHONY: clean

clean:
	rm -f $(OBJ_F) $(EXE_F) $(OBJ_F:.o=.d)  
