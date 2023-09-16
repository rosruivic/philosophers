/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roruiz-v <roruiz-v@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/27 09:22:41 by roruiz-v          #+#    #+#             */
/*   Updated: 2023/09/16 19:27:31 by roruiz-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# define NC	"\e[0m"
# define R 	"\e[31m"
# define G 	"\e[32m"
# define Y 	"\e[33m"
# define B 	"\e[34m"
# define V 	"\e[35m"
# define THINK " is thinking"
# define FORK " has taken a fork"
# define EAT " is eating"
# define SLEEP " is sleeping"
# define DEAD " died"

typedef enum e_error_msg
{
	NO_ERROR,
	ERROR_INVALID_NUM_ARGMTS,
	ERROR_INVALID_TYPE_ARGMTS,
	ERROR_INVALID_NUM_PHILOSOPHERS,
	ERROR_OVERLIMITS,
	ERROR_FORKS_MALLOC = 10,
	ERROR_PHILOS_MALLOC,
	ERROR_INIT_FORK_MUTEX = 20,
	ERROR_INIT_PRINT_MUTEX,
	ERROR_INIT_ERROR_MUTEX,
	ERROR_INIT_PHI_TM_LAST_EAT_MUTEX,
	ERROR_INIT_PHI_N_TMS_HAS_EATEN_MUTEX,
	ERROR_LOCK_FORK_MUTEX = 30,
	ERROR_LOCK_PRINT_MUTEX,
	ERROR_LOCK_ERROR_MUTEX,
	ERROR_LOCK_PHI_TM_LAST_EAT_MUTEX,
	ERROR_LOCK_PHI_N_TMS_HAS_EATEN_MUTEX,
	ERROR_UNLOCK_FORK_MUTEX = 40,
	ERROR_UNLOCK_PRINT_MUTEX,
	ERROR_UNLOCK_ERROR_MUTEX,
	ERROR_UNLOCK_PHI_TM_LAST_EAT_MUTEX,
	ERROR_UNLOCK_PHI_N_TMS_HAS_EATEN_MUTEX,
	ERROR_DESTROYING_FORK_MUTEX = 50,
	ERROR_DESTROYING_PRINT_MUTEX,
	ERROR_DESTROYING_ERROR_MUTEX,
	ERROR_DESTROYING_PHI_TM_LAST_EAT_MUTEX,
	ERROR_DESTROYING_PHI_N_TMS_HAS_EATEN_MUTEX,
	ERROR_CREATING_CONTROL_THREAD = 60,
	ERROR_CREATING_PHILO_THREAD,
	ERROR_IN_PHI_THREAD_JOIN = 70,
	ERROR_IN_CONTROL_THREAD_JOIN,
	END = 99,
}	t_error_msg;

typedef struct s_fork
{
	int				f_state;
	pthread_mutex_t	f_mtx;
}							t_fork;

/**
 * @brief 
 *	pthread_t	*thr_philo;				// thread of the philosopher (id)
 *	int				id_phi;						// phi identification to printf
 *	long      tm_last_eat;		 	// time since his last start/eat moment (MUTEX!)
 *	int	      n_tms_has_eaten;	// #_times phi has already eaten (MUTEX!)
 *	int				n_forks;					// #_forks the philo has in his hands
 *	int				indx_l_fork;      // index of left fork assigned to the phi
 *	int				indx_r_fork;      // index of right fork assigned to the phi
 */
typedef struct s_philo
{
	pthread_t		thr_phi;
	int				id_phi;
	int				hand;
	long			tm_last_eat;
	pthread_mutex_t	lock_tm_last_eat;
	int				n_tms_has_eaten;
	pthread_mutex_t	lock_n_tms_has_eaten;
	int				n_forks;
	int				indx_l_fork;
	int				indx_r_fork;
	struct s_bag	*orgn;
}					t_philo;

/**
 * @brief A mutex stays mutexed while a phi is taken it
 * 
 * 	int			n_phi;						// 1st argm (# of philosophers/forks)
 *	int			tm_to_die;				// 2nd argm (total life time since start/last dinner)
 *	int			tm_to_eat;				// 3rd argm (mandatory time it takes to eat each philo)
 *	int			tm_to_slp;				// 4th argm (mandatory time to sleep after dinner)
 *	int			n_tms_must_eat;		// when exists 5th argmt
 *	long		s_tm;							// program start time (ctrl routine init this)
 *	int			phs_ended_eat;		// when exists 5th argmt
 *	pthread_mutex_t	**forks;	// array of forks MUTEXES
 *	t_philo		*phi;						// array of philos threads & their structures
 */
typedef struct s_bag
{
	int				n_phi;
	long			tm_to_die;
	long			tm_to_eat;
	long			tm_to_slp;
	int				n_tms_must_eat;
	long			s_tm;
	t_fork			*frk;
	t_philo			*phi;
	int				phi_dead;
	long			phi_dead_time;
	pthread_t		thr_ctrl;
	pthread_mutex_t	lock_error;
	pthread_mutex_t	lock_print;
	t_error_msg		error;
}					t_bag;

/* ***********************************************************************/
/* *************         000 - ERROR MSGS CONTROL        *************** */
/* ***********************************************************************/

void	ft_error_msg(t_error_msg error, t_bag *data);
void	ft_free_pointers(t_bag *data);

/* ***********************************************************************/
/* *************         100 - CHECKING ARGMTS           *************** */
/* ***********************************************************************/

void	ft_check_data(t_bag *data, int argc, char **argv);
void	ft_init_data(t_bag *data, int argc, char **argv);
//int		ft_dominant_hand(void);
int		ft_dominant_hand(t_philo *phi);

/* ***********************************************************************/
/* *************         200 - CONTROL THREAD            *************** */
/* ***********************************************************************/

void	ft_ctrl_thr(t_bag *data);
int		ft_ctrl_checks_error_status(t_bag *data);
void	*ft_ctrl_routine(void *data);
void	ft_create_philos_threads(t_bag *d);
void	ft_phi_dead_print(t_bag *d);
void	ft_join_phi_threads(t_bag *data);
void	ft_destroy_phi_mutexes(t_bag *data);

/* ***********************************************************************/
/* *************         300 - PHILOS THREADS            *************** */
/* ***********************************************************************/

void	*ft_phi_routine(void *data);
int		ft_phi_checks_end_status(t_philo *p);
void	ft_phi_is_thinking(t_philo *phi);
void	ft_phi_get_forks(t_philo *phi);
void	ft_phi_is_eating(t_philo *phi);
void	ft_phi_leaves_forks(t_philo *p);
void	ft_phi_is_sleeping(t_philo *phi);

/* ***********************************************************************/
/* ******************          900 - UTILS           ******************* */
/* ***********************************************************************/

long	ft_gtod(void);
void	ft_putstr_fd(char *s, int fd);
int		ft_strlen(char *s);
int		ft_is_digit(char var);
long	ft_philo_atoi(const char *str);

#endif
