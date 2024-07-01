#include "cubed.h"
#include "parser.h"

// Funcion que libera la memoria de la estructura del mapa
void	ft_free_map(t_cube *map)
{

}
// Funcion que cierra ventana y libera lo anterior
int	ft_close(t_cube *map)
{
	mlx_destroy_window(map->ged->mlx, map->ged->win);
	ft_free_map(map);
	exit(EXIT_SUCCESS);
}