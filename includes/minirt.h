/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sehhong <sehhong@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/10 11:03:31 by sehhong           #+#    #+#             */
/*   Updated: 2022/05/10 23:36:49 by sehhong          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define SCN_WIDTH	800
# define SCN_HEIGHT	400

# include <math.h>
# include <stdlib.h>	//malloc
# include <stdio.h>		//strerror
# include <sys/errno.h>	//errno
# include <fcntl.h>		//open
# include <unistd.h>	//close
# include "libft.h"
# include "mlx.h"
# include "structure.h"

void	read_file(t_box *box, char *f_name);

#endif