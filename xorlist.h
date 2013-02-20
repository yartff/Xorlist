#ifndef		XORLIST_H_
# define	XORLIST_H_

# include	<stdint.h>

# define	XOR_KEY(kn, kp)		((intptr_t)kn ^ (intptr_t)kp)
# define	XOR_KEY_ADDR(kn, kp)	((void *)XOR_KEY(kn, kp))

typedef struct	{
  void		*elem;
  intptr_t	key;
}		Xormodule;

typedef struct	{
  Xormodule	*first;
  Xormodule	*last;
  unsigned int	size;
}		Xorlist;

Xorlist		*Xor_create(void);
int		Xor_pushback(Xorlist *, void *);
void		Xor_foreach(Xorlist *, void (*)(void *));
void		Xor_foreach_rev(Xorlist *, void (*)(void *));

#endif
