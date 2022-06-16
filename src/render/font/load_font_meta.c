/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_font_meta.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 13:31:16 by njennes           #+#    #+#             */
/*   Updated: 2022/05/21 15:17:40 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/fcntl.h>
#include <printf.h>
#include "render.h"
#include "leaky.h"
#include "libft.h"
#include "error_utils.h"

inline static int	load_font_infos(t_font *font, int fd);
inline static int	load_font_chars(t_font *font, int fd);
inline static int	parse_char_infos(t_char_meta *chars, char *line);
inline static int	populate_char_info(t_char_meta *c, char *line,
				char *field_name, int *field);

int	load_font_meta(t_font *font, char *path)
{
	int	fd;
	int	ret;

	fd = open(path, O_RDONLY);
	if (fd <= 0)
	{
		printf("Could not load the meta file for the font %s\n", path);
		return (0);
	}
	ret = load_font_infos(font, fd);
	if (ret != RETURN_SUCCESS)
		return (print_cub_err(ret));
	if (!load_font_chars(font, fd))
	{
		printf("Couldn't get the font characters infos from %s\n", path);
		return (0);
	}
	return (1);
}

inline static int	load_font_infos(t_font *font, int fd)
{
	char	*line;
	char	*info_begin;

	line = gc_get_next_line(fd);
	if (!line)
		return (ERR_EMPTY_FILE);
	if (ft_strncmp(line, "info", ft_strlen("info")) != 0)
		return (ERR_FONT_META_INFO_NOT_FOUND);
	line = ft_strskip_alpha(line);
	line = ft_strskip_space(line);
	if (ft_strncmp(line, "face=\"", ft_strlen("face=\"")) != 0)
		return (ERR_FONT_META_NAME_NOT_FOUNT);
	line += ft_strlen("face=\"");
	info_begin = line;
	line = ft_strskip_alpha(line);
	*line = 0;
	font->name = gc_strdup(info_begin);
	line = ft_strskip_space(++line);
	if (ft_strncmp(line, "size=", ft_strlen("size=")) != 0)
		return (ERR_FONT_META_SIZE_NOT_FOUND);
	line += ft_strlen("size=");
	font->font_size = ft_atoi(line);
	if (font->font_size == 0)
		return (ERR_FONT_META_SIZE_ZERO);
	return (1);
}

inline static int	load_font_chars(t_font *font, int fd)
{
	char	*line;

	line = gc_get_next_line(fd);
	while (line)
	{
		if (ft_strncmp(line, "chars count", ft_strlen("chars count")) == 0)
			break ;
		gc_free(line);
		line = gc_get_next_line(fd);
	}
	gc_free(line);
	line = gc_get_next_line(fd);
	while (line)
	{
		if (*line == EOF)
		{
			gc_free(line);
			return (RETURN_SUCCESS);
		}
		if (!print_cub_err(parse_char_infos(font->characters, ft_trimr(line))))
			return (0);
		gc_free(line);
		line = gc_get_next_line(fd);
	}
	return (RETURN_SUCCESS);
}

inline static int	parse_char_infos(t_char_meta *chars, char *line)
{
	int	value;

	line = ft_strskip_alpha(line);
	line = ft_strskip_space(line);
	line = ft_strskip_alpha(line);
	if (*line != '=')
		return (ERR_FONT_META_CHAR_ID_NOT_FOUND);
	value = ft_atoi(++line);
	if (value < 0 || value >= MAX_CHARS_IN_FONT)
		return (1);
	line = ft_strskip_digit(line);
	line = ft_strskip_space(line);
	return (populate_char_info(&chars[value], line, "x", &chars[value].x));
}

inline static int	populate_char_info(t_char_meta *c, char *line,
		char *field_name, int *field)
{
	if (ft_strncmp(line, field_name, ft_strlen(field_name)) != 0)
		return (ERR_FONT_META_FIELD_NAME_NO_MATCH);
	line += ft_strlen(field_name);
	if (*line != '=')
		return (ERR_FONT_META_NO_EQUAL_AFTER_FIELD);
	line++;
	if (!*line)
		return (ERR_FONT_META_REACHED_EOF);
	*field = ft_atoi(line);
	if (*line == '-')
		line++;
	line = ft_strskip_space(ft_strskip_digit(line));
	if (ft_strcmp(field_name, "x") == 0)
		return (populate_char_info(c, line, "y", &c->y));
	else if (ft_strcmp(field_name, "y") == 0)
		return (populate_char_info(c, line, "width", &c->width));
	else if (ft_strcmp(field_name, "width") == 0)
		return (populate_char_info(c, line, "height", &c->height));
	else if (ft_strcmp(field_name, "height") == 0)
		return (populate_char_info(c, line, "xoffset", &c->x_off));
	else if (ft_strcmp(field_name, "xoffset") == 0)
		return (populate_char_info(c, line, "yoffset", &c->y_off));
	else if (ft_strcmp(field_name, "yoffset") == 0)
		return (populate_char_info(c, line, "xadvance", &c->x_advance));
	return (1);
}
