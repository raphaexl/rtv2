
#include "../../includes/rt.h"

t_col3	ft_greyscale(t_col3 c)
{
	double	grey;

	grey = (c.red + c.green + c.blue) / 3;
	c.red = grey;
	c.green = grey;
	c.blue = grey;
	return (c);
}

t_col3	ft_cyanscale(t_col3 c)
{
	double	cyan;

	cyan = (c.red + c.green + c.blue) / 3;
	c.red = 0;
	c.green = ft_clamp(0, cyan, 255);
	c.blue = ft_clamp(0, cyan, 255);
	return (c);
}

t_col3	ft_redscale(t_col3 c)
{
	double red;

	red = (c.red + c.green + c.blue) / 3;
	c.red = ft_clamp(0, red, 255);
	c.green = 0;
	c.blue = 0;
	return (c);
}