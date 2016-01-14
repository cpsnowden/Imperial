OBJ_F=StorageDevice.o
EXE_F=StorageDevice
COMP=g++
CPP_FLG=-Wall -g -MMD

$(EXE_F): $(OBJ_F)
	$(COMP) $(CPP_FLG) $(OBJ_F) -o $(EXE_F)

%.o: %.cpp
	$(COMP) $(CPP_FLG) -c $<

-include $(OBJ_F:.o=.d) 

.PHONY: clean

clean:
	rm -f $(OBJ_F) $(EXE_F) $(OBJ_F:.o=.d)  
