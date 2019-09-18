# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/28 22:15:58 by ebatchas          #+#    #+#              #
#    Updated: 2019/09/17 22:01:05 by ebatchas         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C=gcc

SRCDIR=srcs
LIBDIR=libs
HEADDIR=includes
CFLAGS=-Wall -Wextra -I$(HEADDIR)
LDFLAGS= $(CFLAGS) -L$(LIBDIR)/ -lft -lm

UNAME_S := $(shell uname -s)

ifeq	($(UNAME_S),Linux)
	LDFLAGS += -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lm
	#LDFLAGS = $(CFLAGS) $(LIBDIR)/libft/libft.a -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lm
endif

ifeq	($(UNAME_S),Darwin)
	SDL2 = ./frameworks/SDL2.framework/Versions/A/SDL2
	SDL2_image = ./frameworks/SDL2_image.framework/Versions/A/SDL2_image
	SDL2_ttf = ./frameworks/SDL2_ttf.framework/Versions/A/SDL2_ttf
	LDFLAGS += -F ./frameworks -framework SDL2 -framework SDL2_image -framework SDL2_ttf
	CFLAGS += -F ./frameworks
endif

SRC=$(SRCDIR)/main/main.c\
	$(SRCDIR)/env/compute.c\
	$(SRCDIR)/env/save.c\
	$(SRCDIR)/env/process.c\
	$(SRCDIR)/env/verbose.c\
	$(SRCDIR)/env/load.c\
	$(SRCDIR)/env/env.c\
	$(SRCDIR)/env/init.c\
	$(SRCDIR)/sdl/input.c\
	$(SRCDIR)/sdl/input2.c\
	$(SRCDIR)/sdl/event.c\
	$(SRCDIR)/sdl/sdl.c\
	$(SRCDIR)/gui/gui.c\
	$(SRCDIR)/gui/entry.c\
	$(SRCDIR)/gui/entry2.c\
	$(SRCDIR)/gui/inspector.c\
	$(SRCDIR)/gui/lview.c\
	$(SRCDIR)/gui/cview.c\
	$(SRCDIR)/gui/selection.c\
	$(SRCDIR)/gui/lselect.c\
	$(SRCDIR)/gui/cselect.c\
	$(SRCDIR)/gui/lapply.c\
	$(SRCDIR)/gui/capply.c\
	$(SRCDIR)/gui/apply.c\
	$(SRCDIR)/gui/widget.c\
	$(SRCDIR)/gui/button.c\
	$(SRCDIR)/tools/error.c\
	$(SRCDIR)/tools/utils.c\
	$(SRCDIR)/tools/tools.c\
	$(SRCDIR)/raytrace/draw.c\
	$(SRCDIR)/parser/read.c\
	$(SRCDIR)/parser/read2.c\
	$(SRCDIR)/parser/parse.c\
	$(SRCDIR)/parser/parse_tools.c\
	$(SRCDIR)/mesh/load_mesh.c\
	$(SRCDIR)/mesh/load_obj.c\
	$(SRCDIR)/mesh/mesh.c\
	$(SRCDIR)/mesh/mesh.c\
	$(SRCDIR)/mesh/prim.c\
	$(SRCDIR)/mesh/obj_parser.c\
	$(SRCDIR)/linked/object.c\
	$(SRCDIR)/linked/light.c\
	$(SRCDIR)/raytrace/scene.c\
	$(SRCDIR)/objects/sphere.c\
	$(SRCDIR)/objects/cone.c\
	$(SRCDIR)/objects/cylindre.c\
	$(SRCDIR)/objects/ring.c\
	$(SRCDIR)/objects/plane.c\
	$(SRCDIR)/objects/disque.c\
	$(SRCDIR)/objects/box.c\
	$(SRCDIR)/objects/cube.c\
	$(SRCDIR)/objects/torus.c\
	$(SRCDIR)/objetcs/triangle.c\
	$(SRCDIR)/objects/parallelogram.c\
	$(SRCDIR)/objects/ellipsoid.c\
	$(SRCDIR)/objetcs/paraboloid.c\
	$(SRCDIR)/raytrace/camera.c\
	$(SRCDIR)/raytrace/background.c\
	$(SRCDIR)/geometry/vector1.c\
	$(SRCDIR)/geometry/vector2.c\
	$(SRCDIR)/geometry/matrix.c\
	$(SRCDIR)/geometry/color.c\
	$(SRCDIR)/geometry/color1.c\
	$(SRCDIR)/geometry/color2.c\
	$(SRCDIR)/math/roation.c\
	$(SRCDIR)/math/transform.c\
	$(SRCDIR)/math/quadric.c\
	$(SRCDIR)/math/cubic.c\
	$(SRCDIR)/math/quartic.c\
	$(SRCDIR)/raytrace/raytrace.c\
	$(SRCDIR)/raytrace/pathtrace.c\
	$(SRCDIR)/raytrace/phong.c\
	$(SRCDIR)/filters/filter.c\
	$(SRCDIR)/filters/blur.c\
	$(SRCDIR)/filters/sharpen.c\
	$(SRCDIR)/filters/emboss.c\
	$(SRCDIR)/filters/sobel.c\
	$(SRCDIR)/texture/texture.c\
	$(SRCDIR)/texture/sphere_uv.c\
	$(SRCDIR)/texture/plane_uv.c\
	$(SRCDIR)/texture/cone_uv.c\
	$(SRCDIR)/texture/cube_uv.c\
	$(SRCDIR)/texture/box_uv.c\
	$(SRCDIR)/texture/cylinder_uv.c\
	$(SRCDIR)/texture/torus_uv.c\
	$(SRCDIR)/texture/cubemap.c\
	$(SRCDIR)/perlin/perlin.c\
	$(SRCDIR)/perlin/turbulence.c

