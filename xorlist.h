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
}		*Xorlist;

// Kind of inlined methods, just to not force -O1 optimization
# define	Xor_front(x)	(x->first ? x->first->elem : NULL);
# define	Xor_back(x)	(x->last ? x->last->elem : NULL);
// Let's pretend the user knows what's done here
//# define	Xor_size(x)	(x ? x->size : -1);
# define	Xor_size(x)	(x->size);
Xorlist		Xor_create(void);
int		Xor_destroy(Xorlist);
int		Xor_popback(Xorlist);
int		Xor_popfront(Xorlist);
int		Xor_pushback(Xorlist, void *);
int		Xor_pushfront(Xorlist, void *);
void		Xor_foreach(Xorlist, void (*)(void *));
void		Xor_foreach_rev(Xorlist, void (*)(void *));
void		Xor_sort(Xorlist, int (*)(void *, void *));

#endif
