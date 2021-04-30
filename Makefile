.PHONY: clean All

All:
	@echo "----------Building project:[ ClozeMoodleGenerator - Release ]----------"
	@cd "ClozeMoodleGenerator" && "$(MAKE)" -f  "ClozeMoodleGenerator.mk"
clean:
	@echo "----------Cleaning project:[ ClozeMoodleGenerator - Release ]----------"
	@cd "ClozeMoodleGenerator" && "$(MAKE)" -f  "ClozeMoodleGenerator.mk" clean
