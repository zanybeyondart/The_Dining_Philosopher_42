# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <strings.h>
# include <sys/time.h>

typedef struct s_philo
{
	pthread_t			thread;
	pthread_mutex_t		*right;
	pthread_mutex_t		*left;
}	t_philo;

int main ()
{
	t_philo *main;

	main = malloc(sizeof(t_philo));
	main->left = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(main->left, NULL);
	pthread_mutex_lock(main->left);
	pthread_mutex_unlock(main->left);
}