OBJ=$(LIBDIR)/main.o\
	$(LIBDIR)/load.o\
	$(LIBDIR)/env.o\
	$(LIBDIR)/init.o\
	$(LIBDIR)/compute.o\
	$(LIBDIR)/save.o\
	$(LIBDIR)/process.o\
	$(LIBDIR)/verbose.o\
	$(LIBDIR)/input.o\
	$(LIBDIR)/input2.o\
	$(LIBDIR)/event.o\
	$(LIBDIR)/sdl.o\
	$(LIBDIR)/gui.o\
	$(LIBDIR)/entry.o\
	$(LIBDIR)/entry2.o\
	$(LIBDIR)/widget.o\
	$(LIBDIR)/button.o\
	$(LIBDIR)/inspector.o\
	$(LIBDIR)/lview.o\
	$(LIBDIR)/cview.o\
	$(LIBDIR)/selection.o\
	$(LIBDIR)/lselect.o\
	$(LIBDIR)/cselect.o\
	$(LIBDIR)/lapply.o\
	$(LIBDIR)/capply.o\
	$(LIBDIR)/apply.o\
	$(LIBDIR)/error.o\
	$(LIBDIR)/utils.o\
	$(LIBDIR)/tools.o\
	$(LIBDIR)/read.o\
	$(LIBDIR)/read2.o\
	$(LIBDIR)/parse.o\
	$(LIBDIR)/parse_tools.o\
	$(LIBDIR)/load_mesh.o\
	$(LIBDIR)/mesh.o\
	$(LIBDIR)/prim.o\
	$(LIBDIR)/obj.o\
	$(LIBDIR)/load_obj.o\
	$(LIBDIR)/obj_parser.o\
	$(LIBDIR)/object.o\
	$(LIBDIR)/light.o\
	$(LIBDIR)/sphere.o\
	$(LIBDIR)/cone.o\
	$(LIBDIR)/cylindre.o\
	$(LIBDIR)/ring.o\
	$(LIBDIR)/plane.o\
	$(LIBDIR)/disque.o\
	$(LIBDIR)/box.o\
	$(LIBDIR)/cube.o\
	$(LIBDIR)/torus.o\
	$(LIBDIR)/triangle.o\
	$(LIBDIR)/parallelogram.o\
	$(LIBDIR)/ellipsoid.o\
	$(LIBDIR)/paraboloid.o\
	$(LIBDIR)/scene.o\
	$(LIBDIR)/draw.o\
	$(LIBDIR)/camera.o\
	$(LIBDIR)/raytrace.o\
	$(LIBDIR)/pathtrace.o\
	$(LIBDIR)/phong.o\
	$(LIBDIR)/texture.o\
	$(LIBDIR)/sphere_uv.o\
	$(LIBDIR)/cone_uv.o\
	$(LIBDIR)/cylinder_uv.o\
	$(LIBDIR)/cube_uv.o\
	$(LIBDIR)/box_uv.o\
	$(LIBDIR)/torus_uv.o\
	$(LIBDIR)/plane_uv.o\
	$(LIBDIR)/cubemap.o\
	$(LIBDIR)/perlin.o\
	$(LIBDIR)/filter.o\
	$(LIBDIR)/blur.o\
	$(LIBDIR)/sharpen.o\
	$(LIBDIR)/emboss.o\
	$(LIBDIR)/sobel.o\
	$(LIBDIR)/turbulence.o\
	$(LIBDIR)/vector1.o\
	$(LIBDIR)/vector2.o\
	$(LIBDIR)/matrix.o\
	$(LIBDIR)/rotation.o\
	$(LIBDIR)/transform.o\
	$(LIBDIR)/quadric.o\
	$(LIBDIR)/cubic.o\
	$(LIBDIR)/quartic.o\
	$(LIBDIR)/background.o\
	$(LIBDIR)/color.o\
	$(LIBDIR)/color1.o\
	$(LIBDIR)/color2.o

NAME=rt

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBDIR)/libft/ fclean && make -C $(LIBDIR)/libft
	@cp $(LIBDIR)/libft/libft.a $(LIBDIR)/
	$(CC) $(LDFLAGS) -o $@ $^
ifeq ($(UNAME_S),Darwin)
		@install_name_tool -change @rpath/SDL2.framework/Versions/A/SDL2 $(SDL2) $(NAME)
		@install_name_tool -change @rpath/SDL2_image.framework/Versions/A/SDL2_image $(SDL2_image) $(NAME)
		@install_name_tool -change @rpath/SDL2_ttf.framework/Versions/A/SDL2_ttf $(SDL2_ttf) $(NAME)
endif

$(LIBDIR)/%.o:$(HEADDIR)/%.h

$(LIBDIR)/%.o:$(SRCDIR)/*/%.c
	@$(CC) $(CFLAGS) -o $@ -c $<

.PHONY:clean fclean

clean:
	rm -rf $(LIBDIR)/*.o
	rm -rf $(LIBDIR)/libft.a
	make -C $(LIBDIR)/libft clean

fclean:clean
	rm -rf $(NAME)
	make -C $(LIBDIR)/libft fclean

re : fclean all
