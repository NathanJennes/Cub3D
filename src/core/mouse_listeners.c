/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_listeners.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:31:13 by njennes           #+#    #+#             */
/*   Updated: 2022/05/19 16:41:18 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "core.h"

void	mouse_click_begin(int button)
{
	update_ui(TRUE);
}

void	mouse_click_end(int button)
{
	update_ui(FALSE);
}

void	mouse_wheel_up(void)
{

}

void	mouse_wheel_down(void)
{

}

