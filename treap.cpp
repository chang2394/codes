/*
LINK :- http://www.prefield.com/algorithm/
Treap is a binary search tree that balanced anticipatory using a random number.

Key and Value is added as well as binary search tree common to each node, the order is attached by Key as well as binary search tree. Each node has a Priority On top of that, his has a large Priority than their own children. You go through the rotation of the tree to keep it. I can be implemented in very simple this.

Be balanced anticipatory to be assigned randomly Priority is shown. Since it is not balanced exactly speed to pull in the vertex inferior to red-black tree and AVL tree, the rotation operation is fast, it may be faster than they add or remove vertices.

Amount of calculation

insert, erase, find: O (log n)
eval: amortized O (1)
However expexted

How to use

Eval, such as cache is not required if the mere binary search tree application, I would be 50 lines or so.

typedef xxx Key;
Type from Digi-Key. Assumes total order.
typedef xxx Value;
Type the Value.
typedef xxx Result;
result type of eval.
Treap * find (Treap *, Key);
I return a pointer to the element with the key.
Treap * insert (Treap *, Key, Value);
Insert (key, value) a.
Treap * erase (Treap *, Key);
Delete an element with a key.
Result eval (Treap *);
I assess the value. And returns it if it is cached.

*/

typedef int Key;
 typedef int Value;
 typedef int Result;
 struct Treap {
   Key key;
   Value value;
   int p;
   bool cached;
   Result cache;
   Treap * ch [2]; / / LEFT = ch [0], RIGHT = ch [1]
   Treap (const Key & key, const Value & value): key (key), value (value),
     p (rand ()), cached (0) {ch [0] = ch [1] = 0;}
 };
 Treap * rotate (Treap * t, int b) {
   Treap * s = t-> ch [1-b]; t-> ch [1-b] = s-> ch [b]; s-> ch [b] = t;
   s-> cached = t-> cached = false;
   return s;
 }
 Treap * find (Treap * t, const Key & key) {
   !? return t | | key == t-> key t: find (t-> ch [key <t-> key], key);
 }
 Treap * insert (Treap * t, const Key & key, const Value & value) {
   if (! t) return new Treap (key, value);
   else if (key == t-> key) return t;
   ! int b = (key <t-> key);
   t-> ch [b] = insert (t-> ch [b], key, value);
   if (t-> p> t-> ch [b] -> p) t = rotate (t, 1-b);
   t-> cached = false;
   return t;
 }
 Treap * erase (Treap * t, const Key & key) {
   if (! t) return NULL;
   if (key == t-> key) {
     if (!! t-> ch [0] && t-> ch [1]) return NULL;
     else if (! t-> ch [0]) t = rotate (t, 0);
     else if (! t-> ch [1]) t = rotate (t, 1);
     else t = rotate (t, t-> ch [0] -> p <t-> ch [1] -> p);
     t = erase (t, key);
   } Else {
     ! int b = (key <t-> key);
     t-> ch [b] = erase (t-> ch [b], key);
   }
   t-> cached = false;
   return t;
 }
 Result eval (Treap * t) {
   if (! t) return 0;
   if (! t-> cached)
     t-> cache = eval (t-> ch [0]) + eval (t-> ch [1]) + 1; / / CHANGE IT FLEXIBLE
   t-> cached = true;
   return t-> cache;
 }
 Treap * nth (Treap * t, int n) {/ / NTH ELEMENT
   int l = eval (t-> ch [0]);
   if (n <l) return nth (t-> ch [0], n);
   if (n> l) return nth (t-> ch [1], nl-1);
   return t;
 }
