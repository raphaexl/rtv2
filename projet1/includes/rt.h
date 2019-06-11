/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 15:49:52 by ebatchas          #+#    #+#             */
/*   Updated: 2019/06/08 22:14:01 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# define SCR_WIDTH 1200
# define SCR_HEIGHT 750
# define W_W 960
# define W_H 600
# define START_X (SCR_WIDTH - W_W) / 2 + 100
# define START_Y (SCR_HEIGHT - W_H) / 2 - 20
# define END_X W_W + START_X
# define END_Y  W_H + START_Y
# define NB_THREADS 10
# define ERR_CHECK(cond) if (!(cond)) perror(SDL_GetError());

# include <sys/stat.h>
# include <fcntl.h>
# include "libft.h"
# include "structs.h"

float		ft_modulo(float f);
float		ft_rand48(void);
float		ft_atof(const char *str);
float		ft_clamp(float min, float max, float val);
t_vec3		ft_mix(t_vec3 v1, t_vec3 v2, float mix);
void		ft_fresnel(t_vec3 v, t_vec3 n, float ior, float *kr);
t_vec3		ft_reflect(t_vec3 i, t_vec3 n);
int			ft_refract(t_vec3 i, t_vec3 n, float eta, t_vec3 *r);
int			ft_lambertian_sc(t_intersect *in, t_col3 *att);
int			ft_metal_sc(t_intersect *in, t_col3 *att);
int			ft_dielectric_sc(t_intersect *in, t_col3 *att, float ref_idx);
t_col3		ft_background_color(t_ray *r);
void		ft_error(void);
int			ft_tab_len(char **tab);
void		ft_print_error(char *str);
void		ft_sdl_error(void);
t_font		ft_font(const char *message, const char *font_file, int font_size);

void		ft_env_load_all(t_env *e);
void		ft_env_load_images(t_env *env);
void		ft_env_init(t_env *e, int argc, char *argv[]);
int			ft_env_update_camera(t_camera *c, t_input *in);
void		ft_env_select_object(t_env *e, int x, int y);
void		ft_object_resize(t_object **s, float rev);
int			ft_prev_update(t_env *e, t_input *in);
int			ft_process_event(t_env *e, t_input *in);
int			ft_update_options(t_menu *m, t_input *in, int k);
int			ft_mouse_inside(int mousex, int mousey, SDL_Rect *r);
void		ft_env_display_text(SDL_Renderer *r, char *m);
void		ft_draw(t_env *e);
void		ft_env_quit(t_env *e);

t_vec3		ft_rotate_x(t_vec3 r, float angle);
t_vec3		ft_rotate_y(t_vec3 r, float angle);
t_vec3		ft_rotate_z(t_vec3 r, float angle);
t_vec3		ft_rotate_vec3(t_vec3 r, t_vec3 v, int invert);
t_vec3		ft_translate_vec3(t_vec3 r, t_vec3 v, int invert);
t_vec3		ft_scale_vec3(t_vec3 r, t_vec3 v, int invert);

int			ft_solve_quadric(double c[3], double s[2]);
int			ft_solve_cubic(double w[4], double s[3]);
int			ft_solve_quartic(double w[5], double s[4]);

t_col3		ft_get_light(t_intersect *in, t_light *light);
t_col3		ft_trace(t_intersect *in, t_material *m, t_light *l, t_col3 *a);
t_col3		ft_ray_trace(t_scene *s, t_intersect *in, int depth);
t_col3		ft_edit_trace(t_scene *s, t_intersect *in, int depth);
t_col3		ft_path_trace(t_scene *s, t_intersect *in, int depth);

t_vec3		ft_vec3_read(int fd);
t_col3		ft_col3_read(int fd);
t_material	ft_material_read(int fd);
t_object	*ft_sphere_read(int fd);
t_object	*ft_ring_read(int fd);
t_object	*ft_cylindre_read(int fd);
t_object	*ft_plane_read(int fd);
t_object	*ft_cone_read(int fd);
t_object	*ft_disk_read(int fd);
t_object	*ft_box_read(int fd);
t_object	*ft_cube_read(int fd);
t_object	*ft_torus_read(int fd);
t_object	*ft_triangle_read(int fd);
t_object	*ft_parallelogram_read(int fd);
t_object	*ft_ellipsoid_read(int fd);
t_object	*ft_paraboloid_read(int fd);
t_light		*ft_light_read(int fd);
void		ft_scene_read(t_scene *s, int fd);
void		ft_parse_file(t_scene *s, int	fd);

void		ft_scene_init(t_scene *s, char *const input_file);
void		ft_render(t_scene *s, Uint32 *pix);
void		ft_scene_clear(t_scene *s);

t_object	*ft_sphere_new(void);
int			ft_sphere_intersect(t_sphere *s, t_ray *r, float *t);
t_vec3		ft_normal_sphere(t_sphere *s, t_vec3 p);
int			ft_sphere_compute(t_object *p, t_intersect *in);

t_object	*ft_plane_new(void);
int			ft_plane_intersect(t_plane *plane, t_ray *r, float *t);
t_vec3		ft_normal_plane(t_plane *plane, int ret);
int			ft_plane_compute(t_object *p, t_intersect *in);

t_object	*ft_cone_new(void);
t_vec3		ft_normal_cone(t_cone *cone, t_vec3 p);
int			ft_cone_intersect(t_cone *s, t_ray *r, float *t);
int			ft_cone_compute(t_object *p, t_intersect *in);

t_object	*ft_ring_new(void);
t_vec3		ft_normal_rint(t_ring *ring, t_vec3 p);
int			ft_ring_intersect(t_ring *ring, t_ray *r, float *t);
int			ft_ring_compute(t_object *p, t_intersect *in);

t_object	*ft_cylindre_new(void);
t_vec3		ft_normal_cylindre(t_cylinder *cylindre, t_vec3 p);
int			ft_cylindre_intersect(t_cylinder *cylinder, t_ray *r, float *t);
int			ft_cylindre_compute(t_object *p, t_intersect *in);

t_object	*ft_disk_new(void);
int			ft_disk_intersect(t_disk *disk, t_ray *r, float *t);
int			ft_disk_compute(t_object *d, t_intersect *in);
t_vec3		ft_normal_disk(t_disk *disk, int ret);

t_object	*ft_box_new(void);
t_vec3		ft_normal_box(t_box *cone, t_vec3 p);
int			ft_box_intersect(t_box *box, t_ray *r, float *t);
int			ft_box_compute(t_object *b, t_intersect *in);

t_object	*ft_cube_new(void);
t_vec3		ft_normal_cube(t_cube *cone, t_vec3 p);
int			ft_cube_intersect(t_cube *cube, t_ray *r, float *t);
int			ft_cube_compute(t_object *b, t_intersect *in);

t_object	*ft_torus_new(void);
t_vec3		ft_normal_torus(t_torus *cone, t_vec3 p);
int			ft_torus_intersect(t_torus *torus, t_ray *r, float *t);
int			ft_torus_compute(t_object *b, t_intersect *in);

t_object	*ft_triangle_new(void);
int			ft_triangle_intersect(t_triangle *triangle, t_ray *r, float *t);
int			ft_triangle_compute(t_object *tr, t_intersect *in);
t_vec3		ft_normal_triangle(t_triangle *triangle);

t_object	*ft_parallelogram_new(void);
int			ft_parallelogram_intersect(t_parallelogram *p, t_ray *r, float *t);
int			ft_parallelogram_compute(t_object *para, t_intersect *in);
t_vec3		ft_normal_parallelogram(t_parallelogram *p);

t_object	*ft_ellipsoid_new(void);
int			ft_ellipsoid_intersect(t_ellipsoid *ellipse, t_ray *r, float *t);
int			ft_ellipsoid_compute(t_object *ellipse, t_intersect *in);
t_vec3		ft_normal_ellipsoid(t_ellipsoid *e, t_vec3 p);

t_object	*ft_paraboloid_new(void);
int			ft_paraboloid_intersect(t_paraboloid *pa, t_ray *r, float *t);
int			ft_paraboloid_compute(t_object *parab, t_intersect *in);
t_vec3		ft_normal_paraboloid(t_paraboloid *pa, t_vec3 p);

t_texture	*ft_texture_new(char *img);
void		ft_sphere_uv(t_vec3 p, float *u, float *v);
t_col3		ft_texture_image(t_texture *t, float u, float v);
void		ft_texture_clean(t_texture **t);
int			ft_scene_intersect(t_scene *s, t_intersect *i);
int			ft_scene_intersectl(t_scene *s, t_intersect *i);

float		ft_perlin_noise(t_perlin *pr, t_vec3 p);
void 		ft_perlin_generate(t_vec3 *p);
void		ft_perlin_permute(int *p, int n);
void		ft_perlin_generate_perm(int *p);
void		ft_perlin_init(t_perlin *p);
float		ft_perlin_interp(t_vec3 c[2][2][2], float u, float v, float w);
void		ft_perlin_clean(t_perlin *p);

t_object	*ft_object_new(t_type type, t_object *o);
void		ft_object_remove(t_object **s, int id);
void		ft_object_push_back(t_object **lst, t_object *nw);
void		ft_object_add_back(t_object **lst, t_type type);
void		ft_object_clean(t_object **lst);

t_light		*ft_light_new(t_ltype type, t_light *l);
void		ft_light_push_back(t_light **lst, t_light *nw);
void		ft_light_clean(t_light **lst);

t_camera	ft_camera_new(t_vec3 eye, t_vec3 look_at, t_vec3 up, float a);
t_ray		ft_camera_ray(t_camera *cam, float x, float y);
void		ft_camera_transform(t_camera *cam);
void		ft_update_event(t_input *in);
int			ft_sdl_init(t_ptr *ptr, const char *title);
int			ft_update_renderer(t_ptr *ptr, Uint32 *pixel);
SDL_Texture	*ft_get_render_text(SDL_Renderer *rend, t_font f, SDL_Color color);
void		ft_render_draw_img(SDL_Renderer *r, SDL_Texture *i, t_point p,\
		SDL_Rect *pos);
Uint32		ft_get_pixels(SDL_Surface *s, int x, int y);
void		ft_put_pixels(SDL_Surface *s, int x, int y, Uint32 pixel);
void		ft_save_pixels(Uint32 *pixels, int w, int h);
Uint32		*ft_load_pixels(char *file_name, int *w, int *h);
void		ft_sdl_error(void);
void		ft_sdl_quit(t_ptr *ptr);
#endif
