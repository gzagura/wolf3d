/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gzagura <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/15 19:07:58 by gzagura           #+#    #+#             */
/*   Updated: 2017/12/15 19:08:03 by gzagura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned char	ft_swap_bits(unsigned char octet)
{
	return ((octet >> 4) + (octet << 4));
}
