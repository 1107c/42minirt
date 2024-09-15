/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yeojukim <yeojukim@student.42gyeongsan.kr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 10:22:18 by yeojukim          #+#    #+#             */
/*   Updated: 2024/09/08 10:22:18 by yeojukim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int ac, char **av)
{
	t_rt	*rt;

	rt = ft_calloc(sizeof(t_rt), 1);
	if (ac != 2)
		return (print_err(ACERR));
	rt = malloc(sizeof(t_rt));
	if (!rt)
		return (print_err(INITERR));
	if (!file_check(rt, av[1]))
	{
		init_rt(rt);

	}
	free_obj(&rt->obj);
	free_light(&rt->light);

	return (0);
}




		//printf("----------amb test--------\n");
		//printf("ch : %d\n", rt->amb.ch);
		//printf("ratio : %f\n", rt->amb.ratio);
		//printf("r : %f\n", rt->amb.rgb.r);
		//printf("g : %f\n", rt->amb.rgb.g);
		//printf("b : %f\n\n\n\n", rt->amb.rgb.b);

		//printf("-----------cam test---------\n");
		//printf("coords : %f, %f, %f\n", rt->cam.coords_vec.x, rt->cam.coords_vec.y, rt->cam.coords_vec.z);
		//printf("normal : %f, %f, %f\n", rt->cam.orient_vec.x, rt->cam.orient_vec.y, rt->cam.orient_vec.z);
		//printf("fov : %d\n\n\n\n", rt->cam.fov);

		//printf("----------light test-------\n");
		//printf("coords : %f, %f, %f\n", rt->light->coords_vec.x, rt->light->coords_vec.y, rt->light->coords_vec.z);
		//printf("brightness : %f\n", rt->light->ratio);
		//printf("color : %f, %f, %f\n\n\n\n", rt->light->rgb.r, rt->light->rgb.g, rt->light->rgb.b);

		//printf("----------light(multi) test-------\n");
		//printf("coords : %f, %f, %f\n", rt->light->next->coords_vec.x, rt->light->next->coords_vec.y, rt->light->next->coords_vec.z);
		//printf("brightness : %f\n", rt->light->next->ratio);
		//printf("color : %f, %f, %f\n\n\n\n", rt->light->next->rgb.r, rt->light->next->rgb.g, rt->light->next->rgb.b);

		//printf("-----------plane test-------\n");
		//printf("coords : %f, %f, %f\n", rt->obj->u_obj.plane.coords_vec.x, rt->obj->u_obj.plane.coords_vec.y, rt->obj->u_obj.plane.coords_vec.z);
		//printf("normal : %f, %f, %f\n", rt->obj->u_obj.plane.orient_vec.x, rt->obj->u_obj.plane.orient_vec.y, rt->obj->u_obj.plane.orient_vec.z);
		//printf("color : %f, %f, %f\n\n\n\n", rt->obj->u_obj.plane.rgb.r, rt->obj->u_obj.plane.rgb.g, rt->obj->u_obj.plane.rgb.b);

		//printf("-----------sphere test--------\n");
		//printf("coords : %f, %f, %f\n", rt->obj->next->u_obj.sphere.coords_vec.x, rt->obj->next->u_obj.sphere.coords_vec.y, rt->obj->next->u_obj.sphere.coords_vec.z);
		//printf("diamiter : %f\n", rt->obj->next->u_obj.sphere.diameter);
		//printf("color : %f, %f, %f\n\n\n\n", rt->obj->next->u_obj.sphere.rgb.r, rt->obj->next->u_obj.sphere.rgb.g, rt->obj->next->u_obj.sphere.rgb.b);

		//printf("------------cylinder test----------\n");
		//printf("coords : %f, %f, %f\n", rt->obj->next->next->u_obj.cylinder.coords_vec.x,
		//				rt->obj->next->next->u_obj.cylinder.coords_vec.y,
		//				rt->obj->next->next->u_obj.cylinder.coords_vec.z);
		//printf("normal : %f, %f, %f\n", rt->obj->next->next->u_obj.cylinder.orient_vec.x,
		//				rt->obj->next->next->u_obj.cylinder.orient_vec.y,
		//				rt->obj->next->next->u_obj.cylinder.orient_vec.z);
		//printf("diameter : %f\n", rt->obj->next->next->u_obj.cylinder.diameter);
		//printf("height : %f\n", rt->obj->next->next->u_obj.cylinder.height);
		//printf("color : %f, %f, %f\n", rt->obj->next->next->u_obj.cylinder.rgb.r,
		//				rt->obj->next->next->u_obj.cylinder.rgb.g,
		//				rt->obj->next->next->u_obj.cylinder.rgb.b);
