#include "philo.h"

int	check_if_dead(t_philo *philo)
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

void	print_message(char *str, t_philo *philo, int id)
{
	size_t	time;

	pthread_mutex_lock(philo->write_lock);
	time = get_current_time() - *philo->start_time;
	if (!check_if_dead(philo) || str[0] == 'd')
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(philo->write_lock);
}

void	handle_single_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	print_message("has taken a fork", philo, philo->id);
	ft_usleep(philo->time_to_die);
	while (!check_if_dead(philo))
		ft_usleep(1);
	pthread_mutex_unlock(philo->r_fork);
}

void	take_forks(t_philo *philo)
{
	if (philo->num_of_philos == 1)
	{
		handle_single_philo(philo);
		return ;
	}
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->r_fork);
		print_message("has taken a fork", philo, philo->id);
		pthread_mutex_lock(philo->l_fork);
		print_message("has taken a fork", philo, philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->l_fork);
		print_message("has taken a fork", philo, philo->id);
		pthread_mutex_lock(philo->r_fork);
		print_message("has taken a fork", philo, philo->id);
	}
}

void	eat_sleep_think(t_philo *philo)
{
	take_forks(philo);
	if (philo->num_of_philos == 1)
		return ;
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 1;
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	print_message("is eating", philo, philo->id);
	ft_usleep(philo->time_to_eat);
	pthread_mutex_lock(philo->meal_lock);
	philo->eating = 0;
	pthread_mutex_unlock(philo->meal_lock);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	print_message("is sleeping", philo, philo->id);
	ft_usleep(philo->time_to_sleep);
	print_message("is thinking", philo, philo->id);
	if (philo->num_of_philos % 2 != 0)
	{
		if (philo->time_to_eat * 2 > philo->time_to_sleep)
			ft_usleep(philo->time_to_eat * 2 - philo->time_to_sleep);
	}
}
