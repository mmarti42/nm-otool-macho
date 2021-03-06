# Nm-otool

Disclaimer
----------
> In School 42, almost every project must be written according to a coding syntax standard (also known as "[Norme](./docs/norme.fr.pdf)").
>
> That's why some parts may be strange

About
-----
> Let's analyze the format of MacOS executables and understand how the kernel launches the binaries, by rewriting these two system tools. Essential for all those who want to make security, this project is more generally an opening on the UNIX culture system.

This is the second project of the Advanced Unix branch at School 42 Paris

Installation
------------
Run `make fclean && make`

Usage
-----
`./ft_nm [-prugA] [file ...]`

`./ft_otool [file ...]`

supports:
> archives,  
> 32, 64, fat executables,   
> dylib
