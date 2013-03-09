Xorlist
=======

Double linked list with a single "next" field

The concept is simple as this:

The "key" field can be seen like the next AND the prev pointer of the node.

To get the address of the next item, you apply a xor bitwise operator of the previous item's pointer and its key:

    A ^ B->key == C

So if you flip the operands, you can observe this statement:

    C ^ B->key == A

You can see in the code that methods that can be used in both directions are greatly factorised, and can operate with a single pointer on the first or the last node. Since the previous pointer is always 'NULL', the orientation is totally transparent for the "go" methods which are called by "front" and "back" methods

Advantages:
- You can observe a quite big difference for little programs which needs to list a lot of elements. (On the heap: 2,000 nodes will take 32,000 bytes instead of 48,000). The hardware costs are insignificant on today's computer, except on embedded systems!

Inconvenients:
- You can't start from a node which isn't first or last.
- You must keep the adress of the previous node to calculate the next pointer.

Variations exists with Addition key or Substraction key.

More informations about all that here:
http://en.wikipedia.org/wiki/XOR_linked_list

If you are asking about strange developping decisions I made, just remember I coded this in optimizations purpose.

Cheers.
