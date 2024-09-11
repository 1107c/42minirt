/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myeochoi <myeochoi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:37:46 by ksuh              #+#    #+#             */
/*   Updated: 2024/09/11 13:53:43 by myeochoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"


void	draw(t_rt *rt)
{
	//t_ray	*ray;
	t_fig		*tmp;

	tmp = rt->fig;

	rt->cam->distance_to_view = WINDOW_WIDTH / (2 * tan(ANG * (rt->cam->fov / 2)));
	printf("ratio: %lf\n", rt->cam->distance_to_view);
	get_cam_basis(rt->cam);
	// ray = cam_ray(rt->cam);
	// cam_ray(rt->cam, rt, 0, 0);
	// cam_ray(rt->cam, rt, 1920, 0);
	// cam_ray(rt->cam, rt, 0, 1080);
	// cam_ray(rt->cam, rt, 1920, 1080);
	// draw_plane(rt);
	while (tmp->next)
	{
		draw_fig(rt, tmp, -1, -1);
		tmp = tmp->next;
	}
	// draw_cylinder();
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img->img, 0, 0);
}

void	pixel_to_image(t_image *img, double x, double y, int color)
{
	int	pixel;

	pixel = ((int)y * img->size_line) + ((int)x * 4);
	img->buffer[pixel + 0] = (color) & 0xff;
	img->buffer[pixel + 1] = (color >> 8) & 0xff;
	img->buffer[pixel + 2] = (color >> 16) & 0xff;
	img->buffer[pixel + 3] = (color >> 24);
}

int	encode_rgb(double red, double green, double blue)
{
	return ((int)red << 16 | (int)green << 8 | (int)blue);
}

// void	draw_plane(t_rt *rt)
// {
// 	t_vector	start_point;
// 	t_vector	save_point;
// 	//t_vector	line;

// 	start_point.x = rt->cam->coords->x + rt->cam->distance_to_view * rt->cam->orient_vec->x - 960 * rt->cam->right_vec->x + 540 * rt->cam->up_vec->x;
// 	start_point.y = rt->cam->coords->y + rt->cam->distance_to_view * rt->cam->orient_vec->y - 960 * rt->cam->right_vec->y + 540 * rt->cam->up_vec->y;
// 	start_point.z = rt->cam->coords->z + rt->cam->distance_to_view * rt->cam->orient_vec->z - 960 * rt->cam->right_vec->z + 540 * rt->cam->up_vec->z;
// 	save_point.x = start_point.x;
// 	save_point.y = start_point.y;
// 	save_point.z = start_point.z;
// 	for (int j = 0; j < WINDOW_HEIGHT; j++)
// 	{
// 		for (int i = 0; i < WINDOW_WIDTH; i++)
// 		{
// 			// line.x = start_point.x - rt->cam->coords->x;
// 			// line.y = start_point.y - rt->cam->coords->y;
// 			// line.z = start_point.z - rt->cam->coords->z;
// 			if (intersect_plane(rt->fig, &start_point, rt->cam->coords))
// 				pixel_to_image(rt->img, i, j, 0x5E35B1);
// 			start_point.x += rt->cam->right_vec->x;
// 			start_point.y += rt->cam->right_vec->y;
// 			start_point.z += rt->cam->right_vec->z;
// 		}
// 		save_point.x -= rt->cam->up_vec->x;
// 		save_point.y -= rt->cam->up_vec->y;
// 		save_point.z -= rt->cam->up_vec->z;
// 		start_point.x = save_point.x;
// 		start_point.y = save_point.y;
// 		start_point.z = save_point.z;
// 	}
// }


void draw_fig(t_rt *rt, t_fig *tmp, int i, int j)
{
    t_vector start_point;
	t_vector light_dir;
	light_dir.x = -rt->light->xyz->x;
	light_dir.y = -rt->light->xyz->y;
	light_dir.z = -rt->light->xyz->z;
	//printf("Original sphere color: (%f, %f, %f)\n", tmp->rgb->x, tmp->rgb->y, tmp->rgb->z);
    
    // 조명 방향 벡터 정규화
    double light_length = sqrt(light_dir.x * light_dir.x + light_dir.y * light_dir.y + light_dir.z * light_dir.z);
    light_dir.x /= light_length;
    light_dir.y /= light_length;
    light_dir.z /= light_length;

    // start_point 초기화 (기존 코드 유지)
	start_point = (t_vector){rt->cam->coords->x + rt->cam->distance_to_view * rt->cam->orient_vec->x - 960 * rt->cam->right_vec->x + 540 * rt->cam->up_vec->x,
		rt->cam->coords->y + rt->cam->distance_to_view * rt->cam->orient_vec->y - 960 * rt->cam->right_vec->y + 540 * rt->cam->up_vec->y,
		rt->cam->coords->z + rt->cam->distance_to_view * rt->cam->orient_vec->z - 960 * rt->cam->right_vec->z + 540 * rt->cam->up_vec->z, NULL};

    while (++j < WINDOW_HEIGHT)
    {
        while (++i < WINDOW_WIDTH)
        {
            double d = intersect_sphere(tmp->xyz, rt->cam->coords, &start_point, tmp->diameter / 2);
            
		    if (d > 0 && tmp->type == 1)
            {
				//printf("d: %f\n", d);
                // 교차점 계산
                t_vector intersection;
                intersection.x = rt->cam->coords->x + d * (start_point.x - rt->cam->coords->x);
                intersection.y = rt->cam->coords->y + d * (start_point.y - rt->cam->coords->y);
                intersection.z = rt->cam->coords->z + d * (start_point.z - rt->cam->coords->z);

                // 법선 벡터 계산
                t_vector normal;
                normal.x = (intersection.x - tmp->xyz->x) / (tmp->diameter / 2);
                normal.y = (intersection.y - tmp->xyz->y) / (tmp->diameter / 2);
                normal.z = (intersection.z - tmp->xyz->z) / (tmp->diameter / 2);

                // 법선 벡터 정규화
                double normal_length = sqrt(normal.x * normal.x + normal.y * normal.y + normal.z * normal.z);
                normal.x /= normal_length;
                normal.y /= normal_length;
                normal.z /= normal_length;

                // 조명 강도 계산 (디퓨즈 라이팅)
				double diffuse = fmax(0, dot_product(&normal, &light_dir));
double light_intensity = rt->amblight->light_ratio + (1 - rt->amblight->light_ratio) * diffuse;
                if (light_intensity < 0) light_intensity = 0;
                if (light_intensity > 1) light_intensity = 1;
				printf("Normal vector: (%f, %f, %f)\n", normal.x, normal.y, normal.z);
				printf("Light direction: (%f, %f, %f)\n", light_dir.x, light_dir.y, light_dir.z);
				printf("Light intensity before clamping: %f\n", light_intensity);
                // 최종 색상 계산
                int r = (int)tmp->rgb->x * light_intensity;
                int g = (int)tmp->rgb->y * light_intensity;
                int b = (int)tmp->rgb->z * light_intensity;
				printf("r:%d g:%d b:%d\n", r,g,b);
                pixel_to_image(rt->img, i, j, encode_rgb(r, g, b));
            }
            // start_point 업데이트 (기존 코드 유지)
            start_point.x += rt->cam->right_vec->x;
            start_point.y += rt->cam->right_vec->y;
            start_point.z += rt->cam->right_vec->z;
        }
        // 다음 행으로 이동 (기존 코드 유지)
        start_point.x -= rt->cam->up_vec->x + rt->cam->right_vec->x * i;
        start_point.y -= rt->cam->up_vec->y + rt->cam->right_vec->y * i;
        start_point.z -= rt->cam->up_vec->z + rt->cam->right_vec->z * i;
        i = -1;
    }
}
