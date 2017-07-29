/* vt200.h */

#define ESC "\033"
#define SAVE_CURSOR printf("\0337")	    /* Save current cursor position.*/
#define RESTORE_CURSOR printf("\0338")	/* Restore previous cursor pos. */
#define CURSOR_ON printf("\033[?25h")	/* Text cursor enabled.		    */
#define CURSOR_OFF printf("\033[?25l")	/* Text cursor disabled.	    */
#define CLRSCR printf("\033[2J")	    /* Clear the entire screen.	    */
#define CLRLINE printf("\033[K")	    /* Clear from cursor to eoln.	*/
#define HOME printf("\033[H")		    /* Move cursor to row 1, col 1.	*/
#define POS(row,col) printf("\033[%0d;%0dH", row, col)
