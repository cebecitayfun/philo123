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

int		check_arg_content(char **argv);
void	init_program(t_philo *philos, t_program *program);
void	init_forks(pthread_mutex_t *forks, int philo_num);
void	init_philos(t_philo *philos, t_program *program, pthread_mutex_t *forks,
			char **argv);

int		create_threads(t_program *program, pthread_mutex_t *forks);
void	*philo_routine(void *pointer);
void	*monitor_routine(void *pointer);
int		check_philo_state(t_philo *philo, int *finished_eating);

int		check_if_dead(t_philo *philo);
void	take_forks(t_philo *philo);
void	eat_sleep_think(t_philo *philo);
void	print_message(char *str, t_philo *philo, int id);
void	ft_usleep(size_t milliseconds);

int		ft_atoi(char *str);
size_t	get_current_time(void);
void	destory_all(char *str, t_program *program, pthread_mutex_t *forks);
int		ft_strlen(char *str);

#endif
