#ifndef MAIN_H
#define MAIN_H

#define SYN_OK			0		/* good syntax so far */
#define ERR_EXPECT		1		/* error code of unexpected character */
#define ERR_NEWLINE		2		/* newline in a bad place */
#define ERR_UNTERM		4		/* unterminated */
#define ERR_ESCAPE		8		/* bad escape sequence */
#define ERR_EOF			16		/* EOF in a wrong place */

#endif
