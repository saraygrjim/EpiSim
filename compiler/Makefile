all: init compilar

init:
	@echo ""
	@echo "Compilador de Autómata Celular"
	@echo "Uso de make:"
	@echo "make       -> compilar"
	@echo "make clean -> borrar archivos intermedios"
	@echo ""

compilar: 
	# bison compiler_general.y
	# gcc compiler_general.tab.c -o compiler_general
	# bison compiler_cell.y
	# gcc compiler_cell.tab.c -o compiler_cell
	bison compiler.y
	gcc compiler.tab.c -o compiler

clean:
	@echo "Cleaning..."
	# @rm -rf compiler_general compiler_general.tab.c compiler_cell compiler_cell.tab.c *Result.txt
	@rm -rf compiler compiler.tab.c *Result.cpp