#!/usr/bin/env zsh

if [ "$1" = "md5" ]; then
	diff <(./ft_ssl $@) <($@)
elif [ "$1" = "sha256" ]; then
	argv[1]=()
	diff <(./ft_ssl sha256 $@ | rev | sed -e 's/ = .*//' | rev) <(shasum -a 256 $@ | sed 's/ .*//')
fi
