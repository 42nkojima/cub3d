/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmase <tmase@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/01 17:35:10 by tmase             #+#    #+#             */
/*   Updated: 2026/10/01 18:06:53 by tmase            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

typedef struct  s_vars{
    // 4方向のテクスチャのパス
    char    *path_north; 
    char    *path_south; 
    char    *path_west; 
    char    *path_east; 
    
    // 床と天井の色
    int     top_color;
    int     bottom_color;
    
    // マップ（2次元配列）と、その幅と高さ
    char    **map;
    int         width;
    int         height;

    // プレイヤーの開始位置と向き
    int         col;
    int         raw;
    char      direction; //N, S, W, E
}                       t_vars;

#endif