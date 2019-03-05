#!/usr/bin/env zsh

diff <(./ft_ssl md5 $@) <(md5 $@)
