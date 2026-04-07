#include "philo.h"

void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void	set_philo_times(t_philo *philo, char **argv)
{
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->num_times_to_eat = ft_atoi(argv[5]);
	else
		philo->num_times_to_eat = -1;
}

void	init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks,
		char **argv)
{
	int	i;
	int	philo_num;

	philo_num = ft_atoi(argv[1]);
	i = -1;
	while (++i < philo_num)
	{
		philos[i].id = i + 1;
		philos[i].num_of_philos = philo_num;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		set_philo_times(&philos[i], argv);
		philos[i].start_time = &program->start_time;
		philos[i].last_meal = get_current_time();
		philos[i].write_lock = &program->write_lock;
		philos[i].dead_lock = &program->dead_lock;
		philos[i].meal_lock = &program->meal_lock;
		philos[i].dead = &program->dead_flag;
		philos[i].l_fork = &forks[i];
		philos[i].r_fork = &forks[(i + 1) % philos[i].num_of_philos];
	}
}

void	init_program(t_philo *philos, t_program *program)
{
	program->dead_flag = 0;
	program->philos = philos;
	program->start_time = get_current_time();
	pthread_mutex_init(&program->write_lock, NULL);
	pthread_mutex_init(&program->dead_lock, NULL);
	pthread_mutex_init(&program->meal_lock, NULL);
}
