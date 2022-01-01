include makefile.cfg

all: build link run create_img clean
.PHONEY = all

OBJECTS_C = $(patsubst $(C_SRC)/%.c, $(OBJ)/%.o, $(wildcard $(C_SRC)/*.c))
OBJECTS_ASM  = $(patsubst $(ASM_SRC)/%.asm, $(OBJ)/%.o, $(wildcard $(ASM_SRC)/*.asm))


$(OBJ)/%.o: $(C_SRC)/%.c
	@$(COMPILER) $(C_FLAGS) $< -o $@

$(OBJ)/%.o: $(ASM_SRC)/%.asm
	@$(ASSEMBLER) $(A_FLAGS) $< -o $@
	
build:$(OBJECTS_C) $(OBJECTS_ASM)
	@echo "build"

link:
	@echo "link"
	@$(LINKER) $(L_FLAGS) -o $(OUTPUT) obj/*.o

run:
	@echo "run"
	@$(EMULATOR) $(EMULATOR_FLAGS) $(OUTPUT)

clean:
	@echo "clean"
	@rm -f obj/*.o
	@rm -f obj/kernel/*.bin

create_img:
	@rm -f $(ISO_OUTPUT)
	@echo "create img"
	@cp $(OUTPUT) boot/kernel.bin
	@grub-mkrescue -o $(ISO_OUTPUT) obj/kernel
	@rm -f boot/kernel.bin
