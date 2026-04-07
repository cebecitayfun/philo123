#include "philo.h"

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(10);
	while (!check_if_dead(philo))
	{
		eat_sleep_think(philo);
	}
	return (pointer);
}

int	check_philo_state(t_philo *philo, int *finished_eating)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_current_time() - philo->last_meal > philo->time_to_die)
	{
		pthread_mutex_unlock(philo->meal_lock);
		pthread_mutex_lock(philo->dead_lock);
		*philo->dead = 1;
		pthread_mutex_unlock(philo->dead_lock);
		print_message("died", philo, philo->id);
		return (1);
	}
	if (philo->num_times_to_eat != -1
		&& philo->meals_eaten >= philo->num_times_to_eat)
		(*finished_eating)++;
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	check_all_ate(t_philo *philos, int finished_eating)
{
	if (philos[0].num_times_to_eat != -1
		&& finished_eating == philos[0].num_of_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos[0].dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}

void	*monitor_routine(void *pointer)
{
	t_philo	*philos;
	int		i;
	int		finished_eating;

	philos = (t_philo *)pointer;
	ft_usleep(1);
	while (1)
	{
		i = -1;
		finished_eating = 0;
		while (++i < philos[0].num_of_philos)
		{
			if (check_philo_state(&philos[i], &finished_eating))
				return (NULL);
		}
		if (check_all_ate(philos, finished_eating))
			return (NULL);
		ft_usleep(1);
	}
	return (pointer);
}

int	create_threads(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			i;

	if (pthread_create(&observer, NULL, &monitor_routine, program->philos) != 0)
		destory_all("Thread creation error", program, forks);
	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL,
				&philo_routine, &program->philos[i]) != 0)
			destory_all("Thread creation error", program, forks);
		i++;
	}
	if (pthread_join(observer, NULL) != 0)
		destory_all("Thread join error", program, forks);
	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		pthread_join(program->philos[i].thread, NULL);
		i++;
	}
	return (0);
}
