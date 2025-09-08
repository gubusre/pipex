/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gubusque <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 11:22:55 by gubusque          #+#    #+#             */
/*   Updated: 2025/09/08 12:27:06 by gubusque         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	main(int argc, char* argv)
{
	// Check if acces (0 = archvo1 / 1, ... argc-1 = comandos/ argc = archivo2
	unsigned int	file_perms;

	file_perms = -1;
	file_perms = acces (argv[0], F_OK)
	if (file_perms != 0)
		errors(file_perms);
}
