all: init compilar

init:
	@echo ""
	@echo "Compilador de Autómata Celular"
	@echo "Uso de make:"
	@echo "make       -> compilar"
	@echo "make clean -> borrar archivos intermedios"
	@echo ""

compilar: 
	@echo "Compiling..."
	@bison compiler.y
	@gcc compiler.tab.c -o compiler
	@./run.sh

clean:
	@echo "Cleaning..."
	@rm -rf compiler compiler.tab.c *todojunto.cpp