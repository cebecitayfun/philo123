#include "philo.h"

void	setup_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	assign_philo_parameters(t_philo *philo, char **argv)
{
	philo->time_to_die = ascii_to_int(argv[2]);
	philo->time_to_eat = ascii_to_int(argv[3]);
	philo->time_to_sleep = ascii_to_int(argv[4]);
	if (argv[5])
		philo->num_times_to_eat = ascii_to_int(argv[5]);
	else
		philo->num_times_to_eat = -1;
}

void	setup_philosophers(t_philo *philos, t_program *program, pthread_mutex_t *forks,
		char **argv)
{
	int	i;
	int	philo_num;

	philo_num = ascii_to_int(argv[1]);
	i = -1;
	while (++i < philo_num)
	{
		philos[i].id = i + 1;
		philos[i].num_of_philos = philo_num;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		assign_philo_parameters(&philos[i], argv);
		philos[i].start_time = &program->start_time;
		philos[i].last_meal = get_timestamp();
		philos[i].write_lock = &program->write_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].dead = &program->dead_flag;
		philos[i].l_fork = &forks[i];
		philos[i].r_fork = &forks[(i + 1) % philos[i].num_of_philos];
	}
}

void	setup_simulation(t_philo *philos, t_program *program)
{
	program->dead_flag = 0;
	program->philos = philos;
	program->start_time = get_timestamp();
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
}
