// Create a Doxyfile with doxygen -g
// Edit and customize; at least provide an INPUT for source directories

#include  <stdio.h>


/*  
 * this must NOT be in Doxygen :
 * comment does NOT begin with * or !  
 */

/**
 * \brief 
 *     a structure representing a 
 *    point in a 2D plane
 *
 * Here goes a more detailed description, 
 * blah, blah. it serves the following purposes :
 *
 * <ul>
 * 	 <li> it works
 *   <li> it works fine!
 * </ul>
 *
 * And finally the end.
 */
typedef 
struct point {
	
    /** x-coordinate */
    double x; 
	/** y-coordinate */
    double y; 

} point_t ;

/**
 * \brief 
 *  a  structure representing a line segment (x0,y0) to (x1,y1)
 */
typedef 
struct line_segment {
    /** starting point */
    point_t  startp ; 
	/** ending  point*/
    point_t  endp; 

} line_segment_t ;

/**
 * \brief application entry point
 *
 * \param argc is number of arguments passed in
 * \param argv is an array of arguments as strings (char*) 
 *
 * \return exit code to the OS
 */
int main(int argc, char **argv) {

	point_t a;

	a.x = 0.91 ;
	a.y = 0.88 ;


	return 0;
}
