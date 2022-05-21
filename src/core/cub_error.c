/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 14:50:49 by njennes           #+#    #+#             */
/*   Updated: 2022/05/21 15:13:23 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include "error_utils.h"

int	print_cub_err(int err)
{
	if (err == RETURN_SUCCESS)
		return (1);
	else if (err == ERR_EMPTY_FILE)
		printf("ERROR: Empty file\n");
	else if (err == ERR_FONT_META_INFO_NOT_FOUND)
		printf("ERROR: Could not find 'info' when parsing meta font info\n");
	else if (err == ERR_FONT_META_NAME_NOT_FOUNT)
		printf("ERROR: Could not find 'face' when parsing meta font info\n");
	else if (err == ERR_FONT_META_SIZE_NOT_FOUND)
		printf("ERROR: Could not find 'size' when parsing meta font info\n");
	else if (err == ERR_FONT_META_SIZE_ZERO)
		printf("ERROR: Found a font size of 0 when parsing meta font info\n");
	else if (err == ERR_FONT_META_CHAR_ID_NOT_FOUND)
		printf("ERROR: Couldn't get a char id when parsing meta font info\n");
	else if (err == ERR_FONT_META_FIELD_NAME_NO_MATCH)
		printf("ERROR: The field parsed didn't match the given one when "
			   "parsing meta font info\n");
	else if (err == ERR_FONT_META_NO_EQUAL_AFTER_FIELD)
		printf("ERROR: Didn't found an equal sign after a field when "
			   "parsing meta font info\n");
	else if (err == ERR_FONT_META_REACHED_EOF)
		printf("ERROR: Reached unexpected EOF when parsing meta font info\n");
	return (0);
}
