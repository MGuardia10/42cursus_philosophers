# 42cursus_philosophers
The mandatory part of this project asks us to solve the dining [philosophers problem](https://medium.com/@francescofranco_39234/dining-philosophers-problem-36d0030a4459) and implement a mutithreading solution using mutexes.

![LINUX](https://img.shields.io/badge/Linux-a?style=for-the-badge&logo=linux&color=grey)
![C](https://img.shields.io/badge/C-a?style=for-the-badge&logo=C&color=grey)
![Makefile](https://img.shields.io/badge/Makefile-a?style=for-the-badge&logo=monster&logoColor=orange&color=grey)

You can see the subject [**HERE.**](https://github.com/MGuardia10/42cursus/blob/main/subjects/en/philo_subject_en.pdf)

To visualize the output copy the actions made by the philosophers [**HERE.**](https://nafuka11.github.io/philosophers-visualizer/)

## Installing and running the project:
1- Clone this repository
	
	git clone https://github.com/MGuardia10/42cursus_philosophers.git
2- Navigate to the new directory and run `make`
	
	cd 42cursus_philosophers
   	make
3- `make clean` to remove the object files and work on a cleaner directory

	make clean
4- Start the simulation using the correct arguments:

	./philo <number_philos> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_meals]

## Compiling the Program
The philo program comes with a Makefile that includes the following rules:

- `all`: compiles the program.
- `re`: recompiles the program.
- `clean`: removes obj directory with objects files.
- `fclean`: removes obj directory with objects files and philo binary.

## Disclaimer
> At [42School](https://en.wikipedia.org/wiki/42_(school)), almost every project must be written in accordance to the [Norm](https://github.com/MGuardia10/42cursus/blob/main/subjects/en/norm_en.pdf), the school's coding standard. As a result, the implementation of certain parts may appear strange and for sure had room for improvement.
