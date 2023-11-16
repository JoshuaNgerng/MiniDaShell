#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>

int main()
{
	void	*mlx;
	void	*mlx_win;

	mlx = mlx_init();
	if (!mlx)
	{
		printf("failed mlx\n");
		return (1);
	}
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	mlx_loop(mlx);
	//free(mlx);
	return (0);
}