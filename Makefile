NAME ?= crab_test


#Source file variables
SRCS = main.cc crab.cc dataset.cc

all: A_asan B_no_opt C_O3_asan D_O3 D2_Ofast

# A. Optimizer off, ASAN and UBSAN on  
A_asan:
	g++ $(SRCS) -O0 -fsanitize=address -fsanitize=undefined -g -o $(NAME)_A_asan


# B. Optimizer off, ASAN and UBSAN off   
B_no_opt:
	g++ $(SRCS) -O0 -o $(NAME)_B_no_opt 

# C. O3 Optimizer on, ASAN and UBSAN on 
C_O3_asan: 
	g++ $(SRCS) -O3 -fsanitize=address -fsanitize=undefined -g -o $(NAME)_C_O3_asan

# D. O3 Optimizer on, ASAN and UBSAN off
D_O3:
	g++ $(SRCS) -O3 -o $(NAME)_D_O3

# D2. Ofast Optimizer on, ASAN and UBSAN off
D2_Ofast: 
	g++ $(SRCS) -Ofast -o $(NAME)_D2_Ofast 


#PGO PROFILES (E, F, G)
pgo_gen:
	g++ $(SRCS) -O3 -fprofile-generate -o $(NAME)_profiler

# E. PGO, O3
E_pgo: 
	g++ $(SRCS) -O3  -fprofile-use -o $(NAME)_E_pgo

# F. PGO, LTO, O3
F_pgo_lto: 
	g++ $(SRCS) -O3 -flto -fprofile-use -o $(NAME)_F_pgo_lto

# G. Likely, Unlikely
G_likely: 
	g++ $(SRCS) -O3 -flto -fprofile-use -o $(NAME)_G_likely  

#Phony Targets
.PHONY: all A_asan B_no_opt C_O3_asan D_O3 D2_Ofast pgo_gen E_pgo F_pgo_lto G_likely clean 

clean:
	rm -f *.gcda *.gcno $(NAME)*
