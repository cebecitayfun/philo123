#include "philo.h"

int	is_simulation_ended(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
	{
		pthread_mutex_unlock(philo->dead_lock);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	log_status(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_timestamp() - *philo->start_time;
	if (!is_simulation_ended(philo) || str[0] == 'd')
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}

void	lone_philosopher_routine(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	log_status("has taken a fork", philo, philo->id);
	precise_sleep(philo->time_to_die);
	while (!is_simulation_ended(philo))
		precise_sleep(1);
	pthread_mutex_unlock(philo->r_fork);
}

void	acquire_forks(t_philo *philo)
{
	if (philo->num_of_philos == 1)
	{
		lone_philosopher_routine(philo);
		return ;
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		log_status("has taken a fork", philo, philo->id);
		pthread_mutex_lock(philo->l_fork);
		log_status("has taken a fork", philo, philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		log_status("has taken a fork", philo, philo->id);
		pthread_mutex_lock(philo->r_fork);
		log_status("has taken a fork", philo, philo->id);
	}
}

void	run_actions(t_philo *philo)
{
	acquire_forks(philo);
	if (philo->num_of_philos == 1)
		return ;
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 1;
	philo->last_meal = get_timestamp();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	log_status("is eating", philo, philo->id);
	precise_sleep(philo->time_to_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 0;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	log_status("is sleeping", philo, philo->id);
	precise_sleep(philo->time_to_sleep);
	log_status("is thinking", philo, philo->id);
	if (philo->num_of_philos % 2 != 0)
	{
		if (philo->time_to_eat * 2 > philo->time_to_sleep)
			precise_sleep(philo->time_to_eat * 2 - philo->time_to_sleep);
	}
}
