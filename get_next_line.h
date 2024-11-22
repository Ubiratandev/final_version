#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H
# ifndef	BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

# include <stdlib.h>
# include <unistd.h>
#include <fcntl.h>
char	*ft_strdup(char *src);
char    *ft_strjoin(char *s1, char *s2);
size_t  ft_strlen(const char *str);
char	*get_next_line (int fd);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
typedef struct s_list
{
	void	*content;
	struct s_list	*next;
	int	ctr;
}t_list;

#endif
