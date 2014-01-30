/*

if you are given a pair of points A and B and wants to check whether anotherpoint C lies on left or right of the line formed by joining A and B, 
then simply find their cross product,if it exceeds 0 it lies on left, if 0 then lies on the line else right.

Make two vector AC and AB and find their cross product.
|cross-product| = |X1 X2|
		  |Y1 Y2| 
Hence giving value (X1Y2 - X2Y1).

*/

bool is_left(pii A,pii B,pii C){
	return (((B.x-A.x)*(C.y-A.y) - (B.y-A.y)*(C.x-A.x)) > 0) 	
}
