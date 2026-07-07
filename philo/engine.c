#include "philo.h"

void	*philosopher_cycle(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		precise_sleep(10);
	while (!is_simulation_ended(philo))
	{
		run_actions(philo);
	}
	return (pointer);
}

int	inspect_philosopher(t_philo *philo, int *finished_eating)
{
	pthread_mutex_lock(philo->meal_lock);
	if (get_timestamp() - philo->last_meal > philo->time_to_die)
	{
		pthread_mutex_unlock(philo->meal_lock);
		pthread_mutex_lock(philo->dead_lock);
		*philo->dead = 1;
		pthread_mutex_unlock(philo->dead_lock);
		log_status("died", philo, philo->id);
		return (1);
	}
	if (philo->num_times_to_eat != -1
		&& philo->meals_eaten >= philo->num_times_to_eat)
		(*finished_eating)++;
	pthread_mutex_unlock(philo->meal_lock);
	return (0);
}

int	inspect_meals(t_philo *philos, int finished_eating)
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

void	*supervisor_cycle(void *pointer)
{
	t_philo	*philos;
	int		i;
	int		finished_eating;

	philos = (t_philo *)pointer;
	precise_sleep(1);
	while (1)
	{
		i = -1;
		finished_eating = 0;
		while (++i < philos[0].num_of_philos)
		{
			if (inspect_philosopher(&philos[i], &finished_eating))
				return (NULL);
		}
		if (inspect_meals(philos, finished_eating))
			return (NULL);
		precise_sleep(1);
	}
	return (pointer);
}

int	launch_simulation(t_program *program, pthread_mutex_t *forks)
{
	pthread_t	observer;
	int			i;

	if (pthread_create(&observer, NULL, &supervisor_cycle,
			program->philos) != 0)
		cleanup_resources("Thread creation error", program, forks);
	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL,
				&philosopher_cycle, &program->philos[i]) != 0)
			cleanup_resources("Thread creation error", program, forks);
		i++;
	}
	if (pthread_join(observer, NULL) != 0)
		cleanup_resources("Thread join error", program, forks);
	i = 0;
	while (i < program->philos[0].num_of_philos)
	{
		pthread_join(program->philos[i].thread, NULL);
		i++;
	}
	return (0);
}
