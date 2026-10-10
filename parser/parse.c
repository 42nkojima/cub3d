/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmase <tmase@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 14:15:44 by tmase             #+#    #+#             */
/*   Updated: 2026/10/10 16:57:47 by tmase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

/*.cubを読み込む
	一行ごとを配列に落とし込んでいく、空行の削除はここで
	テクスチャとマップで分けた方がいいかも、配列を
	マップまでたどり着いたらsolongのparser使えそう
	char *texture[]
	と、
	char **map
	みたいな感じ
	それぞれの担当部分だけを入れ込んだ構造体を返すのってできる？
	textureならtexとcolorだけ、mapならmapだけみたいな
	できそう、ほかのところはNULLにするなりなんなり
	textureではなくconfigという名前に
	falseが返った場合にはmainでfree_all(vars)みたいにする
	*/	

bool	parse(char *filepath, t_vars *vars)
{
	int		fd;
	bool	status;

	fd = open(filepath, O_RDONLY);
	status = parse_config(fd, vars) && parse_map(fd, vars);
	close(fd);
	return (status);
}