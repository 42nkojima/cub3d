/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmase <tmase@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/04 14:15:51 by tmase             #+#    #+#             */
/*   Updated: 2026/10/10 20:58:37 by tmase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <parse.h>

/*空行を飛ばしてから読み込み開始
読んだ行を一つずつリストにしてつなげる
最長のものをwidth、heightは毎回+1
アルファベットのある行を常に探しながらリストにセット
あった場合、colにheightと同じ値を記録
rowには何文字目にあったかを記録、directionもその文字によってどれか記録
最後まで行ったら二次元配列に一個ずつくっつけていっておわり
*/

typedef	struct s_list {
	char	*line;
	t_list	*prev;
	t_list	*next;
}				t_list;

bool	map_to_list(t_vars *vars, char *line, t_list *list)
{
	
}

bool	convert_list_to_array(t_vars *vars, t_list *list)
{
	
}

bool	parse_map(int fd, t_vars *vars)
{
	char	*line;
	t_list	*list;

	
	while ((line = get_next_line(fd)) != NULL)
	{
		if (is_empty_line(line))
		{
			free(line);
			continue;
		}
		if (!map_to_list(vars, line, list))
		{
			free(line);
			return (false);
		}
	}
	if (!convert_list_to_array(vars, list))
		return (false);
	return (true);
}