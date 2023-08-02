CC = g++
FLAGS = -Wall -Werror -Wextra -std=c++17
TEST_FLAGS = -lgtest -lgmock -pthread
MODEL_CALC_FILES = ./model/calc/*
MODEL_CREDIT_CALC_FILES = ./model/credit_calc/*
CONTROLLER_CALC_FILES = ./controller/calc/*
CONTROLLER_CREDIT_CALC_FILES = ./controller/credit_calc/*
CONTROLLER_VIEW_FILES = ./view/calc/*.cc ./view/calc/*.h
CONTROLLER_CREDIT_VIEW_FILES = ./view/credit_calc/*
TEST_FILES = ./unit_tests/unit_tests.cc ./model/calc/*.cc ./model/credit_calc/*.cc

all:
	install
#	=== Установка программы ===
#	Возможно понадобятся следующие команды:
#	brew install qt5
#	brew link qt5 --force
install:
	@echo ------------------- INSTALL CALC --------------------
	mkdir build && cd ./main && qmake && make && make clean && rm -rf Makefile && rm -rf .qmake.stash && mv view.app ../build/
	mv build/view.app build/SmartCalc_v2.0.app
	@echo ----------------- INSTALL COMPLETE ------------------

#	=== Установка программы ===
uninstall:
	@echo ------------------- UNINSTALL CALC -------------------
	rm -rf build
	@echo ---------------- UNINSTALL COMPLETE ------------------

#	=== DIST ===
dist:
	@echo -------------------DIST-------------------
	rm -rf Archive_SmartCalc_v2.0/
	mkdir Archive_SmartCalc_v2.0/
	cp -R build/SmartCalc_v2.0.app Archive_SmartCalc_v2.0/
	tar cvzf Archive_SmartCalc_v2.0.tgz ./Archive_SmartCalc_v2.0
	rm -rf Archive_SmartCalc_v2.0/

#	=== dvi ===
dvi:
	open index.html

#	=== Общий тест кода ===
tests: test	leaks clang clean

#	=== Запуск unit-тестов ===
test:
	@echo --------------------- UNIT TESTS ---------------------
	$(CC) $(FLAGS) $(TEST_FILES) -o unit_tests.out $(TEST_FLAGS)
	./unit_tests.out
	@echo ---------------------- SUCCESS -----------------------

#	=== Проверка на утечки памяти ===
leaks:
	@echo --------------------- LEAK TESTS ---------------------
	leaks -atExit -- ./unit_tests.out
	@echo ---------------------- SUCCESS -----------------------

#	=== Проверка clang ===
clang:
	@echo ----------------------- CLANG ------------------------
	cp ../materials/linters/.clang-format .clang-format 
	clang-format -n $(MODEL_CALC_FILES) $(MODEL_CREDIT_CALC_FILES)
	clang-format -n $(CONTROLLER_CALC_FILES) $(CONTROLLER_CREDIT_CALC_FILES)
	clang-format -n $(CONTROLLER_VIEW_FILES) $(CONTROLLER_CREDIT_VIEW_FILES)
	clang-format -n ./unit_tests/unit_tests.cc
	rm -rf .clang-format
	@echo ---------------------- SUCCESS -----------------------

#	=== Очистка ===
clean:
	@echo ----------------------- CLEAN ------------------------
	rm -rf unit_tests.out .clang-format Archive_SmartCalc_v2.0.tgz
	@echo ---------------------- SUCCESS -----------------------