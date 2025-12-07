/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmontoro <gmontoro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/20 13:02:03 by gmontoro          #+#    #+#             */
/*   Updated: 2025/09/23 19:03:27 by gmontoro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../miniRT.h"

void	ft_free(char **sp)
{
	int	i;

	i = 0;
	while (sp[i])
	{
		free(sp[i]);
		i++;
	}
	free(sp);
}

t_parse	*ft_free_parsing(t_parse *p)
{
	if (p->sp != 0)
		ft_free_sp(p);
	if (p->pl != 0)
		ft_free_pl(p);
	if (p->cy != 0)
		ft_free_cy(p);
	if (p->hit != 0)
		ft_free_hit(p->hit);
	if (p->cam)
		free(p->cam);
	free(p);
	p = NULL;
	return (NULL);
}
