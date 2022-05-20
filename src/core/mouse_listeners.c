/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_listeners.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njennes <njennes@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 16:31:13 by njennes           #+#    #+#             */
/*   Updated: 2022/05/20 12:58:20 by njennes          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	update_ui_click_begin(int button);
void	update_ui_click_end(int button);

void	mouse_click_begin(int button)
{
	update_ui_click_begin(button);
}

void	mouse_click_end(int button)
{
	update_ui_click_end(button);
}

void	mouse_wheel_up(void)
{

}

void	mouse_wheel_down(void)
{

}

