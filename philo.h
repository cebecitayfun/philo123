#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define RESET "\033[0m"

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eating;
	int				meals_eaten;
	size_t			last_meal;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			*start_time;
	int				num_of_philos;
	int				num_times_to_eat;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
	int				*dead;
}					t_philo;

typedef struct s_program
{
	int				dead_flag;
	size_t			start_time;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	write_lock;
	t_philo			*philos;
}					t_program;

int		verify_input_digits(char **argv);
void	setup_simulation(t_philo *philos, t_program *program);
void	setup_forks(pthread_mutex_t *forks, int philo_num);
void	setup_philosophers(t_philo *philos, t_program *program, pthread_mutex_t *forks,
			char **argv);

int		launch_simulation(t_program *program, pthread_mutex_t *forks);
void	*philosopher_cycle(void *pointer);
void	*supervisor_cycle(void *pointer);
int		inspect_philosopher(t_philo *philo, int *finished_eating);

int		is_simulation_ended(t_philo *philo);
void	acquire_forks(t_philo *philo);
void	run_actions(t_philo *philo);
void	log_status(char *str, t_philo *philo, int id);
void	precise_sleep(size_t milliseconds);

int		ascii_to_int(char *str);
size_t	get_timestamp(void);
void	cleanup_resources(char *str, t_program *program, pthread_mutex_t *forks);
int		str_length(char *str);

#endif
