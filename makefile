include makefile.cfg

all: build link run clear
.PHONEY = all

OBJECTS = $(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(wildcard $(SRC)/*.c))

$(OBJ)/%.o: $(SRC)/%.c
	@$(COMPILER) $(C_FLAGS) $< -o $@
	
build:$(OBJECTS)
	@echo "build"
	@$(ASSEMBLER) $(A_FLAGS) -o obj/start.o src/start.asm 


link:
	@echo "link"
	@$(LINKER) $(L_FLAGS) -o $(OUTPUT) obj/*.o

run:
	@echo "run"
	@$(EMULATOR) $(EMULATOR_FLAGS) $(OUTPUT)

clear:
	@echo "clear"
	@rm -f obj/*.o
	@rm -f obj/kernel/*.bin
