#include "philo.h"

int	check_arg_content(char **argv)
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

int	validate_args(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (write(2, "Wrong argument count\n", 21), 1);
	if (check_arg_content(argv) == 1)
		return (write(2, "Invalid arguments\n", 18), 1);
	if (ft_atoi(argv[1]) <= 0 || ft_atoi(argv[1]) > 200
		|| ft_atoi(argv[2]) <= 0 || ft_atoi(argv[3]) <= 0
		|| ft_atoi(argv[4]) <= 0
		|| (argv[5] && ft_atoi(argv[5]) <= 0))
		return (write(2, "Invalid arguments\n", 18), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_program		program;
	t_philo			philos[200];
	pthread_mutex_t	forks[200];
	int				k;

	if (validate_args(argc, argv))
		return (1);
	init_program(philos, &program);
	init_forks(forks, ft_atoi(argv[1]));
	init_philos(philos, &program, forks, argv);
	program.start_time = get_current_time();
	k = 0;
	while (k < program.philos[0].num_of_philos)
	{
		program.philos[k].last_meal = program.start_time;
		k++;
	}
	create_threads(&program, forks);
	destory_all(NULL, &program, forks);
	return (0);
}
