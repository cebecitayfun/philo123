#include "philo.h"

int	verify_input_digits(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	parse_and_verify(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (write(2, "Wrong argument count\n", 21), 1);
	if (verify_input_digits(argv) == 1)
		return (write(2, "Invalid arguments\n", 18), 1);
	if (ascii_to_int(argv[1]) <= 0 || ascii_to_int(argv[1]) > 200
		|| ascii_to_int(argv[2]) <= 0 || ascii_to_int(argv[3]) <= 0
		|| ascii_to_int(argv[4]) <= 0
		|| (argv[5] && ascii_to_int(argv[5]) <= 0))
		return (write(2, "Invalid arguments\n", 18), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];
	int				k;

	if (parse_and_verify(argc, argv))
		return (1);
	setup_simulation(philos, &program);
	setup_forks(forks, ascii_to_int(argv[1]));
	setup_philosophers(philos, &program, forks, argv);
	program.start_time = get_timestamp();
	k = 0;
	while (k < program.philos[0].num_of_philos)
	{
		program.philos[k].last_meal = program.start_time;
		k++;
	}
	launch_simulation(&program, forks);
	cleanup_resources(NULL, &program, forks);
	return (0);
}
