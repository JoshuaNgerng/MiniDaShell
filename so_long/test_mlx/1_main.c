#include <mlx.h>
#include <stdlib.h>

int	main(void)
{
	void	*mlx;
	void	*mlx_win;

	mlx =  mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "1st");
	mlx_loop(mlx);
	system("leaks mlx_test");
	return (0);
}
